#include "functions.h"
#include <math.h>


Functions::Functions(TJAW *_obj)
{
    this->obj_ = _obj;
    this->ustawienia_ = new QSettings("config.ini",QSettings::IniFormat);

}


void Functions::Wyswietl(TJAW *_obj)
{
    cout << _obj->naglowek_.toString().toStdString();

    for(int i=0; i< _obj->wiersze_.size(); i++)
    {
        cout << _obj->wiersze_[i]->toString().toStdString() << endl;
    }
    cout << ">end\n";
}


void Functions::suma(QString poleWejsciowe, QString poleWyjsciowe)
{
    double sum=0;
    QString num;
    Wiersz* wiersz;

    for(int w=0; w < obj_->wiersze_.size(); w++)
    {
        wiersz = obj_->wiersze_.at(w);
        if(wiersz->getPole(poleWejsciowe) != NULL)
        {
            sum += wiersz->getPole(poleWejsciowe)->getStrWartosc().toDouble();
        }
    }

    obj_->naglowek_.wstawPole(poleWyjsciowe,num.number(sum));
    Logger::getInstance()->logguj("Wykonano 'suma' dla pola '"+ poleWejsciowe +"'");
}


double Functions::suma(QString poleWejsciowe)
{
    double sum=0;
    Wiersz* wiersz;

    for(int w=0; w < obj_->wiersze_.size(); w++)
    {
        wiersz = obj_->wiersze_.at(w);
        if(wiersz->getPole(poleWejsciowe) != NULL)
        {
            sum += wiersz->getPole(poleWejsciowe)->getStrWartosc().toDouble();
        }
    }
    return sum;
}


void Functions::uruchomFunkcjeDlaTjaw()
{
    QString in, out;

    //----------------------------------------------------------------------
    if(ustawienia_->value("Funkcje/suma").toBool())
    {
        int size = ustawienia_->value("Suma/liczbaKolumn").toInt();
        ustawienia_->beginReadArray("Suma");

        for(int i = 0; i < size; i++ )
        {
            ustawienia_->setArrayIndex(i);
            in = ustawienia_->value("kolumnaWejsciowa").toString();
            out = ustawienia_->value("kolumnaWyjsciowa").toString();
            //cout << "suma IN: " << in.toStdString() << " || OUT: " << out.toStdString()<< endl;
            this->suma(in,out);
        }
        ustawienia_->endArray();
    }
    //----------------------------------------------------------------------
    if(ustawienia_->value("Funkcje/odchylenieStd").toBool())
    {
        Wiersz* wiersz;
        int size = ustawienia_->value("Odchylenie/liczbaKolumn").toInt();
        ustawienia_->beginReadArray("Odchylenie");

        for(int i = 0; i < size; i++ )
        {
            ustawienia_->setArrayIndex(i);
            in = ustawienia_->value("kolumnaWejsciowa").toString();
            out = ustawienia_->value("kolumnaWyjsciowa").toString();
            /*          ;brak implementacji!!     //2- dla pliku
            if(ustawienia->value("zrodlo").toInt() == 2)
            {
                dane.push_back( (double) this->suma(in));
            }
            if(ustawienia->value("zrodlo").toInt() == 1)
            {*/
            for(int w=0; w < obj_->wiersze_.size(); w++)
            {
                wiersz = obj_->wiersze_.at(w);
                if(wiersz->getPole(in) != NULL)
                {
                    dane_.push_back(wiersz->getPole(in)->getStrWartosc().toDouble());
                }
            }
            odchylenie(in,out);
            //}
        }
        ustawienia_->endArray();
    }

    if(filtruj())this->zapisDoPliku();
}


void Functions::uruchomFunkcjeDlaPliku()
{
    QString in, out;

    if(ustawienia_->value("Funkcje/odchylenieStd").toBool())
    {
        int size = ustawienia_->value("Odchylenie/liczbaKolumn").toInt();
        ustawienia_->beginReadArray("Odchylenie");
        for(int i = 0; i < size; i++ )
        {
            ustawienia_->setArrayIndex(i);

            in = ustawienia_->value("kolumnaWejsciowa").toString();
            out = ustawienia_->value("kolumnaWyjsciowa").toString();

            if(ustawienia_->value("dane").toInt() == 2)
            {
                odchylenie(in, out);
            }
        }
        ustawienia_->endArray();
    }
}


void Functions::uruchomPrzedParsowaniem()
{
    //----------------------------------------------------------------------
    if(ustawienia_->value("Funkcje/polaczPliki").toBool())
    {
        QVector<QString> pliki;
        QString plik, output;

        int size = ustawienia_->value("PolaczPliki/liczbaPlikow").toInt();
        output = ustawienia_->value("PolaczPliki/plikWyjsciowy").toString();

        ustawienia_->beginReadArray("PolaczPliki");
        for(int i = 0; i < size; i++ )
        {
            ustawienia_->setArrayIndex(i);
            plik = ustawienia_->value("plikWejsciowy").toString();
            pliki.push_back(plik);
        }
        ustawienia_->endArray();
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
        stream << obj_->naglowek_.toString();

        for(int i=0; i< obj_->wiersze_.size(); i++)
        {
            stream << obj_->wiersze_[i]->toString() << endl;
        }
        stream << ">end";
    }
}


