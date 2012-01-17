/*****************************************************************************
** "tjaw.h"                                                                 **
**                                                                          **
** OPIS:                                                                    **
** Krótki opis klasy                                                        **
**                                                                          **
** HISTORIA ZMIAN:                                                          **
** 0.01 11/12/06 Naprawiono problem wycieku pamiêci                      PK **
** 0.05 11/12/19 Dodano funkcje toString()                               PS **
*****************************************************************************/

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
    Pole* utworzPole(QString nazwa, QString wartosc);
    //void clearRow();
    //void echoWiersz(){cout << wiersz.echoWiersz();}
    QVector<Wiersz*> wiersze_;
    Naglowek naglowek_;
    void wyczysc();
    string toString();
};

#endif // TJAW_H
