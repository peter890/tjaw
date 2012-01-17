#include "tjaw.h"
#include <stdio.h>
#include <iostream>

using namespace std;


TJAW::TJAW()
{
    /*
    for(int i=0; i<10; i++)
    {
        wiersz.pola.append(new PoleTxt(QString("nazwa%1").arg(i),QString("wartosc%1").arg(i)));
    }
   cout << wiersz.echoWiersz().toStdString();
*/

}


Pole* TJAW::utworzPole(QString nazwa, QString wartosc)
{
    bool isNumber = false;
    double number = 0;
    number = wartosc.toDouble(&isNumber); //funkcja toDouble zwraca przez parametr informacje(bool) o tym czy udalo sie przekonwertowac QStringa na Double

    if(isNumber)
    {
        return new PoleNum(nazwa,number);
    }
    else
    {
        return new PoleTxt(nazwa,wartosc);
    }

}


void TJAW::wyczysc()
{
    this->naglowek_.wyczysc();

    for(int i=0; i<this->wiersze_.size(); i++)
    {
        wiersze_[i]->wyczysc();
    }

    QVector<Wiersz*>::iterator it;

    for(it=wiersze_.begin(); it!=wiersze_.end();)
    {
        delete (*it);
        it = wiersze_.erase(it);
    }

}


string TJAW::toString()
{
    QString tjaw;

    tjaw.append(naglowek_.toString());
    tjaw.append("\n");


    for(int i=0; i< wiersze_.size(); i++)
    {
        tjaw.append(wiersze_[i]->toString());
        tjaw.append("\n");
    }

    return tjaw.toStdString();
}
