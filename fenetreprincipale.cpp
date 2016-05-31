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
    ui->setupUi(this);
    ui->centralwidget->setLayout(new QVBoxLayout());

    //Onglets
    onglets = new QTabWidget();

    //Onglet édition
    QWidget* edition= new QWidget();
    edition->setLayout(new QVBoxLayout());
    onglets->addTab(edition, "Édition du problème");
    ui->centralwidget->layout()->addWidget(onglets);

        //Création des composants
        editionTour = new TourEdition();
        editionGroupes = new GroupeGraphique();
        editionTables = new TableGraphiqueEdition();
        editionIndividus = new IndividuGraphique();

        //Et ajout à l'onglet édition
        edition->layout()->addWidget(editionTour);
        edition->layout()->addWidget(editionIndividus);
        edition->layout()->addWidget(editionTables);
        edition->layout()->addWidget(editionGroupes);

    //Onglet Visualisation
    QWidget* visualisation= new QWidget();
    visualisation->setLayout(new QVBoxLayout());
    onglets->addTab(visualisation, "Solution");
    ui->centralwidget->layout()->addWidget(onglets);

        //Composant de sélection de tours pour la visualisation de la solution
        listeTours=new QComboBox();
        listeTours->setMaximumHeight(50);
        changeNombreTours(Meeting::getInstance().obtNombreTours());
        visualisation->layout()->addWidget(listeTours);
        //Composant d'affichage de tour de la solution
        Visualisation* afficheSolution=new Visualisation();
        visualisation->layout()->addWidget(afficheSolution);

        statusBar()->addWidget(new QLabel("Pas de solution calculée"));


    //Connection des signaux au menu, pour le chargement/enregistrement
    connect(this->menuBar()->findChild<QMenu*>("menuFichier")->actions().at(0), SIGNAL(triggered()), this, SLOT(enregistrer()));
    connect(this->menuBar()->findChild<QMenu*>("menuFichier")->actions().at(1), SIGNAL(triggered()), this, SLOT(chargerProbleme()));
    connect(this->menuBar()->findChild<QMenu*>("menuFichier")->actions().at(2), SIGNAL(triggered()), this, SLOT(choisirCheminSolution()));
    connect(afficheSolution, SIGNAL(metaDonneesChangees(QString)), this, SLOT(changeBarreStatut(QString)));


    connect(&Meeting::getInstance(), SIGNAL(modifierTours(int)), this, SLOT(changeNombreTours(int)));
    connect(onglets, SIGNAL(currentChanged(int)), this, SLOT(barreOngletClique(int)));
    connect(listeTours, SIGNAL(currentIndexChanged(int)), afficheSolution, SLOT(tourChange(int)));



}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}
void FenetrePrincipale::enregistrer(QString _chemin)
{
    if(_chemin.isEmpty())
    _chemin = QFileDialog::getSaveFileName(this, tr("Enregistrer"),
                                                  "~/Documents/input.xml",
                                                  tr("XML (*.xml)"));
    parseurXml sauvegarde(Meeting::getInstance());
    sauvegarde.sauveMeeting(_chemin);
}
void FenetrePrincipale::chargerProbleme()
{
    try{
        parseurXml charger(Meeting::getInstance());
        Meeting::getInstance().vider();

        QString chemin = QFileDialog::getOpenFileName(this, tr("Ouvrir"),
                                                      "~/Documents/",
                                                      tr("XML (*.xml)"));
        charger.chargeMeeting(chemin);
    }
    catch(int i)
    {
        if(i==0)
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Erreur","Merci de vérifier vos données");
            messageBox.setFixedSize(500,200);
        }
        if(i==1)
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Erreur","Les données sont incohérentes");
            messageBox.setFixedSize(500,200);
        }
    }
}
void FenetrePrincipale::choisirCheminSolution()
{
    QString _chemin= QFileDialog::getOpenFileName(this, tr("Ouvrir"),
                                                              "~/Documents/",
                                                              tr("XML (*.xml)"));
    chargerSolution(_chemin);
}

void FenetrePrincipale::chargerSolution(QString _chemin)
{
    if(_chemin.isEmpty())
        _chemin="/tmp/output.xml";
    parseurXml charger(Meeting::getInstance());
    try{
    charger.chargeSolution(_chemin);
    }
    catch(int i)
    {
        if(i==0)
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Erreur","Erreur interne du fichier");
            messageBox.setFixedSize(500,200);
        }
        if(i==1)
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Erreur","Les données sont incohérentes");
            messageBox.setFixedSize(500,200);
        }
    }
}

//Slot appellé lorsque le nombre de tours du meeting change
void FenetrePrincipale::changeNombreTours(int _nombreTours)
{
    listeTours->clear();
    for(int i=1; i<= _nombreTours; i++)
    {
        listeTours->addItem("Tour n°" + QString::number(i), i);
    }
}
//Navigation dans les onglet, si on atteint l'onglet solution et qu'il n'existe pas de solution, on lance le calcul
void FenetrePrincipale::barreOngletClique(int _index)
{
    if(_index==1)
    {
        //Si on a suffisament de données pour calculer la solution
        if(Meeting::getInstance().problemeComplet())
        {
            if(Meeting::getInstance().obtSolution()==NULL)
            {
                QProcess * process = new QProcess(this);
                enregistrer("/tmp/input.xml");
                connect(process, SIGNAL(finished(int)), this, SLOT(chargerSolution()));
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
void FenetrePrincipale::changeBarreStatut(QString _texteStatut)
{
    statusBar()->findChild<QLabel*>()->setText(_texteStatut);
    statusBar()->update();
}
