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

        QSqlRelationalTableModel *tablemodel_teachers = new QSqlRelationalTableModel(this);
        tablemodel_teachers->setTable("teachers");
        tablemodel_teachers->setEditStrategy(QSqlTableModel::OnManualSubmit);
        tablemodel_teachers->select();
        tablemodel_teachers->setRelation(4, QSqlRelation("status", "status_name", "name"));
        ui->tableView_2->setModel(tablemodel_teachers);
        ui->tableView_2->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));





            }



/*

        QSqlQuery qry;
        qry.exec("SELECT * FROM subject;");


        ui->tableWidget->setColumnCount(1);
        ui->tableWidget->setRowCount(0);

        qDebug() << qry.size();

        while (qry.next()){
           ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
           QTableWidgetItem *twi = ui->tableWidget->item(1, 0);
           twi = new QTableWidgetItem();
           twi->setText("xyi");
           twi->setText(qry.value(0).toString());
           qDebug() << qry.value(0).toString();

        }
*/
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
    tablemodel_subject->database().transaction();
     if (tablemodel_subject->submitAll()) {
         tablemodel_subject->database().commit();
     } else {
         tablemodel_subject->database().rollback();
         QMessageBox::warning(this, tr("Cached Table"),
                              tr("The database reported an error: %1")
                              .arg(tablemodel_subject->lastError().text()));
     }
}
