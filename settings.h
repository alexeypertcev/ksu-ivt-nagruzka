/****************************************************************************
** Alexey Pertcev alexey.pertcev@gmail.com
****************************************************************************/
#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSqlQueryModel>
#include "errors.h"

QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class Coefficients_model;
QT_END_NAMESPACE

namespace Ui {
    class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent, QSqlRelationalTableModel* tablemodel_spec, QSqlRelationalTableModel* tablemodel_stat);
    ~Settings();
    void set_tab(int index);
private:
    Ui::Settings *ui;
    QSqlRelationalTableModel* tablemodel_spec;
    QSqlRelationalTableModel* tablemodel_stat;
    Coefficients_model* coefficients_model;
private slots:


private slots:
    void on_pushButton_del_dolj_clicked();
    void on_pushButton_add_dolj_clicked();
    void on_pushButton_del_spec_clicked();
    void on_pushButton_add_spec_clicked();
    void on_lineEdit_editingFinished();
    void on_lineEdit_2_editingFinished();
    void on_lineEdit_3_editingFinished();
    void on_lineEdit_4_editingFinished();
    void update_other_data();
    void on_lineEdit_5_editingFinished();
};

class Coefficients_model : public QSqlQueryModel
{
    Q_OBJECT
public:
    Coefficients_model(QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void refresh();
};


#endif // SETTINGS_H
