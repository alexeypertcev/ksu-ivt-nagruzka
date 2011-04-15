//---------------------------------------------
//  alexey.pertcev@gmail.com  Alexey Pertcev
//
//
//---------------------------------------------

#include "mainwindow.h"
#include "ui_mainwindow.h"
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

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/perec/nagruzka.db");

    if (!db.open()){

        QMessageBox m;
        m.setText("db is not open");
        m.exec();

    } else {

        QSqlQuery query;
        query.exec("PRAGMA foreign_keys = ON;");
/*
        QSqlRelationalTableModel *tablemodel_subject = new QSqlRelationalTableModel(this);
        tablemodel_subject->setTable("subject");
        tablemodel_subject->select();
        ui->tableWidget->setModel(tablemodel_subject);

        QSqlRelationalTableModel *tablemodel_teachers = new QSqlRelationalTableModel(this);
        tablemodel_teachers->setTable("teachers");
        tablemodel_teachers->select();
        tablemodel_teachers->setRelation(4, QSqlRelation("status", "status_name", "name"));
        ui->tableView->setModel(tablemodel_teachers);
        ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
*/

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
