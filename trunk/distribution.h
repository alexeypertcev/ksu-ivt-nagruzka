#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <QSqlQueryModel>

class DistributionSqlModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    DistributionSqlModel(QObject *parent = 0);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void setsins(QString id);
    void check_entry();
    void refresh();
private:
    QString subjects_in_semmestre_id;

};

class Sins_to_distrib_preview_SqlModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    Sins_to_distrib_preview_SqlModel(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    void refresh();
    void setspeciality_id(QString id);
    void setsemester(int sem);    // 0 - all, 1 - нечет , 2 - чет
    void setsemester_0();
    void setsemester_1();
    void setsemester_2();
private:
    QString speciality_id;
    QString semester;
};

class Sins_to_distrib_detail_SqlModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    Sins_to_distrib_detail_SqlModel(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    void setsins(QString id);
    void refresh();
private:
    QString subjects_in_semmestre_id;

};

#endif // DISTRIBUTION_H
