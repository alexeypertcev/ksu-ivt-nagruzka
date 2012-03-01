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
    QDir dir;
    QString temp;
    QString copyName;
    QString templateDir = QDir::currentPath();
    temp = QDir::tempPath();

    copyName = QDir::convertSeparators(QString(temp + "/nagr_temp_%1").arg(QDateTime::currentDateTime().toTime_t())+'/');


    qDebug() << "QDir::currentPath(): " << QDir::currentPath();
    qDebug() << "fname: " << fname;
    qDebug() << "templateDir: " << templateDir;
    qDebug() << "temp: " << temp;
    qDebug() << "copyName: " << copyName;

    if(!dir.mkdir(copyName))
    {
        //QString::fromUtf8("Невозможно создать временный каталог")
        return false;
    }
/*
    QZipReader zip_reader(fname);
    if (zip_reader.exists()) {
        // распаковка архива по указанному пути
        zip_reader.extractAll(copyName);
    }
    */
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
