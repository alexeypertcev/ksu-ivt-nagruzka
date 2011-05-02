//---------------------------------------------
//  alexey.pertcev@gmail.com  Alexey Pertcev
//
//
//
//---------------------------------------------

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "table_editor.h"
#include "settings.h"

#include <QtGui>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include <QModelIndex>
#include <QAbstractItemModel>

#define SELECT_STUDENTS "SELECT student_on_course.speciality_name, student_on_course.course, student_on_group.group_, student_on_group.undergroup, student_on_group.quantity FROM student_on_course INNER JOIN student_on_group ON student_on_course.id = student_on_group.student_on_course_id;"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (createConnection()){

        QSqlQuery query;
        query.exec("PRAGMA foreign_keys = ON;");

        // subject table
        tablemodel_subject = new QSqlRelationalTableModel(this);
        tablemodel_subject->setTable("subject");
        tablemodel_subject->setEditStrategy(QSqlTableModel::OnFieldChange);
        tablemodel_subject->select();
        ui->tableView->setModel(tablemodel_subject);
        ui->tableView->update();

        // teachers table
        tablemodel_teachers = new QSqlRelationalTableModel(this);
        tablemodel_teachers->setTable("teachers");
        tablemodel_teachers->setEditStrategy(QSqlTableModel::OnFieldChange);
        tablemodel_teachers->select();
        tablemodel_teachers->setRelation(4, QSqlRelation("status", "name", "name"));

        ui->tableView_2->setModel(tablemodel_teachers);
        ui->tableView_2->setItemDelegate(new QSqlRelationalDelegate(ui->tableView_2));
        ui->tableView_2->update();

        // students table
        tablemodel_students = new QSqlRelationalTableModel(this);
        tablemodel_students->setTable("students");
        tablemodel_students->setEditStrategy(QSqlTableModel::OnFieldChange);
        tablemodel_students->select();
        tablemodel_students->setRelation(1, QSqlRelation("speciality", "name", "name"));

        ui->tableView_3->setModel(tablemodel_students);
        ui->tableView_3->setItemDelegate(new QSqlRelationalDelegate(ui->tableView_3));
        ui->tableView_3->update();

        set_design_window();
     }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_6_activated()
{
    create_all_tables();
    insert_main_data();
}

void MainWindow::on_action_7_activated()
{
    drop_all_tables();
}

void MainWindow::on_pushButton_add_subject_clicked()
{
    QString s = "insert into subject values('')";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        QMessageBox::warning(this, tr("Error querry"),
                             tr("The database reported an error: %1").arg(tablemodel_subject->lastError().text()));
    }
    tablemodel_subject->select();
}

void MainWindow::on_pushButton_del_subject_clicked()
{
    QString s = "DELETE FROM subject WHERE name = '"+ ui->tableView->currentIndex().data(Qt::DisplayRole).toString() + "';";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        QMessageBox::warning(this, tr("Error querry"),
                             tr("The database reported an error: %1").arg(tablemodel_subject->lastError().text()));
    }
    tablemodel_subject->select();
}

void MainWindow::on_pushButton_add_teachers_clicked()
{
    QString s = "insert into teachers values(NULL, 'f', 'i', 'o', 'default', 1.0 );";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        QMessageBox::warning(this, tr("Error querry"),
                             tr("The database reported an error: %1").arg(tablemodel_subject->lastError().text()));
    }
    tablemodel_teachers->select();
}

void MainWindow::on_pushButton_del_teachers_clicked()
{
    int row = ui->tableView_2->currentIndex().row();
    QString s = "DELETE FROM teachers WHERE id = '" + tablemodel_teachers->data( tablemodel_teachers->index(row,0),
                                                                                Qt::DisplayRole ).toString() + "';";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        QMessageBox::warning(this, tr("Error querry"),
                             tr("The database reported an error: %1").arg(tablemodel_subject->lastError().text()));
    }
    tablemodel_teachers->select();
}

void MainWindow::on_action_4_activated()
{
    Settings s;
    s.set_tab(0);
    s.exec();
}

void MainWindow::on_action_5_activated()
{
    Settings s;
    s.set_tab(1);
    s.exec();
}

void MainWindow::set_design_window()
{
    ui->tableView_2->setColumnWidth(0,40);
    ui->tableView_2->setColumnWidth(1,180);
    ui->tableView_2->setColumnWidth(2,180);
    ui->tableView_2->setColumnWidth(3,180);
    ui->tableView_2->setColumnWidth(4,120);
    ui->tableView_2->setColumnWidth(5,60);

    tablemodel_subject->setHeaderData(0, Qt::Horizontal, QObject::tr("Название"));


    tablemodel_teachers->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    tablemodel_teachers->setHeaderData(1, Qt::Horizontal, QObject::tr("Фамилия"));
    tablemodel_teachers->setHeaderData(2, Qt::Horizontal, QObject::tr("Имя"));
    tablemodel_teachers->setHeaderData(3, Qt::Horizontal, QObject::tr("Отчество"));
    tablemodel_teachers->setHeaderData(4, Qt::Horizontal, QObject::tr("Должность"));
    tablemodel_teachers->setHeaderData(5, Qt::Horizontal, QObject::tr("Ставка"));

}

void MainWindow::on_pushButton_clicked()
{
    /*
    QAbstractItemModel* m = tablemodel_teachers->model();
    if(!m->setData( m->index( 1, 1 ), QBrush( Qt::red ), Qt::BackgroundRole )){
        qDebug() << "background not set";
    }
    //tablemodel_teachers->setData(tablemodel_teachers->index( 1, 1 ), "hellowrld", Qt::EditRole);
    //tablemodel_teachers->setData( tablemodel_teachers->index( 1, 1 ), QBrush(Qt::red) , Qt::BackgroundRole );
    */
}

void MainWindow::on_pushButton_add_student_clicked()
{
    QString s = "insert into students values(NULL, 'МОиАИС', 1, 1, 1, 1);";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        QMessageBox::warning(this, tr("Error querry"),
                             tr("The database reported an error: %1").arg(tablemodel_students->lastError().text()));
    }
    tablemodel_students->select();
}

void MainWindow::on_pushButton_del_student_clicked()
{
    int row = ui->tableView_3->currentIndex().row();
    QString s = "DELETE FROM students WHERE id = '" + tablemodel_students->data( tablemodel_students->index(row,0),
                                                                                 Qt::DisplayRole ).toString() + "';";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        QMessageBox::warning(this, tr("Error querry"),
                             tr("The database reported an error: %1").arg(tablemodel_students->lastError().text()));
    }
    tablemodel_students->select();

}


