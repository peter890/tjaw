#ifndef TJAW_H
#define TJAW_H
#include "wiersz.h"
#include "naglowek.h"
#include "pole.h"
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
class TJAW
{
public:
    TJAW();
    Pole* createPole(QString nazwa, QString wartosc);
    void clearRow();
    //void echoWiersz(){cout << wiersz.echoWiersz();}
    QVector<Wiersz*> wiersze;
    Naglowek naglowek;
    void erase();
    string toString();
};

#endif // TJAW_H
