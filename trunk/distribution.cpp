#include "distribution.h"
#include <QDebug>

Distribution::Distribution(QObject *parent) :
    QSqlQueryModel(parent)
{
    subjects_in_semmestre_id = '1';
}

Qt::ItemFlags Distribution::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() > 1 && index.column() < 10 )
    {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

void Distribution::setsins(QString id)
{
    subjects_in_semmestre_id = id;
}
void Distribution::refresh(){}



Sins_to_distribSqlModel::Sins_to_distribSqlModel(QObject *parent) :
    QSqlQueryModel(parent)
{
    subjects_in_semmestre_id = "1";
}

Qt::ItemFlags Sins_to_distribSqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    /*if (index.column() > 8 && index.column() < 24 )
    {
        flags |= Qt::ItemIsEditable;
    }*/
    return flags;
}

void Sins_to_distribSqlModel::setsins(QString id)
{
    subjects_in_semmestre_id = id;
}
void Sins_to_distribSqlModel::refresh()
{
    qDebug() << subjects_in_semmestre_id << " : subjects_in_semmestre_id";
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
