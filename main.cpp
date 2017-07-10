#include "mainwindow.h"
#include <QApplication>
#include <QString>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "fertigungsauftrag.h"
#include "auftragsverwaltung.h"
//#include "produktbeschreibung.h"
#include "mesmqttnode.h"
#include "rfidtag.h"
using namespace std;
void ausgabe(Produktbeschreibung p)
{
    cout << "  Format: " << p.getHochFormat() << endl;
    cout << "  Gravurtext: " << p.getGravurtext() << endl;
    cout << "  Standbild: " << p.getStandbild() << endl;
}
void ausgabe(Bearbeitungsstatus b)
{
    cout << "ba gf gb vs: (" << b.getBeauftragt() <<","<<b.getGefraest()<<","<<b.getGebohrt()<<","<<b.getVersendet()<<")"<< endl;
}

void ausgabe(Fertigungsauftrag a)
{
    cout << "Auftragsnummer: " << a.getAuftragsnummer() << endl;
    ausgabe((a.getProduktbeschreibung()));
    cout << "RFIDNr: "<< a.getRFIDNr() << endl;
    ausgabe((a.getBearbeitungsstatus()));


}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Auftragsverwaltung tfh;
    MainWindow w(NULL,&tfh);
    MESMQTTNode mn(&tfh);
//    mn.publish("RFID1/Tagdaten","Bersenbrueck",strlen("Bersenbrueck")+1);

//    unsigned long long b;
//    scanf("%llu",&b);
//    printf("%lli\n",b);
//    QString qs;
//    qs=QString("%1").arg(b,0,16);
//    cout << qs.toStdString() << endl;

    w.show();




  return a.exec();
}
