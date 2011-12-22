#-------------------------------------------------
#
# Project created by QtCreator 2011-11-29T11:45:57
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = tjaw
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    poletxt.cpp \
    polenum.cpp \
    wiersz.cpp \
    tjaw.cpp \
    tjawparser.cpp \
    naglowek.cpp \
    logger.cpp \
    functions.cpp

HEADERS += \
    pole.h \
    poletxt.h \
    polenum.h \
    wiersz.h \
    tjaw.h \
    tjawparser.h \
    naglowek.h \
    logger.h \
    functions.h

OTHER_FILES += \
    ../tjaw-build-desktop/config.ini
