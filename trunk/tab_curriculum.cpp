/****************************************************************************

****************************************************************************/

#include "tab_curriculum.h"

CurriculumSqlModel::CurriculumSqlModel(QObject *parent)
    : QSqlQueryModel(parent)
{
    speciality_id = '1';
}


Qt::ItemFlags CurriculumSqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() > 0 && index.column() < 12 )
    {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

bool CurriculumSqlModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
    if (index.column() < 1 || index.column() > 11)
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
            field = "controlwork";
            break;
        case 8:
            field = "KCP_hr";
            break;
        case 9:
            field = "is_examen";
            break;
        case 10:
            field = "is_offset";
            break;
        case 11:
            field = "is_coursework";
            break;
        }

    QString s = "update curriculum set "+ field +" = '"+ functions::toDataString(value.toString()) +"' where id = "+ data(primaryKeyIndex).toString();

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    QSqlQuery query;
    if (!query.exec(s)){
        return false;
    }
    this->refresh();
    return true;
}

void CurriculumSqlModel::refresh()
{
    if (speciality_id == "all"){
        this->setQuery("SELECT curriculum.id, special_name || '(' || form_training_name || ')' AS spec_form, "
                       "subject_name, semmester, lection_hr, labs_hr, practice_hr, controlwork, "
                       "KCP_hr, is_examen, is_offset, is_coursework "
                       "FROM curriculum, speciality "
                       "WHERE curriculum.speciality_id = speciality.id "
                       " ORDER BY spec_form, semmester, subject_name, curriculum.id;");
    } else {
        this->setQuery("SELECT curriculum.id, special_name || '(' || form_training_name || ')', "
                       "subject_name, semmester, lection_hr, labs_hr, practice_hr, controlwork, "
                       "KCP_hr, is_examen, is_offset, is_coursework "
                       "FROM curriculum, speciality "
                       "WHERE curriculum.speciality_id = speciality.id AND speciality_id = " + speciality_id +
                       " ORDER BY semmester, subject_name, curriculum.id;");
    }

}

void CurriculumSqlModel::setspeciality_id(QString id)
{
    speciality_id = id;
}

bool CurriculumSqlModel::add()
{
    QSqlQuery query;
    QString s, temp_speciality_id, subject_name, semmester;
    if (speciality_id == "all"){
        s = "SELECT speciality_id, subject_name, semmester "
                   "FROM curriculum "
                   "ORDER BY speciality_id DESC, semmester DESC, subject_name DESC;";
    } else {
        s = "SELECT speciality_id, subject_name, semmester "
                   "FROM curriculum "
                   "WHERE speciality_id = " + speciality_id + " "
                   "ORDER BY semmester DESC, subject_name DESC;";
    }
#ifdef DEBUG_ENABLE_SELECT
    DEBUG_MESSAGE( s )
#endif

    if (!query.exec(s))
    {
        ERROR_REPORT("0x405")
        return false;
    }
    if (query.next()){
            temp_speciality_id = query.value(0).toString();
            subject_name = query.value(1).toString();
            semmester = query.value(2).toString();
    } else {
        if (speciality_id == "all"){
            s = "SELECT id FROM speciality ORDER BY id DESC;";

#ifdef DEBUG_ENABLE_SELECT
            DEBUG_MESSAGE( s )
#endif
            if (!query.exec(s)){
                ERROR_REPORT("0x406")
                return false;
            }
            if (query.next()){
                temp_speciality_id = query.value(0).toString();
            } else {
                ERROR_REPORT("0x407")
                return false;
            }
        } else {
            temp_speciality_id = speciality_id;
        }

        s = "SELECT name FROM subject ORDER BY name DESC;";

#ifdef DEBUG_ENABLE_SELECT
        DEBUG_MESSAGE( s )
#endif
        if (!query.exec(s)){
            ERROR_REPORT("0x408")
            return false;
        }
        if (query.next()){
            subject_name = query.value(0).toString();
            semmester = "1";
        } else {
            ERROR_REPORT("0x409")
            return false;
        }
    }

    s = "insert into curriculum values(NULL, '" + temp_speciality_id + "', '" + subject_name + "', '"  + semmester +  "', 0, 0, 0, 0, 0, 0, 0, 0);";

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif
    return query.exec(s);
}

bool CurriculumSqlModel::del(QString id)
{
    QString s;
    QString subjects_in_semmester_id;
    QSqlQuery query;

    s = "SELECT subjects_in_semmester.id FROM subjects_in_semmester WHERE subjects_in_semmester.curriculum_id = '" + id + "';";

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    if (!query.exec(s)){
        ERROR_REPORT("0x400");
        return false;
    }
    if (query.next()){
        subjects_in_semmester_id = query.value(0).toString();

        if (query.next()){
            ERROR_REPORT("0x401");
        }
    }

    s = "DELETE FROM distribution WHERE distribution.subjects_in_semmester_id = '" + subjects_in_semmester_id + "';";

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    if (!query.exec(s)){
        ERROR_REPORT("0x402");
    }

    s = "DELETE FROM subjects_in_semmester WHERE id = '" + subjects_in_semmester_id + "';";

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    if (!query.exec(s)){
        ERROR_REPORT("0x403");
    }

    s = "DELETE FROM curriculum WHERE id = '" + id + "';";

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    if (!query.exec(s)){
        ERROR_REPORT("0x404");
        return false;
    }
    return true;
}
