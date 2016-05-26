#ifndef INDIVIDUEDITIONGRAPHIQUE_H
#define INDIVIDUEDITIONGRAPHIQUE_H

#include <QDialog>
#include <QList>
#include <QLineEdit>
#include <QCheckBox>
#include "Individu.h"

namespace Ui {
class IndividuEditionGraphique;
}

class IndividuEditionGraphique : public QDialog
{
    Q_OBJECT

public:
    explicit IndividuEditionGraphique(QWidget *parent = 0);
    ~IndividuEditionGraphique();
    void init(int _id=-1);

private:
    Ui::IndividuEditionGraphique *ui;
    QLineEdit* nom;
    QList<QCheckBox *> groupes;
    QPushButton* valider;
    bool creation;
    Individu * personne;
private slots:
    void validation();
};

#endif // INDIVIDUEDITIONGRAPHIQUE_H
