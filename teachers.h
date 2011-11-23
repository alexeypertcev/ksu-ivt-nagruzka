/****************************************************************************
** Alexey Pertcev alexey.pertcev@gmail.com
****************************************************************************/
#ifndef TEACHERS_H
#define TEACHERS_H

#include <QSqlQueryModel>
#include <QItemDelegate>


class TeachersSqlModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    TeachersSqlModel(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void refresh();
    bool add();
    bool del(QString id);
};

#endif // TEACHERS_H
