#ifndef REPORTS_CREATER_H
#define REPORTS_CREATER_H

#include <QtXml>
#include <QtCore/QFile>
#include <QSqlQuery>
#include <QMessageBox>
#include "report_tabledates.h"
#include "errors.h"

#include "libmsdoc/cdocxlsx.h"

class Reports_creater
{
public:
    /*
     report_for_teachers
     report_for_kafedry

     report_for_subject

     */

    Reports_creater();
    bool create_report(QStringList teachers_id_list, QString template_patch, QString report_patch, QString type_report);
    bool create_report_ods( QList<Tabledata> list_tabledata, QString template_path, QString report_path);
    bool create_report_xlsx(QList<Tabledata> list_tabledata, QString template_path, QString report_path);

    bool create_report_for_kafedry(QString report_path);
};

#endif // REPORTS_CREATER_H
