#ifndef SUBJECTINSEMESTER_SQLMODEL_H
#define SUBJECTINSEMESTER_SQLMODEL_H

#include <QSqlQueryModel>

class SubjectinsemesterSqlModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    SubjectinsemesterSqlModel(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void setspeciality_id(QString id);
    void refresh();
    bool add();
private:
    QString speciality_id;

};

#endif // SUBJECTINSEMESTER_SQLMODEL_H
