#include "tab_subject.h"

SubjectSqlModel::SubjectSqlModel(QObject *parent) :
    QSqlQueryModel(parent)
{
}

Qt::ItemFlags SubjectSqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() == 0 )
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
    if (index.column() != 0)
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    QString s = "update subject set name = '"+ value.toString() +"' where name = '"+ data(primaryKeyIndex).toString() + "';";

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    QSqlQuery query;
    if (!query.exec(s)){
        ERROR_REPORT("0x100")
        return false;
    }
    this->refresh();
    return true;
}

bool SubjectSqlModel::add(QString subject)
{
    QString s = "insert into subject values( '" + subject + "');";

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    QSqlQuery query;
    if (!query.exec(s)){
        ERROR_REPORT("0x101")
        return false;
    }
    this->refresh();
    return true;
}

bool SubjectSqlModel::del(QString subject)
{
    QString s = "DELETE FROM subject WHERE name = '" + subject + "';";

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    QSqlQuery query;
    if (!query.exec(s)){
        ERROR_REPORT("0x102")
        return false;
    }
    this->refresh();
    return true;
}
