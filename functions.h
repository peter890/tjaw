#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "tjaw.h"
#include <QSettings>
#include <QFile>
#include <QTextStream>
class Functions
{
public:

    Functions(TJAW* _obj);
    void uruchomFunkcjeDlaTjaw();
    void uruchomFunkcjeDlaPliku();
    void zapisDoPliku(QString nazwaPliku);
    void suma(QString nazwaPolaIn, QString nazwaPolaOut);
protected:
    TJAW* obj;
    QSettings* settings;


};

#endif // FUNCTIONS_H