void Functions::zapisDoPliku()
{
    QSettings ustawienia("config.ini",QSettings::IniFormat);
    QFile plik(ustawienia.value("Opcje/plikWynikowy").toString());
    if(plik.open(QFile::Append | QFile::Text))
    {
        QTextStream stream(&plik);
        //--------------------- STRUMIENIOWY ZAPIS DO PLIKU ------------------
        stream << obj_->naglowek_.toString();

        for(int i=0; i< obj_->wiersze_.size(); i++)
        {
            stream << obj_->wiersze_[i]->toString() << endl;
        }
        stream << ">end" << endl;
    }
}


void Functions::odchylenie(QString poleWejsciowe, QString poleWyjsciowe)
{
    double sumaTmp=0, srednia, wariancja=0, odchylenie;
    QString num;
    int n = dane_.size();

    Logger::getInstance()->logguj("odchylenie");

    for(int i=0; i < n; i++)
    {
        sumaTmp+=dane_[i];
    }

    srednia = sumaTmp/n;

    for(int a=0; a < n; a++)
    {
        wariancja += pow(dane_[a] - srednia,2);  //liczymy licznik
    }

    wariancja = wariancja / n; //licznik przez mianownik
    odchylenie = sqrt(wariancja);
    obj_->naglowek_.wstawPole(poleWyjsciowe,num.number(odchylenie));

    dane_.clear();
}


void Functions::polaczPliki(const QVector<QString> plikiWejsciowe, QString plikWyjsciowy)
{
    QFile file(plikWyjsciowy);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    for(int i=0; i<plikiWejsciowe.size(); i++)
    {
        QFile input(plikiWejsciowe[i]);

        if(input.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&input);
            while(!in.atEnd())
            {
                out << in.readLine() << endl;
            }
        }
        else
            Logger::getInstance()->logguj("Brak niektorych plikow do zlaczenia");
    }
    Logger::getInstance()->logguj("Wykonano laczenie plikow");
}


