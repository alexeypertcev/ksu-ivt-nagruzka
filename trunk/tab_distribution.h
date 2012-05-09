#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <QSqlQueryModel>
#include "errors.h"

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
    bool add();
    bool del(QString id);
    int rowCount (const QModelIndex & parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    int rowCountDB();
    bool clearTable();
private:
    int sum_field(QString field);
    QString subjects_in_semmestre_id;
    int rowsCountDB,
    not_used_lection_hr,
    not_used_labs_hr,
    not_used_practice_hr,
    not_used_individ_hr,
    not_used_kontr_rab_hr,
    not_used_consultation_hr,
    not_used_offset_hr,
    not_used_examen_hr,
    not_used_coursework_hr,
    not_used_diplomwork_hr,
    not_used_praktika_hr,
    not_used_gak_hr,
    not_used_other1,
    not_used_other2,
    not_used_other3,
    not_used_all;
signals:
    void table_changed();

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
    QVariant data(const QModelIndex &index, int role) const;
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
    QVariant data(const QModelIndex &index, int role) const;
    void refresh();
private:
    QString subjects_in_semmestre_id;

};

#endif // DISTRIBUTION_H
