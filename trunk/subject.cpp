#include "subject.h"

#include <QtSql>
#include "students.h"

SubjectSqlModel::SubjectSqlModel(QObject *parent) :
    QSqlQueryModel(parent)
{
}

Qt::ItemFlags SubjectSqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() > 0 && index.column() < 1 )
    {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

void SubjectSqlModel::refresh()
{
    this->setQuery("SELECT "
                   "name "
                   "FROM subject "
                   "ORDER BY name");
}

bool SubjectSqlModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
    if (index.column() < 0 || index.column() > 0)
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    QString field = ";";
    switch (index.column()){
        case 1:
            field = "name";
            break;
        }

    QString s = "update subject set "+ field +" = '"+ value.toString() +"' where name = "+ data(primaryKeyIndex).toString();
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        return false;
    }
    this->refresh();
    return true;
}

bool SubjectSqlModel::add(QString subject)
{
    QString s = "insert into subject values( " + subject + ");";
    qDebug() << s;

    QSqlQuery query;
    return query.exec(s);
}

bool SubjectSqlModel::del(QString subject)
{
    QString s = "DELETE FROM subject WHERE name = '" + subject + "';";
    qDebug() << s;

    QSqlQuery query;
    return query.exec(s);
}
