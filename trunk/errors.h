#ifndef ERRORS_H
#define ERRORS_H

#include <QDebug>
#include <QMessageBox>

#define ERROR_REPORT( err ); qDebug()<<err;
#define DEBUG_MESSAGE( s ); qDebug()<<s;

class Error_report
{
public:
    Error_report();
};

#endif // ERRORS_H
