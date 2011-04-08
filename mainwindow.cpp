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
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::push1(){
    //QSqlQuery sql;
    //sql.exec("insert into subject values('matan2', 'tex2')");
    QSqlTableModel *model = new QSqlTableModel(this);
    //model->setQuery("PRAGMA foreign_keys = 1;");
    model->setTable("subject");
    model->select();
    ui->tableView_2->setModel(model);
}

void MainWindow::on_pushButton_clicked()
{
    QSqlTableModel *tablemodel = new QSqlTableModel(this);
    QSqlQueryModel *querymodel = new QSqlQueryModel(this);

    tablemodel->setTable("teachers");
    querymodel->setQuery("SELECT * FROM employee");

    //model->setQuery("PRAGMA foreign_keys = 1;");
    tablemodel->select();
    //querymodel->setRelation(4, QSqlRelation("status_name", "name", "name"));

    ui->tableView->setModel(tablemodel);

}
