#ifndef SUBJECT_H
#define SUBJECT_H

#include <QSqlQueryModel>
#include <QItemDelegate>
#include "errors.h"
#include "functions.h"

class SubjectSqlModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    SubjectSqlModel(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void refresh();
    bool add(QString subject);
    bool del(QString name);
private:

};



#endif // SUBJECT_H
