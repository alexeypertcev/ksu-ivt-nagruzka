#include "distribution.h"
#include <QDebug>
#include <QMessageBox>
#include <QtSql>

//********************************************************************************
//  class DistributionSqlModel
//********************************************************************************

DistributionSqlModel::DistributionSqlModel(QObject *parent) :
    QSqlQueryModel(parent)
{
    subjects_in_semmestre_id = '1';
}

Qt::ItemFlags DistributionSqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() > 1 && index.column() < 10 )
    {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

void DistributionSqlModel::setsins(QString id)
{
    subjects_in_semmestre_id = id;
}

void DistributionSqlModel::check_entry()
{
    QSqlQuery query;
    QString s = "SELECT id FROM distribution WHERE distribution.subjects_in_semmester_id = " + subjects_in_semmestre_id + ";";
    query.exec(s);

    if(!query.next()){// not supporting sqlite   if ((query.size() == 0) || (query.size() == -1)){
        QString id,lection_hr,labs_hr,practice_hr,individ_hr,kontr_rab_hr,consultation_hr,
                offset_hr,examen_hr,coursework_hr,diplomwork_hr,praktika_hr,gak_hr,
                other1,other2,other3;
qDebug() << "insert in distrib";
        /* subject_in_semester table
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
        */

        s = "SELECT id,lection_hr,labs_hr,practice_hr,individ_hr,kontr_rab_hr,consultation_hr, "
            " offset_hr,examen_hr,coursework_hr,diplomwork_hr,praktika_hr,gak_hr, "
            " other1,other2,other3 FROM subjects_in_semmester WHERE subjects_in_semmester.id = " + subjects_in_semmestre_id + ";";

        if (!query.exec(s)){
            qDebug() << "error select";
        }
        if (!query.next()){
            qDebug() << "error next";
        }

        id              = query.value(0).toString();
        lection_hr      = query.value(1).toString();
        labs_hr         = query.value(2).toString();
        practice_hr     = query.value(3).toString();
        individ_hr      = query.value(4).toString();
        kontr_rab_hr    = query.value(5).toString();
        consultation_hr = query.value(6).toString();
        offset_hr       = query.value(7).toString();
        examen_hr       = query.value(8).toString();
        coursework_hr   = query.value(9).toString();
        diplomwork_hr   = query.value(10).toString();
        praktika_hr     = query.value(11).toString();
        gak_hr          = query.value(12).toString();
        other1          = query.value(13).toString();
        other2          = query.value(14).toString();
        other3          = query.value(15).toString();

        /* distribution table
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "teachers_id INTEGER, "
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
        */

        s =    "insert into distribution values("
               "NULL, "                             // "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "1, "+                            // "teachers_id INTEGER, "
                subjects_in_semmestre_id + ", "+    // "subjects_in_semmester_id INTEGER NOT NULL, "
                lection_hr + ", "+                  // "lection_hr INTEGER NOT NULL, "
                labs_hr + ", "+                     // "labs_hr INTEGER NOT NULL, "
                practice_hr + ", "+                 // "practice_hr INTEGER NOT NULL, "
                individ_hr + ", "+                  // "individ_hr REAL NOT NULL, "
                kontr_rab_hr + ", "+                // "kontr_rab_hr REAL NOT NULL, "
                consultation_hr + ", "+             // "consultation_hr REAL NOT NULL, "
                offset_hr + ", "+                   // "offset_hr REAL NOT NULL, "
                examen_hr + ", "+                   // "examen_hr REAL NOT NULL, "
                coursework_hr + ", "+               // "coursework_hr REAL NOT NULL, "
                diplomwork_hr + ", "+               // "diplomwork_hr REAL NOT NULL, "
                praktika_hr + ", "+                 // "praktika_hr REAL NOT NULL, "
                gak_hr + ", "+                      // "gak_hr REAL NOT NULL, "
                other1 + ", "+                      // "other1 REAL NOT NULL, "
                other2 + ", "+                      // "other2 REAL NOT NULL, "
                other3 +                            // "other3 REAL NOT NULL, "
                ");";




        if (!query.exec(s)){
            qDebug() << "fail insert to distribution";
        }
    }
}

void DistributionSqlModel::refresh()
{
    QSqlQuery query;
    query.exec("SELECT teachers_id FROM distribution WHERE distribution.subjects_in_semmester_id = " + subjects_in_semmestre_id + ";");
    query.next();

    if (query.isNull(0)){
        this->setQuery("SELECT "
                   "teachers_id, "
                   "subjects_in_semmester_id, "
                   "lection_hr, "
                   "labs_hr, "
                   "practice_hr, "
                   "individ_hr, "
                   "kontr_rab_hr, "
                   "consultation_hr, "
                   "offset_hr, "
                   "examen_hr, "
                   "coursework_hr, "
                   "diplomwork_hr, "
                   "praktika_hr, "
                   "gak_hr, "
                   "other1, "
                   "other2, "
                   "other3 "
                   "FROM distribution "
                   "WHERE "
                   "distribution.subjects_in_semmester_id = " + subjects_in_semmestre_id + ";");

    }else{
        this->setQuery("SELECT "
                   "teachers.f || ' ' || teachers.i || ' ' || teachers.o "
                   "subjects_in_semmester_id, "
                   "lection_hr, "
                   "labs_hr, "
                   "practice_hr, "
                   "individ_hr, "
                   "kontr_rab_hr, "
                   "consultation_hr, "
                   "offset_hr, "
                   "examen_hr, "
                   "coursework_hr, "
                   "diplomwork_hr, "
                   "praktika_hr, "
                   "gak_hr, "
                   "other1, "
                   "other2, "
                   "other3 "
                   "FROM distribution,teachers "
                   "WHERE "
                   "distribution.teachers_id = teachers.id AND "
                   "distribution.subjects_in_semmester_id = " + subjects_in_semmestre_id + ";");
    }
}

//********************************************************************************
//  class Sins_to_distrib_preview_SqlModel
//********************************************************************************

Sins_to_distrib_preview_SqlModel::Sins_to_distrib_preview_SqlModel(QObject *parent) :
    QSqlQueryModel(parent)
{
    semester = " 1 ";
    speciality_id = '1';
}

Qt::ItemFlags Sins_to_distrib_preview_SqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    /*if (index.column() > 8 && index.column() < 24 )
    {
        flags |= Qt::ItemIsEditable;
    }*/
    return flags;
}