bool Functions::filtruj()
{
    if(ustawienia_->value("Funkcje/filtrowanie").toBool())
    {
        int size = ustawienia_->value("Filtr/liczbaKolumn").toInt();

        QString nazwaPola;
        Pole* pole;
        bool isNumber;
        bool isDate;
        bool isTime;
        bool wynik = true;

        ustawienia_->beginReadArray("Filtr");

        for(int i = 0; i < size; i++ )
        {
            ustawienia_->setArrayIndex(i);
            nazwaPola = ustawienia_->value("nazwaPola").toString();
            pole = obj_->naglowek_.getPole(nazwaPola);

            if(pole != NULL)
            {
                pole->getStrWartosc().toDouble(&isNumber);

                //==============================================================================================================
                QDate data = QDate::fromString(pole->getStrWartosc().trimmed(),"yyyy/MM/dd");

                if(!data.isNull() && data.isValid())
                {
                    isDate = true;
                }
                else
                {
                    isDate = false;
                }
                //-------------------------------------------------------------------------
                QTime time = QTime::fromString(pole->getStrWartosc().trimmed(),"hh:mm:ss");

                if(!time.isNull() && time.isValid())
                {
                    isTime = true;
                }
                else
                {
                    isTime = false;
                }
                //==============================================================================================================

                if(isNumber)
                {
                    ustawienia_->value("wiekszeOd").toDouble(&isNumber);

                    if(isNumber)
                    {
                        if(pole->getStrWartosc().toDouble() > ustawienia_->value("wiekszeOd").toDouble())
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }

                    ustawienia_->value("mniejszeOd").toDouble(&isNumber);
                    if(isNumber)
                    {
                        if(pole->getStrWartosc().toDouble() < ustawienia_->value("mniejszeOd").toDouble())
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }

                    ustawienia_->value("rowne").toDouble(&isNumber);
                    if(isNumber)
                    {

                        if(pole->getStrWartosc().toDouble() == ustawienia_->value("rowne").toDouble())
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }

                    ustawienia_->value("rozne").toDouble(&isNumber);
                    if(isNumber)
                    {
                        if(pole->getStrWartosc().toDouble() != ustawienia_->value("rozne").toDouble())
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }

                    ustawienia_->value("wieRowOd").toDouble();
                    if(isNumber)
                    {
                        if(pole->getStrWartosc().toDouble() >= ustawienia_->value("wieRowOd").toDouble())
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }

                    ustawienia_->value("mniRowOd").toDouble();
                    if(isNumber)
                    {
                        if(pole->getStrWartosc().toDouble() <= ustawienia_->value("mniRowOd").toDouble())
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }
                }
                //==============================================================================================================

                if(isDate)
                {
                    QDate dataTmp;
                    data = QDate::fromString(pole->getStrWartosc().trimmed(),"yyyy/MM/dd");

                    dataTmp = QDate::fromString(ustawienia_->value("wiekszeOd").toString(),"yyyy/MM/dd");
                    if(!dataTmp.isNull() && dataTmp.isValid())
                    {
                        if(data > dataTmp)
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }

                    dataTmp = QDate::fromString(ustawienia_->value("mniejszeOd").toString(),"yyyy/MM/dd");
                    if(!dataTmp.isNull() && dataTmp.isValid())
                    {
                        if(data < dataTmp)
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }

                    dataTmp = QDate::fromString(ustawienia_->value("rowne").toString(),"yyyy/MM/dd");
                    if(!dataTmp.isNull() && dataTmp.isValid())
                    {
                        if(data == dataTmp)
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }

                    dataTmp = QDate::fromString(ustawienia_->value("rozne").toString(),"yyyy/MM/dd");
                    if(!dataTmp.isNull() && dataTmp.isValid())
                    {
                        if(data != dataTmp)
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }

                    dataTmp = QDate::fromString(ustawienia_->value("wieRowOd").toString(),"yyyy/MM/dd");
                    if(!dataTmp.isNull() && dataTmp.isValid())
                    {
                        if(data >= dataTmp)
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }

                    dataTmp = QDate::fromString(ustawienia_->value("mniRowOd").toString(),"yyyy/MM/dd");
                    if(!dataTmp.isNull() && dataTmp.isValid())
                    {
                        if(data <= dataTmp)
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }
                }
                //==============================================================================================================

                if(isTime)
                {
                    QTime timeTmp;
                    time = QTime::fromString(pole->getStrWartosc().trimmed(),"hh:mm:ss");

                    timeTmp = QTime::fromString(ustawienia_->value("wiekszeOd").toString(),"hh:mm:ss");
                    if(!timeTmp.isNull() && timeTmp.isValid())
                    {

                        if(time > timeTmp)
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }

                    timeTmp = QTime::fromString(ustawienia_->value("mniejszeOd").toString(),"hh:mm:ss");
                    if(!timeTmp.isNull() && timeTmp.isValid())
                    {
                        if(time < timeTmp)
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }

                    timeTmp = QTime::fromString(ustawienia_->value("rowne").toString(),"hh:mm:ss");
                    if(!timeTmp.isNull() && timeTmp.isValid())
                    {
                        if(time == timeTmp)
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }

                    timeTmp = QTime::fromString(ustawienia_->value("rozne").toString(),"hh:mm:ss");
                    if(!timeTmp.isNull() && timeTmp.isValid())
                    {
                        if(time != timeTmp)
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }

                    timeTmp = QTime::fromString(ustawienia_->value("wieRowOd").toString(),"hh:mm:ss");
                    if(!timeTmp.isNull() && timeTmp.isValid())
                    {

                        if(time >= timeTmp)
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }

                    timeTmp = QTime::fromString(ustawienia_->value("mniRowOd").toString(),"hh:mm:ss");
                    if(!timeTmp.isNull() && timeTmp.isValid())
                    {
                        if(time <= timeTmp)
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }
                }
                //==============================================================================================================

                else //String
                {
                    QString string, stringTmp;
                    string = pole->getStrWartosc().trimmed();

                    stringTmp = ustawienia_->value("wiekszeOd").toString();
                    if(!stringTmp.isEmpty())
                    {
                        if(string > stringTmp)
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }

                    stringTmp = ustawienia_->value("mniejszeOd").toString();
                    if(!stringTmp.isEmpty())
                    {
                        if(string < stringTmp)
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }

                    stringTmp = ustawienia_->value("rowne").toString();
                    if(!stringTmp.isEmpty())
                    {
                        if(string == stringTmp)
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }

                    stringTmp = ustawienia_->value("rozne").toString();
                    if(!stringTmp.isEmpty())
                    {
                        if(string > stringTmp)
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }

                    stringTmp = ustawienia_->value("wieRowOd").toString();
                    if(!stringTmp.isEmpty())
                    {
                        if(string >= stringTmp)
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }

                    stringTmp = ustawienia_->value("mniRowOd").toString();
                    if(!stringTmp.isEmpty())
                    {
                        if(string <= stringTmp)
                        {
                            wynik = wynik & true;
                        }
                        else
                        {
                            wynik = wynik & false;
                        }
                    }
                }
            }
            else
                wynik = wynik & false;
        }
        ustawienia_->endArray();
        return wynik;
    }
    return true;
}

