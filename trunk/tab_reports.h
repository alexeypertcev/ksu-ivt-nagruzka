#ifndef REPORTS_CREATER_H
#define REPORTS_CREATER_H

#include <QtXml>
#include <QtCore/QFile>
#include <QSqlQuery>
#include "report_tabledates.h"
#include "errors.h"

#include "libmsdoc/cdocxlsx.h"

bool create_report(QStringList teachers_id_list, QString template_patch, QString report_patch, QString type_report);
bool create_report_ods( QList<Tabledata> list_tabledata, QString template_patch, QString report_patch);
bool create_report_xlsx(QList<Tabledata> list_tabledata, QString template_patch, QString report_patch);

class reports_creater
{
public:
    reports_creater();
};



#endif // REPORTS_CREATER_H
