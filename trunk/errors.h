#ifndef MERRORS_H
#define MERRORS_H

#include <QDebug>
#include <QMessageBox>


#define ERROR_REPORT( err );     Error_report err_report;\
                                 err_report.show_mesage_error( err );

#define DEBUG_MESSAGE( s ); qDebug()<<s;

class Error_report
{

public:
    Error_report();
    void show_mesage_error(QString s_err);
private:
    QMap<QString, QString> map;
};

#endif // MERRORS_H
