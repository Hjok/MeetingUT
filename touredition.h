#ifndef TOUREDITION_H
#define TOUREDITION_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class TourEdition;
}
/*!
 * \brief La classe TourEdition permet d'éditer le nombre de tours du problème
 */
class TourEdition : public QWidget
{
    Q_OBJECT

public:
    explicit TourEdition(QWidget *parent = 0);
    ~TourEdition();

private:
    /*! Le fichier ui */
    Ui::TourEdition *ui;
    /*! La ligne d'édition du nombre de tour */
    QLineEdit* nombreDeTours;
    /*! Le bouton de validation */
    QPushButton* validerNombreDeTours;
private slots:
    void changerNombreTours();
    void nombreToursChange(int _nombreTours);
};

#endif // TOUREDITION_H
