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
    //cout << "\njestem w funkcji suma\n";
    //if(obj->wiersze.size() > 0)
    //{
        for(int w=0; w < obj->wiersze.size(); w++)
        {
            wiersz = obj->wiersze.at(w);
            if(wiersz->getPole(_nazwaPolaIn) != NULL)
            {
                sum += wiersz->getPole(_nazwaPolaIn)->getStrWartosc().toDouble();

            }

        }

        obj->naglowek.wstawPole(nazwaPolaOut,num.number(sum));


    //}

}
void Functions::uruchomFunkcjeDlaTjaw()
{

    QString in, out;
    QSettings settings("config.ini",QSettings::IniFormat);
    if(settings.value("Funkcje/suma").toBool())
    {
        int size = settings.value("Suma/size").toInt();
        settings.beginReadArray("Suma");
        for(int i = 0; i < size; i++ )
        {
            settings.setArrayIndex(i);
            in = settings.value("kolumnaIn").toString();
            out = settings.value("kolumnaOut").toString();
            cout << "suma IN: " << in.toStdString() << " || OUT: " << out.toStdString()<< endl <<endl;
            this->suma(in,out);
            cout << obj->toString() <<endl;
        }
        settings.endArray();

    }

}

