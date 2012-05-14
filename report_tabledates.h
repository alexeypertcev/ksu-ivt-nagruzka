#ifndef REPORT_TABLEDATES_H
#define REPORT_TABLEDATES_H

#include <QObject>
#include <QStringList>
#include "errors.h"

class Tabledata
{
public:
    Tabledata();

    void set_header_sheet(QStringList hs);
    void set_list_one(QList<QStringList> lo);
    void set_list_two(QList<QStringList> lt);
    void set_list_one_sum(QStringList lon);
    void set_list_two_sum(QStringList lts);
    void set_list_all_sum(QStringList las);

    QString get_header_FIO();
    QString get_header_degre_and_status();
    QString get_header_academic_year();
    QString get_header_name_kafedry_faculty();
    QString get_header_business_base_of_training();
    QString get_header_vice_rector_on_education_work();
    QString get_header_obiem();

    /*
    query.exec("insert into other_data values('academic_year', '2011/2012')");
    query.exec("insert into other_data values('name_kafedry_faculty', 'Программного обеспечения и администрирования информационных систем')");
    query.exec("insert into other_data values('business_base_of_training', 'бюджет')");
    query.exec("insert into other_data values('vice_rector_on_education_work', 'Захаров В.В.')");
    */

    QStringList get_header_sheet();
    QList<QStringList> get_list_one();
    QList<QStringList> get_list_two();
    QStringList get_list_one_sum();
    QStringList get_list_two_sum();
    QStringList get_list_all_sum();

private:
    QStringList header_sheet;
    QList<QStringList> list_one;
    QList<QStringList> list_two;
    QStringList list_one_sum;
    QStringList list_two_sum;
    QStringList list_all_sum;
};
#endif // REPORT_TABLEDATES_H
