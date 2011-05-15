/****************************************************************************
** Alexey Pertcev alexey.pertcev@gmail.com
****************************************************************************/

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

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
        query.exec("CREATE TABLE speciality (name TEXT NOT NULL, "
                   "CONSTRAINT name PRIMARY KEY (name))");
        query.exec("CREATE TABLE subject (name TEXT NOT NULL, "
                   "CONSTRAINT name PRIMARY KEY (name))");
        query.exec("CREATE TABLE students ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "speciality_name TEXT NOT NULL, "
                   "course INTEGER NOT NULL, "
                   "num_group INTEGER NOT NULL, "
                   "num_undergroup INTEGER NOT NULL, "
                   "quantity_course INTEGER NOT NULL, "
                   "CONSTRAINT speciality_name FOREIGN KEY (speciality_name) "
                   "REFERENCES speciality (name))");
        query.exec("CREATE TABLE status ( "
                   "name TEXT NOT NULL, "
                   "hours INTEGER NOT NULL, "
                   "CONSTRAINT name PRIMARY KEY (name))");
        query.exec("CREATE TABLE teachers ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "f TEXT NOT NULL, "
                   "i TEXT NOT NULL, "
                   "o TEXT NOT NULL, "
                   "status_name TEXT NOT NULL, "
                   "rate REAL NOT NULL, "
                   "CONSTRAINT status_name FOREIGN KEY (status_name) "
                   "  REFERENCES status (name)) ");
        query.exec("CREATE TABLE curriculum ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "speciality_name TEXT NOT NULL, "
                   "subject_name TEXT NOT NULL, "
                   "semmestr INTEGER NOT NULL, "
                   "lection_hr INTEGER, "
                   "labs_hr INTEGER, "
                   "practice_hr INTEGER, "
                   "KCP_hr INTEGER, "
                   "is_examen INTEGER, "
                   "is_offset INTEGER, "
                   "is_coursework INTEGER, "
                   "CONSTRAINT subject_name FOREIGN KEY (subject_name) "
                   "  REFERENCES subject (name), "
                   "CONSTRAINT speciality_name FOREIGN KEY (speciality_name) "
                   "  REFERENCES speciality (name))");
        query.exec("CREATE TABLE subjects_in_semmestre ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "students_id INTEGER NOT NULL, "
                   "curriculum_id INTEGER NOT NULL, "
                   "CONSTRAINT students_id FOREIGN KEY (students_id) "
                   "  REFERENCES students (id), "
                   "CONSTRAINT curriculum_id FOREIGN KEY (curriculum_id) "
                   "  REFERENCES curriculum (id)) ");
        query.exec("CREATE TABLE distribution ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "subjects_in_semmestre_id INTEGER NOT NULL, "
                   "teachers_id INTEGER NOT NULL, "
                   "CONSTRAINT subjects_in_semmestre_id FOREIGN KEY (subjects_in_semmestre_id) "
                   "  REFERENCES subjects_in_semmestre (id), "
                   "CONSTRAINT teachers_id FOREIGN KEY (teachers_id) "
                   "  REFERENCES teachers (id))");

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
        query.exec("PRAGMA foreign_keys = ON;");
        query.exec("insert into subject values('ПП')");
        query.exec("insert into subject values('ООП')");
        query.exec("insert into subject values('СИИ')");
        query.exec("insert into speciality values('МОиАИС')");
        query.exec("insert into speciality values('ПО')");
        query.exec("insert into speciality values('Ин.-яз.')");
        query.exec("insert into status values('default', 0)");
        query.exec("insert into status values('профессор', 680)");
        query.exec("insert into status values('доцент', 730)");
        query.exec("insert into status values('ст. преподаватель', 780)");
        query.exec("insert into status values('ассистент', 830)");
        query.exec("insert into teachers values(NULL, 'f', 'i', 'o', 'default', 1.0 );");
        query.exec("insert into teachers values(NULL, 'f', 'i', 'o', 'default',     1.0 );");
        query.exec("insert into teachers values(NULL, 'f', 'i', 'o', 'default',   1.0 );");

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
        query.exec("DROP TABLE subjects_in_semmestre");
        query.exec("DROP TABLE curriculum");
        query.exec("DROP TABLE students");
        query.exec("DROP TABLE teachers");
        query.exec("DROP TABLE speciality");
        query.exec("DROP TABLE subject");
        query.exec("DROP TABLE status");
    }
    return true;
}

#endif
