/****************************************************************************

****************************************************************************/

#include <QtSql>
#include "teachers.h"

TeachersSqlModel::TeachersSqlModel(QObject *parent) :
    QSqlQueryModel(parent)
{
}

Qt::ItemFlags TeachersSqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() > 0 && index.column() < 6 )
    {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

void TeachersSqlModel::refresh()
{
    this->setQuery("SELECT students.id, special_name || '(' || form_training_name || ')', "
                   "course, num_group, num_undergroup, quantity_course "
                   "FROM students, speciality "
                   "WHERE students.speciality_id = speciality.id;");
}

bool TeachersSqlModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
    if (index.column() < 1 || index.column() > 5)
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    QString field = ";";
    switch (index.column()){
        case 1:
            field = "speciality_id";
            break;
        case 2:
            field = "course";
            break;
        case 3:
            field = "num_group";
            break;
        case 4:
            field = "num_undergroup";
            break;
        case 5:
            field = "quantity_course";
            break;
        }

    QString s = "update students set "+ field +" = '"+ value.toString() +"' where id = "+ data(primaryKeyIndex).toString();
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        return false;
    }
    this->refresh();
    return true;
}
bool TeachersSqlModel::add(QString speciality_id, QString course, QString num_group, QString num_undergroup,
                           QString quantity_course)
{
    QString s = "insert into students values(NULL, "+ speciality_id +", "+ course +", "+ num_group +", "+
                                                      num_undergroup +", "+ quantity_course +");";
    qDebug() << s;

    QSqlQuery query;
    query.exec(s);

    return true;
}

bool TeachersSqlModel::del(QString id)
{
    QString s = "DELETE FROM students WHERE id = '" + id + "';";
    qDebug() << s;

    QSqlQuery query;
    query.exec(s);

    return true;
}
