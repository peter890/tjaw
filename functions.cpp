#include "functions.h"

Functions::Functions(TJAW *_obj)
{
    this->obj = _obj;
    this->settings = new QSettings("config.ini",QSettings::IniFormat);
}

void Functions::suma(QString nazwaPolaIn, QString nazwaPolaOut)
{
    double sum=0;
    QString num;
    Wiersz* wiersz;

    for(int w=0; w < obj->wiersze.size(); w++)
    {
        wiersz = obj->wiersze.at(w);
        if(wiersz->getPole(nazwaPolaIn) != NULL)
        {
            sum += wiersz->getPole(nazwaPolaIn)->getStrWartosc().toDouble();

        }

    }

    obj->naglowek.wstawPole(nazwaPolaOut,num.number(sum));
    Logger::getInstance()->logguj(QDateTime::currentDateTime().toString("hh:mm:ss") + " - Wykonano 'suma' dla pola '"+ nazwaPolaIn +"'");


}
double Functions::suma(QString nazwaPolaIn)
{
    double sum=0;

    Wiersz* wiersz;

    for(int w=0; w < obj->wiersze.size(); w++)
    {
        wiersz = obj->wiersze.at(w);
        if(wiersz->getPole(nazwaPolaIn) != NULL)
        {
            sum += wiersz->getPole(nazwaPolaIn)->getStrWartosc().toDouble();

        }

    }
    return sum;

}
void Functions::uruchomFunkcjeDlaTjaw()
{

    QString in, out;
    //----------------------------------------------------------------------
    if(settings->value("Funkcje/suma").toBool())
    {
        int size = settings->value("Suma/size").toInt();
        settings->beginReadArray("Suma");
        for(int i = 0; i < size; i++ )
        {
            settings->setArrayIndex(i);
            in = settings->value("kolumnaIn").toString();
            out = settings->value("kolumnaOut").toString();
            //cout << "suma IN: " << in.toStdString() << " || OUT: " << out.toStdString()<< endl;
            this->suma(in,out);

        }
        settings->endArray();

    }
    //----------------------------------------------------------------------
    if(settings->value("Funkcje/odchylenieStd").toBool())
    {
        int size = settings->value("Odchylenie/size").toInt();
        settings->beginReadArray("Odchylenie");
        for(int i = 0; i < size; i++ )
        {
            settings->setArrayIndex(i);
            in = settings->value("kolumnaIn").toString();

            dane.push_back( (double) this->suma(in));

        }
        settings->endArray();
        cout << "rozmiar vectora dane " << dane.size()<< endl;
    }
    //cout << obj->toString() <<endl;
    //cout << ">end";

}
void Functions::zapisDoPliku(QString nazwaPliku)
{
    qDebug("nazwa Pliku: " +nazwaPliku.toAscii());
    QFile plik(nazwaPliku);
    if(plik.open(QFile::Append | QFile::Text))
    {
        QTextStream stream(&plik);
        //--------------------- STRUMIENIOWY ZAPIS DO PLIKU ------------------
        stream << obj->naglowek.toString();

        for(int i=0; i< obj->wiersze.size(); i++)
            stream << obj->wiersze[i]->toString() << endl;
        stream << ">end";
    }

}

void Functions::odchylenie(QString nazwaPolaIn, QString nazwaPolaOut)
{

}


