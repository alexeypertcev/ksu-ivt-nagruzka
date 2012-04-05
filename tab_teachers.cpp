/****************************************************************************

****************************************************************************/

#include <QtSql>
#include "tab_teachers.h"

TeachersSqlModel::TeachersSqlModel(QObject *parent) :
    QSqlQueryModel(parent)
{
    id = "";
    f = "";
    i = "";
    o = "";
    status_name = "";
    rate = "";
    staff_id = "";
    bool_save_removed = false;
}

Qt::ItemFlags TeachersSqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() > 0 && index.column() < 7 )
    {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

void TeachersSqlModel::refresh()
{
    this->setQuery("SELECT teachers.id, f, i, o, status_name, rate , staff.name "
                   "FROM teachers, staff WHERE teachers.id != '0' AND teachers.staff_id = staff.id "
                   "ORDER BY teachers.f, teachers.i, teachers.o");
    table_changed();
}

bool TeachersSqlModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
    if (index.column() < 1 || index.column() > 6)
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
        case 6:
            field = "staff_id";
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

bool TeachersSqlModel::add()
{
    QString s = "insert into teachers values(NULL, ' ', ' ', ' ', 'выберите..', '1', 0);";
    qDebug() << s;
    QSqlQuery query;

    bool_save_removed = false;
    return query.exec(s);
}

bool TeachersSqlModel::del(QString id)
{
    QString s = "DELETE FROM teachers WHERE id = '" + id + "';";
//    qDebug() << s;

    QSqlQuery query;

    query.exec("SELECT id, f, i, o, status_name, rate, staff_id FROM teachers WHERE id = '"+ id + "';");
    query.next();
   this->id = query.value(0).toString();
    f = query.value(1).toString();
    i = query.value(2).toString();
    o = query.value(3).toString();
    status_name = query.value(4).toString();
    rate = query.value(5).toString();
    staff_id = query.value(6).toString();

    bool_save_removed = true;
    return query.exec(s);
}

bool TeachersSqlModel::cancel_del()
{
    QString s = "insert into teachers values('"+id+"', '"+f+"', '" +i+"', '"+o+"', '"+status_name+"', '"+rate+"', '"+staff_id+"');";
    qDebug() << s;

    QSqlQuery query;
    bool_save_removed = false;
    return query.exec(s);
}

bool TeachersSqlModel::save_removed()
{
    return bool_save_removed;
}


/************************************************************************
/  TeachersReportSqlModel
************************************************************************/

TeachersReportSqlModel::TeachersReportSqlModel(QObject *parent) :
    QSqlQueryModel(parent)
{
}

Qt::ItemFlags TeachersReportSqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    return flags;
}

void TeachersReportSqlModel::refresh()
{
    this->setQuery("SELECT teachers.id, f || ', ' || i || ', ' || o, status_name "
                   "FROM teachers WHERE teachers.id != '0'");
}
