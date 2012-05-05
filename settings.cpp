#include "settings.h"
#include "ui_settings.h"

#include <QtGui>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include <QModelIndex>

Settings::Settings(QWidget *parent, QSqlRelationalTableModel* tm_spec, QSqlRelationalTableModel* tm_stat) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);


    tablemodel_spec = tm_spec;
    tablemodel_spec->setRelation(3, QSqlRelation("form_training", "name", "name"));
    ui->tableView->setModel(tablemodel_spec);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    ui->tableView->update();

    tablemodel_stat = tm_stat;
    ui->tableView_2->setModel(tablemodel_stat);
    ui->tableView_2->update();

    tablemodel_spec->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    tablemodel_spec->setHeaderData(1, Qt::Horizontal, QObject::tr("Факультет"));
    tablemodel_spec->setHeaderData(2, Qt::Horizontal, QObject::tr("Специальность"));
    tablemodel_spec->setHeaderData(3, Qt::Horizontal, QObject::tr("Форма обучения"));
    ui->tableView->setColumnWidth(0,35);
    ui->tableView->setColumnWidth(1,85);
    ui->tableView->setColumnWidth(2,100);
    ui->tableView->setColumnWidth(3,105);

    ui->tableView_2->setColumnWidth(0,120);

    coefficients_model = new Coefficients_model();
    coefficients_model->refresh();
    ui->tableView_3->setModel(coefficients_model);

    coefficients_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Название"));
    coefficients_model->setHeaderData(2, Qt::Horizontal, QObject::tr("Норма"));
    ui->tableView_3->setColumnWidth(0,0);
    ui->tableView_3->setColumnWidth(1,360);
    ui->tableView_3->setColumnWidth(2,50);

    update_other_data();
}

Settings::~Settings()
{
    delete ui;
}


void Settings::on_pushButton_add_spec_clicked()
{
    QString s = "insert into speciality values(NULL, 'ФИВТ', 'МОиАИС', 'оч')";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        QMessageBox::warning(this, tr("Error querry"),
                             tr("The database reported an error: %1").arg(tablemodel_spec->lastError().text()));
    }
    tablemodel_spec->select();
}

void Settings::on_pushButton_del_spec_clicked()
{
    int row = ui->tableView->currentIndex().row();
    QString s = "DELETE FROM speciality WHERE id = '" + tablemodel_spec->data( tablemodel_spec->index(row,0),
                                                                              Qt::DisplayRole ).toString() + "';";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        QMessageBox::warning(this, tr("Error querry"),
                             tr(" Невозможно выполнить данное действие \n Возможно значение которое вы хотите удалить испульзуется в базе данных"));
    }
    tablemodel_spec->select();
}

void Settings::on_pushButton_add_dolj_clicked()
{
    QString s = "insert into status values('', 0)";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        QMessageBox::warning(this, tr("Error querry"),
                             tr("The database reported an error: %1").arg(tablemodel_stat->lastError().text()));
    }
    tablemodel_stat->select();
}

void Settings::on_pushButton_del_dolj_clicked()
{
    QString s = "DELETE FROM status WHERE name = '"+ ui->tableView_2->currentIndex().data(Qt::DisplayRole).toString() + "';";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        QMessageBox::warning(this, tr("Error querry"),
                             tr("The database reported an error: %1").arg(tablemodel_stat->lastError().text()));
    }
    tablemodel_stat->select();
}

void Settings::set_tab(int index){
    ui->tabWidget->setCurrentIndex(index);
}

void Settings::on_lineEdit_editingFinished()
{
    QString s = "update other_data set 'value' = '"+ ui->lineEdit->text() +"' where name = 'academic_year'";
    QSqlQuery query;
    query.exec(s);
    update_other_data();
}

void Settings::on_lineEdit_2_editingFinished()
{
    QString s = "update other_data set 'value' = '"+ ui->lineEdit_2->text() +"' where name = 'name_kafedry_faculty'";
    QSqlQuery query;
    query.exec(s);
    update_other_data();
}

