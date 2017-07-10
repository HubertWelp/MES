#include "mesmqttnode.h"
#include <iostream>
#include <QMessageBox>
using namespace std;
#include "mesrfidtag.h"
#include "bearbeitungsstatus.h"
#define TOPIC1 "RFID1/Tagdaten"
#define TOPIC2 "RFID2/Tagdaten"
#define TOPIC3 "RFID3/Tagdaten"
#define TOPIC4 "RFID4/Tagdaten"
Auftragsverwaltung* MESMQTTNode::auftraege=NULL;

MESMQTTNode::MESMQTTNode(Auftragsverwaltung* av, QObject* parent)
    :    QObject(parent)
{
    auftraege=av;
    setMsgRcvdCallback(mqttMessageHandler);
    subscribe(TOPIC1);
    subscribe(TOPIC2);
    subscribe(TOPIC3);
    subscribe(TOPIC4);
    connect(auftraege,SIGNAL(beauftragt(int)),this,SLOT(beauftragungStarten(int)));
}
MESMQTTNode::~MESMQTTNode()
{
    unsubscribe(TOPIC1);
    unsubscribe(TOPIC2);
    unsubscribe(TOPIC3);
    unsubscribe(TOPIC4);
}
void MESMQTTNode::mqttMessageHandler(char* t, char* m, int l)
{
    cout << "Nachricht empfangen" << endl;
    cout << "Topic: " << t << endl;
    cout << "Message: " << m << endl;

    if(strcmp(t,TOPIC1)==0)
        bearbeiteTopic1(m, l);
    else if(strcmp(t,TOPIC2)==0)
        bearbeiteTopic(m, l);
    else if(strcmp(t,TOPIC3)==0)
        bearbeiteTopic(m, l);
    else if(strcmp(t,TOPIC4)==0)
        bearbeiteTopic4(m, l);


}

void byteStreamToHexString(char* hex, const unsigned char* byte, int len)
{
    int i;
    for (i=0; i<len; i++)
    {
        sprintf(hex+i*2, "%02X", byte[i]);
    }
    hex[i*2] = 0;
}

int hexStringToByteStream(unsigned char* byte, const char* hex, int len)
{
    int n=0,ret=1;
    const char* pos = hex;
    n=0;
    do
    {
        ret = sscanf(pos,"%2hhX",&byte[n]);
        if(ret==1)
        {
            n++;
            pos += 2;
        }
    }while(n<len/2 && ret==1);
    return n;
}


void MESMQTTNode::beauftragungStarten(int auftragsIndex)
{
    char message[10000];
    int msgLen;

    // Nachricht zum Schreiben des RFID-Sensor 1 verschicken
    if(auftragsIndex!=-1 && auftraege)
    {
        cout << "Auftrag " << auftragsIndex << " muss gestartet werden" << endl;
        Fertigungsauftrag fa = auftraege->getAuftrag(auftragsIndex);


        // Bearbeitungsstatus des Auftrags aufdatieren
        Bearbeitungsstatus b = fa.getBearbeitungsstatus();
        b.setBeauftragt(Bearbeitungsstatus::erledigt);
        fa.setBearbeitungsstatus(b);

        // MQTT-wa-Message mit den Fertigungsauftragsdaten erstellen und versenden
        strcpy(message,"wa");   // Message-Typ
        // Tagdaten in Message schreiben
        MESRFIDTag tagData;
        tagData.fromFertigungsauftrag(fa);
        cout << "Durchmesser: " << tagData.getBohrlochDurchmesser() << endl;
        // Tagdaten von binär nach hexstring wandeln
        // +8 und -8 w.g. wa, d.h. TagID darf nicht in Message enthalten sein
        byteStreamToHexString(message+2,(const unsigned char*)&tagData+8,sizeof(tagData)-8);


        cout << "beauftragungStarten::message: " << message << endl;

        publish("MES/Command/RFID1",message,strlen(message));
    }
}

