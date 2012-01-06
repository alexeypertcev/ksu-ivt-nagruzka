#include <QtXml>
#include <QtCore/QFile>
#include <QSqlQuery>
#include "workzip.cpp"
#include "xlslib_2_3_0/xlslib.h"

bool xml_work(QString path);
int removeFolder(QDir & dir);
bool create_report_xls(QStringList teachers_id_list, QString report_patch);


bool create_report(QStringList teachers_id_list, QString report_patch, QString type_report){

    if(type_report == "xls"){
        return create_report_xls(teachers_id_list,report_patch);
    } else if (type_report == "ods"){

    } else {
        return false;
    }
    return true;
}

bool create_report_xls(QStringList teachers_id_list, QString report_patch)
{
    using namespace std;
    using namespace xlslib_core;

    QSqlQuery query;
    QStringList hide;
    hide << "Министерство образования и науки Российской Федерации" <<         /* 0 */
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


    workbook wb;
    for (int i=0; i<teachers_id_list.size(); ++i){
        query.exec("SELECT f FROM teachers WHERE id = " + teachers_id_list.at(i) + ";");
        query.next();

        worksheet* sh = wb.sheet(query.value(0).toString().toStdWString());

        sh->merge(10,0,11,0);
        sh->merge(10,1,11,1);
        sh->merge(10,2,11,2);
        sh->merge(10,3,11,3);
        sh->merge(10,4,11,4);
        sh->merge(10,5,11,5);
        sh->merge(10,6,11,6);
        sh->merge(10,7,11,7);

        sh->merge(10,13,11,13);
        sh->merge(10,14,11,14);
        sh->merge(10,15,11,15);
        sh->merge(10,16,11,16);
        sh->merge(10,17,11,17);
        sh->merge(10,18,11,18);
        sh->merge(10,19,11,19);
        sh->merge(10,20,11,20);

        sh->merge(10,24,11,24);
        sh->merge(10,25,11,25);

        sh->merge(10,8,10,10);
        sh->merge(10,11,10,12);
        sh->merge(10,21,10,23);

        // set column width
        // 0,91 sm
        sh->defaultColwidth(3);
        // 1sm = 1150
        sh->colwidth(0,10300);
        sh->colwidth(24,1470);
        sh->colwidth(25,830);

        //set row height
        sh->defaultRowHeight(13);

        sh->rowheight(10, 25);
        sh->rowheight(11, 81);


        xf_t* xf1 = wb.xformat();
        CGlobalRecords cglobalrecords;
        font_t* font = new font_t(cglobalrecords);
        font->SetName(QString("Times New Roman").toStdString());
        font->SetHeight(8);
        xf1->SetFont(font);



        /*
                font_t(CGlobalRecords& gRecords,
                           unsigned16_t index, const std::string& name,
                           unsigned16_t height, boldness_option_t boldstyle,
                           underline_option_t underline, script_option_t script,
                           color_name_t color, unsigned16_t attributes,
                           unsigned8_t family, unsigned8_t charset);

 typedef enum
 {
         SCRIPT_NONE = 0,
         SCRIPT_SUPER,
         SCRIPT_SUB
 } script_option_t;

 typedef enum
 {
         UNDERLINE_NONE = 0,
         UNDERLINE_SINGLE,
         UNDERLINE_DOUBLE,
         UNDERLINE_SINGLEACC,
         UNDERLINE_DOUBLEACC
 } underline_option_t;

 typedef enum
 {
         BOLDNESS_BOLD = 0,
         BOLDNESS_HALF,
         BOLDNESS_NORMAL,
         BOLDNESS_DOUBLE
 } boldness_option_t;
          */


//        xf1->GetFont()->SetName(QString("Times New Roman").toStdString());
//        xf1->GetFont()->SetHeight(8);
        //xf1->SetFont();

        //cell_t * cell;
        //cell->fontname("Times New Roman");



        sh->label(0,0,hide.at(0).toStdWString(), xf1);
        sh->label(1,0,hide.at(1).toStdWString(), xf1);
        sh->label(2,0,hide.at(2).toStdWString(), xf1);
        sh->label(3,0,hide.at(3).toStdWString(), xf1);

        sh->label(0,24,hide.at(4).toStdWString());
        sh->label(1,24,hide.at(5).toStdWString());
        sh->label(3,24,hide.at(6).toStdWString());

        sh->label(4,0,hide.at(7).toStdWString());
        sh->label(5,0,hide.at(8).toStdWString());
        sh->label(6,0,hide.at(9).toStdWString());
        sh->label(7,0,hide.at(10).toStdWString());
        sh->label(8,0,hide.at(11).toStdWString());

        sh->label(10,0,hide.at(12).toStdWString());
        sh->label(10,1,hide.at(13).toStdWString());
        sh->label(10,2,hide.at(14).toStdWString());
        sh->label(10,3,hide.at(15).toStdWString());
        sh->label(10,4,hide.at(16).toStdWString());
        sh->label(10,5,hide.at(17).toStdWString());
        sh->label(10,6,hide.at(18).toStdWString());
        sh->label(10,7,hide.at(19).toStdWString());

        sh->label(10,8,hide.at(20).toStdWString());

        sh->label(11,8,hide.at(21).toStdWString());
        sh->label(11,9,hide.at(22).toStdWString());
        sh->label(11,10,hide.at(23).toStdWString());

        sh->label(10,11,hide.at(24).toStdWString());

        sh->label(11,11,hide.at(25).toStdWString());
        sh->label(11,11,hide.at(26).toStdWString());

        sh->label(10,13,hide.at(27).toStdWString());
        sh->label(10,14,hide.at(28).toStdWString());
        sh->label(10,15,hide.at(29).toStdWString());
        sh->label(10,16,hide.at(30).toStdWString());
        sh->label(10,17,hide.at(31).toStdWString());
        sh->label(10,18,hide.at(32).toStdWString());
        sh->label(10,19,hide.at(33).toStdWString());
        sh->label(10,20,hide.at(34).toStdWString());
        sh->label(10,21,hide.at(35).toStdWString());

        sh->label(10,24,hide.at(36).toStdWString());
        sh->label(10,25,hide.at(37).toStdWString());


        //sh->









    }
    wb.Dump(report_patch.toStdString());
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
