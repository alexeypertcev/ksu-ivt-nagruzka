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

#endif // REPORTS_CREATER_H
