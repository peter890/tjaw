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
    TjawParser parser("test_q2.dtr");

    t.start();
    parser.Parsuj(&tjaw);
    qDebug("Time elapsed: %d ms", t.elapsed());



    cin.get();
    return 0;

    //return a.exec();
}
