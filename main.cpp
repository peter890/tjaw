#include <QtCore/QCoreApplication>
#include "tjaw.h"
#include "tjawparser.h"
#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    cout << "z maina\n";
    TJAW tjaw;
    //tjaw.createPole(" ","32N0000");
    //tjaw.createPole("az","-90");
    //cout << tjaw.wiersz.echoWiersz().toStdString();
    TjawParser parser("test_q2.dtr");
    parser.Parsuj(&tjaw);
    //cout << tjaw.wiersz.echoWiersz().toStdString();



    //return a.exec();
}
