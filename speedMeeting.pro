QT += core \
      xml\
      gui\
        testlib

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = speedMeeting
CONFIG += console
CONFIG -= app_bundle

QMAKE_CFLAGS_WARN_ON -= -Wunused-parameter -Wunused -Wextra
QMAKE_CXXFLAGS_WARN_ON -= -Wunused-parameter -Wunused -Wextra
QMAKE_CFLAGS_WARN_OFF += -Wunused-parameter -Wunused -Wextra
QMAKE_CXXFLAGS_WARN_OFF += -Wunused-parameter -Wunused -Wextra

TEMPLATE = app

SOURCES += main.cpp \
    meeting.cpp \
    groupemanager.cpp \
    individu.cpp \
    groupe.cpp \
    chargeur.cpp \
    table.cpp \
    solution.cpp \
    rencontre.cpp \
    tour.cpp \
    matriceinteret.cpp \
    fenetreprincipale.cpp \
    groupegraphique.cpp \
    tablegraphiqueedition.cpp \
    individugraphique.cpp \
    individueditiongraphique.cpp \
    touredition.cpp \
    visualisation.cpp

HEADERS += \
    Groupe.h \
    GroupeManager.h \
    Individu.h \
    Meeting.h \
    Rencontre.h \
    Table.h \
    Tour.h \
    Solution.h \
    chargeur.h \
    matriceinteret.h \
    fenetreprincipale.h \
    groupegraphique.h \
    tablegraphiqueedition.h \
    individugraphique.h \
    individueditiongraphique.h \
    touredition.h \
    visualisation.h

FORMS += \
    fenetreprincipale.ui \
    groupegraphique.ui \
    tablegraphiqueedition.ui \
    individugraphique.ui \
    individueditiongraphique.ui \
    touredition.ui

