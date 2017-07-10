#ifndef FERTIGUNGSAUFTRAG_H
#define FERTIGUNGSAUFTRAG_H
#include <iostream>
#include "produktbeschreibung.h"
#include "bearbeitungsstatus.h"
using namespace std;
class Fertigungsauftrag
{
public:
    Fertigungsauftrag();
    Fertigungsauftrag(Produktbeschreibung p);
    static void setLetzteAuftragsNr(unsigned long long nr);
    void setAuftragsNr(unsigned long long nr);
    void setProduktbeschreibung(Produktbeschreibung p);
    void setRFIDNr(unsigned long long nr);
    void setBearbeitungsstatus(Bearbeitungsstatus s);
    unsigned long long getAuftragsnummer();
    Produktbeschreibung getProduktbeschreibung();
    unsigned long long getRFIDNr();
    Bearbeitungsstatus getBearbeitungsstatus();
    friend ostream& operator <<(ostream& fout, Fertigungsauftrag& f);
    friend istream& operator >>(istream& fin, Fertigungsauftrag& f);
private:
    static unsigned long long letzteAuftragsNr;

    unsigned long long auftragsNr;
    Produktbeschreibung produktbeschreibung;
    unsigned long long RFIDNr;
    Bearbeitungsstatus bearbeitungsstatus;
};

#endif // FERTIGUNGSAUFTRAG_H
