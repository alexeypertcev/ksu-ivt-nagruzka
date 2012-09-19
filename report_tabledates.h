#ifndef REPORT_TABLEDATES_H
#define REPORT_TABLEDATES_H

#include <QObject>
#include <QStringList>
#include "errors.h"
#include "functions.h"

class Tabledata
{
public:
    Tabledata();

    void clear();
    void set_header_sheet(QStringList hs);
    void set_list_one(QList<QStringList> lo);
    void set_list_two(QList<QStringList> lt);
//    void set_list_one_sum(QStringList lon);
//    void set_list_two_sum(QStringList lts);
//    void set_list_all_sum(QStringList las);

    QString get_header_FIO();
    QString get_header_Family();
    QString get_header_Family_I_O();
    QString get_header_degre_and_status();
    QString get_header_academic_year();
    QString get_header_name_kafedry_faculty();
    QString get_header_business_base_of_training();
    QString get_header_vice_rector_on_education_work();
    QString get_header_obiem();

    void set_header_obiem(double ob);

    QStringList get_header_sheet();
    QList<QStringList> get_list_one();
    QList<QStringList> get_list_two();
    QStringList get_list_one_sum();
    QStringList get_list_two_sum();
    QStringList get_list_all_sum();

    QList<QStringList> get_list(int i);
    QStringList get_list_sum(int i);

    QString get_name_table_fam();
    QString get_name_table_all();
    void set_name_table_fam(QString s);
    void set_name_table_part(QString s);

    void remove_list_one_last();
    void remove_list_two_last();
    bool is_empty_list_one();
    bool is_empty_list_two();
    QStringList get_list_one_last();
    QStringList get_list_two_last();
    int get_total_hours();

private:
    double obiem;

    QString name_table_fam;
    QString name_table_part;

    QStringList header_sheet;
    QList<QStringList> list_one;
    QList<QStringList> list_two;

};
#endif // REPORT_TABLEDATES_H
