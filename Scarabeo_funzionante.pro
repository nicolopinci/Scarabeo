#-------------------------------------------------
#
# Project created by QtCreator 2017-01-06T15:09:51
#
#-------------------------------------------------

QT       += core gui
QT       +=concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScarabeoConInterfaccia
TEMPLATE = app


SOURCES += main.cpp\
        finestraprincipale.cpp

HEADERS  += finestraprincipale.h \
    Dizionario.h \
    Globali.h \
    Griglia.h \
    Parole.h \
    Sacchetto.h \
    Turni.h \
    Suggerimenti.h \
    Debug.h

FORMS    += finestraprincipale.ui

CONFIG += c++11

DISTFILES += \
    it_IT.aff \
    it_IT.dic \
    sc_IT.aff \
    Lettere.txt
