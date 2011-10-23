#-------------------------------------------------
#
# Project created by QtCreator 2011-10-23T23:02:40
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = libraryParser
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    library-pskel.cxx

OTHER_FILES += \
    library.xsd \
    library.xml

HEADERS += \
    library-pskel.hxx
