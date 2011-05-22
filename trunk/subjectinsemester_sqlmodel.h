#ifndef SUBJECTINSEMESTER_SQLMODEL_H
#define SUBJECTINSEMESTER_SQLMODEL_H

#include <QSqlQueryModel>

class SubjectinsemesterSqlModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit SubjectinsemesterSqlModel(QObject *parent = 0);

signals:

public slots:

};

#endif // SUBJECTINSEMESTER_SQLMODEL_H
