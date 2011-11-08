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
    this->setQuery("SELECT id, f, i, o, status_name, rate "
                   "FROM teachers WHERE id != '0'; ");
}

bool TeachersSqlModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
    if (index.column() < 1 || index.column() > 5)
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    QString field = ";";
    switch (index.column()){
        case 1:
            field = "f";
            break;
        case 2:
            field = "i";
            break;
        case 3:
            field = "o";
            break;
        case 4:
            field = "status_name";
            break;
        case 5:
            field = "rate";
            break;
        }

    QString s = "update teachers set "+ field +" = '"+ value.toString() +"' where id = "+ data(primaryKeyIndex).toString();
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        return false;
    }
    this->refresh();
    return true;
}

bool TeachersSqlModel::add(QString f, QString i, QString o, QString status_name,
                           QString rate)
{
    QString s = "insert into teachers values(NULL, "+ f +", "+ i +", "+ o +", "+
                                                      status_name +", "+ rate +");";
//    qDebug() << s;

    QSqlQuery query;

    return query.exec(s);
}

bool TeachersSqlModel::del(QString id)
{
    QString s = "DELETE FROM teachers WHERE id = '" + id + "';";
//    qDebug() << s;

    QSqlQuery query;

    return query.exec(s);
}
