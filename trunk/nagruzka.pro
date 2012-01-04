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
    report.cpp \
    xlslib_2_3_0/xlslib/assert_assist.cpp \
    xlslib_2_3_0/xlslib/blank.cpp \
    xlslib_2_3_0/xlslib/boolean.cpp \
    xlslib_2_3_0/xlslib/cbridge.cpp \
    xlslib_2_3_0/xlslib/cell.cpp \
    xlslib_2_3_0/xlslib/colinfo.cpp \
    xlslib_2_3_0/xlslib/colors.cpp \
    xlslib_2_3_0/xlslib/continue.cpp \
    xlslib_2_3_0/xlslib/datast.cpp \
    xlslib_2_3_0/xlslib/docsumminfo.cpp \
    xlslib_2_3_0/xlslib/err.cpp	\
    xlslib_2_3_0/xlslib/extformat.cpp \
    xlslib_2_3_0/xlslib/font.cpp \
    xlslib_2_3_0/xlslib/format.cpp \
    xlslib_2_3_0/xlslib/formula.cpp \
    xlslib_2_3_0/xlslib/globalrec.cpp \
    xlslib_2_3_0/xlslib/HPSF.cpp \
    xlslib_2_3_0/xlslib/index.cpp \
    xlslib_2_3_0/xlslib/label.cpp \
    xlslib_2_3_0/xlslib/merged.cpp \
    xlslib_2_3_0/xlslib/note.cpp \
    xlslib_2_3_0/xlslib/number.cpp \
    xlslib_2_3_0/xlslib/range.cpp \
    xlslib_2_3_0/xlslib/recdef.cpp \
    xlslib_2_3_0/xlslib/record.cpp \
    xlslib_2_3_0/xlslib/row.cpp \
    xlslib_2_3_0/xlslib/sheetrec.cpp \
    xlslib_2_3_0/xlslib/summinfo.cpp \
    xlslib_2_3_0/xlslib/unit.cpp \
    xlslib_2_3_0/xlslib/workbook.cpp \
    xlslib_2_3_0/oledoc/binfile.cpp \
    xlslib_2_3_0/oledoc/oledoc.cpp \
    xlslib_2_3_0/oledoc/olefs.cpp \
    xlslib_2_3_0/oledoc/oleprop.cpp \
    xlslib_2_3_0/common/overnew.cpp


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
    xlslib_2_3_0/xlslib.h \
    xlslib_2_3_0/common/ac-config.linux32.h \
    xlslib_2_3_0/common/overnew.h \
    xlslib_2_3_0/common/xlconfig.h \
    xlslib_2_3_0/common/xlsys.h \
    xlslib_2_3_0/common/stringtok.h \
    xlslib_2_3_0/common/systype.h \
    xlslib_2_3_0/common/timespan.h \
    xlslib_2_3_0/common/xls_poppack.h \
    xlslib_2_3_0/common/xls_pshpack1.h \
    xlslib_2_3_0/common/xls_pshpack2.h \
    xlslib_2_3_0/common/xls_pshpack4.h \
    xlslib_2_3_0/common/xlstypes.h \
    xlslib_2_3_0/oledoc/binfile.h \
    xlslib_2_3_0/oledoc/oledoc.h \
    xlslib_2_3_0/oledoc/olefs.h \
    xlslib_2_3_0/oledoc/oleprop.h \
    xlslib_2_3_0/xlslib/biffsection.h \
    xlslib_2_3_0/xlslib/blank.h \
    xlslib_2_3_0/xlslib/boolean.h \
    xlslib_2_3_0/xlslib/cell.h \
    xlslib_2_3_0/xlslib/colinfo.h \
    xlslib_2_3_0/xlslib/colors.h \
    xlslib_2_3_0/xlslib/common.h \
    xlslib_2_3_0/xlslib/continue.h \
    xlslib_2_3_0/xlslib/datast.h \
    xlslib_2_3_0/xlslib/docsumminfo.h \
    xlslib_2_3_0/xlslib/err.h \
    xlslib_2_3_0/xlslib/extformat.h \
    xlslib_2_3_0/xlslib/font.h \
    xlslib_2_3_0/xlslib/format.h \
    xlslib_2_3_0/xlslib/formtags.h \
    xlslib_2_3_0/xlslib/formula.h \
    xlslib_2_3_0/xlslib/globalrec.h \
    xlslib_2_3_0/xlslib/HPSF.h \
    xlslib_2_3_0/xlslib/index.h \
    xlslib_2_3_0/xlslib/label.h \
    xlslib_2_3_0/xlslib/merged.h \
    xlslib_2_3_0/xlslib/note.h \
    xlslib_2_3_0/xlslib/number.h \
    xlslib_2_3_0/xlslib/range.h \
    xlslib_2_3_0/xlslib/recdef.h \
    xlslib_2_3_0/xlslib/record.h \
    xlslib_2_3_0/xlslib/rectypes.h\
    xlslib_2_3_0/xlslib/row.h \
    xlslib_2_3_0/xlslib/sheetrec.h \
    xlslib_2_3_0/xlslib/summinfo.h \
    xlslib_2_3_0/xlslib/unit.h \
    xlslib_2_3_0/xlslib/workbook.h \
    xlslib_2_3_0/xlslib/tostr.h


FORMS    += mainwindow.ui \
    settings.ui

CONFIG += link_pkgconfig
PKGCONFIG = xls
