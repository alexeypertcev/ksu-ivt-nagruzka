/****************************************************************************
** Alexey Pertcev alexey.pertcev@gmail.com
****************************************************************************/

#ifndef CONNECTION_H
#define CONNECTION_H

#define PATH_DB "/home/perec/nagruzka.db"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

QSqlDatabase db;

static bool createConnection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(PATH_DB);
    
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
        query.exec("CREATE TABLE student_on_course ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "speciality_name TEXT NOT NULL, "
                   "course INTEGER NOT NULL, "
                   "CONSTRAINT speciality_name FOREIGN KEY (speciality_name) "
                   " REFERENCES speciality (name))");
        query.exec("CREATE TABLE student_on_group ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "student_on_course_id INTEGER NOT NULL, "
                   "group_ INTEGER NOT NULL, "
                   "undergroup INTEGER NOT NULL, "
                   "quantity INTEGER NOT NULL, "
                   "CONSTRAINT student_on_course_id FOREIGN KEY (student_on_course_id) "
                   " REFERENCES student_on_course (id))");
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
                   "CONSTRAINT subject_name FOREIGN KEY (subject_name) "
                   "  REFERENCES subject (name), "
                   "CONSTRAINT speciality_name FOREIGN KEY (speciality_name) "
                   "  REFERENCES speciality (name))");
        query.exec("CREATE TABLE subjects_in_semmestre ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "student_on_course_id INTEGER NOT NULL, "
                   "curriculum_id INTEGER NOT NULL, "
                   "CONSTRAINT student_on_course_id FOREIGN KEY (student_on_course_id) "
                   "  REFERENCES student_on_course (id), "
                   "CONSTRAINT curriculum_id FOREIGN KEY (curriculum_id) "
                   "  REFERENCES curriculum (id)) ");
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
        query.exec("insert into subject values('PP')");
        query.exec("insert into subject values('OOP')");
        query.exec("insert into subject values('CII')");
        query.exec("insert into speciality values('MOiAIS')");
        query.exec("insert into speciality values('PO')");
        query.exec("insert into status values('default', 0)");
        query.exec("insert into status values('proffessor', 0)");
        query.exec("insert into status values('docent', 0)");
        query.exec("insert into status values('aspirant', 0)");
        query.exec("insert into teachers values(NULL, 'f', 'i', 'o', 'proffessor', 1.0 );");
        query.exec("insert into teachers values(NULL, 'f', 'i', 'o', 'docent',     1.0 );");
        query.exec("insert into teachers values(NULL, 'f', 'i', 'o', 'aspirant',   1.0 );");

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
        query.exec("DROP TABLE speciality");
        query.exec("DROP TABLE subject");
        query.exec("DROP TABLE student_on_course");
        query.exec("DROP TABLE student_on_group");
        query.exec("DROP TABLE status");
        query.exec("DROP TABLE teachers");
        query.exec("DROP TABLE curriculum");
        query.exec("DROP TABLE subjects_in_semmestre");
    }
    return true;
}

#endif
