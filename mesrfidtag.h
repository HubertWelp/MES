#ifndef MESRFIDTAG_H
#define MESRFIDTAG_H
#include "rfidtag.h"
#include "fertigungsauftrag.h"
class MESRFIDTag : public RFIDTag
{
public:
    MESRFIDTag();
    RFIDTag& fromFertigungsauftrag(Fertigungsauftrag fa);
//    Fertigungsauftrag toFertigungsauftrag();
    Bearbeitungsstatus::Status getBeauftragt();
    Bearbeitungsstatus::Status getGefraest();
    Bearbeitungsstatus::Status getGebohrt();
    Bearbeitungsstatus::Status getVersendet();
    void setGefraest(Bearbeitungsstatus::Status s);
    void setGebohrt(Bearbeitungsstatus::Status s);
    void setVersendet(Bearbeitungsstatus::Status s);
    char* getGravurtext();
    float getTextPositionX();
    float getTextPositionY();
    bool getHochformat();
    float getBohrlochDurchmesser();
    float getBohrlochPositionX();
    float getBohrlochPositionY();




private:

    typedef struct
    {
        unsigned int beauftragt:2;
        unsigned int gefraest:2;
        unsigned int gebohrt:2;
        unsigned int versendet:2;
        unsigned int unused1:2;
        unsigned int unused2:2;
        unsigned int unused3:2;
        unsigned int unused4:2;
        unsigned int unused5:2;
        unsigned int unused6:2;
        unsigned int unused7:2;
        unsigned int unused8:2;
        unsigned int unused9:2;
        unsigned int unused10:2;
        unsigned int unused11:2;
        unsigned int unused12:2;
    }BsTagDataT;

    typedef struct{
        char gravurtext[40];
        float x;
        float y;
        bool hochFormat;
    } FrTagDataT;

    typedef struct{
        float durchmesser;
        float x;
        float y;
    } BoTagDataT;

    typedef struct{
        BsTagDataT bearbeitungsstatus;      // 4
        BoTagDataT bohrDaten;               // 52
        FrTagDataT fraesDaten;              // 12
    }FaTagDataT;

};

#endif // MESRFIDTAG_H
