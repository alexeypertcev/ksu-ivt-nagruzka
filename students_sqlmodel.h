/****************************************************************************

****************************************************************************/

#ifndef STUDENTS_SQLMODEL_H
#define STUDENTS_SQLMODEL_H

#include <QSqlQueryModel>
#include <QItemDelegate>


class StudentsSqlModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    StudentsSqlModel(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void refresh();
    //bool add();

};

#endif // STUDENTS_SQLMODEL_H
