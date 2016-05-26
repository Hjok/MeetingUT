#ifndef INDIVIDUGRAHIQUE_H
#define INDIVIDUGRAHIQUE_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include "Meeting.h"
#include "individueditiongraphique.h"

namespace Ui {
class IndividuGraphique;
}

class IndividuGraphique : public QWidget
{
    Q_OBJECT

public:
    explicit IndividuGraphique(QWidget *parent = 0);
    ~IndividuGraphique();

private:
    Ui::IndividuGraphique *ui;
    QPushButton* ajouterIndividu;
    QPushButton* modifierIndividu;
    QPushButton* supprimerIndividu;
    QComboBox* listeIndividus;
    IndividuEditionGraphique* editionIndividu;
private slots:
    void suppressionIndividu();
    void individuAjoute(QString _name, int _id);
    void individuSupprime(int _id);
    void modificationIndividu();
    void ajoutIndividu();
};

#endif // INDIVIDUGRAHIQUE_H
