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

    //Label d'affichage de la v aleur du tour
    valeurTour= new QLabel();
    layout()->addWidget(valeurTour);

    //Création du widget contenant l'affichage du tour
    conteneurTour= new QWidget();
    conteneurTour->setLayout(new QHBoxLayout());
        //Comme on ne peut pas supprimer le modèle d'une vue on crée les vues à la demande, et pas à l'initialisation
        personnesNonPlacees=NULL;
        //L'affichage des rencontres
        rencontres= new QWidget();
        layoutTableaux = new QGridLayout();
        rencontres->setLayout(layoutTableaux);
        conteneurTour->layout()->addWidget(rencontres);

    layout()->addWidget(conteneurTour);

    //On écoute les signaux indiquant que la solution a été calculée ou invalidée
    connect(&Meeting::obtenirInstance().obtenirSolution(), SIGNAL(solutionCree()), this, SLOT(solutionAffiche()));
    connect(&Meeting::obtenirInstance().obtenirSolution(), SIGNAL(solutionSupprimee()), this, SLOT(solutionDesactivee()));

    //Connexion de la sélection du menu de sélection de tours avec la composant qui affiche le tour afin de mettre ce dernier à jour
    connect(listeTours, SIGNAL(currentIndexChanged(int)), this, SLOT(tourChange(int)));
}
/*!
 * \brief Visualisation::solutionAffiche appellé après le calcul d'un solution, initialise l'affichage
 */
void Visualisation::solutionAffiche()
{
    //Si la solution existe bien
    if(!Meeting::obtenirInstance().obtenirSolution().solutionVide())
    {
        //On ajuste la valeur de la solution
        valeurSolution->setText("Valeur de la solution : " + QString::number(Meeting::obtenirInstance().obtenirSolution().obtenirValeur()));

        //On initialise le menu de sélection de tours
        for(int i=1; i<= Meeting::obtenirInstance().obtenirProbleme().obtenirNombreTours(); i++)
        {
            listeTours->addItem("Tour n°" + QString::number(i), i);
        }
        //On crée une vue pour chaque table, et on les ajoute
        QTableView* tableau;
        for(int i=0; i< Meeting::obtenirInstance().obtenirSolution().obtenirTour(numero).obtenirNombreRencontre(); i++)
        {
            tableau=new QTableView();
            tableaux.append(tableau);
            layoutTableaux->addWidget(tableau, i/3, i%3);
        }
        //On crée la vue des personnes non placées
        personnesNonPlacees = new QListView();
        //Et on l'ajoute
        conteneurTour->layout()->addWidget(personnesNonPlacees);
        //On indique qu'on est prêt à recevoir des données
        afficher=true;
        //Et on affiche le tour
        afficheTour();
        //On signale que les métadonnées ont changéet on les transmet
        emit metaDonneesChangees(Meeting::obtenirInstance().obtenirSolution().obtenirMetaDonneesText());
    }
}
/*!
 * \brief Visualisation::tourChange appelé lorsque la sélection du tour change
 * Met à jour l'affichage
 * \param _numero le numéro du nouveau tour à afficher
 */
void Visualisation::tourChange(int _numero)
{
    numero=_numero;
    //On vérifie qu'il existe une solution et qu'on est prêt à l'afficher
    if(!Meeting::obtenirInstance().obtenirSolution().solutionVide() && afficher)
        afficheTour();
}
/*!
 * \brief Visualisation::afficheTour alimente les différentes vues en données
 */
void Visualisation::afficheTour()
{
    //Valeur du tour
    valeurTour->setText("Valeur du tour : " + QString::number(Meeting::obtenirInstance().obtenirSolution().obtenirTour(numero).obtenirValeur()));
    //On indique le modèle de la vue des personnes non placées
    personnesNonPlacees->setModel(&Meeting::obtenirInstance().obtenirSolution().obtenirTour(numero));
    //Ainsi que le modèle de chaque vue de table
    for(int i=0; i<Meeting::obtenirInstance().obtenirSolution().obtenirTour(numero).obtenirNombreRencontre(); i++)
    {
        tableaux[i]->setModel(&Meeting::obtenirInstance().obtenirSolution().obtenirTour(numero).obtenirRencontre(i));
    }
}
/*!
 * \brief Visualisation::solutionDesactivee appalé lorsque la solution devient invalide
 * Vide le composant et le marque comme ne pouvant plus recevoir de données
 */
void Visualisation::solutionDesactivee()
{
    //Le composant ne pourra plus afficher
    afficher=false;

    //On vide les laebels et le menu de sélection des tours
    valeurSolution->clear();
    valeurTour->clear();
    listeTours->clear();

    //On supprime la vue des personnes non placées
    conteneurTour->layout()->removeWidget(personnesNonPlacees);
    delete personnesNonPlacees;
    personnesNonPlacees =NULL;

    //On supprime les vues des tables
    for(int i=0; i<tableaux.length(); i++)
    {
        layoutTableaux->removeWidget(tableaux[i]);
    }
    qDeleteAll(tableaux);
    tableaux.clear();
    //Et on signale que les métadonnées sont vides
    emit metaDonneesChangees();

}
