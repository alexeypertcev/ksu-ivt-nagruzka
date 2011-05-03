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

        // curriculum table
        tablemodel_curriculum = new QSqlRelationalTableModel(this);
        tablemodel_curriculum->setTable("curriculum");
        tablemodel_curriculum->setEditStrategy(QSqlTableModel::OnFieldChange);
        tablemodel_curriculum->select();
        tablemodel_curriculum->setRelation(1, QSqlRelation("speciality", "name", "name"));
        tablemodel_curriculum->setRelation(2, QSqlRelation("subject", "name", "name"));

        ui->tableView_4->setModel(tablemodel_curriculum);
        ui->tableView_4->setItemDelegate(new QSqlRelationalDelegate(ui->tableView_4));
        ui->tableView_4->update();

        // subjects_in_semmestre table
        tablemodel_subjects_in_semmestre = new QSqlRelationalTableModel(this);
        tablemodel_subjects_in_semmestre->setTable("subjects_in_semmestre");
        tablemodel_subjects_in_semmestre->setEditStrategy(QSqlTableModel::OnFieldChange);
        tablemodel_subjects_in_semmestre->select();
        tablemodel_subjects_in_semmestre->setRelation(1, QSqlRelation("students", "id", "id"));
        tablemodel_subjects_in_semmestre->setRelation(2, QSqlRelation("curriculum", "id", "id"));

        ui->tableView_5->setModel(tablemodel_subjects_in_semmestre);
        ui->tableView_5->setItemDelegate(new QSqlRelationalDelegate(ui->tableView_5));
        ui->tableView_5->update();

        // distribution table
        tablemodel_distribution = new QSqlRelationalTableModel(this);
        tablemodel_distribution->setTable("distribution");
        tablemodel_distribution->setEditStrategy(QSqlTableModel::OnFieldChange);
        tablemodel_distribution->select();
        tablemodel_distribution->setRelation(1, QSqlRelation("subjects_in_semmestre", "id", "id"));
        tablemodel_distribution->setRelation(2, QSqlRelation("teachers", "id", "id"));

        ui->tableView_6->setModel(tablemodel_distribution);
        ui->tableView_6->setItemDelegate(new QSqlRelationalDelegate(ui->tableView_6));
        ui->tableView_6->update();


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
    tablemodel_teachers->setTable("teachers");
    tablemodel_teachers->setEditStrategy(QSqlTableModel::OnFieldChange);
    tablemodel_teachers->select();
    tablemodel_teachers->setRelation(4, QSqlRelation("status", "name", "name"));

    ui->tableView_2->setModel(tablemodel_teachers);
    ui->tableView_2->setItemDelegate(new QSqlRelationalDelegate(ui->tableView_2));
    ui->tableView_2->update();

    //ui->tableView_2->itemDelegate()->

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

void MainWindow::on_pushButton_add_curriculum_clicked()
{
    QString s = "insert into curriculum values(NULL, 'МОиАИС', 'ПП', 1, 1, 1, 1, 1);";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){QMessageBox::warning(this, tr("Error querry"), "");}

    tablemodel_curriculum->select();
}

void MainWindow::on_pushButton_del_curriculum_clicked()
{

}

void MainWindow::on_pushButton_add_subjects_in_semmestre_clicked()
{
    QString s = "insert into subjects_in_semmestre values(NULL, 1, 1);";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){QMessageBox::warning(this, tr("Error querry"), "");}

    tablemodel_subjects_in_semmestre->select();
}

void MainWindow::on_pushButton_del_subjects_in_semmestre_clicked()
{

}

void MainWindow::on_pushButton_add_distribution_clicked()
{
    QString s = "insert into distribution values(NULL, 1, 1);";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){QMessageBox::warning(this, tr("Error querry"), "");}

    tablemodel_distribution->select();
}

void MainWindow::on_pushButton_del_distribution_clicked()
{

}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch(index){
    case 0:
        update_subject();
        break;
    case 1:
        update_teachers();
        break;
    case 2:
        update_students();
        break;
    case 3:
        update_curriculum();
        break;
    case 4:
        update_subject_in_semestre();
        break;
    case 5:
        update_disctibution();
        break;
    case 6:

        break;
    default:

        break;
    }
}
void MainWindow::update_subject()
{

}

void MainWindow::update_teachers()
{

}

void MainWindow::update_students()
{

}

void MainWindow::update_curriculum()
{

}

void MainWindow::update_subject_in_semestre()
{

}

void MainWindow::update_disctibution()
{

}
