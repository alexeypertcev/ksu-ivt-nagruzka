/****************************************************************************

****************************************************************************/

#ifndef CURRICULUMSQLMODEL_H
#define CURRICULUMSQLMODEL_H

#include <QSqlQueryModel>

class CurriculumSqlModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    CurriculumSqlModel(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    bool setFirstName(int personId, const QString &firstName);
    bool setLastName(int personId, const QString &lastName);
    void refresh();
};

#endif