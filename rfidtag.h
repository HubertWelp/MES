#ifndef RFIDTAG_H
#define RFIDTAG_H

class RFIDTag
{
public:
    RFIDTag();
    const unsigned char* getUserdata();
    int userdataLength();
    unsigned long long getRFIDNr();
    void setUserdata(const unsigned char* buffer, int l);
    void setRFIDNr(const unsigned long long nr);
protected:
    unsigned char id[8];
    unsigned char userdata[28][4];
};

#endif // RFIDTAG_H
