#include <QtCore/QCoreApplication>
#include <stdio.h>
#include <iostream>
#include <QTime>
#include "static.h"
#include "tjaw.h"
#include "tjawparser.h"

using namespace std;


int main(int argc, char *argv[])
{
    QTime t;
    TJAW tjaw;
    //TjawParser parser("test_q2.dtr");
    TjawParser parser;

    t.start();
    qDebug("Pracuje...");
    parser.Parsuj(&tjaw);
    qDebug("Skonczylem w : %d ms", t.elapsed());

    cin.get();
    return 0;
}
