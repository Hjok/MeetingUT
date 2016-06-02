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
/*!
 * \brief La classe IndividuEditionGraphique est une popup permettant de créer ou de modifier un individu
 */
class IndividuEditionGraphique : public QDialog
{
    Q_OBJECT

public:
    explicit IndividuEditionGraphique(QWidget *parent = 0);
    ~IndividuEditionGraphique();
    void init(int _id=-1);

private:
    /*! le fichier ui */
    Ui::IndividuEditionGraphique *ui;
    /*! Le composant gérant l'édition du nom du bonhomme */
    QLineEdit* nom;
    /*! La liste des cases à cocher des groupes */
    QList<QCheckBox *> groupes;
    /*! le bouton de validation */
    QPushButton* valider;
    /*! Si la popup est en mode création (ou à défaut en modification) */
    bool creation;
    /*! Un pointeur vers l'individu qui est en cours de modification */
    Individu * personne;
private slots:
    void validation();
};

#endif // INDIVIDUEDITIONGRAPHIQUE_H
