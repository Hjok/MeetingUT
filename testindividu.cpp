#include "testindividu.h"

TestIndividu::TestIndividu(QObject *parent) : QObject(parent)
{

}

void TestIndividu::nom()
{
    Individu i1("Bauer", "Jack");
    QVERIFY(i1.obtNomComplet() == "Jack Bauer");
    QVERIFY(i1.obtNom() == "Bauer");
    QVERIFY(i1.obtPrenom() == "Jack");
    Individu i2("Bauer", "Jack");
    QVERIFY(i2.obtNomComplet() == "Jack Bauer");
    QVERIFY(i2.obtNom() == "Bauer");
    QVERIFY(i2.obtPrenom() == "Jack");
}

void TestIndividu::id()
{
    Individu i1("B", "1");
    Individu i2("B", "2");
    QVERIFY(i1.obtId()+1 == i2.obtId());
}

void TestIndividu::groupes()
{
    Groupe g1("groupe1");
    Groupe g2("groupe2");
    Groupe g3("groupe3");
    QList<Groupe*> lg;
    Individu i1("B1", "11", lg);
    QVERIFY(i1.obtGroupes().size() == 0);
    i1.ajouterGroupe(&g1);
    lg.append(&g1);
    lg.append(&g2);
    lg.append(&g3);

    QVERIFY(i1.obtGroupes().size() == 1);
    QVERIFY(i1.obtGroupes().first() == &g1);

    Individu i2("B", "2", lg);

    QVERIFY(i2.obtGroupes().size() == 3);
    QVERIFY(i2.obtGroupes().first() == &g1);

    i2.retirerGroupe(&g1);

    QVERIFY(i2.obtGroupes().size() == 2);
    QVERIFY(i2.obtGroupes().first() == &g2);

}
