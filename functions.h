/*****************************************************************************
** "functions.h"                                                            **
**                                                                          **
** OPIS:                                                                    **
** Krótki opis klasy                                                        **
**                                                                          **
** HISTORIA ZMIAN:                                                          **
** 0.01 11/12/10 Pierwsza implementacja klasy                            PK **
** 0.05 11/12/14 Dodano funkcje suma()                                   PS **
** 0.05 11/12/19 Obsluga pliku INI                                       PK **
** 0.05 11/12/22 Dodano funkcje zapisDoPliku()                           PS **                                                                         **
** 0.05 11/12/27 Dodano funkcje odchylenie()                             PK **                                                                         **
**               Dodano funkcje Wyswietl()                               PS **                                                                         **
** 0.05 11/12/29 Dodano przeladowana funkcje zapisDoPliku()              PK **
**               Obsluga filtrowania wynikow                             PK **
** 0.05 12/01/04 Poprawiono krytyczne bledy                              PK **                                                                         **
*****************************************************************************/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "tjaw.h"
#include <QSettings>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include "logger.h"


class Functions
{
public:

    Functions(TJAW* _obj);
    void uruchomFunkcjeDlaTjaw();
    void uruchomFunkcjeDlaPliku();
    void uruchomPrzedParsowaniem();

    void zapisDoPliku(QString nazwaPliku);
    void zapisDoPliku();
    void suma(QString poleWejsciowe, QString poleWyjsciowe);
    double suma(QString poleWejsciowe);
    void odchylenie(QString poleWejsciowe, QString poleWyjsciowe);
    void polaczPliki(const QVector<QString> plikiWejsciowe, QString plikWyjsciowy);
    bool filtruj();

    static void Wyswietl(TJAW* _obj);

protected:
    TJAW* obj_;
    QSettings* ustawienia_;
    QVector<double> dane_;
};

#endif // FUNCTIONS_H
