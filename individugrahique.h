#ifndef INDIVIDUGRAHIQUE_H
#define INDIVIDUGRAHIQUE_H

#include <QWidget>

namespace Ui {
class individugrahique;
}

class individugrahique : public QWidget
{
    Q_OBJECT

public:
    explicit individugrahique(QWidget *parent = 0);
    ~individugrahique();

private:
    Ui::individugrahique *ui;
};

#endif // INDIVIDUGRAHIQUE_H
