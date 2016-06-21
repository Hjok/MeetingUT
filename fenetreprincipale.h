#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include "groupegraphique.h"
#include "tablegraphiqueedition.h"
#include "individugraphique.h"
#include <QTabWidget>
#include <chargeur.h>
#include <touredition.h>
#include <QComboBox>
#include <QLabel>
#include <visualisation.h>

namespace Ui {
class FenetrePrincipale;
}
/*!
 * \brief La classe FenetrePrincipale est la classe qui gère la fenêtre principale
 *
 */

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT

public:
    explicit FenetrePrincipale(QWidget *parent = 0);
    ~FenetrePrincipale();

private:
    /*! Le fichier ui décrivant la fenêtre vide et sa barre d'outils */
    Ui::FenetrePrincipale *ui;
    /*! Le composant contenant tout le reste : le widget gérant les onglets */
    QTabWidget* onglets;
    /*! Le composant d'édition des groupes, contenu dans l'onglet d'édition */
    GroupeGraphique* editionGroupes;
    /*! Le composant d'édition des tables, contenu dans l'onglet d'édition */
    TableGraphiqueEdition* editionTables;
    /*! Le composant d'édition des individus, contenu dans l'onglet d'édition */
    IndividuGraphique* editionIndividus;
    /*! Le composant d'édition du nombre de tour, contenu dans l'onglet d'édition */
    TourEdition* editionTour;
    /*! Le composant de visualisation de la solution */
    Visualisation* afficheSolution;
private slots:
    void enregistrer(QString _chemin=QString());
    void chargerProbleme();
    void choisirCheminSolution();
    void chargerSolution(QString _chemin=QString());
    void barreOngletClique(int _index);
    void changeBarreStatut(QString _texteStatut);

};

#endif // FENETREPRINCIPALE_H
