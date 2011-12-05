#include "tjawparser.h"
#include <QRegExp>
#include <QFile>
#include<QTextStream>

#include <iostream>
#include <fstream>

using namespace std;
TjawParser::TjawParser(QString fileName)
{
    this->fileName = fileName;
    cout << "fileName: " << fileName.toStdString();
}
void TjawParser::Parsuj(TJAW * tjaw)
{
    //QRegExp rem("\s*:\s*");
    //QRegExp end(">end");
    //rem.setPatternSyntax(QRegExp::FixedString);
    //ifstream plik(fileName.toAscii().data());
    QFile plik(fileName); //uchwyt do pliku
    QTextStream in(&plik); //tworzy strumien na podstawie uchwytu
    if(plik.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!in.atEnd()) // jesli nie koniec pliku
        {
            wiersz = in.readLine(); //czytaj wiersz

            if(wiersz.toStdString().find(":")) //dopisac kolejne mozliwe znaczniki komentarzy
            {

                if(!wiersz.toStdString().find(">end")) //jesli koniec trajektorii
                {
                    cout << "znalazlem koniec trajektorii\n";
                    for(int i=0; i<linie.size(); i++)
                    {
                        QString linia(linie[i]);
                        QString pole_nazwa, pole_wartosc;
                        bool czyToNazwa = true;

                        for(int j=0; j<=linia.size()+1; j++)
                        {
                            if(linia[j] != ' ')
                            {
                                if(linia[j] == '=')
                                    czyToNazwa = false;
                                if(czyToNazwa)
                                    pole_nazwa.append(linia[j]);
                                else
                                {
                                    if(linia[j+1] != ' ')
                                   pole_wartosc.append(linia[j+1]);
                                }

                                if(linia[j+1] == ' ' || j == linia.length())
                                {
                                    cout << "|"<< pole_nazwa.toStdString() << "=[" << pole_wartosc.toStdString() << "]";
                                    tjaw->createPole(pole_nazwa.trimmed(),pole_wartosc.trimmed()); //tworzenie obiektu pole
                                    pole_nazwa.clear(); //czyszczenie zmiennych lokalnych
                                    pole_wartosc.clear();
                                    czyToNazwa = true;
                                }
                            }

                        }
                        cout << endl;

                    }
                }
                else
                    linie.push_back(wiersz);


            }
            else
                cout << "\nkomentarz: " << wiersz.toStdString() << endl;
        }
    }
    cout << "\nSkonczylem parsowac\n";
}

