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
    bool cancel_del();
    bool save_removed();
private:
    QString id;
    QString f;
    QString i;
    QString o;
    QString status_name;
    QString rate;
    QString staff_id;
    bool bool_save_removed;
};


class TeachersReportSqlModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    TeachersReportSqlModel(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    void refresh();

private:

};


#endif // TEACHERS_H