void MESMQTTNode::bearbeiteTopic1(char *m, int l)
{
    if(strncmp(m,"td",2)!=0)    // Tagdaten-Nachricht?
        return;

    if(!auftraege)
        return;

//    cout << "Auswertung der Nachricht und Aufdatierung der Auftragsverwaltung" << endl;
    MESRFIDTag tagData;
    hexStringToByteStream((unsigned char*)&tagData,m+2,l-2);

//    Fertigungsauftrag faFromTag = tagData.toFertigungsauftrag();


    cout << "ba: " << tagData.getBeauftragt() << endl;
    cout << "fr: " << tagData.getGefraest() << endl;
    cout << "bo: " << tagData.getGebohrt() << endl;
    cout << "vs: " << tagData.getVersendet() << endl;
    //        sscanf("1234","%lli",&tagData);


    unsigned long long rfidnr=tagData.getRFIDNr();
    cout << rfidnr << endl;
    int index = auftraege->searchFertigungsauftragByRFIDNr(tagData.getRFIDNr());
    cout << index << endl;
    if(index != -1)
    {
        QString meldung;
        meldung = QString("Tag-Nummer %1 bereits vergeben\nVerarbeitung abgebrochen.").arg(rfidnr,0,16);
        cout <<  meldung.toStdString() << endl;
        auftraege->setFehlerZustand(meldung);
        return;
    }
    else
    {
        cout << "Neue beauftragt " << endl;
        // Auftrag wurde gerade gestartet => Aufdatierung des aktuell selektierten Fertigungsauftrags inkl. Eintrag der RFDINr
        index = auftraege->getIndexBeauftragung();
        if(index != -1)
        {
            Fertigungsauftrag fa = auftraege->getAuftrag(index);
            Bearbeitungsstatus b = fa.getBearbeitungsstatus();
            fa.setRFIDNr(tagData.getRFIDNr());
            if(b.setBeauftragt(tagData.getBeauftragt()))
            {
                QString meldung;
                meldung = QString("Ungültiger Bearbeitungsszustand \"beauftragt\" in Zeile %1!\nVerarbeitung abgebrochen.").arg(index+1);
                cout <<  meldung.toStdString() << endl;
                auftraege->setFehlerZustand(meldung);
                return;
            }

            if(b.setGefraest(tagData.getGefraest()))
            {
                QString meldung;
                meldung = QString("Ungültiger Bearbeitungsszustand \"gefräst\" in Zeile %1!\nVerarbeitung abgebrochen.").arg(index+1);
                cout <<  meldung.toStdString() << endl;
                auftraege->setFehlerZustand(meldung);
                return;
            }
            if(b.setGebohrt(tagData.getGebohrt()))
            {
                QString meldung;
                meldung = QString("Ungültiger Bearbeitungsszustand \"gebohrt\" in Zeile %1!\nVerarbeitung abgebrochen.").arg(index+1);
                cout <<  meldung.toStdString() << endl;
                auftraege->setFehlerZustand(meldung);
                return;
            }
            if(b.setVersendet(tagData.getVersendet()))
            {
                QString meldung;
                meldung = QString("Ungültiger Bearbeitungsszustand \"versendet\" in Zeile %1!\nVerarbeitung abgebrochen.").arg(index+1);
                cout <<  meldung.toStdString() << endl;
                auftraege->setFehlerZustand(meldung);
                return;
            }
            fa.setBearbeitungsstatus(b);
            cout << "RFID nach Beauftragung: " << fa.getRFIDNr() << endl;
            auftraege->setAuftrag(index,fa);
            auftraege->resetIndexBeauftragung();
            auftraege->speichere();
        }
    }

}

