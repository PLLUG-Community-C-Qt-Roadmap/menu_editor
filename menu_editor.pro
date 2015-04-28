#-------------------------------------------------
#
# Project created by QtCreator 2015-04-28T18:21:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = menu_editor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    consoleprintmenuvisitor.cpp \
    composite.cpp \
    menu.cpp \
    menuitem.cpp \
    menuiterator.cpp

HEADERS  += mainwindow.h \
    consoleprintmenuvisitor.h \
    composite.h \
    menu.h \
    menuitem.h \
    menuiterator.h \
    menuvisitor.h

FORMS    += mainwindow.ui
