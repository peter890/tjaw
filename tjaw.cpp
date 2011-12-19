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
Pole* TJAW::createPole(QString nazwa, QString wartosc)
{
    bool isNumber = false;

    double number = 0;
    number = wartosc.toDouble(&isNumber); //funkcja toDouble zwraca przez parametr informacje(bool) o tym czy udalo sie przekonwertowac QStringa na Double
    if(isNumber)
    {
        return new PoleNum(nazwa,number);
        //cout << wartosc.toStdString() << " jest liczba: "<< isNumber << endl;
    }
    else
    {
       return new PoleTxt(nazwa,wartosc);
    }

}
void TJAW::erase()
{
    this->naglowek.erase();
    for(int i=0; i<this->wiersze.size(); i++)
        wiersze[i]->erase();
    QVector<Wiersz*>::iterator it;
    for(it=wiersze.begin(); it!=wiersze.end();)
    {
        delete (*it);
        it = wiersze.erase(it);
    }

}
string TJAW::toString()
{
    QString tjaw;


    tjaw.append(naglowek.toString());
    tjaw.append("\n");


    for(int i=0; i< wiersze.size(); i++)
    {
        tjaw.append(wiersze[i]->toString());
        tjaw.append("\n");
    }
    return tjaw.toStdString();


}
