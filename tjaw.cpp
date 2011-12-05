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
void TJAW::createPole(QString nazwa, QString wartosc)
{
    bool isNumber = false;

    double number = 0;
    number = wartosc.toDouble(&isNumber); //funkcja toDouble zwraca przez parametr informacje(bool) o tym czy udalo sie przekonwertowac QStringa na Double
    if(isNumber)
    {
        wiersz.pola.append(new PoleNum(nazwa,number));
        //cout << wartosc.toStdString() << " jest liczba: "<< isNumber << endl;
    }
    else
    {
       wiersz.pola.append(new PoleTxt(nazwa,wartosc));
    }

}
