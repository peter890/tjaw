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
    TjawParser(QString fileName);
    TjawParser();
    void Parsuj(TJAW*);
    //void wykonajObliczeniaTraj(int* functions[]);
private:
    QVector<QString> linie;
    QString wiersz;
    QString fileName;
};

#endif // TJAWPARSER_H
