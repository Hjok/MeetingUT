#ifndef TESTINDIVIDU_H
#define TESTINDIVIDU_H

#include <QObject>
#include <QtTest/QtTest>
#include "Individu.h"

class TestIndividu : public QObject
{
    Q_OBJECT
public:
    explicit TestIndividu(QObject *parent = 0);

signals:

public slots:

private slots:
    void nom();
    void id();
    void groupes();
};

#endif // TESTINDIVIDU_H
