#-------------------------------------------------
#
# Project created by QtCreator 2011-02-16T00:15:31
#
#-------------------------------------------------

QT       += core gui sql

TARGET = nagruzka
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    table_editor.cpp \
    settings.cpp \
    curriculum_sqlmodel.cpp

HEADERS  += mainwindow.h \
    table_editor.h \
    connection.h \
    settings.h \
    curriculum_sqlmodel.h

FORMS    += mainwindow.ui \
    settings.ui
