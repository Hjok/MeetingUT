#ifndef TOUREDITION_H
#define TOUREDITION_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class TourEdition;
}

class TourEdition : public QWidget
{
    Q_OBJECT

public:
    explicit TourEdition(QWidget *parent = 0);
    ~TourEdition();

private:
    Ui::TourEdition *ui;
    QLineEdit* nombreDeTours;
    QPushButton* validerNombreDeTours;
private slots:
    void changerNombreTours();
    void nombreToursChange(int _nombreTours);
};

#endif // TOUREDITION_H
