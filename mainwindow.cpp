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
    //QSqlQuery query;
    //query.exec("SELECT name, salary FROM employee WHERE salary > 50000");

  //  while (query.next()) {
  //    QString name = query.value(0).toString();
  //    int salary = query.value(1).toInt();
  //    qDebug() << name << salary;
  //  }
  /*
   QSqlQuery query;
   query.prepare("INSERT INTO employee (id, name, salary) "
          "VALUES (:id, :name, :salary)");
   query.bindValue(":id", 1001);
   query.bindValue(":name", "Thad Beaumont");
   query.bindValue(":salary", 65000);
   query.exec();


   QSqlQuery query;
   query.prepare("INSERT INTO employee (id, name, salary) "
          "VALUES (?, ?, ?)");
   query.addBindValue(1001);
   query.addBindValue("Thad Beaumont");
   query.addBindValue(65000);
   query.exec();



  */


    QSqlTableModel *tablemodel = new QSqlTableModel(this);
    QSqlQueryModel *querymodel = new QSqlQueryModel(this);

    tablemodel->setTable("teachers");
    querymodel->setQuery("SELECT * FROM employee");

    //model->setQuery("PRAGMA foreign_keys = 1;");
    tablemodel->select();
    //querymodel->setRelation(4, QSqlRelation("status_name", "name", "name"));

    ui->tableView->setModel(tablemodel);

}
