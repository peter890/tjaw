#ifndef WIERSZ_H
#define WIERSZ_H
#include <QVector>
#include "pole.h"
#include "polenum.h"
#include "poletxt.h"
class Wiersz
{
public:
    Wiersz();
    Wiersz(Pole*);
    QVector<Pole*> pola;
    void wstawPole(QString nazwa, QString wartosc);
    void erase();
    QString echoWiersz();
    int size(){return pola.size();}

};

#endif // WIERSZ_H
