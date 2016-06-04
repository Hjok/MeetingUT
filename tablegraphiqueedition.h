#ifndef TABLEGRAPHIQUEEDITION_H
#define TABLEGRAPHIQUEEDITION_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QObject>

namespace Ui {
class TableGraphiqueEdition;
}
/*!
 * \brief La classe TableGraphiqueEdition
 */
class TableGraphiqueEdition : public QWidget
{
    Q_OBJECT

public:
    explicit TableGraphiqueEdition(QWidget *parent = 0);
    ~TableGraphiqueEdition();

private:
    /*! le fichier d'ui */
    Ui::TableGraphiqueEdition *ui;
    /*! Le bouton d'ajout de table */
    QPushButton* ajouterTables;
    /*! Le bouton de suppression */
    QPushButton* supprimerTables;
    /*! Le champs pour la capacité des tables */
    QLineEdit* nombreDePlaces;
    /*! Le champs pour le nombre de tables */
    QLineEdit* nombreDeTables;
    /*! Le menu déroulant des tables existantes */
    QComboBox* listeTables;
private slots:
    void ajouterNouvellesTables();
    void retirerTable();

    void ajoutTable(QString _label, int _id, int _capacite);
    void retraitTable(int _id);

};

#endif // TABLEGRAPHIQUEEDITION_H
