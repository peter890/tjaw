#include "polenum.h"


PoleNum::PoleNum(QString nazwa, double wartosc):Pole(nazwa)
{
    this->wartosc_ = wartosc;
}


void PoleNum::setWartosc(double wartosc)
{
    this->wartosc_ = wartosc;
}


double PoleNum::getWartosc()
{
    return wartosc_;
}


QString PoleNum::getStrWartosc()
{
    QString tmp;
    return tmp.setNum(this->wartosc_);
}
