#ifndef TJAWPARSER_H
#define TJAWPARSER_H

#include <QVector>
#include <QString>
#include <string>
#include "tjaw.h"
using namespace std;

class TjawParser
{
public:
    TjawParser(QString fileName);
    void Parsuj(TJAW*);
private:
    QVector<QString> linie;
    QString wiersz;
    QString fileName;
};

#endif // TJAWPARSER_H