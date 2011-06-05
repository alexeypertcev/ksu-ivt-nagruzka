#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <QSqlQueryModel>

class Distribution : public QSqlQueryModel
{
    Q_OBJECT
public:
    Distribution(QObject *parent = 0);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void setsins(QString id);
    void refresh();
private:
    QString subjects_in_semmestre_id;

};


class Sins_to_distribSqlModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    Sins_to_distribSqlModel(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    void setsins(QString id);
    void refresh();
private:
    QString subjects_in_semmestre_id;

};

#endif // DISTRIBUTION_H
