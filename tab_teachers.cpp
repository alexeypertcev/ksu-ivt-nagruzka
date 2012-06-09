/****************************************************************************

****************************************************************************/

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

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    QSqlQuery query;
    if (!query.exec(s)){
        ERROR_REPORT("0x200")
        return false;
    }
    this->refresh();
    return true;
}

bool TeachersSqlModel::add()
{
    QString s = "insert into teachers values(NULL, ' ', ' ', ' ', 'выберите..', '1', 0);";

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    QSqlQuery query;

    bool_save_removed = false;
    if (!query.exec(s)){
        ERROR_REPORT("0x201")
        return false;
    }
    this->refresh();
    return true;
}

bool TeachersSqlModel::del(QString id)
{
    QSqlQuery query;
    QString s = "SELECT id, f, i, o, status_name, rate, staff_id FROM teachers WHERE id = '"+ id + "';";

#ifdef DEBUG_ENABLE_SELECT
    DEBUG_MESSAGE( s )
#endif

    if (query.exec(s)){
        if (query.next()){
            this->id = query.value(0).toString();
            f = query.value(1).toString();
            i = query.value(2).toString();
            o = query.value(3).toString();
            status_name = query.value(4).toString();
            rate = query.value(5).toString();
            staff_id = query.value(6).toString();

            bool_save_removed = true;
        }
    }
    s = "DELETE FROM teachers WHERE id = '" + id + "';";

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    if (!query.exec(s)){
        ERROR_REPORT("0x202")
        return false;
    }
    this->refresh();
    return true;
}

bool TeachersSqlModel::cancel_del()
{
    QString s = "insert into teachers values('"+ this->id +"', '"+f+"', '" +i+"', '"+o+"', '"+status_name+"', '"+rate+"', '"+staff_id+"');";

#ifdef DEBUG_ENABLE_MODIFY
    DEBUG_MESSAGE( s )
#endif

    QSqlQuery query;
    bool_save_removed = false;
    if (!query.exec(s)){
        ERROR_REPORT("0x203")
        return false;
    }
    this->refresh();
    return true;
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
    rowsCountDB = rowCountDB();
    this->setQuery("SELECT teachers.id, f || ', ' || i || ' ' || o, status_name "
                   "FROM teachers WHERE teachers.id != '0' "
                   "ORDER BY teachers.f, teachers.i, teachers.o");
}

int TeachersReportSqlModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return QSqlQueryModel::rowCount(parent) + 1;
}

int TeachersReportSqlModel::rowCountDB(){
    QSqlQuery query;
    QString s = "SELECT COUNT(*) FROM teachers ;";

#ifdef DEBUG_ENABLE_SELECT
    DEBUG_MESSAGE( s )
#endif

    if (query.exec(s)){
        if (query.next()){
            return query.value(0).toInt();
        }
    }
    return 0;
}

QVariant TeachersReportSqlModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);

    switch (role)
    {
    case Qt::DisplayRole:
        if (index.row() == (rowsCountDB-1))
        {
            if (index.column() == 0){
               return 0;
            }
            if (index.column() == 1){
               return "Вакансии";
            }
        }
        break;
    case Qt::BackgroundColorRole:
        if (index.row() == (rowsCountDB-1)) {
            return qVariantFromValue(QColor(235, 235, 235));
        }
    }
    return value;
}
