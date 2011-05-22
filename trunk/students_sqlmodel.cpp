/****************************************************************************

****************************************************************************/

#include <QtSql>
#include "students_sqlmodel.h"

StudentsSqlModel::StudentsSqlModel(QObject *parent) :
    QSqlQueryModel(parent)
{
}

Qt::ItemFlags StudentsSqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() > 0 && index.column() < 10 )
    {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

void StudentsSqlModel::refresh()
{
    this->setQuery("SELECT students.id, special_name || '(' || form_training_name || ')', "
                   "course, num_group, num_undergroup, quantity_course "
                   "FROM students, speciality "
                   "WHERE students.speciality_id = speciality.id;");
}
