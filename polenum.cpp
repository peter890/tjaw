#include "polenum.h"


PoleNum::PoleNum(QString nazwa, double wartosc):Pole(nazwa)
{
    this->_wartosc = wartosc;
}
void PoleNum::setWartosc(double wartosc)
{
    this->_wartosc = wartosc;
}
double PoleNum::getWartosc()
{
    return _wartosc;
}
QString PoleNum::getStrWartosc()
{
    QString tmp;
    return tmp.setNum(this->_wartosc);

}
