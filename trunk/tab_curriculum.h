/****************************************************************************
** Alexey Pertcev alexey.pertcev@gmail.com
****************************************************************************/

#ifndef CURRICULUMSQLMODEL_H
#define CURRICULUMSQLMODEL_H

#include <QItemDelegate>
#include <QSpinBox>
#include <QtSql>
#include "errors.h"
#include "functions.h"

class CurriculumSqlModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    CurriculumSqlModel(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void setspeciality_id(QString id);
    void refresh();
    bool add();
    bool del(QString id);
private:
    QString speciality_id;
};

#endif
