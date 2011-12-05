#include "wiersz.h"


Wiersz::Wiersz()
{
}
void Wiersz::wyczysc()
{
    for(int i=0; i<pola.size(); i++)
    {
        delete pola[i];
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
