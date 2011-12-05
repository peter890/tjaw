#ifndef POLETXT_H
#define POLETXT_H
#include "pole.h"
class PoleTxt : public Pole
{
public:
    PoleTxt(QString nazwa, QString wartosc);
    void setWartosc(QString wartosc);
    QString getWartosc();
    virtual QString StrWartosc();
private:
    QString _wartosc;
};

#endif // POLETXT_H
