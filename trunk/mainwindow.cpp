//---------------------------------------------
//  alexey.pertcev@gmail.com  Alexey Pertcev
//
//
//---------------------------------------------

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "table_editor.h"

#include <QtGui>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include <QModelIndex>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (createConnection()){

        QSqlQuery query;
        query.exec("PRAGMA foreign_keys = ON;");

        tablemodel_subject = new QSqlRelationalTableModel(this);
        tablemodel_subject->setTable("subject");
        tablemodel_subject->select();
        ui->tableView->setModel(tablemodel_subject);
        ui->tableView->update();

        QSqlRelationalTableModel *tablemodel_teachers = new QSqlRelationalTableModel(this);
        tablemodel_teachers->setTable("teachers");
        tablemodel_teachers->setEditStrategy(QSqlTableModel::OnManualSubmit);
        tablemodel_teachers->select();
        tablemodel_teachers->setRelation(4, QSqlRelation("status", "status_name", "name"));
        ui->tableView_2->setModel(tablemodel_teachers);
        ui->tableView_2->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

            }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::push1(){

}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_pushButton_5_clicked()
{

}

void MainWindow::on_action_6_activated()
{
 //   create_new_db();
}

void MainWindow::on_pushButton_3_clicked()
{
    QString s = "insert into subject values('')";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        QMessageBox::warning(this, tr("Error querry"),
                             tr("The database reported an error: %1")
                             .arg(tablemodel_subject->lastError().text()));
    }
    tablemodel_subject->select();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString s = "DELETE FROM subject WHERE name = '"+ ui->tableView->currentIndex().data(Qt::DisplayRole).toString() + "';";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        QMessageBox::warning(this, tr("Error querry"),
                             tr("The database reported an error: %1")
                             .arg(tablemodel_subject->lastError().text()));
    }
    tablemodel_subject->select();
}
