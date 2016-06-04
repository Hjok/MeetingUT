#include "tablegraphiqueedition.h"
#include "ui_tablegraphiqueedition.h"
#include "Meeting.h"
#include <QMessageBox>

TableGraphiqueEdition::TableGraphiqueEdition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableGraphiqueEdition)
{
    //Récupération du fichier graphique et des différents composants
    ui->setupUi(this);
    nombreDePlaces = findChild<QLineEdit *>("nombreDePlaces");
    nombreDePlaces->setValidator( new QIntValidator(0, 100, this) );
    nombreDeTables = findChild<QLineEdit *>("nombreDeTables");
    nombreDeTables->setValidator( new QIntValidator(0, 100, this) );
    ajouterTables = findChild<QPushButton *>("valideNouvellesTables");
    listeTables = findChild<QComboBox*>("listeTables");
    supprimerTables = findChild<QPushButton *>("supprimerTable");


    Meeting& meeting =  Meeting::obtenirInstance();
    //Connection des boutons d'ajout et de suppression
    connect(ajouterTables, SIGNAL(clicked()), this, SLOT(ajouterNouvellesTables()));
    connect(supprimerTables, SIGNAL(clicked()), this, SLOT(retirerTable()));

    //Connection des signaux de création du back-office, afin de mettre à jour la liste des tables
    connect(&meeting.obtenirProbleme(), SIGNAL(tableCree(QString,int,int)), this, SLOT(ajoutTable(QString,int,int)));
    connect(&meeting.obtenirProbleme(), SIGNAL(tableSupprimee(int)), this, SLOT(retraitTable(int)));

    //Réglage de la taille maximum
    setMaximumHeight(50);
}

TableGraphiqueEdition::~TableGraphiqueEdition()
{
    delete ui;
}
/*!
 * \brief TableGraphiqueEdition::ajouterNouvellesTables ajoute des nouvelles tables. Appelé lorsque l'utilisateur clique sur le bouton d'ajout
 */
void TableGraphiqueEdition::ajouterNouvellesTables()
{
    //Si on a toutes les données nécessaires
    if(!nombreDePlaces->text().isEmpty() && !nombreDeTables->text().isEmpty() && nombreDePlaces->text().toInt() && nombreDeTables->text().toInt())
    {
        //On ajoute les nouvelles tables
        Meeting::obtenirInstance().obtenirProbleme().ajoutTables(nombreDeTables->text().toInt(),nombreDePlaces->text().toInt());
        nombreDePlaces->setText("places par table");
        nombreDeTables->setText("nombre de tables");
        //La liste des tables sera mises à jour par le signal lancé par la classe instance
    }
    else
    {
        //Sinon on signale à l'utilisateur qu'il maque des choses
        QMessageBox messageBox;
        messageBox.critical(0,"Erreur","Merci de vérifier vos données");
        messageBox.setFixedSize(500,200);
    }

}
/*!
 * \brief TableGraphiqueEdition::ajoutTable permet de mettre la liste des tables à jour suite à un ajout
 * Est appelé lorsque la classe instance envoie un signal de création
 * \param _label
 * \param _id
 * \param _capacite
 */
void TableGraphiqueEdition::ajoutTable(QString _label, int _id, int _capacite)
{
    //On se sert du label et de la capacité pour créer le tecte à afficher et on met l'id dans la case "data" pour accèder facilement aux items de la liste
    listeTables->addItem(_label + " ("+ QString::number(_capacite) +" places)", _id);
}
/*!
 * \brief TableGraphiqueEdition::retirerTable permet de supprimer une table
 * Est appellé lorsque l'utilisateur clique sur le bouton de suppression
 */
void TableGraphiqueEdition::retirerTable()
{
    //Si une table est sélectionnée dans la liste
    if(!listeTables->currentData().isNull())
    {
        //On la retire du problème
        Meeting::obtenirInstance().obtenirProbleme().supprimerTable(listeTables->currentData().toInt());
    }
    //La mise à jour de la liste sera faite sur le signal de la classe instance
}
/*!
 * \brief TableGraphiqueEdition::retraitTable permet de mettre à jour la liste suite au retrait d'une table
 * Est appellée lorsque instance envoie un signal de supprssion
 * \param _id l'id de la table à supprimer
 */
void TableGraphiqueEdition::retraitTable(int _id)
{
    listeTables->removeItem(listeTables->findData(listeTables->currentData()));
}
