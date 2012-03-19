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


OdsWriter::OdsWriter(QObject *parent){
    parsed_ods_file = true;
}
OdsWriter::~OdsWriter(){}

bool OdsWriter::open(QString fname){
    QDir dir;
    QString temp;   
    QString templateDir = QDir::currentPath();
    temp = QDir::tempPath();
    tempdir_name = QDir::convertSeparators(QString(temp + "/nagr_temp_%1").arg(QDateTime::currentDateTime().toTime_t())+'/');

/*----------------------------------------------------------------
    qDebug() << "QDir::currentPath(): " << QDir::currentPath();
    qDebug() << "fname: " << fname;
    qDebug() << "templateDir: " << templateDir;
    qDebug() << "temp: " << temp;
    qDebug() << "tempdir_name: " << tempdir_name;
----------------------------------------------------------------*/

    if(!dir.mkdir(tempdir_name))
    {
        //QString::fromUtf8("Невозможно создать временный каталог")
        return false;
    } else {
        // extract from zip
        decompress(fname, tempdir_name);
    }

    QDomDocument opt;
    iFile.setFileName(tempdir_name + "content.xml");
    iFile.open(QFile::ReadOnly);
    domDocument.setContent(&iFile);
    domElement = domDocument.documentElement();

    parsed_ods_file = true;
    QDomNode temp_node;
    int count;
    if(domElement.tagName() == "office:document-content"){
        temp_node = domElement.firstChild();
        count = 0;
        while ((temp_node.toElement().tagName() != "office:body" )){
            temp_node = temp_node.nextSibling();
            ++count;
            if (count == 100){
                parsed_ods_file = false;
                break;
            }
            node_office_body = temp_node;
        }
        if (parsed_ods_file){
            temp_node = node_office_body.toElement().firstChild();
            if (temp_node.toElement().tagName() == "office:spreadsheet"){
                node_office_spreadsheet = temp_node;
                temp_node = node_office_spreadsheet.toElement().firstChild();

                if (temp_node.toElement().tagName() == "table:table"){
                    node_office_first_sheet = temp_node;
                } else {
                    parsed_ods_file = false;
                }
            } else {
                parsed_ods_file = false;
            }
        }
    }

//    qDebug() << "node_office_body: " << node_office_body.toElement().tagName();
//    qDebug() << "node_office_spreadsheet: " << node_office_spreadsheet.toElement().tagName();
//    qDebug() << "node_office_first_sheet: " << node_office_first_sheet.toElement().tagName();

    node_office_current_sheet = node_office_first_sheet;

    return parsed_ods_file;
}


bool OdsWriter::save(QString fname){

    iFile.close();
    oFile.setFileName(tempdir_name + "content.xml");

    oFile.open(QFile::ReadWrite);
    QTextStream out(&oFile);
    out.setCodec( QTextCodec::codecForName("UTF-8") );
    domDocument.save(out, 4);//, QDomNode::EncodingFromTextStream);
    oFile.close();

    compress(fname, tempdir_name);

    removeDir(tempdir_name);

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


bool CardOdsWriter::writeSheet(Tabledata table_data, int i){

    QDomNode temp_node;
    int count = 0;
    temp_node = node_office_first_sheet.firstChild();
   // qDebug() << "writeSheet method: " << node_office_first_sheet.toElement().tagName();
    while ((temp_node.toElement().tagName() != "table:table-row" )){
        temp_node = temp_node.nextSibling();
        ++count;
        if (count == 1000){
            parsed_ods_file = false;
            break;
        }
    }

    if (parsed_ods_file){
        temp_node = temp_node.nextSibling();
        temp_node = temp_node.nextSibling();
        temp_node = temp_node.nextSibling();
        temp_node = temp_node.nextSibling();
        temp_node = temp_node.nextSibling();

        temp_node = temp_node.firstChild();
        temp_node = temp_node.nextSibling();
        temp_node = temp_node.firstChild();

        if (temp_node.toElement().text() == "_ФИО"){
            qDebug() << "set fio";
            temp_node.childNodes().item(0).setNodeValue( table_data.get_header_sheet().at(0) + " " + table_data.get_header_sheet().at(1) + " " + table_data.get_header_sheet().at(2)); // ФИО преподавателя
        }
    }

    setTextToCell(1,1,"test");
    return parsed_ods_file;
}

bool CardOdsWriter::add_sheet(){
    return true;
}
bool CardOdsWriter::remove_old_sheet(){
    return true;
}

bool CardOdsWriter::setTextToCell(unsigned int row, unsigned int collumn, QString text)
{/*0-numering, нумерация с нуля*/
    QDomNode temp_node;
    temp_node = node_office_current_sheet.firstChild();

    int count = 0;
    while ((temp_node.toElement().tagName() != "table:table-row" )){
        temp_node = temp_node.nextSibling();
        ++count;
        if (count == 1000){
            parsed_ods_file = false;
            break;
        }
    }
    /*temp_node = первая строка*/

    for (unsigned int i=0; i<row; ++i){
        if (temp_node.toElement().tagName() == ""){
            /*записи закончились*/
            /*анализировать сколько осталось и создавать новые строки*/
        } else{
            temp_node = temp_node.nextSibling();
        }
    }

    /*temp_node - нужная строка*/
    temp_node = temp_node.firstChild();  /*temp_node первый столбец*/

    for (unsigned int i=0; i<collumn; ++i){
        /*если есть атрибут table:number-columns-repeated увеличить i на его значение*/


    }


   return false;
}