void Settings::on_lineEdit_3_editingFinished()
{
    QString s = "update other_data set 'value' = '"+ ui->lineEdit_3->text() +"' where name = 'business_base_of_training'";
    QSqlQuery query;
    query.exec(s);
    update_other_data();
}

void Settings::on_lineEdit_4_editingFinished()
{
    QString s = "update other_data set 'value' = '"+ ui->lineEdit_4->text() +"' where name = 'vice_rector_on_education_work'";
    QSqlQuery query;
    query.exec(s);
    update_other_data();
}

void Settings::update_other_data()
{
    QSqlQuery query;
    query.exec("SELECT name, value FROM other_data");

    while(query.next()){
        if (query.value(0).toString() == "academic_year"){
            ui->lineEdit->setText(query.value(1).toString());
        } else if (query.value(0).toString() == "name_kafedry_faculty"){
            ui->lineEdit_2->setText(query.value(1).toString());
        } else if (query.value(0).toString() == "business_base_of_training"){
            ui->lineEdit_3->setText(query.value(1).toString());
        } else if (query.value(0).toString() == "vice_rector_on_education_work"){
            ui->lineEdit_4->setText(query.value(1).toString());
        } else {
            ERROR_REPORT("0x");
        }
    }
}

/***********************************************************
*   Coefficients_model
************************************************************/


Coefficients_model::Coefficients_model(QObject *parent) :
    QSqlQueryModel(parent)
{


}

Qt::ItemFlags Coefficients_model::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() == 2 )
    {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

void Coefficients_model::refresh()
{
    this->setQuery("SELECT name, name, value  "
                   "FROM coefficients");

}

QVariant Coefficients_model::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    QString buf;
    switch (role)
    {
    case Qt::DisplayRole:
        if (index.column() == 1)
        {
            if (value.toString() == "coefficient_lection_hr"){
                return "Для лекций, часов на лекцию";
            }
            if (value.toString() == "coefficient_labs_for_undergroup_hr"){
                return "Для лабораторных работ, часов на подгруппу";
            }
            if (value.toString() == "coefficient_practice_for_group_hr"){
                return "Для практических занятий, часов на группу";
            }
            if (value.toString() == "coefficient_individ_for_KCR_hr"){
                return "Для индивидуальных занятий, часов на КСР";
            }
            if (value.toString() == "coefficient_kontr_rab_for_quantitycourse_min"){
                return "Для контрольных работ, минут на количество человек на курсе";
            }
            if (value.toString() == "coefficient_offset_for_quantitycourse_min"){
                return "Для зачетов, минут на количество человек на курсе";
            }
            if (value.toString() == "coefficient_examen_for_quantitycourse_min"){
                return "Для экзаменов, минут на количество человек на курсе";
            }
            if (value.toString() == "coefficient_coursework_for_quantitycourse_hr"){
                return "Для курсовых работ, минут на количество человек на курсе";
            }
            if (value.toString() == "coefficient_consultation_ochnui_percent"){
                return "Для консультаций очной формы, процент от лекций";
            }
            if (value.toString() == "coefficient_consultation_zaochnui_percent"){
                return "Для консультаций заочной формы, процент от лекций";
            }
            if (value.toString() == "coefficient_consultation_och_zaoch_percent"){
                return "Для консультаций очно-заочной формы, процент от лекций";
            }
            if (value.toString() == "coefficient_consultation_add_is_examen_for_group"){
                return "Дополнительно для консультаций (если экзамен), часов на группу ";
            }
        }
        break;
    }
    return value;
}

bool Coefficients_model::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
    if (index.column() != 2)
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);

    QString s = "update coefficients set value = '"+ value.toString() +"' where name = '"+ data(primaryKeyIndex, Qt::DisplayRole).toString() + "';";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        return false;
    }
    refresh();
    return true;
}
