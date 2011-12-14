#ifndef TJAW_H
#define TJAW_H
#include "wiersz.h"
#include "naglowek.h"
#include "pole.h"
#include <stdio.h>
#include <iostream>
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
};

#endif // TJAW_H
