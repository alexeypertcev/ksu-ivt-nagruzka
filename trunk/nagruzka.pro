#-------------------------------------------------
#
# Project created by QtCreator 2011-02-16T00:15:31
#
#-------------------------------------------------

QT       += static core gui sql zlib

TARGET = nagruzka
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp \
    curriculum_sqlmodel.cpp \
    delegates.cpp \
    subjectinsemester_sqlmodel.cpp \
    distribution.cpp \
    components.cpp \
    workzip.cpp \
    workzip/zip.cpp \
    workzip/unzip.cpp \
    workzip/zipglobal.cpp \
    students.cpp \
    teachers.cpp \
    report.cpp

HEADERS  += mainwindow.h \
    connection.h \
    settings.h \
    curriculum_sqlmodel.h \
    delegates.h \
    subjectinsemester_sqlmodel.h \
    distribution.h \
    components.h \
    workzip/zip.h \
    workzip/zip_p.h \
    workzip/unzip.h \
    workzip/unzip_p.h \
    workzip/zipentry_p.h \
    workzip/zipglobal.h \
    workzip/zlib/zlib.h \
    workzip/zlib/zconf.h \
    students.h \
    teachers.h

FORMS    += mainwindow.ui \
    settings.ui
