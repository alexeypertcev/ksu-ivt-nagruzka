#ifndef REPORTS_CREATER_H
#define REPORTS_CREATER_H

#include <QtXml>
#include <QtCore/QFile>
#include <QSqlQuery>
#include "report_writter_ods.h"

bool create_report(QStringList teachers_id_list, QString template_patch, QString report_patch, QString type_report);
bool xml_work(QString path);
int removeFolder(QDir & dir);
bool create_report_xls(QStringList teachers_id_list, QString template_patch, QString report_patch);
bool create_report_ods(QStringList teachers_id_list, QString template_patch, QString report_patch);


class reports_creater
{
public:
    reports_creater();
};

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

#endif // REPORTS_CREATER_H
