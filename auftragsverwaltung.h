#ifndef AUFTRAGSVERWALTUNG_H
#define AUFTRAGSVERWALTUNG_H
#include "fertigungsauftrag.h"
#include <QObject>
#include <iostream>
#include <fstream>
#define DATEI "fertigungsauftraege.txt"
class Auftragsverwaltung : public QObject
{
    Q_OBJECT
public:
    explicit Auftragsverwaltung(QObject *parent = 0);
    void lade(QString dateiname=DATEI);
    void speichere(QString dateiname=DATEI);
    const QList<Fertigungsauftrag>& getAuftraege();
    void addAuftrag(Fertigungsauftrag fa);
    void setAuftrag(int nr, Fertigungsauftrag fa);
    Fertigungsauftrag getAuftrag(int nr);
    int getAnzahlAuftraege();
    int getNextAuftragsNr();
    int searchFertigungsauftragByRFIDNr(unsigned long long rfidnr);
    void setIndexBeauftragung(int index);
    void resetIndexBeauftragung();
    int getIndexBeauftragung();
    void setFehlerZustand(QString f);
signals:
    void beauftragt(int auftragsIndex);
    void auftragChanged(int auftragsIndex);
    void fehlerZustand(QString nachricht);
public slots:


private:
    QList<Fertigungsauftrag> auftraege;
    int indexBeauftragung;
};

#endif // AUFTRAGSVERWALTUNG_H
