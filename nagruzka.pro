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
    settings.cpp \
    curriculum_sqlmodel.cpp \
    delegates.cpp \
    subjectinsemester_sqlmodel.cpp \
    students_sqlmodel.cpp \
    saveidcombobox.cpp

HEADERS  += mainwindow.h \
    connection.h \
    settings.h \
    curriculum_sqlmodel.h \
    delegates.h \
    subjectinsemester_sqlmodel.h \
    students_sqlmodel.h \
    saveidcombobox.h

FORMS    += mainwindow.ui \
    settings.ui
