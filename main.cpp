#include <QtCore/QCoreApplication>
#include "tjaw.h"
#include "tjawparser.h"
#include <stdio.h>
#include <iostream>
#include <QTime>
using namespace std;

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    QTime t;

    TJAW tjaw;
    //tjaw.createPole(" ","32N0000");
    //tjaw.createPole("az","-90");
    //cout << tjaw.wiersz.echoWiersz().toStdString();
    TjawParser parser("test_q2.dtr");

    t.start();
    parser.Parsuj(&tjaw);
    qDebug("Time elapsed: %d ms", t.elapsed());


    for(int i=0; i< tjaw.wiersze.size(); i++)
    //cout << tjaw.wiersze[i]->echoWiersz().toStdString() << endl;
    cout << "waga: " << tjaw.wiersze.size();

return 0;

    //return a.exec();
}
