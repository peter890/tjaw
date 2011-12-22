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
        this->pola.push_back(new PoleNum(nazwa,number));
        //cout << wartosc.toStdString() << " jest liczba: "<< isNumber << endl;
    }
    else
    {
        this->pola.push_back(new PoleTxt(nazwa,wartosc));
    }
}

void Naglowek::erase()
{
    QVector<Pole*>::iterator it;
    for(it=pola.begin(); it!=pola.end();)
    {
        delete (*it);
        it = pola.erase(it);
    }
}


QString Naglowek::toString()
{
    QString naglowek;
    for(int i=0; i< pola.size(); i++)
    {
        if(!pola.at(i)->getNazwa().isEmpty() && !pola.at(i)->getStrWartosc().isEmpty() )
            naglowek.append(pola.at(i)->getNazwa() + "=" + pola.at(i)->getStrWartosc() + " ");
        else
            if(pola.at(i)->getStrWartosc().isEmpty())
                naglowek.append(pola.at(i)->getNazwa() + " ");
    }
    return naglowek;
}


