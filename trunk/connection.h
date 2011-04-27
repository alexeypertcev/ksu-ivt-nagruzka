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
        query.exec("CREATE TABLE student_on_course (id INTEGER AUTO_INCREMENT NOT NULL, "
                   "speciality_name TEXT NOT NULL, "
                   "course INTEGER NOT NULL, "
                   "CONSTRAINT id PRIMARY KEY (id), "
                   "CONSTRAINT speciality_name FOREIGN KEY (speciality_name)"
                   "REFERENCES speciality (name))");
        query.exec("CREATE TABLE student_on_group (id INTEGER AUTO_INCREMENT NOT NULL, "
                   "student_on_course_id INTEGER NOT NULL, "
                   "group INTEGER NOT NULL, "
                   "undergroup INTEGER NOT NULL, "
                   "quantity INTEGER NOT NULL, "
                   "CONSTRAINT id PRIMARY KEY (id), "
                   "CONSTRAINT student_on_course_id FOREIGN KEY (student_on_course_id)"
                   "REFERENCES student_on_course (id))");
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

        /*
            query.exec("create table person (id int primary key, "
                       "firstname varchar(20), lastname varchar(20))");
            query.exec("insert into person values(101, 'Danny', 'Young')");
            query.exec("insert into person values(102, 'Christine', 'Holand')");
            query.exec("insert into person values(103, 'Lars', 'Gordon')");
            query.exec("insert into person values(104, 'Roberto', 'Robitaille')");
            query.exec("insert into person values(105, 'Maria', 'Papadopoulos')");

            query.exec("create table offices (id int primary key,"
                                                     "imagefile int,"
                                                     "location varchar(20),"
                                                     "country varchar(20),"
                                                     "description varchar(100))");
            query.exec("insert into offices "
                       "values(0, 0, 'Oslo', 'Norway',"
                       "'Oslo is home to more than 500 000 citizens and has a "
                       "lot to offer.It has been called \"The city with the big "
                       "heart\" and this is a nickname we are happy to live up to.')");
            query.exec("insert into offices "
                       "values(1, 1, 'Brisbane', 'Australia',"
                       "'Brisbane is the capital of Queensland, the Sunshine State, "
                       "where it is beautiful one day, perfect the next.  "
                       "Brisbane is Australia''s 3rd largest city, being home "
                       "to almost 2 million people.')");
            query.exec("insert into offices "
                       "values(2, 2, 'Redwood City', 'US',"
                       "'You find Redwood City in the heart of the Bay Area "
                       "just north of Silicon Valley. The largest nearby city is "
                       "San Jose which is the third largest city in California "
                       "and the 10th largest in the US.')");
            query.exec("insert into offices "
                       "values(3, 3, 'Berlin', 'Germany',"
                       "'Berlin, the capital of Germany is dynamic, cosmopolitan "
                       "and creative, allowing for every kind of lifestyle. "
                       "East meets West in the metropolis at the heart of a "
                       "changing Europe.')");
            query.exec("insert into offices "
                       "values(4, 4, 'Munich', 'Germany',"
                       "'Several technology companies are represented in Munich, "
                       "and the city is often called the \"Bavarian Silicon Valley\". "
                       "The exciting city is also filled with culture, "
                       "art and music. ')");
            query.exec("insert into offices "
                       "values(5, 5, 'Beijing', 'China',"
                       "'Beijing as a capital city has more than 3000 years of "
                       "history. Today the city counts 12 million citizens, and "
                       "is the political, economic and cultural centre of China.')");
                       */
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
}

#endif
