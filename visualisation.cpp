#include "visualisation.h"
#include "Meeting.h"
#include <QTableView>
#include <QListView>
#include "fenetreprincipale.h"

Visualisation::Visualisation(QWidget *parent) : QWidget(parent)
{
    afficher=false;
    setLayout(new QVBoxLayout());

    //Composant affichant la valeur de la solution
    valeurSolution=new QLabel();
    //On limite se taille
    valeurSolution->setMaximumHeight(50);
    //Et on l'ajoute au layout principal
    layout()->addWidget(valeurSolution);

    //Composant de sélection de tours pour la visualisation de la solution
    listeTours=new QComboBox();
    //On limite sa taille pour ne pas qu'il prenne trop de place verticale
    listeTours->setMaximumHeight(50);
    //Et on l'ajoute au layout principal
    layout()->addWidget(listeTours);


    valeurTour= new QLabel();
    layout()->addWidget(valeurTour);


    conteneurTour= new QWidget();
    conteneurTour->setLayout(new QHBoxLayout());

        personnesNonPlacees=NULL;
        rencontres= new QWidget();
        layoutTableaux = new QGridLayout();
        rencontres->setLayout(layoutTableaux);
        conteneurTour->layout()->addWidget(rencontres);

    layout()->addWidget(conteneurTour);

    connect(&Meeting::getInstance(), SIGNAL(solutionCree()), this, SLOT(solutionAffiche()));
    connect(&Meeting::getInstance(), SIGNAL(solutionSupprimee()), this, SLOT(solutionDesactivee()));

    //Connexion de la sélection du menu de sélection de tours avec la composant qui affiche le tour afin de mettre ce dernier à jour
    connect(listeTours, SIGNAL(currentIndexChanged(int)), this, SLOT(tourChange(int)));
}

void Visualisation::solutionAffiche()
{
    if(Meeting::getInstance().obtSolution())
    {
        //On ajuste la valeur de la solution
        valeurSolution->setText("Valeur de la solution : " + QString::number(Meeting::getInstance().obtSolution()->obtValeur()));

        //On initialise le menu de sélection de tours
        for(int i=1; i<= Meeting::getInstance().obtNombreTours(); i++)
        {
            listeTours->addItem("Tour n°" + QString::number(i), i);
        }

        QTableView* tableau;
        for(int i=0; i< Meeting::getInstance().obtSolution()->obtTour(numero).obtNombreRencontre(); i++)
        {
            tableau=new QTableView();
            tableaux.append(tableau);
            layoutTableaux->addWidget(tableau, i/3, i%3);
        }
        //Transform to List View ?
        personnesNonPlacees = new QListView();

        conteneurTour->layout()->addWidget(personnesNonPlacees);
        afficher=true;
        afficheTour();

        emit metaDonneesChangees(Meeting::getInstance().obtSolution()->obtMetaDonneesText());
    }
}
void Visualisation::tourChange(int _numero)
{
    numero=_numero;
    //La vérification sur personnes non placées vérifie que tout est bien initialisé
    if(Meeting::getInstance().obtSolution() && afficher)
        afficheTour();
}
void Visualisation::afficheTour()
{
    //Valeur du tour
    valeurTour->setText("Valeur du tour : " + QString::number(Meeting::getInstance().obtSolution()->obtTour(numero).obtValeur()));

    personnesNonPlacees->setModel(&Meeting::getInstance().obtSolution()->obtTour(numero));
    for(int i=0; i<Meeting::getInstance().obtSolution()->obtTour(numero).obtNombreRencontre(); i++)
    {
        tableaux[i]->setModel(&Meeting::getInstance().obtSolution()->obtTour(numero).obtRencontre(i));
    }
}
void Visualisation::solutionDesactivee()
{
    afficher=false;
    valeurSolution->clear();
    valeurTour->clear();
    listeTours->clear();

    conteneurTour->layout()->removeWidget(personnesNonPlacees);
    delete personnesNonPlacees;
    personnesNonPlacees =NULL;
    for(int i=0; i<tableaux.length(); i++)
    {
        layoutTableaux->removeWidget(tableaux[i]);
    }
    qDeleteAll(tableaux);
    tableaux.clear();
    emit metaDonneesChangees();

}
