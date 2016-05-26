#include "individugrahique.h"
#include "ui_individugrahique.h"

individugrahique::individugrahique(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::individugrahique)
{
    ui->setupUi(this);
}

individugrahique::~individugrahique()
{
    delete ui;
}
