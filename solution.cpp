#include "Solution.h"

Tour& Solution::obtenirTour(int _numero)
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
QString Solution::obtenirMetaDonneesText()
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
 * obtenirValeur renvoie la valeur de la solution, qui correspond à la somme des valeur des tours
 */
int Solution::obtenirValeur() const
{
    int valeur=0;
    for(int i=0; i<tours.length(); i++)
    {
        valeur += tours[i].obtenirValeur();
    }
    return valeur;
}
