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
