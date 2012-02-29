#include "report_writter_ods.h"
#include <QDir>
#include <QDirIterator>
#include <QProcess>
#include <QDateTime>
#include <QDebug>
#include <QTextOStream>
#include <QMessageBox>
#include "workzip.cpp"

reports_writter_ods::reports_writter_ods()
{
}


OdsWriter::OdsWriter(QObject *parent){}
OdsWriter::~OdsWriter(){}

bool OdsWriter::open(QString fname){
    return true;
}
bool OdsWriter::save(QString fname){
    return true;
}
bool OdsWriter::removeDir(QString dirName){

    bool result = true;
    QDir dir(dirName);

    if (dir.exists(dirName)) {
    Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
        if (info.isDir()) {
        result = removeDir(info.absoluteFilePath());
        }
        else {
        result = QFile::remove(info.absoluteFilePath());
        }

        if (!result) {
        return result;
        }
    }
    result = dir.rmdir(dirName);
    }

    return result;
}


CardOdsWriter::CardOdsWriter(QObject *parent){}
CardOdsWriter::~CardOdsWriter(){}
bool CardOdsWriter::writeTable(Tabledata table_data){
    return true;
}
bool CardOdsWriter::add_sheet(){
    return true;
}
bool CardOdsWriter::remove_old_sheet(){
    return true;
}