void MESMQTTNode::bearbeiteTopic(char *m, int l)
{
    if(strncmp(m,"td",2)!=0)    // Tagdaten-Nachricht?
        return;

    if(!auftraege)
        return;

    cout << "Auswertung der Nachricht und Aufdatierung der Auftragsverwaltung" << endl;
    MESRFIDTag tagData;
    hexStringToByteStream((unsigned char*)&tagData,m+2,l-2);



    cout << tagData.getBeauftragt() << endl;
    cout << tagData.getGefraest() << endl;
    cout << tagData.getGebohrt() << endl;
    cout << tagData.getVersendet() << endl;
    //        sscanf("1234","%lli",&tagData);


    unsigned long long rfidnr=tagData.getRFIDNr();
    cout << rfidnr << endl;
    int index = auftraege->searchFertigungsauftragByRFIDNr(tagData.getRFIDNr());
    cout << index << endl;
    if(index != -1)
    {
        cout << "Bestehenden Auftrag aufdatieren " << endl;
        Fertigungsauftrag fa = auftraege->getAuftrag(index);
        Bearbeitungsstatus b = fa.getBearbeitungsstatus();
        fa.setRFIDNr(tagData.getRFIDNr());
        if(b.setBeauftragt(tagData.getBeauftragt()))
        {
            QString meldung;
            meldung = QString("Ungültiger Bearbeitungsszustand \"beauftragt\" in Zeile %1!\nVerarbeitung abgebrochen.").arg(index+1);
            cout <<  meldung.toStdString() << endl;
            auftraege->setFehlerZustand(meldung);
            return;
        }

        if(b.setGefraest(tagData.getGefraest()))
        {
            QString meldung;
            meldung = QString("Ungültiger Bearbeitungsszustand \"gefräst\" in Zeile %1!\nVerarbeitung abgebrochen.").arg(index+1);
            cout <<  meldung.toStdString() << endl;
            auftraege->setFehlerZustand(meldung);
            return;
        }
        if(b.setGebohrt(tagData.getGebohrt()))
        {
            QString meldung;
            meldung = QString("Ungültiger Bearbeitungsszustand \"gebohrt\" in Zeile %1!\nVerarbeitung abgebrochen.").arg(index+1);
            cout <<  meldung.toStdString() << endl;
            auftraege->setFehlerZustand(meldung);
            return;
        }
        if(b.setVersendet(tagData.getVersendet()))
        {
            QString meldung;
            meldung = QString("Ungültiger Bearbeitungsszustand \"versendet\" in Zeile %1!\nVerarbeitung abgebrochen.").arg(index+1);
            cout <<  meldung.toStdString() << endl;
            auftraege->setFehlerZustand(meldung);
            return;
        }
        fa.setBearbeitungsstatus(b);
        auftraege->setAuftrag(index,fa);

    }
    auftraege->speichere();

}

//void MESMQTTNode::bearbeiteTopic4(char *m, int l)
//{
//    if(strncmp(m,"td",2)!=0)    // Tagdaten-Nachricht?
//        return;

//    if(!auftraege)
//        return;

////    cout << "Auswertung der Nachricht und Aufdatierung der Auftragsverwaltung" << endl;
//    MESRFIDTag tagData;
//    hexStringToByteStream((unsigned char*)&tagData,m+2,l-2);

////    Fertigungsauftrag faFromTag = tagData.toFertigungsauftrag();


//    cout << "ba: " << tagData.getBeauftragt() << endl;
//    cout << "fr: " << tagData.getGefraest() << endl;
//    cout << "bo: " << tagData.getGebohrt() << endl;
//    cout << "vs: " << tagData.getVersendet() << endl;
//    //        sscanf("1234","%lli",&tagData);

//    if(tagData.getVersendet()!=Bearbeitungsstatus::offen)   // nicht relevant
//        return;

//    unsigned long long rfidnr=tagData.getRFIDNr();
//    cout << rfidnr << endl;
//    int index = auftraege->searchFertigungsauftragByRFIDNr(tagData.getRFIDNr());
//    cout << index << endl;
//    if(index==-1)   // unbekannter Tag - kann nicht versendet werden
//        return;

//}

void MESMQTTNode::bearbeiteTopic3(char *m, int l)
{

}

