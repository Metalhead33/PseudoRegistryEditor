#-------------------------------------------------
#
# Project created by QtCreator 2016-12-26T20:39:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RegistryEditor
TEMPLATE = app

LIBS += -L"/usr/local/lib" -lRegistryStructure

SOURCES += main.cpp\
        MainWindow.cpp \
    ElementContainerItem.cpp

HEADERS  += MainWindow.hpp \
    ElementContainerItem.hpp

FORMS    += MainWindow.ui
