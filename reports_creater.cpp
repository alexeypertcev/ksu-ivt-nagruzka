#include "reports_creater.h"
#include "workzip.cpp"


bool create_report(QStringList teachers_id_list, QString template_patch, QString report_patch, QString type_report){

    // тут запрос к БД на все данные, подсчет суммарных данных
    QSqlQuery query;

    QList<QStringList> list_one;

    QStringList s;
    s << "a" << "b" <<  "c";
    list_one << s;
    s.clear();
    s << "d" << "e";
    list_one << s;
    qDebug() << list_one;



    if(type_report == "xls"){
        return create_report_xls(teachers_id_list,template_patch, report_patch);
    } else if (type_report == "ods"){
        return create_report_ods(teachers_id_list,template_patch, report_patch);
    } else {
        return false;
    }
    return true;
}

bool create_report_ods(QStringList teachers_id_list, QString template_patch, QString report_patch)
{
    qDebug() << "teachers_id_list: " << teachers_id_list;
    qDebug() << "report_patch: " << report_patch;

    QDir template_patch_qdir(template_patch);
    template_patch_qdir.cdUp();

    qDebug() << template_patch_qdir;


    QString temp_dir = "temp_002311";
    QString temp_patch = template_patch_qdir.absolutePath() + "/" + temp_dir;
    QDir d(temp_patch);

    if ( !d.exists()){
        qDebug() << "mkdir";
        d.setPath(template_patch_qdir.absolutePath());
        d.mkdir(temp_dir);

        //decompress(, temp_patch);

        xml_work(temp_patch + "/content.xml");

        //пакует немного криво
        compress("path_output_ods_file", temp_patch);

        //d.setPath(" " + "/" + temp_dir);
        removeFolder(d);
    }

    return true;
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

bool create_report_xls(QStringList teachers_id_list, QString template_patch, QString report_patch)
{
    QSqlQuery query;
    QStringList head;
    head << "Министерство образования и науки Российской Федерации" <<         /* 0 */
            "Государственное образовательное учреждение" <<
            "высшего профессионального образования" <<
            "Курский государственный университет" <<

            "УТВЕРЖДАЮ" <<                                                      /* 4*/
            "Проректор по научной работе" <<
            "____________________/Худин А.Н." <<

            "                                                              КАРТОЧКА УЧЕБНЫХ ПОРУЧЕНИЙ НА 2010/2011 УЧЕБНЫЙ ГОД (бюджет)" <<

            "Фамилия, имя, отчество преподавателя" <<                           /* 8 */
            "Ученая степень, звание, должность" <<
            "Кафедра, факультет" <<
            "Объем и вид нагрузки" <<

            "Наименование учебной дисциплины или учебных поручений" <<          /* 12 */
            "Факультет" <<
            "Специальность" <<
            "Форма обучения" <<
            "Курс" <<
            "Количество групп" <<
            "Количество подгрупп" <<
            "Количество студентов" <<
            "По учебному плану" <<                   /* 20 */
            "Лекции" <<
            "Семинары и практич. работы" <<
            "Лабораторные работы" <<
            "Рук-во сам. раб" <<                    /* 24 */
            "индивидуальная" <<
            "аудиторная" <<
            "Контрольные работы" <<
            "Консультации" <<
            "Зачеты" <<
            "Экзамены" <<                            /* 30 */
            "Курсовые работы" <<
            "Дипломные работы" <<
            "Практика" <<
            "ГАК" <<
            "Прочие виды работ" <<
            "Итого" <<
            "Примечания" <<

            "Итого за 1-ое полугодие" <<             /* 38 */
            "Итого за 2-ое полугодие" <<
            "Итого за год" <<
            "Декан" <<
            "Зав. кафедрой" <<
            "Преподаватель";                         /* 43 */



    for (int i=0; i<teachers_id_list.size(); ++i){
        query.exec("SELECT f FROM teachers WHERE id = " + teachers_id_list.at(i) + ";");
        query.next();











    }
    //wb.Dump(report_patch.toStdString());
    return true;
}



reports_creater::reports_creater()
{
}
