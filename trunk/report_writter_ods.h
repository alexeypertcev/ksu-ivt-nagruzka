#ifndef REPORTS_WRITTER_ODS_H
#define REPORTS_WRITTER_ODS_H

#include <QObject>
#include <QMap>
#include <QStringList>
#include "report_tabledates.h"


class reports_writter_ods
{
public:
    reports_writter_ods();
};


class OdsWriter : public QObject
{
    Q_OBJECT
public:
    explicit OdsWriter(QObject *parent = 0);
    ~OdsWriter();
    bool open(QString fname);
    bool save(QString fname);

protected:
    QString tempdir_name;

private:
    bool removeDir(QString dirName);
};

class CardOdsWriter : public OdsWriter
{
    Q_OBJECT
public:
    explicit CardOdsWriter(QObject *parent = 0);
    ~CardOdsWriter();
    bool writeSheet(Tabledata table_data, int i/*номер листа*/);
private:
    bool add_sheet();
    bool remove_old_sheet();
};




#endif // _REPORTS_WRITTER_ODS_H
