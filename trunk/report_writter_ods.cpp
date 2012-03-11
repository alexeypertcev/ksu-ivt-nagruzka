#include "report_writter_ods.h"
#include <QDir>
#include <QDirIterator>
#include <QProcess>
#include <QDateTime>
#include <QDebug>
#include <QTextOStream>
#include <QMessageBox>
#include <QtXml>
#include "workzip.cpp"

reports_writter_ods::reports_writter_ods()
{
}


OdsWriter::OdsWriter(QObject *parent){}
OdsWriter::~OdsWriter(){}

bool OdsWriter::open(QString fname){
    QDir dir;
    QString temp;   
    QString templateDir = QDir::currentPath();
    temp = QDir::tempPath();
    tempdir_name = QDir::convertSeparators(QString(temp + "/nagr_temp_%1").arg(QDateTime::currentDateTime().toTime_t())+'/');

//----------------------------------------------------------------
    qDebug() << "QDir::currentPath(): " << QDir::currentPath();
    qDebug() << "fname: " << fname;
    qDebug() << "templateDir: " << templateDir;
    qDebug() << "temp: " << temp;
    qDebug() << "tempdir_name: " << tempdir_name;
//----------------------------------------------------------------

    if(!dir.mkdir(tempdir_name))
    {
        //QString::fromUtf8("Невозможно создать временный каталог")
        return false;
    } else {
        // extract from zip
        decompress(fname, tempdir_name);
    }
    return true;
}


bool OdsWriter::save(QString fname){

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

    QDomDocument opt;
    QFile iFile(tempdir_name + "content.xml");
    iFile.open(QFile::ReadOnly);
    opt.setContent(&iFile);

    bool parsed_ok = true;

    QDomElement domElement = opt.documentElement();
    QDomNode node1, node2, node3;
    int count;
    if(domElement.tagName() == "office:document-content"){
            node1 = domElement.firstChild();
            count = 0;
            while ((node1.toElement().tagName() != "office:body" )){
              node1 = node1.nextSibling();
              ++count;
              if (count == 100){
                  parsed_ok = false;
                  break;
              }
            }
            if (parsed_ok){
              node1 = node1.toElement().firstChild();
              node1 = node1.toElement().firstChild();
              node1 = node1.toElement().firstChild();
              count = 0;
              while ((node1.toElement().tagName() != "table:table-row" )){
                node1 = node1.nextSibling();
                ++count;
                if (count == 1000){
                    parsed_ok = false;
                    break;
                }
              }

              if (parsed_ok){
                  node2 = node1.nextSibling();
                  node2 = node2.nextSibling();
                  node2 = node2.nextSibling();
                  node2 = node2.nextSibling();
                  node2 = node2.nextSibling();

                  node3 = node2.firstChild();
                  node3 = node3.nextSibling();
                  node3 = node3.firstChild();
                  qDebug() << node3.toElement().tagName();
                  qDebug() << node3.toElement().text();

                  if (node3.toElement().text() == "_ФИО"){
                      node3.childNodes().item(0).setNodeValue( table_data.get_header_sheet().at(0) + ", " + table_data.get_header_sheet().at(1) + ", " + table_data.get_header_sheet().at(2)); // ФИО преподавателя
                  }
              }


            }
     } else {parsed_ok = false;}

    if (parsed_ok){
     iFile.close();
        QFile oFile(tempdir_name + "content.xml");
        oFile.open(QFile::ReadWrite);
            QTextStream out(&oFile);
            out.setCodec( QTextCodec::codecForName("UTF-8") );
            opt.save(out, 4);//, QDomNode::EncodingFromTextStream);
            oFile.close();
    } else {
        qDebug() << "error template format";
    }





    return true;

    /*
    bool xml_work(QString path){

        bool parsed_ok = true;

        QDomDocument opt;
          QFile iFile(path);
          iFile.open(QFile::ReadOnly);
          opt.setContent(&iFile);

          QDomElement domElement = opt.documentElement();
          QDomNode node1, node2, node3;
          int count;
          if(domElement.tagName() == "office:document-content"){
                  node1 = domElement.firstChild();
                  count = 0;
                  while ((node1.toElement().tagName() != "office:body" )){
                    node1 = node1.nextSibling();
                    ++count;
                    if (count == 100){
                        parsed_ok = false;
                        break;
                    }
                  }
                  if (parsed_ok){
                    node1 = node1.toElement().firstChild();
                    node1 = node1.toElement().firstChild();


                    node1 = node1.toElement().firstChild();
                    count = 0;
                    while ((node1.toElement().tagName() != "table:table-row" )){
                      node1 = node1.nextSibling();
                      ++count;
                      if (count == 1000){
                          parsed_ok = false;
                          break;
                      }
                    }

                    if (parsed_ok){
                        node2 = node1.nextSibling();
                        node2 = node2.nextSibling();
                        node2 = node2.nextSibling();
                        node2 = node2.nextSibling();
                        node2 = node2.nextSibling();

                        node3 = node2.firstChild();
                        node3 = node3.nextSibling();
                        node3 = node3.firstChild();
                        qDebug() << node3.toElement().tagName();
                        qDebug() << node3.toElement().text();

                        if (node3.toElement().text() == "_ФИО"){
                            node3.childNodes().item(0).setNodeValue( "ЛОПИН" ); // ФИО преподавателя
                        }
                    }


                  }

    //              node.childNodes().item(0).setNodeValue( "кирилица" );  office:document-content
    //              qDebug() << node.toElement().text();
    //              node = node.nextSibling();
    //              qDebug() << node.toElement().text();

           } else {parsed_ok = false;}

          if (parsed_ok){
           iFile.close();
              QFile oFile(path);
              oFile.open(QFile::ReadWrite);
                  QTextStream out(&oFile);
                  out.setCodec( QTextCodec::codecForName("UTF-8") );
                  opt.save(out, 4);//, QDomNode::EncodingFromTextStream);
                  oFile.close();
          } else {
              qDebug() << "error template format";
          }
        return true;
    }

    */
}




bool CardOdsWriter::add_sheet(){
    return true;
}
bool CardOdsWriter::remove_old_sheet(){
    return true;
}
