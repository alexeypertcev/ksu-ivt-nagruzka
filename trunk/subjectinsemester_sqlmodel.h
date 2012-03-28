/****************************************************************************
** Alexey Pertcev alexey.pertcev@gmail.com
****************************************************************************/
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
    int rowCount (const QModelIndex & parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    int rowCountDB();
private:
    unsigned int get_sum_current_speciality();
    QString speciality_id;
    unsigned int rowsCountDB;
    unsigned int sum;

};

#endif // SUBJECTINSEMESTER_SQLMODEL_H
