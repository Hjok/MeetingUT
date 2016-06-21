#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"
#include "Meeting.h"
#include "GroupeManager.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QAction>
#include <QFileDialog>
#include "visualisation.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    //On commence par charger le fichier ui
    ui->setupUi(this);
    //Et on ajoute un layout pour pouvoir placer nos composants
    ui->centralwidget->setLayout(new QVBoxLayout());

    //Initialisation du composant d'onglets
    onglets = new QTabWidget();
    //Et ajout au layout principal, qu'il occupera seul
    ui->centralwidget->layout()->addWidget(onglets);

        //Création de l'onglet d'édition
        QWidget* edition= new QWidget();
            //Ajout d'un layout
            edition->setLayout(new QVBoxLayout());
            //On ajoute le wiget d'édition à la barre d'onglet
            onglets->addTab(edition, "Édition du problème");

                //Création des composants d'édition
                editionTour = new TourEdition();
                editionGroupes = new GroupeGraphique();
                editionTables = new TableGraphiqueEdition();
                editionIndividus = new IndividuGraphique();

                //Et ajout à l'onglet édition
                edition->layout()->addWidget(editionTour);
                edition->layout()->addWidget(editionIndividus);
                edition->layout()->addWidget(editionTables);
                edition->layout()->addWidget(editionGroupes);

        //Création de l'onglet de visualisation
        QWidget* visualisation= new QWidget();
            //Ajout d'un layout au xidget de visualisation
            visualisation->setLayout(new QVBoxLayout());
            //Et ajout de la visualisation à la barre d'onglet
            onglets->addTab(visualisation, "Solution");

                //Création du composant d'affichage de tour de la solution
                afficheSolution=new Visualisation();
                //Et ajout au layout de visualisation
                visualisation->layout()->addWidget(afficheSolution);



    //Connection des signaux du menu aux slots correspondant, pour le chargement/enregistrement
    //Enregistrement
    connect(this->menuBar()->findChild<QMenu*>("menuFichier")->actions().at(0), SIGNAL(triggered()), this, SLOT(enregistrer()));
    //Chargement d'un problème
    connect(this->menuBar()->findChild<QMenu*>("menuFichier")->actions().at(1), SIGNAL(triggered()), this, SLOT(chargerProbleme()));
    //Chargement d'une solution
    connect(this->menuBar()->findChild<QMenu*>("menuFichier")->actions().at(2), SIGNAL(triggered()), this, SLOT(choisirCheminSolution()));

    //Initialisation de la barre de statuts de la fenêtre, c'est elle qui contiendra les méta-données des solutions
    statusBar()->addWidget(new QLabel("Pas de solution calculée"));
    //Et connexion du signal de changement des métadonnées de la classe d'affichage des tours avec le slot de changement de barre des statuts
    connect(afficheSolution, SIGNAL(metaDonneesChangees(QString)), this, SLOT(changeBarreStatut(QString)));

    //Connection du changement d'onglet avec le slot qui gère la génération du problème
    connect(onglets, SIGNAL(currentChanged(int)), this, SLOT(barreOngletClique(int)));



}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}
/*!
 * Slot d'enregistrement, qui va sauvegarder le problème à l'emplacement chemin
 * Si _chemin n'est pas fourni, il le demande à l'utilisateur
 * Ce slot est utilisé lors du calcul de solution, avec en argument un chemin temporaire
 */
void FenetrePrincipale::enregistrer(QString _chemin)
{
    if(_chemin.isEmpty())
    _chemin = QFileDialog::getSaveFileName(this, tr("Enregistrer"),
                                                  "~/Documents/input.xml",
                                                  tr("XML (*.xml)"));
    //Si l'utilisateur a bien rentré un nom
    if(! _chemin.isEmpty())
    {
        //On crée une instance de parseurXml qui gérera l'enregistrement du meeting actuel
        ParseurXml sauvegarde(Meeting::obtenirInstance());
        sauvegarde.sauveMeeting(_chemin);
    }
}
/*!
 * Slot de chargement du problème, qui va charger un problème sauvegardé en demandant son emplacement à l'utilisateur
 *
 */
