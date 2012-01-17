#include "tjawparser.h"
#include <QRegExp>
#include <QFile>
#include<QTextStream>
#include "logger.h"
#include "tjawparser.h"
#include <iostream>
#include <fstream>

using namespace std;


TjawParser::TjawParser(QString nazwaPliku)
{
    this->nazwaPliku_ = nazwaPliku;
    cout << "fileName: " << nazwaPliku.toStdString() <<endl;
}


TjawParser::TjawParser()
{
    QSettings ustawienia("config.ini",QSettings::IniFormat);
    this->nazwaPliku_ = ustawienia.value("Opcje/plikZrodlowy").toString();
}


void TjawParser::Parsuj(TJAW * tjaw)
{
    Functions funkcje(tjaw);
    funkcje.uruchomPrzedParsowaniem();


    QSettings ustawienia("config.ini",QSettings::IniFormat);
    QFile output(ustawienia.value("Opcje/plikWynikowy").toString());

    if(output.exists())
    {
        output.remove();
    }


    QFile plik(nazwaPliku_); //uchwyt do pliku
    QTextStream in(&plik); //tworzy strumien na podstawie uchwytu

    if(plik.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        Logger::getInstance()->logguj("otworzylem plik: " + nazwaPliku_);
        while(!in.atEnd()) // jesli nie koniec pliku
        {
            wiersz_ = in.readLine().trimmed(); //czytaj wiersz

            if(!wiersz_.isEmpty())
            {
                if(wiersz_.toStdString().find(":")) //dopisac kolejne mozliwe znaczniki komentarzy
                {
                    if(!wiersz_.toStdString().find(">end") || wiersz_.isEmpty() ) //jesli koniec trajektorii
                    {
                        for(int i=0; i<linie_.size(); i++)
                        {
                            tjaw->wiersze_.append(new Wiersz());
                            QString linia(linie_[i]);
                            QString pole_nazwa, pole_wartosc;
                            bool czyToNazwa = true;

                            for(int j=0; j<=linia.size()+1; j++)
                            {
                                if(linia[j] != ' ')
                                {
                                    if(linia[j] == '=')
                                    {
                                        czyToNazwa = false;
                                    }
                                    if(czyToNazwa)
                                    {
                                        pole_nazwa.append(linia[j]);
                                    }
                                    else
                                    {
                                        if(linia[j+1] != ' ' && linia[j+1].toAscii() != 0)
                                        {
                                            pole_wartosc.append(linia[j+1]);
                                        }

                                    }

                                    if(linia[j+1] == ' ' || j == linia.length())
                                    {

                                        if(i == 0)
                                        {
                                            tjaw->naglowek_.wstawPole(pole_nazwa.trimmed(),pole_wartosc.trimmed());
                                        }
                                        else
                                        {
                                            tjaw->wiersze_.at(tjaw->wiersze_.size()-1)->wstawPole(pole_nazwa.trimmed(),pole_wartosc.trimmed()); //tworzenie obiektu pole
                                        }
                                        pole_nazwa.clear(); //czyszczenie zmiennych lokalnych
                                        pole_wartosc.clear();
                                        czyToNazwa = true;
                                    }
                                }
                            }
                        }

                        Logger::getInstance()->logguj("Uruchomiono funkcje dla trajektorii: " + tjaw->naglowek_.toString());
                        funkcje.uruchomFunkcjeDlaTjaw();
                        Logger::getInstance()->logguj("Zakonczone funkcje dla trajektorii");


                        //--------------------- WYSWIETLANIE ------------------
                        //Functions::Wyswietl(tjaw);


                        //return; //tutaj mozemy dzialac na JEDNEJ KONKRETNEJ
                        tjaw->wyczysc();
                        linie_.clear();

                    }
                    else
                    {
                        linie_.push_back(wiersz_);
                    }
                }
            }
        }
    }
    funkcje.uruchomFunkcjeDlaPliku();
    plik.close();
    Logger::getInstance()->logguj( "Zamknieto plik: " + nazwaPliku_);
}

