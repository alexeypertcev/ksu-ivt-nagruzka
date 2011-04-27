/****************************************************************************

****************************************************************************/

#ifndef STUDENTSSQLMODEL_H
#define STUDENTSSQLMODEL_H

#include <QSqlQueryModel>

class StudentsSqlModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    StudentsSqlModel(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    bool setFirstName(int personId, const QString &firstName);
    bool setLastName(int personId, const QString &lastName);
    void refresh();
};

#endif
