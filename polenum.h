#ifndef POLENUM_H
#define POLENUM_H
#include "pole.h"
class PoleNum: public Pole
{
public:
    PoleNum(QString nazwa, double wartosc);
    void setWartosc(double wartosc);
    virtual QString getStrWartosc();
    double getWartosc();
private:
    double _wartosc;
};

#endif // POLENUM_H
