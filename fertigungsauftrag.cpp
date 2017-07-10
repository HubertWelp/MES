#include "fertigungsauftrag.h"
#include <stdlib.h>
unsigned long long Fertigungsauftrag::letzteAuftragsNr=1000;

ostream& operator <<(ostream& fout, Fertigungsauftrag& f)
{
    fout << f.auftragsNr << ",";
    fout << f.produktbeschreibung;
    fout << f.RFIDNr << ",";
    fout << f.bearbeitungsstatus;
    return fout;
}
istream& operator >>(istream& fin, Fertigungsauftrag& f)
{
    char s[100];
    fin.getline(s,100,',');
    cout << "auf: " << s << endl;
    sscanf(s,"%llu",&f.auftragsNr);
    cout << "auf: " << f.auftragsNr << endl;
    fin >> f.produktbeschreibung;
    fin.getline(s,100,',');
    cout << "<<" << s << endl;
    sscanf(s,"%llu",&f.RFIDNr);
    fin >> f.bearbeitungsstatus;
    return fin;
}

Fertigungsauftrag::Fertigungsauftrag()
{
    RFIDNr = 0;
    letzteAuftragsNr++;
    auftragsNr=letzteAuftragsNr;
}

Fertigungsauftrag::Fertigungsauftrag(Produktbeschreibung p)
{
    RFIDNr = 0;
    letzteAuftragsNr++;
    auftragsNr=letzteAuftragsNr;
    produktbeschreibung = p;
}

void Fertigungsauftrag::setLetzteAuftragsNr(unsigned long long nr)
{
    if(nr>letzteAuftragsNr)
        letzteAuftragsNr=nr;
}

void Fertigungsauftrag::setAuftragsNr(unsigned long long nr)
{
    auftragsNr=nr;
}

void Fertigungsauftrag::setProduktbeschreibung(Produktbeschreibung p)
{
    produktbeschreibung=p;
}

void Fertigungsauftrag::setRFIDNr(unsigned long long nr)
{
    RFIDNr=nr;
}

void Fertigungsauftrag::setBearbeitungsstatus(Bearbeitungsstatus s)
{
    bearbeitungsstatus=s;
}
unsigned long long Fertigungsauftrag::getAuftragsnummer()
{
    return auftragsNr;
}

Produktbeschreibung Fertigungsauftrag::getProduktbeschreibung()
{
    return produktbeschreibung;
}

unsigned long long Fertigungsauftrag::getRFIDNr()
{
    return RFIDNr;
}

Bearbeitungsstatus Fertigungsauftrag::getBearbeitungsstatus()
{
    return bearbeitungsstatus;
}
