#include "Solution.h"

Tour& Solution::obtTour(int _numero)
{
    int j=0;
    for (QList<Tour>::iterator i = tours.begin(); i != tours.end(); ++i)
    {
        if(j== _numero)
            return *i;
        j++;
    }
    throw 1;
}
QString Solution::obtMetaDonneesText()
{
    QString text=QString();
    for(QMap<QString, QString>::iterator i=metaDonnees.begin(); i!=metaDonnees.end(); ++i)
    {
        text+=i.key() + " : " + i.value();
        if(i.value()!=metaDonnees.last())
            text+=", ";
    }
    return text;
}
/*!
 * obtValeur renvoie la valeur de la solution, qui correspond à la somme des valeur des tours
 */
int Solution::obtValeur() const
{
    int valeur=0;
    for(int i=0; i<tours.length(); i++)
    {
        valeur += tours[i].obtValeur();
    }
    return valeur;
}
