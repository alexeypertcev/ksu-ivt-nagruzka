/****************************************************************************

****************************************************************************/

#include <QtSql>
#include <QMessageBox>
#include "curriculum_sqlmodel.h"

CurriculumSqlModel::CurriculumSqlModel(QObject *parent)
    : QSqlQueryModel(parent)
{
    speciality_id = '1';
}


Qt::ItemFlags CurriculumSqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() > 0 && index.column() < 11 )
    {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

bool CurriculumSqlModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
    if (index.column() < 1 || index.column() > 10)
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    //int id = data(primaryKeyIndex).toInt();
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
    this->refresh();
    return true;
}

void CurriculumSqlModel::refresh()
{
    this->setQuery("SELECT curriculum.id, special_name || '(' || form_training_name || ')', "
                   "subject_name, semmester, lection_hr, labs_hr, practice_hr, "
                   "KCP_hr, is_examen, is_offset, is_coursework "
                   "FROM curriculum, speciality "
                   "WHERE curriculum.speciality_id = speciality.id AND speciality_id = " + speciality_id +
                   ";");


}

void CurriculumSqlModel::setspeciality_id(QString id)
{
    speciality_id = id;
}

bool CurriculumSqlModel::add()
{
    QString s = "insert into curriculum values(NULL, '" + speciality_id + "', 'ПП', 1, 0, 0, 0, 0, 0, 0, 0);";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s))
    {
        return false;
    }
    return true;
}

bool CurriculumSqlModel::del(QString id)
{
    QString s = "DELETE FROM curriculum WHERE id = '" + id + "';";
    qDebug() << s;

    QSqlQuery query;
    query.exec(s);
}