void FenetrePrincipale::chargerProbleme()
{
    try{

        QString chemin = QFileDialog::getOpenFileName(this, tr("Ouvrir"),
                                                      "~/Documents/",
                                                      tr("XML (*.xml)"));
        if(!chemin.isEmpty())
        {
            ParseurXml charger(Meeting::obtenirInstance());
            charger.chargeMeeting(chemin);
        }
    }
    catch(int i)
    {
        if(i==0)
        {
            //Le programme n'a pas réussi à ouvrir ou à parser le fichier indiqué
            QMessageBox messageBox;
            messageBox.critical(0,"Erreur","Merci de vérifier vos données");
            messageBox.setFixedSize(500,200);
        }
        if(i==1)
        {
            //Le fichier a été correctement parsé, mais il est incohérent (utilisateurs appartiennent à des groupes inexistants, etc.)
            QMessageBox messageBox;
            messageBox.critical(0,"Erreur","Les données sont incohérentes");
            messageBox.setFixedSize(500,200);
        }
    }
}
/*!
 * Slot qui est appelé lorsque l'utilisateur sélectionne l'option "charger une solution"
 * Il demande le chemin à l'utilisateur et appelle le slot de chargement de solution avec ce chemin
 */
void FenetrePrincipale::choisirCheminSolution()
{
    QString chemin= QFileDialog::getOpenFileName(this, tr("Ouvrir"),
                                                              "~/Documents/",
                                                              tr("XML (*.xml)"));
    if(!chemin.isEmpty())
        chargerSolution(chemin);
}
/*!
 * Le slot permettant de charger une solution
 * Il peut-être appelé par l'utilisateur via choisirCheminSolution ou par le processus de calcul de la solution
 *
 */
void FenetrePrincipale::chargerSolution(QString _chemin)
{
    //Le chemin par défaut est celui qu'utilise le processus de calcul de la solution
    if(_chemin.isEmpty())
        _chemin="/tmp/output.xml";

    //Création de l'instance permettant de charger la solution
    ParseurXml charger(Meeting::obtenirInstance());
    try{
    charger.chargeSolution(_chemin);
    }
    catch(int i)
    {
        if(i==0)
        {
            //Si le fichier est introuvable ou incorect syntaxiquement
            QMessageBox messageBox;
            messageBox.critical(0,"Erreur","Erreur interne du fichier");
            messageBox.setFixedSize(500,200);
        }
        if(i==1)
        {
            //Si la solution n'est pas cohérente avec le problème (appel à des individus ou groupes qui n'existent pas, etc.)
            QMessageBox messageBox;
            messageBox.critical(0,"Erreur","Les données sont incohérentes");
            messageBox.setFixedSize(500,200);
        }
    }
}

/*!
 * Slot appelé au clici sur l'onglet solution, si aucune solution n'existe et que les données du problème
 * ont été fournies, il lance le calcul de la solution.
 */
void FenetrePrincipale::barreOngletClique(int _index)
{
    //Si l'onglet solution a été sélectionné
    if(_index==1)
    {
        //Si on a suffisament de données pour calculer la solution
        if(Meeting::obtenirInstance().obtenirProbleme().problemeComplet())
        {
            //Si la solution n'a pas déjà été calculée
            if(Meeting::obtenirInstance().obtenirSolution().solutionVide())
            {
                QProcess * process = new QProcess(this);
                //On enregistre le problème
                enregistrer("/tmp/input.xml");
                //On connecte la fin du calcul et le chargement de la solution, ainsi à la fin du calcul la solution sera immédiatement lue
                connect(process, SIGNAL(finished(int)), this, SLOT(chargerSolution()));
                //Et on lance le calcul
                process->start("SpeedMeetingSolver /tmp/input.xml /tmp/output.xml");
            }
        }
        //Sinon on revient sur l'onglet d'édition du problème et on lance une erreur
        else
        {
            onglets->setCurrentIndex(0);
            QMessageBox messageBox;
            messageBox.critical(0,"Erreur","Il manque des données pour pouvoir traiter le problème");
            messageBox.setFixedSize(500,200);
        }
    }
}
/*!
 * Slot permettant d'inscrire un texte dans la barre de statut
 */
void FenetrePrincipale::changeBarreStatut(QString _texteStatut)
{
    statusBar()->findChild<QLabel*>()->setText(_texteStatut);
    statusBar()->update();
}
