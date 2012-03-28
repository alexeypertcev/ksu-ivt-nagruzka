#include <QtSql>
#include <QMessageBox>
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
    if (index.column() > 8 && index.column() < 24 )
    {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

bool SubjectinsemesterSqlModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
    if (index.column() < 9 || index.column() > 23)
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    QString field = ";";
    switch (index.column()){
        case 9:
            field = "lection_hr";
            break;
        case 10:
            field = "labs_hr";
            break;
        case 11:
            field = "practice_hr";
            break;
        case 12:
            field = "individ_hr";
            break;
        case 13:
            field = "kontr_rab_hr";
            break;
        case 14:
            field = "consultation_hr";
            break;
        case 15:
            field = "offset_hr";
            break;
        case 16:
            field = "examen_hr";
            break;
        case 17:
            field = "coursework_hr";
            break;
        case 18:
            field = "diplomwork_hr";
            break;
        case 19:
            field = "praktika_hr";
            break;
        case 20:
            field = "gak_hr";
            break;
        case 21:
            field = "other1";
            break;
        case 22:
            field = "other2";
            break;
        case 23:
            field = "other3";
        }

    QString s = "update subjects_in_semmester set "+ field +" = '"+ value.toString() +"' where id = "+ data(primaryKeyIndex, Qt::DisplayRole).toString();
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        return false;
    }
    this->refresh();
    return true;
}

void SubjectinsemesterSqlModel::refresh()
{
    rowsCountDB = rowCountDB();
    sum = get_sum_current_speciality();
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
                   "students.speciality_id = " + speciality_id + " "
                   "ORDER BY curriculum.semmester, curriculum.subject_name;");
}

unsigned int SubjectinsemesterSqlModel::get_sum_current_speciality(){
    QSqlQuery query;
    QString s =
            "SELECT "
            "subjects_in_semmester.lection_hr+subjects_in_semmester.labs_hr+subjects_in_semmester.practice_hr+"
            "individ_hr+kontr_rab_hr+consultation_hr+"
            "offset_hr+examen_hr+coursework_hr+diplomwork_hr+praktika_hr+gak_hr+"
            "other1+other2+other3 AS sum "
            "FROM subjects_in_semmester, curriculum, students, speciality "
            "WHERE subjects_in_semmester.curriculum_id = curriculum.id AND "
            "subjects_in_semmester.students_id = students.id AND "
            "students.speciality_id = speciality.id AND "
            "students.speciality_id = " + speciality_id + " "
            "ORDER BY curriculum.semmester, curriculum.subject_name;";

    if (query.exec(s)) {
        unsigned int temp_sum = 0;
        while (query.next()) {
            temp_sum += query.value(0).toUInt();
        }
        return temp_sum;
    } else {
        return 0;
    }
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
    return true;
}

int SubjectinsemesterSqlModel::rowCount (const QModelIndex & parent) const
{
    if (parent.isValid()) return 0;
    return QSqlQueryModel::rowCount(parent) + 1;
}

QVariant SubjectinsemesterSqlModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);

    switch (role)
    {
    case Qt::DisplayRole:
        if (index.row() == rowsCountDB)
        {
            switch(index.column()){
            case 1:
               return "Всего: ";

            case 24:
                return sum;

            default:
               return "";
            }
        }
        break;
    case Qt::BackgroundColorRole:
        {
            if (index.row() == rowsCountDB) return qVariantFromValue(QColor(224, 255, 193));
            else return value;
        }
        break;
    case Qt::FontRole:
        if (index.row() == rowsCountDB)
        {
            QFont fnt = QFont(qvariant_cast<QFont>(value));
            fnt.setBold(true);

            return qVariantFromValue(fnt);
        }
        else return value;
        break;
    case Qt::TextColorRole:


        break;
    }
    return value;
}

int SubjectinsemesterSqlModel::rowCountDB(){
    QSqlQuery query;
    //QString s = "SELECT COUNT(*) FROM subjects_in_semmester WHERE students.speciality_id = " + speciality_id + ";";

    QString s ="SELECT COUNT(*) "
              "FROM subjects_in_semmester, curriculum, students, speciality "
              "WHERE subjects_in_semmester.curriculum_id = curriculum.id AND "
              "subjects_in_semmester.students_id = students.id AND "
              "students.speciality_id = speciality.id AND "
              "students.speciality_id = " + speciality_id + " "
              "ORDER BY curriculum.semmester, curriculum.subject_name;";
    if (query.exec(s)) {
        query.next();
        return query.value(0).toInt();
    } else {
        return 0;
    }
}
