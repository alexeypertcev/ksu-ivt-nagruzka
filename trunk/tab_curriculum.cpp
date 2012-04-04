/****************************************************************************

****************************************************************************/

#include <QtSql>
#include <QMessageBox>
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

    QString s = "update curriculum set "+ field +" = '"+ value.toString() +"' where id = "+ data(primaryKeyIndex).toString();
    qDebug() << s;

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
    if (!query.exec(s))
    {
        return false;
    }
    query.next();
    if (query.value(0).toString() == "" || query.value(1).toString() == "" || query.value(2).toString() == ""){
        if (speciality_id == "all"){
            query.exec("SELECT id FROM speciality ORDER BY id DESC;");
            query.next();
            temp_speciality_id = query.value(0).toString();
        } else {
            temp_speciality_id = speciality_id;
        }

        query.exec("SELECT name FROM subject ORDER BY name DESC;");
        query.next();
        subject_name = query.value(0).toString();

        semmester = "1";

    } else {
        temp_speciality_id = query.value(0).toString();
        subject_name = query.value(1).toString();
        semmester = query.value(2).toString();
    }

    s = "insert into curriculum values(NULL, '" + temp_speciality_id + "', '" + subject_name + "', '"  + semmester +  "', 0, 0, 0, 0, 0, 0, 0, 0);";
    return query.exec(s);
}

bool CurriculumSqlModel::del(QString id)
{
    QString s = "DELETE FROM curriculum WHERE id = '" + id + "';";
    qDebug() << s;

    QSqlQuery query;
    query.exec(s);

    return TRUE;
}
