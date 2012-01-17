#include "poletxt.h"


PoleTxt::PoleTxt(QString nazwa, QString wartosc):Pole(nazwa)
{
    this->wartosc_ = wartosc;
}


void PoleTxt::setWartosc(QString wartosc)
{
    this->wartosc_ = wartosc;
}


QString PoleTxt::getWartosc()
{
    return wartosc_;
}


QString PoleTxt::getStrWartosc()
{
    return this->wartosc_;

}
