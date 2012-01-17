/*****************************************************************************
** "naglowek.h"                                                             **
**                                                                          **
** OPIS:                                                                    **
** Krótki opis klasy                                                        **
**                                                                          **
** HISTORIA ZMIAN:                                                          **
** 0.01 11/12/06 Pierwsza implementacja klasy                            PK **
**               Dodano funkcje wstawPole()                              PK **
** 0.05 11/12/14 Dodano funkcje erase() -czyszczenie vectora pola        PK **
** 0.05 11/12/22 Dodano funkcje toString()                               PK **
** 0.05 11/12/29 Dodano funkcje getPole(int) i getPole(QString)          PK **
*****************************************************************************/

#ifndef NAGLOWEK_H
#define NAGLOWEK_H
#include <QVector>
#include <QString>
#include "pole.h"
#include "polenum.h"
#include "poletxt.h"


class Naglowek
{
public:
    Naglowek();
    QVector<Pole*> pola_;
    void wstawPole(QString nazwa, QString wartosc);
    void wyczysc();
    QString toString();
    Pole* getPole(int index);
    Pole* getPole(QString nazwa);
};

#endif // NAGLOWEK_H
