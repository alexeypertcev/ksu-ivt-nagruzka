#-------------------------------------------------
#
# Project created by QtCreator 2011-02-16T00:15:31
#
#-------------------------------------------------

QT       += static core gui sql zlib xml

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
    teachers_list.cpp \
    reports_creater.cpp \
    report_writter_ods.cpp \
    report_tabledates.cpp


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
    teachers.h \
    teachers_list.h \
    reports_creater.h \
    report_writter_ods.h \
    report_tabledates.h


FORMS    += mainwindow.ui \
    settings.ui \
    teachers_list.ui


