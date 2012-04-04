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
