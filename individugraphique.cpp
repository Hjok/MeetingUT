#include "individugraphique.h"
#include "ui_individugraphique.h"

IndividuGraphique::IndividuGraphique(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IndividuGraphique)
{
    ui->setupUi(this);
    ajouterIndividu = findChild<QPushButton *>("ajoutIndividu");
    listeIndividus = findChild<QComboBox*>("listeIndividus");
    supprimerIndividu = findChild<QPushButton *>("supprimerIndividu");
    modifierIndividu = findChild<QPushButton *>("modifierIndividu");

    editionIndividu = new IndividuEditionGraphique();
    Meeting& meeting =  Meeting::obtenirInstance();
    connect(&meeting.obtenirProbleme(), SIGNAL(individuCree(QString,int)), this, SLOT(individuAjoute(QString,int)));
    connect(&meeting.obtenirProbleme(), SIGNAL(individuSupprime(int)), this, SLOT(individuSupprime(int)));
    connect(supprimerIndividu, SIGNAL(clicked()), this, SLOT(suppressionIndividu()));
    connect(modifierIndividu, SIGNAL(clicked()), this, SLOT(modificationIndividu()));
    connect(ajouterIndividu, SIGNAL(clicked()), this, SLOT(ajoutIndividu()));

    setMaximumHeight(50);
}

IndividuGraphique::~IndividuGraphique()
{
    delete ui;
}

void IndividuGraphique::suppressionIndividu()
{
    if(!listeIndividus->currentData().isNull())
        Meeting::obtenirInstance().obtenirProbleme().supprimerIndividu(listeIndividus->currentData().toInt());
}
void IndividuGraphique::individuAjoute(QString _name, int _id)
{
    listeIndividus->addItem(_name, _id);
}
void IndividuGraphique::individuSupprime(int _id)
{
    listeIndividus->removeItem(listeIndividus->findData(_id));
}
void IndividuGraphique::ajoutIndividu()
{
    editionIndividu->init();
    editionIndividu->exec();
}
void IndividuGraphique::modificationIndividu()
{
    if(!listeIndividus->currentData().isNull())
    {
        editionIndividu->init(listeIndividus->currentData().toInt());
        editionIndividu->exec();
    }
}
