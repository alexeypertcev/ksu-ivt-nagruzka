#include "distribution.h"
#include <QDebug>

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
void DistributionSqlModel::refresh()
{
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
