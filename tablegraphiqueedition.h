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

class TableGraphiqueEdition : public QWidget
{
    Q_OBJECT

public:
    explicit TableGraphiqueEdition(QWidget *parent = 0);
    ~TableGraphiqueEdition();

private:
    Ui::TableGraphiqueEdition *ui;
    QPushButton* ajouterTables;
    QPushButton* supprimerTables;
    QLineEdit* nombreDePlaces;
    QLineEdit* nombreDeTables;
    QComboBox* listeTables;
private slots:
    void ajouterNouvellesTables();
    void retirerTable();

    void ajoutTable(QString _label, int _id, int _capacite);
    void retraitTable(int _id);

};

#endif // TABLEGRAPHIQUEEDITION_H
