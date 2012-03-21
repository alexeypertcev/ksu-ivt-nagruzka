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

    QDomNode temp_node, temp_node2;
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
    /*temp_node = первая строка*/

    if (parsed_ods_file){
        temp_node = temp_node.nextSibling(); /* 2я */
        temp_node = temp_node.nextSibling(); /* 3я */
        temp_node = temp_node.nextSibling(); /* 4я */
        temp_node = temp_node.nextSibling(); /* 5я */
        temp_node = temp_node.nextSibling(); /* 6я */

        temp_node2 = temp_node.firstChild();  /*вошли в 1ю ячейку 6й строки*/
        temp_node2 = temp_node2.nextSibling(); /*перешли к 2й ячейке 6й строки*/

        if (temp_node2.firstChild().toElement().text() == "_ФИО"){
            temp_node2.firstChild().childNodes().item(0).setNodeValue( table_data.get_header_sheet().at(0) + " " + table_data.get_header_sheet().at(1) + " " + table_data.get_header_sheet().at(2)); // ФИО преподавателя
        } else {parsed_ods_file = false;}

        temp_node = temp_node.nextSibling(); /* 7я строка*/

        temp_node2 = temp_node.firstChild();  /*вошли в 1ю ячейку 7й строки*/
        temp_node2 = temp_node2.nextSibling(); /*перешли к 2й ячейке 7й строки*/

        if (temp_node2.firstChild().toElement().text() == "_Ученаястепень"){
            temp_node2.firstChild().childNodes().item(0).setNodeValue( table_data.get_header_sheet().at(3));
        } else {parsed_ods_file = false;}

        temp_node = temp_node.nextSibling(); /* 8я строка*/

        temp_node2 = temp_node.firstChild();  /*вошли в 1ю ячейку 8й строки*/
        temp_node2 = temp_node2.nextSibling(); /*перешли к 2й ячейке 8й строки*/

        if (temp_node2.firstChild().toElement().text() == "_Каффакульт"){
            temp_node2.firstChild().childNodes().item(0).setNodeValue( table_data.get_header_sheet().at(4));
        } else {parsed_ods_file = false;}

        temp_node = temp_node.nextSibling(); /* 9я строка*/

        temp_node2 = temp_node.firstChild();  /*вошли в 1ю ячейку 9й строки*/
        temp_node2 = temp_node2.nextSibling(); /*перешли к 2й ячейке 9й строки*/

        if (temp_node2.firstChild().toElement().text() == "_объем"){
            temp_node2.firstChild().childNodes().item(0).setNodeValue( table_data.get_header_sheet().at(5));
        } else {parsed_ods_file = false;}

        temp_node = temp_node.nextSibling(); /* 10я строка*/
        temp_node = temp_node.nextSibling(); /* 11я строка*/
        temp_node = temp_node.nextSibling(); /* 12я строка*/
        temp_node = temp_node.nextSibling(); /* 13я строка*/


    }

    return parsed_ods_file;
}

bool CardOdsWriter::add_sheet(){
    return true;
}
bool CardOdsWriter::remove_old_sheet(){
    return true;
}

bool OdsWriter::prepareCurrentSheet()
{/*Замена всех записей о повторяющихся строках/столбцах повторяющимися строками/столбцами*/
 /*Удаление последних записей о повторяющихся столбцах/строках*/
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
    QString style_name = "ro1";

    while (temp_node.toElement().tagName() != ""){
        if (temp_node.toElement().attribute("table:number-rows-repeated", "none") == "none"){
            /* запись об одной строке*/
            temp_node = temp_node.nextSibling();
        } else {
            /*запись о повторяющихся*/
            if (temp_node.nextSibling().toElement().isNull()){
                /*это последняя запись с повторениями - удаляем атрибут table:number-rows-repeated*/

            } else {
                /*это непоследняя запись с повторениями - добавляем копии*/


            }
        }
    }


    return false;
}

bool OdsWriter::setTextToCell(unsigned int row, unsigned int collumn, QString text)
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
    QString style_name = "ro1";


    for (unsigned int i=0; i<row; ++i){
        if (temp_node.toElement().tagName() == ""){
            /*записи закончились*/
            /*анализировать сколько осталось и создавать новые строки*/
        } else{
            /*запись о строке есть, анализ - одна или несколько повторяющихся*/
            if (temp_node.toElement().attribute("table:number-rows-repeated", "none") == "none"){
                /* запись об одной строке*/
                temp_node = temp_node.nextSibling();
            } else {
                /*запись о повторяющихся*/
                style_name = temp_node.toElement().attribute("table:style-name", "ro1");
                temp_node.toElement().attribute("table:number-rows-repeated", "none").toInt();


            }
        }
    }

    /*temp_node - нужная строка*/
    temp_node = temp_node.firstChild();  /*temp_node первый столбец*/

    for (unsigned int i=0; i<collumn; ++i){
        /*если есть атрибут table:number-columns-repeated увеличить i на его значение*/


    }


   return false;
}
