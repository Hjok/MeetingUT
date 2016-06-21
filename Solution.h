#ifndef SOLUTION_H
#define SOLUTION_H
#include "QList"
#include "Tour.h"

/*!
 * \brief La classe solution décrit une solution a une instance du problème
 */
class Solution:public QObject
{
    Q_OBJECT
public:
    Solution(){};

    //Gestion des tours
    void ajoutTour(Tour& _tour){tours.append(_tour);};
    Tour &obtenirTour(int _numero);
    int obtenirNumeroNouveauTour(){return tours.length();};
    QString obtenirMetaDonneesText();

    //Gestion des métadonnées
    void definirMetaDonnees(QMap<QString, QString> _metaDonnees){metaDonnees=_metaDonnees;};
    QMap<QString, QString>& obtenirMetaDonnees(){return metaDonnees;};

    int obtenirValeur() const;


    void solutionConstruite();
    bool solutionVide() const{return tours.isEmpty();};


private:
    /*! Liste contenant les tours de la solution */
    QList<Tour> tours;
    /*! Map contenant les données relatives au calcul de la solution */
    QMap<QString, QString> metaDonnees;
signals:
    void solutionCree();
    void solutionSupprimee();
public slots:
    void vider();

};

#endif // SOLUTION_H
