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
    QVector<Pole*> pola;
    void wyczysc();
    QString echoWiersz();
    int size(){return pola.size();}

};

#endif // WIERSZ_H
