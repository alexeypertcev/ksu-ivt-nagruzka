//---------------------------------------------
//  alexey.pertcev@gmail.com  Alexey Pertcev
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

        QSqlTableModel *tablemodel_subject = new QSqlTableModel(this);
        tablemodel_subject->setTable("subject");
        tablemodel_subject->select();
        ui->tableView_2->setModel(tablemodel_subject);

        QSqlRelationalTableModel *tablemodel_teachers = new QSqlRelationalTableModel(this);
        tablemodel_teachers->setTable("teachers");
        tablemodel_teachers->select();

        ui->tableView->setModel(tablemodel_teachers);
        tablemodel_teachers->setRelation(4, QSqlRelation("status", "status_name", "name"));

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
