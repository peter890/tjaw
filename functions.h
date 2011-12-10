#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "tjaw.h"
class Functions
{
public:
    Functions(){}
    Functions(TJAW* _obj);
    void suma(QString _nazwaPolaIn, QString nazwaPolaOut);
protected:
    TJAW* obj;
};

#endif // FUNCTIONS_H
