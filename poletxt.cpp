#include "poletxt.h"


PoleTxt::PoleTxt(QString nazwa, QString wartosc):Pole(nazwa)
{
    this->_wartosc = wartosc;
}
void PoleTxt::setWartosc(QString wartosc)
{
    this->_wartosc = wartosc;
}
QString PoleTxt::getWartosc()
{
    return _wartosc;
}
QString PoleTxt::StrWartosc()
{
    return this->_wartosc;

}
