#include <QtXml>
#include <QtCore/QFile>
#include <QSqlQuery>
#include "workzip.cpp"
#include "xlslib_2_3_0/xlslib.h"

bool xml_work(QString path);
int removeFolder(QDir & dir);


bool create_report(QStringList teachers_id_list, QString report_patch, QString type_report){

    QSqlQuery query;
    //query.exec("SELECT f FROM teachers WHERE id = 0;");
    //query.next();








    return true;
}

void create_report_ods(QString applicationDirPath)
{
    QString temp_dir = "temp_002311";
    QString temp_patch = applicationDirPath + "/" + temp_dir;
    QDir d(temp_patch);

    if ( !d.exists()){
        qDebug() << "mkdir";
        d.setPath(applicationDirPath);
        d.mkdir(temp_dir);

        decompress(applicationDirPath + "/template.ods", temp_patch);

        xml_work(temp_patch + "/content.xml");

        //пакует немного криво
        compress("path_output_ods_file", temp_patch);

        d.setPath(applicationDirPath + "/" + temp_dir);
        removeFolder(d);
    }
}

//Функция удаления папки
int removeFolder(QDir & dir)
{
   int res = 0;
   //Получаем список каталогов
   QStringList lstDirs  = dir.entryList(QDir::Dirs  |
                                   QDir::AllDirs |
                                   QDir::NoDotAndDotDot);
   //Получаем список файлов
   QStringList lstFiles = dir.entryList(QDir::Files);
   //Удаляем файлы
   foreach (QString entry, lstFiles)
   {
      QString entryAbsPath = dir.absolutePath() + "/" + entry;
      QFile::remove(entryAbsPath);
   }
   //Для папок делаем рекурсивный вызов
   foreach (QString entry, lstDirs)
   {
      QString entryAbsPath = dir.absolutePath() + "/" + entry;
      QDir temp_dir(entryAbsPath);
      removeFolder(temp_dir);
   }
   //Удаляем обрабатываемую папку
   if (!QDir().rmdir(dir.absolutePath()))
   {
      res = 1;
   }
   return res;
}








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
