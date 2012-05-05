/****************************************************************************
** Alexey Pertcev alexey.pertcev@gmail.com
****************************************************************************/

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtGui>
#include <QtSql>
#include "errors.h"

QSqlDatabase db;

static bool createConnection(QString path_db)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path_db);

    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }
    return true;
}

static bool create_all_tables(){

    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    } else{
        QSqlQuery query;
        query.exec("PRAGMA foreign_keys = ON;");
        query.exec("CREATE TABLE form_training ( "
                   "name TEXT NOT NULL, "
                   "CONSTRAINT name PRIMARY KEY (name))");
        query.exec("CREATE TABLE subject ( "
                   "name TEXT NOT NULL, "
                   "CONSTRAINT name PRIMARY KEY (name))");
        query.exec("CREATE TABLE speciality ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "faculty_name TEXT NOT NULL,"
                   "special_name TEXT NOT NULL, "
                   "form_training_name TEXT NOT NULL,"
                   "CONSTRAINT form_training_name FOREIGN KEY (form_training_name) "
                   "REFERENCES form_training (name))");
        query.exec("CREATE TABLE students ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "speciality_id INTEGER NOT NULL, "
                   "course INTEGER NOT NULL, "
                   "num_group INTEGER NOT NULL, "
                   "num_undergroup INTEGER NOT NULL, "
                   "quantity_course INTEGER NOT NULL, "
                   "CONSTRAINT speciality_id FOREIGN KEY (speciality_id) "
                   "REFERENCES speciality (id))");
        query.exec("CREATE TABLE status ( "
                   "name TEXT NOT NULL, "
                   "hours INTEGER NOT NULL, "
                   "CONSTRAINT name PRIMARY KEY (name))");
        query.exec("CREATE TABLE staff ( "
                   "id INTEGER NOT NULL, "
                   "name TEXT NOT NULL, "
                   "CONSTRAINT id PRIMARY KEY (id))");
        query.exec("CREATE TABLE teachers ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "f TEXT NOT NULL, "
                   "i TEXT NOT NULL, "
                   "o TEXT NOT NULL, "
                   "status_name TEXT, "
                   "rate REAL NOT NULL, "
                   "staff_id INTEGER NOT NULL, "
                   "CONSTRAINT staff_id FOREIGN KEY (staff_id) "
                   "  REFERENCES staff (id), "
                   "CONSTRAINT status_name FOREIGN KEY (status_name) "
                   "  REFERENCES status (name)) ");
        query.exec("CREATE TABLE curriculum ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "speciality_id INTEGER NOT NULL, "
                   "subject_name TEXT NOT NULL, "
                   "semmester INTEGER NOT NULL, "
                   "lection_hr INTEGER NOT NULL, "
                   "labs_hr INTEGER NOT NULL, "
                   "practice_hr INTEGER NOT NULL, "
                   "controlwork INTEGER NOT NULL, "
                   "KCP_hr INTEGER NOT NULL, "
                   "is_examen INTEGER NOT NULL, "
                   "is_offset INTEGER NOT NULL, "
                   "is_coursework INTEGER NOT NULL, "
                   "CONSTRAINT subject_name FOREIGN KEY (subject_name) "
                   "  REFERENCES subject (name), "
                   "CONSTRAINT speciality_id FOREIGN KEY (speciality_id) "
                   "  REFERENCES speciality (id))");
        query.exec("CREATE TABLE subjects_in_semmester ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "curriculum_id INTEGER NOT NULL, "
                   "students_id INTEGER NOT NULL, "
                   "lection_hr INTEGER NOT NULL, "
                   "labs_hr INTEGER NOT NULL, "
                   "practice_hr INTEGER NOT NULL, "
                   "individ_hr REAL NOT NULL, "
                   "kontr_rab_hr REAL NOT NULL, "
                   "consultation_hr REAL NOT NULL, "
                   "offset_hr REAL NOT NULL, "
                   "examen_hr REAL NOT NULL, "
                   "coursework_hr REAL NOT NULL, "
                   "diplomwork_hr REAL NOT NULL, "
                   "praktika_hr REAL NOT NULL, "
                   "gak_hr REAL NOT NULL, "
                   "other1 REAL NOT NULL, "
                   "other2 REAL NOT NULL, "
                   "other3 REAL NOT NULL, "
                   "CONSTRAINT students_id FOREIGN KEY (students_id) "
                   "  REFERENCES students (id), "
                   "CONSTRAINT curriculum_id FOREIGN KEY (curriculum_id) "
                   "  REFERENCES curriculum (id)) ");
        query.exec("CREATE TABLE distribution ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "teachers_id INTEGER NOT NULL, "
                   "subjects_in_semmester_id INTEGER NOT NULL, "
                   "lection_hr INTEGER NOT NULL, "
                   "labs_hr INTEGER NOT NULL, "
                   "practice_hr INTEGER NOT NULL, "
                   "individ_hr REAL NOT NULL, "
                   "kontr_rab_hr REAL NOT NULL, "
                   "consultation_hr REAL NOT NULL, "
                   "offset_hr REAL NOT NULL, "
                   "examen_hr REAL NOT NULL, "
                   "coursework_hr REAL NOT NULL, "
                   "diplomwork_hr REAL NOT NULL, "
                   "praktika_hr REAL NOT NULL, "
                   "gak_hr REAL NOT NULL, "
                   "other1 REAL NOT NULL, "
                   "other2 REAL NOT NULL, "
                   "other3 REAL NOT NULL, "
                   "CONSTRAINT subjects_in_semmester_id FOREIGN KEY (subjects_in_semmester_id) "
                   "  REFERENCES subjects_in_semmester (id), "
                   "CONSTRAINT teachers_id FOREIGN KEY (teachers_id) "
                   "  REFERENCES teachers (id))");
        query.exec("CREATE TABLE coefficients ( "
                   "id INTEGER NOT NULL, "
                   "name TEXT NOT NULL, "
                   "value INTEGER NOT NULL, "
                   "CONSTRAINT id PRIMARY KEY (id))");
        query.exec("CREATE TABLE other_data ( "
                   "id INTEGER NOT NULL, "
                   "name TEXT NOT NULL, "
                   "value TEXT NOT NULL, "
                   "CONSTRAINT id PRIMARY KEY (id))");
    }
    return true;
}

