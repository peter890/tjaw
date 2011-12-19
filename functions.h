#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "tjaw.h"
#include <QSettings>
class Functions
{
public:

    Functions(TJAW* _obj);
    void uruchomFunkcjeDlaTjaw();
    void uruchomFunkcjeDlaPliku();
    void suma(QString _nazwaPolaIn, QString nazwaPolaOut);
protected:
    TJAW* obj;
};

#endif // FUNCTIONS_H