void MESMQTTNode::bearbeiteTopic4(char *m, int l)
{
    if(strncmp(m,"td",2)!=0)    // Tagdaten-Nachricht?
        return;

    if(!auftraege)
        return;

    cout << "Auswertung der Nachricht und Aufdatierung der Auftragsverwaltung" << endl;
    MESRFIDTag tagData;
    hexStringToByteStream((unsigned char*)&tagData,m+2,l-2);



    cout << tagData.getBeauftragt() << endl;
    cout << tagData.getGefraest() << endl;
    cout << tagData.getGebohrt() << endl;
    cout << tagData.getVersendet() << endl;
    //        sscanf("1234","%lli",&tagData);


    unsigned long long rfidnr=tagData.getRFIDNr();
    cout << rfidnr << endl;
    int index = auftraege->searchFertigungsauftragByRFIDNr(tagData.getRFIDNr());
    cout << index << endl;
    if(index == -1)
    {
        QString meldung;
        meldung = QString("Tag-Nummer %1 nicht in Datenbank vorhanden\nVerarbeitung abgebrochen.").arg(rfidnr,0,16);
        cout <<  meldung.toStdString() << endl;
        return;
    }
    if(tagData.getVersendet()==Bearbeitungsstatus::na)   // nicht relevant
    {
        bearbeiteTopic(m,l);
        return;
    }
    if(tagData.getVersendet()==Bearbeitungsstatus::erledigt)
    {
        bearbeiteTopic(m,l);

        // schicke push-on-Nachricht an RFID4
        char message[10000]="";
        strcpy(message,"puon");   // Message-Typ
        cout << "beauftragungStarten::message: " << message << endl;
        publish("MES/Command/RFID4",message,strlen(message));

        return;
    }

    if(tagData.getVersendet()==Bearbeitungsstatus::offen)
    {
    // Bearbeitungsstatus "versendet" ändern und auf Tag schreiben
    // 1. Überprüfe, ob alle vorherigen Bearbeitungsschritte durchgeführt worden sind
        int ok;
        ok =        tagData.getBeauftragt()==Bearbeitungsstatus::erledigt
                && (tagData.getGefraest()==Bearbeitungsstatus::erledigt || tagData.getGefraest()==Bearbeitungsstatus::na)
                && (tagData.getGebohrt()==Bearbeitungsstatus::erledigt || tagData.getGebohrt()==Bearbeitungsstatus::na);
        if(!ok)
        {
            QString meldung;
            meldung = QString("Ungültiger Bearbeitungsszustand zum Versenden\nVerarbeitung abgebrochen.");
            cout <<  meldung.toStdString() << endl;
            return;
        }

    // 2. Schicke push-off-Nachricht
        // schicke push-on-Nachricht an RFID4
        char message[10000]="";
        strcpy(message,"puoff");   // Message-Typ
        cout << "beauftragungStarten::message: " << message << endl;
        publish("MES/Command/RFID4",message,strlen(message));

    // 3. Schicke write-Nachricht mit neuen Versendet-Status
        cout << "Bestehenden Auftrag aufdatieren " << endl;
        Fertigungsauftrag fa = auftraege->getAuftrag(index);
        // Bearbeitungsstatus des Auftrags aufdatieren
        Bearbeitungsstatus b = fa.getBearbeitungsstatus();
        b.setVersendet(Bearbeitungsstatus::erledigt);
        fa.setBearbeitungsstatus(b);

        // MQTT-wa-Message mit den Fertigungsauftragsdaten erstellen und versenden
        strcpy(message,"wa");   // Message-Typ
        // Tagdaten in Message schreiben
        MESRFIDTag tagData;
        tagData.fromFertigungsauftrag(fa);
        // Tagdaten von binär nach hexstring wandeln
        // +8 und -8 w.g. wa, d.h. TagID darf nicht in Message enthalten sein
        byteStreamToHexString(message+2,(const unsigned char*)&tagData+8,sizeof(tagData)-8);
        cout << "beauftragungStarten::message: " << message << endl;
        publish("MES/Command/RFID4",message,strlen(message));
    }

}