static bool insert_main_data()
{

    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    } else{
        QSqlQuery query;

        // main data
        query.exec("PRAGMA foreign_keys = ON;");
        query.exec("insert into form_training values('оч')");
        query.exec("insert into form_training values('оч-заоч')");
        query.exec("insert into form_training values('заоч')");
        query.exec("insert into speciality values(NULL, 'ФИВТ','МОиАИС', 'оч')");
        query.exec("insert into speciality values(NULL, 'ФИВТ','МОиАИС', 'оч-заоч')");
        query.exec("insert into speciality values(NULL, 'ФИВТ','ПО', 'оч')");
        query.exec("insert into speciality values(NULL, 'ФИВТ','ИАЯ', 'оч')");
        query.exec("insert into status values('выберите..', 0)");
        query.exec("insert into status values('профессор', 680)");
        query.exec("insert into status values('доцент', 730)");
        query.exec("insert into status values('ст. препод.', 780)");
        query.exec("insert into status values('ассистент', 830)");
        query.exec("insert into status values('декан', 500)");
        query.exec("insert into status values('зав. кафедрой', 700)");
        query.exec("insert into staff values(0, 'штатный')");
        query.exec("insert into staff values(1, 'внешний совместитель')");
        query.exec("insert into staff values(2, 'внутр.')");
        query.exec("insert into teachers values(0, 'выберите..', ' ', ' ', 'выберите..', 1 , 0);");

        query.exec("insert into coefficients values(1, 'coefficient_lection_hr', 1)");
        query.exec("insert into coefficients values(2, 'coefficient_labs_for_undergroup_hr', 1)");
        query.exec("insert into coefficients values(3, 'coefficient_practice_for_group_hr', 1)");
        query.exec("insert into coefficients values(4, 'coefficient_individ_for_KCR_hr', 1)");
        query.exec("insert into coefficients values(5, 'coefficient_kontr_rab_for_quantitycourse_min', 15)");
        query.exec("insert into coefficients values(6, 'coefficient_offset_for_quantitycourse_min', 15)");
        query.exec("insert into coefficients values(7, 'coefficient_examen_for_quantitycourse_min', 20)");
        query.exec("insert into coefficients values(8, 'coefficient_coursework_for_quantitycourse_hr', 3)");
        query.exec("insert into coefficients values(9, 'coefficient_consultation_ochnui_percent', 5)");
        query.exec("insert into coefficients values(10, 'coefficient_consultation_zaochnui_percent', 15)");
        query.exec("insert into coefficients values(11, 'coefficient_consultation_och_zaoch_percent', 10)");
        query.exec("insert into coefficients values(12, 'coefficient_consultation_add_is_examen_for_group', 2)");


        query.exec("insert into other_data values(1, 'academic_year', '2011/2012')");
        query.exec("insert into other_data values(2, 'name_kafedry_faculty', 'Программного обеспечения и администрирования информационных систем')");
        query.exec("insert into other_data values(3, 'business_base_of_training', 'бюджет')");
        query.exec("insert into other_data values(4, 'vice_rector_on_education_work', 'Захаров В.В.')");

        //from anatoly zhmakin

        query.exec("insert into subject values('Информационные системы')");
        query.exec("insert into subject values('Основы микроэлектроники')");
        query.exec("insert into subject values('Архитектура компьютера')");
        query.exec("insert into subject values('Информационные системы')");
        query.exec("insert into subject values('Компьютерные сети, интернет и мультимедиа технологии')");
        query.exec("insert into subject values('Компьютерное моделирование')");

        query.exec("insert into teachers values(NULL, 'Жмакин', 'Анатолий', 'Петрович', 'зав. кафедрой', 1.2 , 0 );");
        query.exec("insert into teachers values(NULL, 'Лопин', 'Вячеслав', 'Николаевич', 'профессор', 1.0 , 0 );");
        query.exec("insert into teachers values(NULL, 'Бабкин', 'Евгений', 'Александрович', 'профессор', 1.0 , 0 );");
        query.exec("insert into teachers values(NULL, 'Кудинов', 'Виталий', 'Алексеевич', 'профессор', 0.5 , 0 );");

        query.exec("insert into students values(NULL, 1, 1, 1, 2, 25 );");
        query.exec("insert into students values(NULL, 1, 2, 1, 2, 22 );");
        query.exec("insert into students values(NULL, 1, 3, 2, 3, 32 );");
        query.exec("insert into students values(NULL, 1, 4, 2, 3, 28 );");
        query.exec("insert into students values(NULL, 1, 5, 1, 2, 28 );");
        query.exec("insert into students values(NULL, 2, 5, 1, 1, 6 );");
        query.exec("insert into students values(NULL, 2, 6, 1, 1, 8 );");
        query.exec("insert into students values(NULL, 4, 3, 1, 2, 15 );");
        query.exec("insert into students values(NULL, 4, 4, 1, 2, 19 );");
        query.exec("insert into students values(NULL, 4, 5, 1, 2, 21 );");
        query.exec("insert into students values(NULL, 3, 2, 1, 2, 16 );");
        query.exec("insert into students values(NULL, 3, 3, 1, 1, 13 );");
        query.exec("insert into students values(NULL, 3, 4, 1, 2, 16 );");

        query.exec("insert into curriculum values(NULL, 1, 'Информатика',1, 36, 34, 0, 0, 1, 0, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Программирование',1, 36, 30, 0, 2, 0, 0, 1, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Программирование',2, 32, 30, 0, 0, 0, 1, 0, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Введение в системное программирование',2, 20, 18, 0, 0, 0, 0, 1, 0 );");
        query.exec("insert into curriculum values(NULL, 1, 'Программирование',3, 0, 0, 16, 0, 0, 0, 1, 1 );");
        query.exec("insert into curriculum values(NULL, 1, 'Структуры и алгоритмы компьютерной обработки данных',3, 36, 36, 0, 0, 0, 0, 1, 0 );");
     }
    return true;
}

static bool drop_all_tables()
{

    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    } else{
        QSqlQuery query;
        query.exec("DROP TABLE distribution");
        query.exec("DROP TABLE subjects_in_semmester");
        query.exec("DROP TABLE curriculum");
        query.exec("DROP TABLE students");
        query.exec("DROP TABLE teachers");
        query.exec("DROP TABLE speciality");
        query.exec("DROP TABLE subject");
        query.exec("DROP TABLE status");
        query.exec("DROP TABLE form_training");
        query.exec("DROP TABLE staff");
    }
    return true;
}

#endif
