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
    QVector<Pole*> pola;
    void wstawPole(QString nazwa, QString wartosc);
    void erase();
    QString echo();
};

#endif // NAGLOWEK_H
