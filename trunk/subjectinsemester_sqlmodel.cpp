#include "subjectinsemester_sqlmodel.h"

SubjectinsemesterSqlModel::SubjectinsemesterSqlModel(QObject *parent) :
    QSqlQueryModel(parent)
{
        speciality_id = '1';
}

Qt::ItemFlags SubjectinsemesterSqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() > 0 && index.column() < 19 )
    {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

bool SubjectinsemesterSqlModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{/*
    if (index.column() < 1 || index.column() > 18)
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    QString field = ";";
    switch (index.column()){
        case 1:
            field = "speciality_id";
            break;
        case 2:
            field = "subject_name";
            break;
        case 3:
            field = "semmester";
            break;
        case 4:
            field = "lection_hr";
            break;
        case 5:
            field = "labs_hr";
            break;
        case 6:
            field = "practice_hr";
            break;
        case 7:
            field = "KCP_hr";
            break;
        case 8:
            field = "is_examen";
            break;
        case 9:
            field = "is_offset";
            break;
        case 10:
            field = "is_coursework";
            break;
        default:
            field = ";";
        }

    QString s = "update curriculum set "+ field +" = '"+ value.toString() +"' where id = "+ data(primaryKeyIndex).toString();
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        //QMessageBox::warning(this, tr("Error querry"));
        return false;
    }
    this->refresh();*/
    return true;
}

void SubjectinsemesterSqlModel::refresh()
{
    this->setQuery("SELECT subjects_in_semmester.id, curriculum.subject_name, curriculum.semmester, "
                   "speciality.faculty_name, speciality.special_name, "
                   "speciality.form_training_name, students.course, "
                   "students.num_group, students.num_undergroup, "
                   "students.quantity_course, subjects_in_semmester.lection_hr, "
                   "subjects_in_semmester.labs_hr, subjects_in_semmester.practice_hr,"
                   "individ_hr, ayditor_hr,  kontr_rab_hr, consultation_hr, "
                   "offset_hr,  examen_hr, coursework_hr, diplomwork_hr, praktika_hr, gak_hr, "
                   "other1,  other2, other3, "
                   "subjects_in_semmester.lection_hr+subjects_in_semmester.labs_hr+subjects_in_semmester.practice_hr+"
                   "individ_hr+ayditor_hr+kontr_rab_hr+consultation_hr+"
                   "offset_hr+examen_hr+coursework_hr+diplomwork_hr+praktika_hr+gak_hr+"
                   "other1+other2+other3 AS sum "
                   "FROM subjects_in_semmester, curriculum, students, speciality "
                   "WHERE subjects_in_semmester.curriculum_id = curriculum.id AND "
                   "subjects_in_semmester.students_id = students.id AND "
                   "students.speciality_id = speciality.id AND "
                   "students.speciality_id = " + speciality_id + ";");
}

void SubjectinsemesterSqlModel::setspeciality_id(QString id)
{
    speciality_id = id;
}

bool SubjectinsemesterSqlModel::add()
{
    /*
    QString s = "insert into curriculum values(NULL, '" + speciality_id + "', 'ПП', 1, 0, 0, 0, 0, 0, 0, 0);";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s))
    {
        return false;
    }
    return true;
    */
}
