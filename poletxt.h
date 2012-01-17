/*****************************************************************************
** "poletxt.h"                                                              **
**                                                                          **
** OPIS:                                                                    **
** Krótki opis klasy                                                        **
**                                                                          **
** HISTORIA ZMIAN:                                                          **
** 0.9 11/12/05 Utworzono klase                                         PK **
*****************************************************************************/
#ifndef POLETXT_H
#define POLETXT_H
#include "pole.h"


class PoleTxt : public Pole
{
public:
    PoleTxt(QString nazwa, QString wartosc);
    void setWartosc(QString wartosc);
    QString getWartosc();
    virtual QString getStrWartosc();

private:
    QString wartosc_;
};

#endif // POLETXT_H
