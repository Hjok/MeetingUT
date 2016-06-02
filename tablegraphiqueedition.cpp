#include "tablegraphiqueedition.h"
#include "ui_tablegraphiqueedition.h"
#include "Meeting.h"
#include <QMessageBox>

TableGraphiqueEdition::TableGraphiqueEdition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableGraphiqueEdition)
{
    ui->setupUi(this);
    nombreDePlaces = findChild<QLineEdit *>("nombreDePlaces");
    nombreDePlaces->setValidator( new QIntValidator(0, 100, this) );
    nombreDeTables = findChild<QLineEdit *>("nombreDeTables");
    nombreDeTables->setValidator( new QIntValidator(0, 100, this) );
    ajouterTables = findChild<QPushButton *>("valideNouvellesTables");
    listeTables = findChild<QComboBox*>("listeTables");
    supprimerTables = findChild<QPushButton *>("supprimerTable");

    Meeting& meeting =  Meeting::obtenirenirInstance();

    connect(ajouterTables, SIGNAL(clicked()), this, SLOT(ajouterNouvellesTables()));
    connect(supprimerTables, SIGNAL(clicked()), this, SLOT(retirerTable()));
    connect(&meeting, SIGNAL(tableCree(QString,int,int)), this, SLOT(ajoutTable(QString,int,int)));
    connect(&meeting, SIGNAL(tableSupprimee(int)), this, SLOT(retraitTable(int)));
    setMaximumHeight(50);
    setMinimumHeight(50);
}

TableGraphiqueEdition::~TableGraphiqueEdition()
{
    delete ui;
}
void TableGraphiqueEdition::ajouterNouvellesTables()
{
    if(!nombreDePlaces->text().isEmpty() && !nombreDeTables->text().isEmpty() && nombreDePlaces->text().toInt() && nombreDeTables->text().toInt())
    {
        Meeting::obtenirenirInstance().ajoutTables(nombreDeTables->text().toInt(),nombreDePlaces->text().toInt());
        nombreDePlaces->setText("places par table");
        nombreDeTables->setText("nombre de tables");
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Erreur","Merci de vérifier vos données");
        messageBox.setFixedSize(500,200);
    }

}
void TableGraphiqueEdition::ajoutTable(QString _label, int _id, int _capacite)
{
    listeTables->addItem(_label + " ("+ QString::number(_capacite) +" places)", _id);
}
void TableGraphiqueEdition::retirerTable()
{
    if(!listeTables->currentData().isNull())
    {
        Meeting::obtenirenirInstance().supprimerTable(listeTables->currentData().toInt());
    }
}
void TableGraphiqueEdition::retraitTable(int _id)
{
    listeTables->removeItem(listeTables->findData(listeTables->currentData()));
}
