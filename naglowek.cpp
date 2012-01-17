#include "naglowek.h"


Naglowek::Naglowek()
{
}


void Naglowek::wstawPole(QString nazwa, QString wartosc)
{
    bool isNumber = false;
    double number = 0;
    number = wartosc.toDouble(&isNumber); //funkcja toDouble zwraca przez parametr informacje(bool) o tym czy udalo sie przekonwertowac QStringa na Double

    if(isNumber)
    {
        this->pola_.push_back(new PoleNum(nazwa,number));
        //cout << wartosc.toStdString() << " jest liczba: "<< isNumber << endl;
    }
    else
    {
        this->pola_.push_back(new PoleTxt(nazwa,wartosc));
    }
}



void Naglowek::wyczysc()
{
    QVector<Pole*>::iterator it;

    for(it=pola_.begin(); it!=pola_.end();)
    {
        delete (*it);
        it = pola_.erase(it);
    }
}


QString Naglowek::toString()
{
    QString naglowek;
    for(int i=0; i< pola_.size(); i++)
    {
        if(!pola_.at(i)->getNazwa().isEmpty() && !pola_.at(i)->getStrWartosc().isEmpty() )
        {
            naglowek.append(pola_.at(i)->getNazwa() + "=" + pola_.at(i)->getStrWartosc() + " ");
        }
        else
        {
            if(pola_.at(i)->getStrWartosc().isEmpty())
            {
                naglowek.append(pola_.at(i)->getNazwa() + " ");
            }
        }
    }
    return naglowek;
}


Pole* Naglowek::getPole(int index)
{
    if(index>=0 && index<pola_.size())
    {
        return pola_.at(index);
    }
    return NULL;
}


Pole* Naglowek::getPole(QString nazwa)
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

