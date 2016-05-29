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

namespace Ui {
class FenetrePrincipale;
}

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT

public:
    explicit FenetrePrincipale(QWidget *parent = 0);
    ~FenetrePrincipale();

private:
    Ui::FenetrePrincipale *ui;
    GroupeGraphique* editionGroupes;
    TableGraphiqueEdition* editionTables;
    IndividuGraphique* editionIndividus;
    QTabWidget* onglets;
    TourEdition* editionTour;
    QComboBox* listeTours;
private slots:
    void enregistrer(QString _chemin=QString());
    void chargerProbleme();
    void choisirCheminSolution();
    void chargerSolution(QString _chemin=QString());
    void changeNombreTours(int _nombreTours);
    void barreOngletClique(int _index);
    void changeBarreStatut(QString _texteStatut);

};

#endif // FENETREPRINCIPALE_H
