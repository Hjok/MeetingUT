QT += core \
    testlib
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
    testindividu.cpp \
    groupe.cpp

HEADERS += \
    Groupe.h \
    GroupeManager.h \
    Individu.h \
    Meeting.h \
    Rencontre.h \
    Table.h \
    Tour.h \
    testindividu.h
