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

QString Wiersz::toString()
{
  QString wiersz;
  for(int i=0; i<pola.size(); i++)
  {
      if(!pola.at(i)->getNazwa().isEmpty() && !pola.at(i)->getStrWartosc().isEmpty() )
          wiersz.append(pola.at(i)->getNazwa() + "=" + pola.at(i)->getStrWartosc() + " ");
      else
      if(pola.at(i)->getStrWartosc().isEmpty())
          wiersz.append(pola.at(i)->getNazwa() + " ");
  }
  return wiersz;
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

Pole* Wiersz::getPole(int i)
{
    if(i>=0 && i<pola.size())
    {
        return pola.at(i);
    }
    return NULL;
}

Pole* Wiersz::getPole(QString name)
{
    for(int i=0; i<pola.size(); i++)
    {
        if(pola.at(i)->getNazwa() == name)
        {
            return pola.at(i);
        }
    }
    return NULL;


}






