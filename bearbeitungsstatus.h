#ifndef BEARBEITUNGSSTATUS_H
#define BEARBEITUNGSSTATUS_H
#include <iostream>
#include <string>
using namespace std;
class Bearbeitungsstatus
{

public:
    enum Status {offen,erledigt,na};
    Bearbeitungsstatus();

    int setBeauftragt(Status s);
    int setGefraest(Status s);
    int setGebohrt(Status s);
    int setVersendet(Status s);
    Status getBeauftragt();
    Status getGefraest();
    Status getGebohrt();
    Status getVersendet();
    static string statusToString(Status s);
    friend ostream& operator<<(ostream& fout, Bearbeitungsstatus& b);
    friend istream& operator>>(istream& fout, Bearbeitungsstatus& b);
private:
    Status beauftragt;
    Status gefraest;
    Status gebohrt;
    Status versendet;
    const static string STATUS[3];
};
#endif // BEARBEITUNGSSTATUS_H
