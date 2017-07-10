#include "auftragsverwaltung.h"

Auftragsverwaltung::Auftragsverwaltung(QObject *parent) :
    QObject(parent)
{
    resetIndexBeauftragung();
}

const QList<Fertigungsauftrag>& Auftragsverwaltung::getAuftraege()
{
    return auftraege;
}
void Auftragsverwaltung::addAuftrag(Fertigungsauftrag fa)
{
    auftraege.push_back(fa);
}
void Auftragsverwaltung::setAuftrag(int nr, Fertigungsauftrag fa)
{
    if(nr>=auftraege.count() || nr<0 || auftraege.isEmpty())
    {

    }else
    {
        auftraege[nr] = fa;
        emit auftragChanged(nr);
    }
}
Fertigungsauftrag Auftragsverwaltung::getAuftrag(int nr)
{
    if(nr>=auftraege.count() || nr<0 || auftraege.isEmpty())
    {
        return Fertigungsauftrag();
    }else
    {
        return auftraege[nr];
    }
}

void Auftragsverwaltung::lade(QString dateiname)
{
    ifstream din;
    int i=0;
    Fertigungsauftrag f;
    din.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    try{
        din.open(dateiname.toStdString().c_str());
        din>>f;
        while(!din.eof())
        {
            auftraege.push_back(Fertigungsauftrag(f));
            din >> f;
            i++;
        }

        din.close();
    }
    catch (std::ifstream::failure e)
    {
        if(!din.eof())
            std::cerr << "Exception opening file\n" << e.what() << endl;
    }
}


void Auftragsverwaltung::speichere(QString dateiname)
{
    ofstream dout;
    QList<Fertigungsauftrag>::iterator ifa;
    dout.exceptions ( std::ofstream::failbit | std::ofstream::badbit );
    try{
        dout.open(dateiname.toStdString().c_str());
        for(ifa=auftraege.begin();ifa!=auftraege.end();ifa++)
            dout << *ifa << endl;

        dout.close();
    }
    catch (std::ofstream::failure e)
    {
        std::cerr << "Exception opening/writing/closing file\n";
    }
}

int Auftragsverwaltung::getAnzahlAuftraege()
{
    return auftraege.count();
}
int Auftragsverwaltung::getNextAuftragsNr()
{
    QList<Fertigungsauftrag>::iterator ifa;
    unsigned int anr=0;
    for(ifa=auftraege.begin();ifa!=auftraege.end();ifa++)
    {
        if(ifa->getAuftragsnummer()>anr)
        {
            anr = ifa->getAuftragsnummer();
        }
    }
    if(anr==0)
        return 1000;
    else return anr+1;
}

int Auftragsverwaltung::searchFertigungsauftragByRFIDNr(unsigned long long rfidnr)
{
    printf("rfidnr = %lli\n",rfidnr);
    int index=0;
    QList<Fertigungsauftrag>::iterator ifa;

    for(ifa=auftraege.begin();ifa!=auftraege.end() && ifa->getRFIDNr()!=rfidnr;ifa++)
        index++;
    if(ifa==auftraege.end())
        return -1;
    else
        return index;
}

void Auftragsverwaltung::setIndexBeauftragung(int index)
{
    if(getAuftrag(index).getBearbeitungsstatus().getBeauftragt()!=Bearbeitungsstatus::offen)
    {
        fehlerZustand("Fertigungsauftrag ist bereits in Bearbeitung!");
        return;
    }
    if(getIndexBeauftragung()!=-1)
    {
        fehlerZustand("Anderer Fertigungsauftag wird gerade beauftragt!");
        return;
    }
    indexBeauftragung = index;
    emit beauftragt(indexBeauftragung);
}

void Auftragsverwaltung::resetIndexBeauftragung()
{
    cout << "resetIndexBeauftragung"<<endl;
    indexBeauftragung = -1;
//    emit beauftragt(indexBeauftragung);
}

int Auftragsverwaltung::getIndexBeauftragung()
{
    return indexBeauftragung;
}


void Auftragsverwaltung::setFehlerZustand(QString f)
{
    emit fehlerZustand(f);
}
