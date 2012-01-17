#include "wiersz.h"


Wiersz::Wiersz()
{
}


Wiersz::Wiersz(Pole * pole)
{
    pola_.push_back(pole);
}


void Wiersz::wyczysc()
{
    QVector<Pole*>::iterator it;

    for(it=pola_.begin(); it!=pola_.end();)
    {
        delete (*it);
        it = pola_.erase(it);
    }

}


QString Wiersz::toString()
{
    QString wiersz;

    for(int i=0; i<pola_.size(); i++)
    {
        if(!pola_.at(i)->getNazwa().isEmpty() && !pola_.at(i)->getStrWartosc().isEmpty() )
        {
            wiersz.append(pola_.at(i)->getNazwa() + "=" + pola_.at(i)->getStrWartosc() + " ");
        }
        else
        {
            if(pola_.at(i)->getStrWartosc().isEmpty())
            {
                wiersz.append(pola_.at(i)->getNazwa() + " ");
            }
        }
    }
    return wiersz;
}


void Wiersz::wstawPole(QString nazwa, QString wartosc)
{
    bool isNumber = false;
    double number = 0;
    number = wartosc.toDouble(&isNumber); //funkcja toDouble zwraca przez parametr informacje(bool) o tym czy udalo sie przekonwertowac QStringa na Double

    if(isNumber)
    {
        this->pola_.append(new PoleNum(nazwa,number));
    }
    else
    {
        this->pola_.append(new PoleTxt(nazwa,wartosc));
    }
}


Pole* Wiersz::getPole(int index)
{
    if(index>=0 && index<pola_.size())
    {
        return pola_.at(index);
    }
    return NULL;
}


Pole* Wiersz::getPole(QString nazwa)
{
    for(int i=0; i<pola_.size(); i++)
    {
        if(pola_.at(i)->getNazwa() == nazwa)
        {
            return pola_.at(i);
        }
    }
    return NULL;
}

