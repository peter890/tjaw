/*****************************************************************************
** "tjawparser.h"                                                           **
**                                                                          **
** OPIS:                                                                    **
** Krótki opis klasy                                                        **
**                                                                          **
** HISTORIA ZMIAN:                                                          **
** 0.1 11/12/05 Zaimplemetowano pierwsze funkcje parsera                 PK **
** 0.2 11/12/06 Optymalizacja pracy parsera                              PK **
** 0.5 11/12/10 Dodano generowanie naglowka trajektorii                  PS **
** 0.55 11/12/19 Dodano obs³uge pliku konfiguracyjnego                   PK **
** 0.7 12/01/07 Znaleziono i poprawiono b³êdy krytyczne              PK, PS **
*****************************************************************************/
#ifndef TJAWPARSER_H
#define TJAWPARSER_H

#include <QVector>
#include <QString>
#include <string>
#include "tjaw.h"
#include "functions.h"

using namespace std;


class TjawParser
{
public:
    TjawParser(QString nazwaPliku_);
    TjawParser();
    void Parsuj(TJAW*);
    //void wykonajObliczeniaTraj(int* functions[]);

private:
    QVector<QString> linie_;
    QString wiersz_;
    QString nazwaPliku_;
};

#endif // TJAWPARSER_H
