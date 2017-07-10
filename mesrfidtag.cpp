#include "mesrfidtag.h"
#include <string.h>

MESRFIDTag::MESRFIDTag()
{
}
RFIDTag& MESRFIDTag::fromFertigungsauftrag(Fertigungsauftrag fa)
{
    FaTagDataT fatd={0};

    fatd.bearbeitungsstatus.beauftragt = fa.getBearbeitungsstatus().getBeauftragt();
    fatd.bearbeitungsstatus.gefraest = fa.getBearbeitungsstatus().getGefraest();
    fatd.bearbeitungsstatus.gebohrt = fa.getBearbeitungsstatus().getGebohrt();
    fatd.bearbeitungsstatus.versendet = fa.getBearbeitungsstatus().getVersendet();

    if(fa.getBearbeitungsstatus().getGebohrt()!=Bearbeitungsstatus::na)
    {
        if(fa.getProduktbeschreibung().getHochFormat())
        {
            fatd.bohrDaten.durchmesser = 5.0;
            fatd.bohrDaten.x = 105.0;
            fatd.bohrDaten.y = 20.0;
        }else
        {
            fatd.bohrDaten.durchmesser = 5.0;
            fatd.bohrDaten.x = 190.0;
            fatd.bohrDaten.y = 149.0;
        }

    }
    if(fa.getBearbeitungsstatus().getGefraest()!=Bearbeitungsstatus::na)
    {
        if(fa.getProduktbeschreibung().getHochFormat())
        {
            strcpy(fatd.fraesDaten.gravurtext,fa.getProduktbeschreibung().getGravurtext().c_str());
            fatd.fraesDaten.hochFormat = true;
            fatd.fraesDaten.x = 10.5;
            fatd.fraesDaten.y = 14.9-0.25*strlen(fatd.fraesDaten.gravurtext);
        }else
        {
            strcpy(fatd.fraesDaten.gravurtext,fa.getProduktbeschreibung().getGravurtext().c_str());
            fatd.fraesDaten.hochFormat = false;
            fatd.fraesDaten.x = 10.5-0.25*strlen(fatd.fraesDaten.gravurtext);
            fatd.fraesDaten.y = 14.9;
        }

    }
    unsigned long long id = fa.getRFIDNr();
    memcpy(&this->id,&id,8);
    memcpy(&this->userdata,&fatd,sizeof(fatd));
    return *this;

}
extern void byteStreamToHexString(char* hex, const unsigned char* byte, int len);

//Fertigungsauftrag MESRFIDTag::toFertigungsauftrag()
//{
//    Fertigungsauftrag fa;
//    FaTagDataT* fatd = (FaTagDataT*)&userdata;
//    fa.setRFIDNr(getRFIDNr());
//    char hexString[10000];
//    byteStreamToHexString(hexString,(unsigned char*)fatd,4);
//    cout << "toFertigungsaufrag: " << hexString << endl;
//    cout << "toFertigungsaufrag: " << fatd->bearbeitungsstatus.beauftragt << endl;
//    cout << "toFertigungsaufrag: " << fatd->bearbeitungsstatus.gefraest << endl;
//    cout << "toFertigungsaufrag: " << fatd->bearbeitungsstatus.gebohrt << endl;
//    cout << "toFertigungsaufrag: " << fatd->bearbeitungsstatus.versendet << endl;
//    Bearbeitungsstatus b;
//    b.setBeauftragt((Bearbeitungsstatus::Status)fatd->bearbeitungsstatus.beauftragt);
//    b.setGebohrt((Bearbeitungsstatus::Status)fatd->bearbeitungsstatus.gebohrt);
//    b.setGefraest((Bearbeitungsstatus::Status)fatd->bearbeitungsstatus.gefraest);
//    b.setVersendet((Bearbeitungsstatus::Status)fatd->bearbeitungsstatus.versendet);
//    fa.setBearbeitungsstatus(b);

//    return fa;
//}
Bearbeitungsstatus::Status MESRFIDTag::getBeauftragt()
{
    FaTagDataT* fatd = (FaTagDataT*)&userdata;
    return (Bearbeitungsstatus::Status)fatd->bearbeitungsstatus.beauftragt;
}

Bearbeitungsstatus::Status MESRFIDTag::getGefraest()
{
    FaTagDataT* fatd = (FaTagDataT*)&userdata;
    return (Bearbeitungsstatus::Status)fatd->bearbeitungsstatus.gefraest;
}
Bearbeitungsstatus::Status MESRFIDTag::getGebohrt()
{
    FaTagDataT* fatd = (FaTagDataT*)&userdata;
    return (Bearbeitungsstatus::Status)fatd->bearbeitungsstatus.gebohrt;
}
Bearbeitungsstatus::Status MESRFIDTag::getVersendet()
{
    FaTagDataT* fatd = (FaTagDataT*)&userdata;
    return (Bearbeitungsstatus::Status)fatd->bearbeitungsstatus.versendet;
}

void MESRFIDTag::setGefraest(Bearbeitungsstatus::Status s)
{
    FaTagDataT* fatd = (FaTagDataT*)&userdata;
    fatd->bearbeitungsstatus.gefraest = s;
}

void MESRFIDTag::setGebohrt(Bearbeitungsstatus::Status s)
{
    FaTagDataT* fatd = (FaTagDataT*)&userdata;
    fatd->bearbeitungsstatus.gebohrt = s;
}

void MESRFIDTag::setVersendet(Bearbeitungsstatus::Status s)
{
    FaTagDataT* fatd = (FaTagDataT*)&userdata;
    fatd->bearbeitungsstatus.versendet = s;
}

char *MESRFIDTag::getGravurtext()
{
    FaTagDataT* fatd = (FaTagDataT*)&userdata;
    return fatd->fraesDaten.gravurtext;
}

float MESRFIDTag::getTextPositionX()
{
    FaTagDataT* fatd = (FaTagDataT*)&userdata;
    return fatd->fraesDaten.x;
}

float MESRFIDTag::getTextPositionY()
{
    FaTagDataT* fatd = (FaTagDataT*)&userdata;
    return fatd->fraesDaten.y;
}

bool MESRFIDTag::getHochformat()
{
    FaTagDataT* fatd = (FaTagDataT*)&userdata;
    return fatd->fraesDaten.hochFormat;
}

float MESRFIDTag::getBohrlochDurchmesser()
{
    FaTagDataT* fatd = (FaTagDataT*)&userdata;
    return fatd->bohrDaten.durchmesser;
}

float MESRFIDTag::getBohrlochPositionX()
{
    FaTagDataT* fatd = (FaTagDataT*)&userdata;
    return fatd->bohrDaten.x;
}

float MESRFIDTag::getBohrlochPositionY()
{
    FaTagDataT* fatd = (FaTagDataT*)&userdata;
    return fatd->bohrDaten.y;
}






