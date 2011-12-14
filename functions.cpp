#include "functions.h"

Functions::Functions(TJAW *_obj)
{
    this->obj = _obj;
}
void Functions::suma(QString _nazwaPolaIn, QString nazwaPolaOut)
{
    double sum=0;
    QString num;
    Wiersz* wiersz;
    cout << "\njestem w funkcji suma\n";

    for(int w=0; w < obj->wiersze.size(); w++)
    {
        wiersz = obj->wiersze.at(w);
        if(wiersz->getPole(_nazwaPolaIn) != NULL)
        {
            sum += wiersz->getPole(_nazwaPolaIn)->getStrWartosc().toDouble();
            cout << wiersz->getPole(_nazwaPolaIn)->getStrWartosc().toDouble() << endl;
        }

    }

    obj->naglowek.wstawPole(nazwaPolaOut,num.number(sum));

    cout << endl << obj->naglowek.echo().toStdString() << endl;
    for(int i=0; i< obj->wiersze.size(); i++)
    cout << obj->wiersze[i]->echoWiersz().toStdString() << endl;

}

