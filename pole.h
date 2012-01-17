/*****************************************************************************
** "pole.h"                                                                 **
**                                                                          **
** OPIS:                                                                    **
** Krótki opis klasy                                                        **
**                                                                          **
** HISTORIA ZMIAN:                                                          **
** 0.9 11/12/05 Utworzono klase                                          PK **
*****************************************************************************/

#ifndef POLE_H
#define POLE_H
#include <QString>


class Pole
{
public:
    Pole(QString nazwa){this->nazwa_ = nazwa;}
    QString getNazwa(){return nazwa_;}
    virtual QString getStrWartosc(){return "";}
    void setNazwa(QString nazwa){this->nazwa_ = nazwa;}

private:
    QString nazwa_;
};

#endif // POLE_H
