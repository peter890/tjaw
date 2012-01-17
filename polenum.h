/*****************************************************************************
** "polenum.h"                                                              **
**                                                                          **
** OPIS:                                                                    **
** Krótki opis klasy                                                        **
**                                                                          **
** HISTORIA ZMIAN:                                                          **
** 0.9 11/12/05 Utworzono klase                                         PK **
*****************************************************************************/
#ifndef POLENUM_H
#define POLENUM_H
#include "pole.h"


class PoleNum: public Pole
{
public:
    PoleNum(QString nazwa, double wartosc);
    void setWartosc(double wartosc);
    virtual QString getStrWartosc();
    double getWartosc();

private:
    double wartosc_;
};

#endif // POLENUM_H
