#ifndef REPORTS_CREATER_H
#define REPORTS_CREATER_H

#include <QtXml>
#include <QtCore/QFile>
#include <QSqlQuery>
#include <QMessageBox>
#include "report_tabledates.h"
#include "errors.h"

#include "libmsdoc/cdocxlsx.h"

class Reports
{
public:
    //    bool create_report_ods( QList<Tabledata> list_tabledata, QString template_path, QString report_path);

    Reports(){}

    bool create_report_teacherscard(QStringList teachers_id_list, QString template_patch, QString report_patch, QString type_report, bool split_kard);

    bool write_report_teacherscard_xlsx(QList<Tabledata> list_tabledata, QString template_path, QString report_path);

    bool create_report_for_kafedry(QString report_path);
};

#endif // REPORTS_CREATER_H
