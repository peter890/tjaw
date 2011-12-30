#include "functions.h"
#include <math.h>

Functions::Functions(TJAW *_obj)
{
    this->obj = _obj;
    this->settings = new QSettings("config.ini",QSettings::IniFormat);

}
void Functions::Wyswietl(TJAW *_obj)
{
    cout << _obj->naglowek.toString().toStdString();

    for(int i=0; i< _obj->wiersze.size(); i++)
        cout << _obj->wiersze[i]->toString().toStdString() << endl;
    cout << ">end\n";
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
    Logger::getInstance()->logguj("Wykonano 'suma' dla pola '"+ nazwaPolaIn +"'");


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
    if(settings->value("Funkcje/odchylenieStd").toBool()) //2- dla pliku
    {
        Wiersz* wiersz;
        int size = settings->value("Odchylenie/size").toInt();
        settings->beginReadArray("Odchylenie");
        for(int i = 0; i < size; i++ )
        {
            settings->setArrayIndex(i);
            in = settings->value("kolumnaIn").toString();
            out = settings->value("kolumnaOut").toString();
            if(settings->value("dane").toInt() == 2)
            {
                dane.push_back( (double) this->suma(in));
            }
            if(settings->value("dane").toInt() == 1)
            {
                for(int w=0; w < obj->wiersze.size(); w++)
                {
                    wiersz = obj->wiersze.at(w);
                    if(wiersz->getPole(in) != NULL)
                    {
                        dane.push_back(wiersz->getPole(in)->getStrWartosc().toDouble());
                    }
                }
                odchylenie(in,out);
            }
        }
        settings->endArray();
    }

    //cout << obj->toString() <<endl;
    //cout << ">end";
    if(filtruj())this->zapisDoPliku();

}
void Functions::uruchomFunkcjeDlaPliku()
{
    QString in, out;

    if(settings->value("Funkcje/odchylenieStd").toBool())
    {
        int size = settings->value("Odchylenie/size").toInt();
        settings->beginReadArray("Odchylenie");
        for(int i = 0; i < size; i++ )
        {
            settings->setArrayIndex(i);

            in = settings->value("kolumnaIn").toString();
            out = settings->value("kolumnaOut").toString();

            if(settings->value("dane").toInt() == 2)
            {
                odchylenie(in, out);
            }


        }
        settings->endArray();

    }

}

void Functions::uruchomPrzedParsowaniem()
{
    //----------------------------------------------------------------------
    if(settings->value("Funkcje/polaczPliki").toBool())
    {
        QVector<QString> pliki;
        QString plik, output;

        int size = settings->value("PolaczPliki/size").toInt();
        output = settings->value("PolaczPliki/wyPlik").toString();

        settings->beginReadArray("PolaczPliki");
        for(int i = 0; i < size; i++ )
        {
            settings->setArrayIndex(i);
            plik = settings->value("wePlik").toString();
            pliki.push_back(plik);

        }
        settings->endArray();
        polaczPliki(pliki,output);
        Logger::getInstance()->logguj("Pliki zlaczono do pliku: " + output);
    }

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
void Functions::zapisDoPliku()
{
    QSettings settings("config.ini",QSettings::IniFormat);
    QFile plik(settings.value("Opcje/outputFile").toString());
    if(plik.open(QFile::Append | QFile::Text))
    {
        QTextStream stream(&plik);
        //--------------------- STRUMIENIOWY ZAPIS DO PLIKU ------------------
        stream << obj->naglowek.toString();

        for(int i=0; i< obj->wiersze.size(); i++)
            stream << obj->wiersze[i]->toString() << endl;
        stream << ">end" << endl;
    }
}

void Functions::odchylenie(QString nazwaPolaIn, QString nazwaPolaOut)
{
    double sumaTmp, srednia, wariancja, odchylenie;
    QString num;
    int n = dane.size();

    for(int i=0; i < n; i++)
    {
        sumaTmp+=dane[i];
    }

    srednia = sumaTmp/n;
    //cout << "srednia: " << srednia;

    for(int a=0; a < n; a++)
    {
        wariancja += pow(dane[a] - srednia,2);  //liczymy licznik
    }
    wariancja = wariancja / n; //licznik przez mianownik
    odchylenie = sqrt(wariancja);
    obj->naglowek.wstawPole(nazwaPolaOut,num.number(odchylenie));

    //cout << "\t odchylenie: " << odchylenie << "\n";
    dane.clear();


}

void Functions::polaczPliki(const QVector<QString> inputFiles, QString outputFile)
{
    QFile file(outputFile);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    for(int i=0; i<inputFiles.size(); i++)
    {
        QFile input(inputFiles[i]);

        if(input.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&input);
            while(!in.atEnd())
                out << in.readLine() << endl;
        }
        else
            //qDebug("Nie ma plikow");
            Logger::getInstance()->logguj("Brak niektorych plikow do zlaczenia");
    }
    if(log) Logger::getInstance()->logguj("Wykonano laczenie plikow");
}

bool Functions::filtruj()
{
    int size = settings->value("Filtr/size").toInt();

    QString nazwaPola;
    bool isNumber;
    bool isDate;
    bool isText;
    bool isTime;
    bool wynik = true;

    Pole* pole;
    settings->beginReadArray("Filtr");
    for(int i = 0; i < size; i++ )
    {

        settings->setArrayIndex(i);
        nazwaPola = settings->value("nazwaPola").toString();
        pole = obj->naglowek.getPole(nazwaPola);
        if(pole != NULL)
        {
            pole->getStrWartosc().toDouble(&isNumber);
            if(isNumber)
            {
                settings->value("wiekszeOd").toDouble(&isNumber);

                if(isNumber){

                    if(pole->getStrWartosc().toDouble() > settings->value("wiekszeOd").toDouble())
                    {wynik = wynik & true;}
                    else
                    {wynik = wynik & false;}
                }

                settings->value("mniejszeOd").toDouble(&isNumber);
                if(isNumber)
                {

                    if(pole->getStrWartosc().toDouble() < settings->value("mniejszeOd").toDouble())
                    {wynik = wynik & true;}
                    else
                    {wynik = wynik & false;}
                }

                settings->value("rowne").toDouble(&isNumber);
                if(isNumber)
                {

                    if(pole->getStrWartosc().toDouble() == settings->value("rowne").toDouble())
                    {wynik = wynik & true;}
                    else
                    {wynik = wynik & false;}
                }

                settings->value("wieRowOd").toDouble();
                if(isNumber)
                {

                    if(pole->getStrWartosc().toDouble() >= settings->value("wieRowOd").toDouble())
                    {wynik = wynik & true;}
                    else
                    {wynik = wynik & false;}
                }

                settings->value("mniRowOd").toDouble();
                if(isNumber)
                {

                    if(pole->getStrWartosc().toDouble() <= settings->value("mniRowOd").toDouble())
                    {wynik = wynik & true;}
                    else
                    {wynik = wynik & false;}
                }

            }
        }
        else
            wynik = wynik & false;
    }
    settings->endArray();
    return wynik;

}

