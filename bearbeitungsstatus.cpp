#include "bearbeitungsstatus.h"
#include <stdlib.h>
const string Bearbeitungsstatus::STATUS[3]={"na","offen","erledigt"};
ostream& operator<<(ostream& fout, Bearbeitungsstatus& b)
{
    fout << b.beauftragt << "," << b.gefraest << "," << b.gebohrt << "," << b.versendet << ",";
    return fout;
}
istream& operator>>(istream& fin, Bearbeitungsstatus& b)
{
    char s[100];
    fin.getline(s,100,',');
    b.beauftragt = (Bearbeitungsstatus::Status)atoi(s);
    fin.getline(s,100,',');
    b.gefraest = (Bearbeitungsstatus::Status)atoi(s);
    fin.getline(s,100,',');
    b.gebohrt = (Bearbeitungsstatus::Status)atoi(s);
    fin.getline(s,100,',');
    b.versendet = (Bearbeitungsstatus::Status)atoi(s);
    return fin;
}

Bearbeitungsstatus::Bearbeitungsstatus()
    :beauftragt(offen)
    ,gefraest(na)
    ,gebohrt(na)
    ,versendet(na)
{
}

int Bearbeitungsstatus::setBeauftragt(Status s)
{
    if(s>2)
        return 1;
    beauftragt = s;
    return 0;
}

int Bearbeitungsstatus::setGefraest(Status s)
{

    if(s>2)
        return 1;
    if(gefraest==na && s==offen || gefraest==offen && s==erledigt || gefraest==s)
    {
        gefraest = s;
        return 0;
    }else
        return 2;

}

int Bearbeitungsstatus::setGebohrt(Status s)
{
    if(s>2)
        return 1;
    if(gebohrt==na && s==offen || gebohrt==offen && s==erledigt || gebohrt==s)
    {
        gebohrt = s;
        return 0;
    }else
        return 2;
}

int Bearbeitungsstatus::setVersendet(Status s)
{
    if(s>2)
        return 1;
    if(versendet==na && s==offen || versendet==offen && s==erledigt || versendet==s)
    {
        versendet = s;
        return 0;
    }else
        return 2;

}
Bearbeitungsstatus::Status Bearbeitungsstatus::getBeauftragt()
{
    return beauftragt;
}

Bearbeitungsstatus::Status Bearbeitungsstatus::getGefraest()
{
    return gefraest;
}
Bearbeitungsstatus::Status Bearbeitungsstatus::getGebohrt()
{
    return gebohrt;
}
Bearbeitungsstatus::Status Bearbeitungsstatus::getVersendet()
{
    return versendet;
}
string Bearbeitungsstatus::statusToString(Status s)
{
    return STATUS[s];
}
