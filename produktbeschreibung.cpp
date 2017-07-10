#include "produktbeschreibung.h"
#include <stdlib.h>
const  string Produktbeschreibung::FORMAT[2] =  {"quer","hoch"};
const  string Produktbeschreibung::STANDBILD[2] =  {"nein","ja"};

ostream& operator <<(ostream& fout, Produktbeschreibung& p)
{
    fout << p.hochFormat << "," << p.gravurtext << "," << p.standbild << ",";
    return fout;
}
istream& operator >>(istream& fin, Produktbeschreibung& p)
{
    char s[100];
    fin.getline(s,100,',');
    p.hochFormat = (bool)atoi(s);
    fin.getline(s,100,',');
    p.setGravurtext(s);
    fin.getline(s,100,',');
    p.standbild = (bool)atoi(s);
    return fin;
}

Produktbeschreibung::Produktbeschreibung(bool hf, string t, bool s)
{
    setHochFormat(hf);
    setGravurtext(t);
    setStandbild(s);
}
void Produktbeschreibung::setHochFormat(bool hf)
{
    hochFormat = hf;
}

void Produktbeschreibung::setGravurtext(string s)
{
    gravurtext=s.substr(0,39);
}

void Produktbeschreibung::setStandbild(bool s)
{
    standbild = s;

}

bool Produktbeschreibung::getHochFormat()
{
    return hochFormat;
}

string Produktbeschreibung::getGravurtext()
{
    return gravurtext;
}

bool Produktbeschreibung::getStandbild()
{
    return standbild;
}

string Produktbeschreibung::formatToString()
{
    return FORMAT[hochFormat];
}

string Produktbeschreibung::standbildToString()
{
    return STANDBILD[standbild];

}
