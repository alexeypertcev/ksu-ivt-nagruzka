#ifndef TEACHERS_LIST_H
#define TEACHERS_LIST_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlQuery>
//#include <QItemDelegate>

QT_BEGIN_NAMESPACE
class Teachers_list_model;
QT_END_NAMESPACE

namespace Ui {
    class Teachers_list;
}

class Teachers_list : public QWidget
{
    Q_OBJECT

public:
    explicit Teachers_list(QWidget *parent = 0);
    ~Teachers_list();
public slots:
    void update();
private:
    Ui::Teachers_list *ui;
    Teachers_list_model* sqlmodel_teachers_list;
};



class Teachers_list_model : public QSqlQueryModel
{
    Q_OBJECT
public:
    Teachers_list_model(QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void refresh();
private:
    QStringList all_hours;
};


#endif // TEACHERS_LIST_H
