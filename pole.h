#ifndef POLE_H
#define POLE_H
#include <QString>
class Pole
{
public:
    Pole(QString nazwa){this->nazwa = nazwa;}
    QString getNazwa(){return nazwa;}
    virtual QString StrWartosc(){return "";}
    void setNazwa(QString nazwa){this->nazwa = nazwa;}

private:
    QString nazwa;
};

#endif // POLE_H
