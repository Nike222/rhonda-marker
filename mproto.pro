#-------------------------------------------------
#
# Project created by QtCreator 2011-03-27T16:57:14
#
#-------------------------------------------------

QT       += core gui \
                xmlpatterns \
                xml

TARGET = mproto
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    document/document.cpp \
    ui/filechooseedit.cpp \
    document/framesstore.cpp \
    document/framesmark.cpp \
    document/framesstore_image.cpp \
    document/framesstore_video.cpp \
    ui/stackedwidget.cpp \
    ui/libobjectslist.cpp \
    ui/liblistview.cpp \
    libs/TreeModel/xmlModel.cpp \
    libs/TreeModel/xmlItem.cpp \
    libs/ListModel/listModel.cpp \
    libs/xmllib/xmllibrary.cpp \
    libs/xmllib/xmllibrarygroups.cpp \
    document/recentdocs.cpp \
    ui/libchooseedit.cpp

HEADERS  += mainwindow.hpp \
    document/document.hpp \
    ui/filechooseedit.hpp \
    document/framesstore.hpp \
    document/framesmark.hpp \
    document/framesstore_image.hpp \
    document/framesstore_video.hpp \
    ui/stackedwidget.hpp \
    ui/libobjectslist.h \
    ui/liblistview.h \
    libs/TreeModel/xmlModel.h \
    libs/TreeModel/xmlItem.h \
    libs/ListModel/listModel.h \
    libs/xmllib/xmllibrary.hpp \
    libs/xmllib/xmllibrarygroups.hpp \
    document/recentdocs.h \
    ui/libchooseedit.hpp

FORMS    += mainwindow.ui
