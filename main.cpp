
#include <Meeting.h>
#include <fenetreprincipale.h>
#include <QApplication>
#include <QTableView>

#include "testindividu.h"
#include <QPushButton>
#include "groupegraphique.h"

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    FenetrePrincipale mw;
    mw.show();


    return a.exec();
}
