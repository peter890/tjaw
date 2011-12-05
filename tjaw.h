#ifndef TJAW_H
#define TJAW_H
#include "wiersz.h"
#include <stdio.h>
#include <iostream>
using namespace std;
class TJAW
{
public:
    TJAW();
    void createPole(QString nazwa, QString wartosc);
    //void echoWiersz(){cout << wiersz.echoWiersz();}
    Wiersz wiersz;
};

#endif // TJAW_H
