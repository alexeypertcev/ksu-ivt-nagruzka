//---------------------------------------------
//  alexey.pertcev@gmail.com  Alexey Pertcev
//
//
//
//---------------------------------------------

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "settings.h"
#include "curriculum_sqlmodel.h"
#include "delegates.h"

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
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (createConnection()){

        QSqlQuery query;
        query.exec("PRAGMA foreign_keys = ON;");

        tablemodel_spec = new QSqlRelationalTableModel(this);
        tablemodel_spec->setTable("speciality");
        tablemodel_spec->setEditStrategy(QSqlTableModel::OnFieldChange);
        tablemodel_spec->select();

        ui->comboBox->setModel(tablemodel_spec);
        ui->comboBox_2->setModel(tablemodel_spec);

        tablemodel_stat = new QSqlRelationalTableModel(this);
        tablemodel_stat->setTable("status");
        tablemodel_stat->setEditStrategy(QSqlTableModel::OnFieldChange);
        tablemodel_stat->select();

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
        sqlmodel_curriculum = new CurriculumSqlModel(this);
        update_curriculum();
        ui->tableView_4->setModel(sqlmodel_curriculum);

        ComboBoxDelegate *speciality_delegate = new ComboBoxDelegate("speciality",this);

        SpinBoxDelegate *semester_delegate = new SpinBoxDelegate(1,12,this);
        ui->tableView_4->setItemDelegateForColumn(3, semester_delegate);

        ui->tableView_4->update();





        set_design_window();

        QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update_curriculum()));
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
    Settings* s = new Settings(this, tablemodel_spec, tablemodel_stat);
    s->set_tab(0);
    s->exec();
}

void MainWindow::on_action_5_activated()
{
    Settings* s = new Settings(this, tablemodel_spec, tablemodel_stat);
    s->set_tab(1);
    s->exec();
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
    // необязательно, тк в модели всегда актуальное значение
    //sqlmodel_curriculum->setspeciality(ui->comboBox->currentText());

    if (!sqlmodel_curriculum->add()){
        QMessageBox::warning(this, tr("Error querry"),"");
    }
    sqlmodel_curriculum->refresh();
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
    sqlmodel_curriculum->setspeciality(ui->comboBox->currentText());
    sqlmodel_curriculum->refresh();
}

void MainWindow::update_subject_in_semestre()
{

}

void MainWindow::update_disctibution()
{

}

void MainWindow::set_design_window()
{
    tablemodel_subject->setHeaderData(0, Qt::Horizontal, QObject::tr("Название"));

    ui->tableView_2->setColumnWidth(0,40);
    ui->tableView_2->setColumnWidth(1,180);
    ui->tableView_2->setColumnWidth(2,180);
    ui->tableView_2->setColumnWidth(3,180);
    ui->tableView_2->setColumnWidth(4,120);
    ui->tableView_2->setColumnWidth(5,60);

    tablemodel_teachers->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    tablemodel_teachers->setHeaderData(1, Qt::Horizontal, QObject::tr("Фамилия"));
    tablemodel_teachers->setHeaderData(2, Qt::Horizontal, QObject::tr("Имя"));
    tablemodel_teachers->setHeaderData(3, Qt::Horizontal, QObject::tr("Отчество"));
    tablemodel_teachers->setHeaderData(4, Qt::Horizontal, QObject::tr("Должность"));
    tablemodel_teachers->setHeaderData(5, Qt::Horizontal, QObject::tr("Ставка"));

    ui->tableView_3->setColumnWidth(0,39);
    ui->tableView_3->setColumnWidth(1,150);
    ui->tableView_3->setColumnWidth(2,145);
    ui->tableView_3->setColumnWidth(3,145);
    ui->tableView_3->setColumnWidth(4,145);
    ui->tableView_3->setColumnWidth(5,145);

    tablemodel_students->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    tablemodel_students->setHeaderData(1, Qt::Horizontal, QObject::tr("Специальность"));
    tablemodel_students->setHeaderData(2, Qt::Horizontal, QObject::tr("Курс"));
    tablemodel_students->setHeaderData(3, Qt::Horizontal, QObject::tr("Кол-во групп"));
    tablemodel_students->setHeaderData(4, Qt::Horizontal, QObject::tr("Кол-во подгрупп"));
    tablemodel_students->setHeaderData(5, Qt::Horizontal, QObject::tr("Кол-во человек"));

    int h=85;
    ui->tableView_4->setColumnWidth(0,40);
    ui->tableView_4->setColumnWidth(1,140);
    ui->tableView_4->setColumnWidth(2,140);
    ui->tableView_4->setColumnWidth(3,h);
    ui->tableView_4->setColumnWidth(4,h);
    ui->tableView_4->setColumnWidth(5,h);
    ui->tableView_4->setColumnWidth(6,h);
    ui->tableView_4->setColumnWidth(7,h);

    sqlmodel_curriculum->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    sqlmodel_curriculum->setHeaderData(1, Qt::Horizontal, QObject::tr("Специальность"));
    sqlmodel_curriculum->setHeaderData(2, Qt::Horizontal, QObject::tr("Курс"));
    sqlmodel_curriculum->setHeaderData(3, Qt::Horizontal, QObject::tr("Семестр"));
}
