#include "wiersz.h"


Wiersz::Wiersz()
{
}
Wiersz::Wiersz(Pole * pole)
{
    pola.push_back(pole);
}
void Wiersz::erase()
{

    QVector<Pole*>::iterator it;
    for(it=pola.begin(); it!=pola.end();)
    {
        delete (*it);
        it = pola.erase(it);
    }

}

QString Wiersz::echoWiersz()
{
  QString wiersz;
  for(int i=0; i<pola.size(); i++)
  {
      wiersz.append(pola[i]->getNazwa() + "=" + pola[i]->StrWartosc() + " ");
  }
  return wiersz + '\n';
}

void Wiersz::wstawPole(QString nazwa, QString wartosc)
{
    bool isNumber = false;

    double number = 0;
    number = wartosc.toDouble(&isNumber); //funkcja toDouble zwraca przez parametr informacje(bool) o tym czy udalo sie przekonwertowac QStringa na Double
    if(isNumber)
    {
        this->pola.append(new PoleNum(nazwa,number));
        //cout << wartosc.toStdString() << " jest liczba: "<< isNumber << endl;
    }
    else
    {
       this->pola.append(new PoleTxt(nazwa,wartosc));
    }
}
