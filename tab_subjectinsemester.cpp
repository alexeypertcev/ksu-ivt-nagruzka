#include "tab_subjectinsemester.h"

SubjectinsemesterSqlModel::SubjectinsemesterSqlModel(QObject *parent) :
    QSqlQueryModel(parent)
{
        speciality_id = '1';
}

Qt::ItemFlags SubjectinsemesterSqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() >= 8 && index.column() <= 22 )
    {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

bool SubjectinsemesterSqlModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
    if (index.column() < 8 || index.column() > 22)
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    QString field = ";";
    switch (index.column()){
        case 8:
            field = "lection_hr";
            break;
        case 9:
            field = "labs_hr";
            break;
        case 10:
            field = "practice_hr";
            break;
        case 11:
            field = "individ_hr";
            break;
        case 12:
            field = "kontr_rab_hr";
            break;
        case 13:
            field = "consultation_hr";
            break;
        case 14:
            field = "offset_hr";
            break;
        case 15:
            field = "examen_hr";
            break;
        case 16:
            field = "coursework_hr";
            break;
        case 17:
            field = "diplomwork_hr";
            break;
        case 18:
            field = "praktika_hr";
            break;
        case 19:
            field = "gak_hr";
            break;
        case 20:
            field = "other1";
            break;
        case 21:
            field = "other2";
            break;
        case 22:
            field = "other3";
        }

    QString s = "update subjects_in_semmester set "+ field +" = '"+ functions::toDataString(value.toString()) +"' where id = "+ data(primaryKeyIndex, Qt::DisplayRole).toString();
#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    QSqlQuery query;
    if (!query.exec(s)){
        ERROR_REPORT("0x500");
        return false;
    }
    this->refresh();
    return true;
}

void SubjectinsemesterSqlModel::refresh()
{
    rowsCountDB = rowCountDB();
    sum = get_sum_current_speciality();
    if (speciality_id == "all"){
        this->setQuery("SELECT subjects_in_semmester.id, curriculum.subject_name, curriculum.semmester, "
                       "speciality.special_name || '(' || speciality.form_training_name || ')', "
                       "students.course, "
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
                       "students.speciality_id = speciality.id "
                       "ORDER BY speciality.special_name, speciality.form_training_name, curriculum.semmester, curriculum.subject_name, subjects_in_semmester.id;");
    } else {
        this->setQuery("SELECT subjects_in_semmester.id, curriculum.subject_name, curriculum.semmester, "
                       "speciality.special_name || '(' || speciality.form_training_name || ')', "
                       "students.course, "
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
                       "ORDER BY speciality.special_name, speciality.form_training_name, curriculum.semmester, curriculum.subject_name, subjects_in_semmester.id;");
    }
}

unsigned int SubjectinsemesterSqlModel::get_sum_current_speciality(){
    QSqlQuery query;
    QString s;
    if (speciality_id == "all"){
        s =     "SELECT "
                "subjects_in_semmester.lection_hr+subjects_in_semmester.labs_hr+subjects_in_semmester.practice_hr+"
                "individ_hr+kontr_rab_hr+consultation_hr+"
                "offset_hr+examen_hr+coursework_hr+diplomwork_hr+praktika_hr+gak_hr+"
                "other1+other2+other3 AS sum "
                "FROM subjects_in_semmester, curriculum, students, speciality "
                "WHERE subjects_in_semmester.curriculum_id = curriculum.id AND "
                "subjects_in_semmester.students_id = students.id AND "
                "students.speciality_id = speciality.id "
                "ORDER BY speciality.special_name, speciality.form_training_name, curriculum.semmester, curriculum.subject_name, subjects_in_semmester.id;";
    } else {
        s =     "SELECT "
                "subjects_in_semmester.lection_hr+subjects_in_semmester.labs_hr+subjects_in_semmester.practice_hr+"
                "individ_hr+kontr_rab_hr+consultation_hr+"
                "offset_hr+examen_hr+coursework_hr+diplomwork_hr+praktika_hr+gak_hr+"
                "other1+other2+other3 AS sum "
                "FROM subjects_in_semmester, curriculum, students, speciality "
                "WHERE subjects_in_semmester.curriculum_id = curriculum.id AND "
                "subjects_in_semmester.students_id = students.id AND "
                "students.speciality_id = speciality.id AND "
                "students.speciality_id = " + speciality_id + " "
                "ORDER BY speciality.special_name, speciality.form_training_name, curriculum.semmester, curriculum.subject_name, subjects_in_semmester.id;";
    }

#ifdef DEBUG_ENABLE_SELECT
    DEBUG_MESSAGE( s )
#endif

    if (query.exec(s)) {
        unsigned int temp_sum = 0;
        while (query.next()) {
            temp_sum += query.value(0).toUInt();
        }
        return temp_sum;
    } else {
        ERROR_REPORT("0x501");
        return 0;
    }
}

void SubjectinsemesterSqlModel::setspeciality_id(QString id)
{
    speciality_id = id;
}

bool SubjectinsemesterSqlModel::add()
{
    return false;
}

bool SubjectinsemesterSqlModel::del(QString id)
{
    QString s;
    QSqlQuery query;
    s = "DELETE FROM distribution WHERE distribution.subjects_in_semmester_id = '" + id + "';";

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    if (!query.exec(s)){
        ERROR_REPORT("0x502");
        return false;
    }

    s = "DELETE FROM subjects_in_semmester WHERE id = '" + id + "';";

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    if (!query.exec(s)){
        ERROR_REPORT("0x503");
        return false;
    }
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
        if (index.row() == (int)rowsCountDB)
        {
            switch(index.column()){
            case 1:
               return "Всего: ";

            case 23:
                return sum;

            default:
               return "";
            }
        }
        break;
    case Qt::BackgroundColorRole:
        {
            if (index.row() == (int)rowsCountDB) {
                return qVariantFromValue(QColor(224, 255, 193));
            } else if (index.column() <= 7 || index.column() == 23) {
                    return qVariantFromValue(QColor(235, 235, 235));
                } else {
                    return value;
                }
        }
        break;
    case Qt::FontRole:
        if (index.row() == (int)rowsCountDB)
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
    QString s;
    if (speciality_id == "all"){
        s ="SELECT COUNT(*) "
                  "FROM subjects_in_semmester, curriculum, students, speciality "
                  "WHERE subjects_in_semmester.curriculum_id = curriculum.id AND "
                  "subjects_in_semmester.students_id = students.id AND "
                  "students.speciality_id = speciality.id ";
    } else {
        s ="SELECT COUNT(*) "
                  "FROM subjects_in_semmester, curriculum, students, speciality "
                  "WHERE subjects_in_semmester.curriculum_id = curriculum.id AND "
                  "subjects_in_semmester.students_id = students.id AND "
                  "students.speciality_id = speciality.id AND "
                  "students.speciality_id = " + speciality_id + " ";
    }

#ifdef DEBUG_ENABLE_SELECT
    DEBUG_MESSAGE( s )
#endif

    if (query.exec(s)) {
        if (query.next()){
            return query.value(0).toInt();
        } else {
            ERROR_REPORT("0x507");
            return 0;
        }
    } else {
        ERROR_REPORT("0x504");
        return 0;
    }
}

bool SubjectinsemesterSqlModel::clearTable(){
    QString s;
    QSqlQuery query;
    s = "DELETE FROM distribution;";

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    if (!query.exec(s)){
        ERROR_REPORT("0x505");
    }

    s = "DELETE FROM subjects_in_semmester;";

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    if (!query.exec(s)){
        ERROR_REPORT("0x506");
        return false;
    }
    return true;
}
