#include "settings.h"
#include "ui_settings.h"

#include <QtGui>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include <QModelIndex>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);


    tablemodel_spec = new QSqlRelationalTableModel(this);
    tablemodel_spec->setTable("speciality");
    tablemodel_spec->setEditStrategy(QSqlTableModel::OnFieldChange);
    tablemodel_spec->select();
    ui->tableView->setModel(tablemodel_spec);
    ui->tableView->update();

    tablemodel_stat = new QSqlRelationalTableModel(this);
    tablemodel_stat->setTable("status");
    tablemodel_stat->setEditStrategy(QSqlTableModel::OnFieldChange);
    tablemodel_stat->select();
    ui->tableView_2->setModel(tablemodel_stat);
    ui->tableView_2->update();

}

Settings::~Settings()
{
    delete ui;
}


void Settings::on_pushButton_add_spec_clicked()
{
    QString s = "insert into speciality values('')";
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
    QString s = "DELETE FROM speciality WHERE name = '"+ ui->tableView->currentIndex().data(Qt::DisplayRole).toString() + "';";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        QMessageBox::warning(this, tr("Error querry"),
                             tr("The database reported an error: %1").arg(tablemodel_spec->lastError().text()));
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
