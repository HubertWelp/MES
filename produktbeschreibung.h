#ifndef PRODUKTBESCHREIBUNG_H
#define PRODUKTBESCHREIBUNG_H
#include <string>
#include <iostream>
using namespace std;

class Produktbeschreibung
{

public:
//    enum Format {horizontal, vertikal};
    const static string FORMAT[2];
    const static string STANDBILD[2];
    Produktbeschreibung(bool hf=false, string t="", bool s=true);
    void setHochFormat(bool hf);
    void setGravurtext(string s);
    void setStandbild(bool s);
    bool getHochFormat();
    string getGravurtext();
    bool getStandbild();
    friend ostream& operator << (ostream& fout, Produktbeschreibung& p);
    friend istream& operator >> (istream& fin, Produktbeschreibung& p);
    string formatToString();
    string standbildToString();
private:
    bool hochFormat;
    string gravurtext;
    bool standbild;


};
ostream& operator << (ostream& fout, Produktbeschreibung& p);
istream& operator >> (istream& fin, Produktbeschreibung& p);
#endif // PRODUKTBESCHREIBUNG_H
