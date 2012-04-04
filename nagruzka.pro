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
    delegates.cpp \
    components.cpp \
    workzip.cpp \
    workzip/zip.cpp \
    workzip/unzip.cpp \
    workzip/zipglobal.cpp \
    teachers_list.cpp \
    report_writter_ods.cpp \
    report_tabledates.cpp \
    tab_curriculum.cpp \
    tab_distribution.cpp \
    tab_subject.cpp \
    tab_subjectinsemester.cpp \
    tab_teachers.cpp \
    tab_students.cpp \
    tab_reports.cpp


HEADERS  += mainwindow.h \
    connection.h \
    settings.h \
    delegates.h \
    components.h \
    workzip/zip.h \
    workzip/zip_p.h \
    workzip/unzip.h \
    workzip/unzip_p.h \
    workzip/zipentry_p.h \
    workzip/zipglobal.h \
    workzip/zlib/zlib.h \
    workzip/zlib/zconf.h \
    teachers_list.h \
    report_writter_ods.h \
    report_tabledates.h \
    tab_reports.h \
    tab_teachers.h \
    tab_subjectinsemester.h \
    tab_subject.h \
    tab_students.h \
    tab_distribution.h \
    tab_curriculum.h


FORMS    += mainwindow.ui \
    settings.ui \
    teachers_list.ui


