QT += core \
      xml
QT -= gui

CONFIG += c++11

TARGET = speedMeeting
CONFIG += console
CONFIG -= app_bundle

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
    tour.cpp

HEADERS += \
    Groupe.h \
    GroupeManager.h \
    Individu.h \
    Meeting.h \
    Rencontre.h \
    Table.h \
    Tour.h \
    Solution.h \
    chargeur.h