void Sins_to_distrib_preview_SqlModel::refresh()
{
    this->setQuery("SELECT subject_name, semmester, subjects_in_semmester.id FROM subjects_in_semmester, curriculum "
                   "WHERE (subjects_in_semmester.curriculum_id = curriculum.id AND "
                   "curriculum.speciality_id = " + speciality_id + ") AND ("
                   + semester + " );");
}

void Sins_to_distrib_preview_SqlModel::setspeciality_id(QString id)
{
    speciality_id = id;
}

void Sins_to_distrib_preview_SqlModel::setsemester_0()
{
    setsemester(0);
}
void Sins_to_distrib_preview_SqlModel::setsemester_1()
{
    setsemester(1);
}
void Sins_to_distrib_preview_SqlModel::setsemester_2()
{
    setsemester(2);
}

void Sins_to_distrib_preview_SqlModel::setsemester(int sem)
{
    if (sem == 1){
        semester = " curriculum.semmester = '1' "
                "OR curriculum.semmester = '3' "
                "OR curriculum.semmester = '5' "
                "OR curriculum.semmester = '7' "
                "OR curriculum.semmester = '9' "
                "OR curriculum.semmester = '11' ";
    } else if (sem == 2){
        semester = " curriculum.semmester = '2' "
                "OR curriculum.semmester = '4' "
                "OR curriculum.semmester = '6' "
                "OR curriculum.semmester = '8' "
                "OR curriculum.semmester = '10' "
                "OR curriculum.semmester = '12' ";
    } else if (sem == 0){
        semester = " 1 ";
    }
}
//********************************************************************************
//  class Sins_to_distrib_detail_SqlModel
//********************************************************************************

Sins_to_distrib_detail_SqlModel::Sins_to_distrib_detail_SqlModel(QObject *parent) :
    QSqlQueryModel(parent)
{
    subjects_in_semmestre_id = "1";
}

Qt::ItemFlags Sins_to_distrib_detail_SqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    /*if (index.column() > 8 && index.column() < 24 )
    {
        flags |= Qt::ItemIsEditable;
    }*/
    return flags;
}

void Sins_to_distrib_detail_SqlModel::setsins(QString id)
{
    subjects_in_semmestre_id = id;
}
void Sins_to_distrib_detail_SqlModel::refresh()
{
    this->setQuery("SELECT subjects_in_semmester.id, curriculum.subject_name, curriculum.semmester, "
                   "speciality.special_name, "
                   "speciality.form_training_name, students.course, "
                   "students.num_group, students.num_undergroup, "
                   "students.quantity_course, subjects_in_semmester.lection_hr, "
                   "subjects_in_semmester.labs_hr, subjects_in_semmester.practice_hr,"
                   "individ_hr, kontr_rab_hr, consultation_hr, "
                   "offset_hr,  examen_hr, coursework_hr, diplomwork_hr, praktika_hr, gak_hr, "
                   "other1,  other2, other3, "
                   "subjects_in_semmester.lection_hr+subjects_in_semmester.labs_hr+subjects_in_semmester.practice_hr+"
                   "individ_hr+kontr_rab_hr+consultation_hr+"
                   "offset_hr+examen_hr+coursework_hr+diplomwork_hr+praktika_hr+gak_hr+"
                   "other1+other2+other3 AS sum "
                   "FROM subjects_in_semmester, curriculum, students, speciality "
                   "WHERE subjects_in_semmester.curriculum_id = curriculum.id AND "
                   "subjects_in_semmester.students_id = students.id AND "
                   "students.speciality_id = speciality.id AND "
                   "subjects_in_semmester.id = " + subjects_in_semmestre_id + ";");
}
