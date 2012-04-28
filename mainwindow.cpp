//---------------------------------------------
//  alexey.pertcev@gmail.com  Alexey Pertcev
//
//---------------------------------------------



#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "delegates.h"
#include "settings.h"
#include "tab_subject.h"
#include "tab_teachers.h"
#include "tab_students.h"
#include "tab_curriculum.h"
#include "tab_subjectinsemester.h"
#include "tab_distribution.h"
#include "tab_reports.h"
#include "teachers_list.h"
#include "dialogs.h"


#include <QtGui>
#include <QtSql>
#include <QMessageBox>
#include <QStatusBar>


MainWindow::MainWindow(QString apppath, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    version = "v0.141";
    applicationDirPath = apppath;
    path_db = applicationDirPath + "/nagruzka.db";
    report_path = applicationDirPath;
    report_format = "xlsx";

    sqlmodel_subject = new SubjectSqlModel(this);
    tablemodel_spec = new QSqlRelationalTableModel(this);
    spec_for_combobox_sqlmodel = new SpecialityForComboBoxSqlModel(this);
    tablemodel_stat = new QSqlRelationalTableModel(this);
    sqlmodel_teachers = new TeachersSqlModel(this);
    sqlmodel_students = new StudentsSqlModel(this);
    sqlmodel_curriculum = new CurriculumSqlModel(this);
    sqlmodel_subinsem = new SubjectinsemesterSqlModel(this);
    sinstodistrib_preview = new Sins_to_distrib_preview_SqlModel(this);
    sinstodistrib_detail = new Sins_to_distrib_detail_SqlModel(this);
    sqlmodel_distribution = new DistributionSqlModel(this);
    sqlmodel_teachers_report = new TeachersReportSqlModel(this);

    ui->lineEdit_3->setText(applicationDirPath + "/subject_in_semester.csv");
    ui->lineEdit->setText("/home/perec/Загрузки/ПОиАИС_utf8.txt");

    if (createConnection(path_db)){
        load_db();
    }
}

MainWindow::~MainWindow()
{
    teachers_list->close();
    teachers_list->~Teachers_list();
    delete ui;
}

void MainWindow::load_db()
{
    QSqlQuery query;

    query.exec("PRAGMA foreign_keys = ON;");

    tablemodel_spec = new QSqlRelationalTableModel(this);
    tablemodel_spec->setTable("speciality");
    tablemodel_spec->setEditStrategy(QSqlTableModel::OnFieldChange);
    tablemodel_spec->select();

    //sqlmodel_spec = new QSqlQueryModel(this);
    spec_for_combobox_sqlmodel->refresh();

    ui->comboBox->setModel(spec_for_combobox_sqlmodel);
    ui->comboBox_2->setModel(spec_for_combobox_sqlmodel);
    ui->comboBox_3->setModel(spec_for_combobox_sqlmodel);

    tablemodel_stat = new QSqlRelationalTableModel(this);
    tablemodel_stat->setTable("status");
    tablemodel_stat->setEditStrategy(QSqlTableModel::OnFieldChange);
    tablemodel_stat->select();

    // subject table
    sqlmodel_subject->refresh();
    ui->tableView->setModel(sqlmodel_subject);

    // teachers table
    sqlmodel_teachers->refresh();
    ui->tableView_2->setModel(sqlmodel_teachers);

    StatusDelegate *status_delegate = new StatusDelegate(this);
    ui->tableView_2->setItemDelegateForColumn(4, status_delegate);

    StaffDelegate *staff_delegate = new StaffDelegate(this);
    ui->tableView_2->setItemDelegateForColumn(6, staff_delegate);



    ui->tableView_2->update();

    // students table
    //sqlmodel_students = new StudentsSqlModel(this);
    sqlmodel_students->refresh();
    ui->tableView_3->setModel(sqlmodel_students);
    SpecialityDelegate *speciality_delegate = new SpecialityDelegate(this);
    SpinBoxDelegate *course_delegate = new SpinBoxDelegate(1,6,this);
    ui->tableView_3->setItemDelegateForColumn(1, speciality_delegate);
    ui->tableView_3->setItemDelegateForColumn(2, course_delegate);
    ui->tableView_3->update();

    // curriculum table
    // sqlmodel_curriculum = new CurriculumSqlModel(this);
    update_curriculum();
    ui->tableView_4->setModel(sqlmodel_curriculum);

    SpecialityDelegate *speciality_delegate1 = new SpecialityDelegate(this);
    ComboBoxDelegate *subject_delegate = new ComboBoxDelegate("subject",this);
    SpinBoxDelegate *semester_delegate = new SpinBoxDelegate(1,12,this);
    SpinBoxDelegate *contrwork_delegate = new SpinBoxDelegate(0,6,this);
    CheckBoxDelegate *checkBox_delegate = new CheckBoxDelegate(this);
    ui->tableView_4->setItemDelegateForColumn(1, speciality_delegate1);
    ui->tableView_4->setItemDelegateForColumn(2, subject_delegate);
    ui->tableView_4->setItemDelegateForColumn(3, semester_delegate);
    ui->tableView_4->setItemDelegateForColumn(7, contrwork_delegate);
    ui->tableView_4->setItemDelegateForColumn(9, checkBox_delegate);
    ui->tableView_4->setItemDelegateForColumn(10, checkBox_delegate);
    ui->tableView_4->setItemDelegateForColumn(11, checkBox_delegate);

    ui->tableView_4->update();

    // subjects_in_semmester table
    // sqlmodel_subinsem = new SubjectinsemesterSqlModel(this);
    update_subinsem();
    ui->tableView_5->setModel(sqlmodel_subinsem);


    // distribution tables

    // sinstodistrib_preview = new Sins_to_distrib_preview_SqlModel(this);
    update_sins_to_distribution_preview();
    ui->tableView_6->setModel(sinstodistrib_preview);

    // sinstodistrib_detail = new Sins_to_distrib_detail_SqlModel(this);
    update_sins_to_distribution_detail();
    ui->tableView_7->setModel(sinstodistrib_detail);

    // sqlmodel_distribution = new DistributionSqlModel(this);
    update_sqlmodel_distribution();
    ui->tableView_8->setModel(sqlmodel_distribution);

    FioDelegate *fio_delegate = new FioDelegate(this);
    ui->tableView_8->setItemDelegateForColumn(3, fio_delegate);
    ui->tableView_8->update();

    // report table
    sqlmodel_teachers_report->refresh();
    ui->tableView_9->setModel(sqlmodel_teachers_report);
    ui->tableView_9->update();


    settings = new Settings(this, tablemodel_spec, tablemodel_stat);
    teachers_list = new Teachers_list();
    set_design_all_tab();
    update_report_name();

    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update_curriculum()));
    QObject::connect(ui->comboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(update_subinsem()));
    QObject::connect(ui->comboBox_3, SIGNAL(currentIndexChanged(int)), this, SLOT(update_distribution()));
    QObject::connect(ui->tableView_6, SIGNAL(activated(QModelIndex)), this, SLOT(update_sins_to_distribution_detail()));
    QObject::connect(ui->tableView_6, SIGNAL(activated(QModelIndex)), this, SLOT(update_sqlmodel_distribution()));
    QObject::connect(ui->radioButton_3, SIGNAL(clicked()), this, SLOT(update_distribution()));
    QObject::connect(ui->radioButton_2, SIGNAL(clicked()), this, SLOT(update_distribution()));
    QObject::connect(ui->radioButton, SIGNAL(clicked()), this, SLOT(update_distribution()));
    QObject::connect(ui->tableView_9, SIGNAL(activated(QModelIndex)), this, SLOT(update_report_name()));

    QObject::connect(ui->radioButton_4, SIGNAL(clicked()), this, SLOT(update_report_name()));
    QObject::connect(ui->radioButton_5, SIGNAL(clicked()), this, SLOT(update_report_name()));
    QObject::connect(ui->radioButton_6, SIGNAL(clicked()), this, SLOT(update_report_name()));
    QObject::connect(ui->radioButton_7, SIGNAL(clicked()), this, SLOT(update_report_name()));

    QObject::connect(sqlmodel_distribution, SIGNAL(table_changed()), teachers_list, SLOT(update()));
    QObject::connect(sqlmodel_teachers, SIGNAL(table_changed()), teachers_list, SLOT(update()));
}

void MainWindow::set_applicationDirPath(QString app_path){
    applicationDirPath = app_path;
}

QString MainWindow::get_applicationDirPath(){
    return applicationDirPath;
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
    sqlmodel_subject->add(QString(" "));
    sqlmodel_subject->refresh();
}

void MainWindow::on_pushButton_del_subject_clicked()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedRows();
    QModelIndex index = indexes.at(0);
    sqlmodel_subject->del( sqlmodel_subject->data( sqlmodel_subject->index(index.row(),0), Qt::DisplayRole ).toString());

//    sqlmodel_subject->del(ui->tableView->currentIndex().data(Qt::DisplayRole).toString());
    sqlmodel_subject->refresh();
}

void MainWindow::on_pushButton_add_teachers_clicked()
{
    sqlmodel_teachers->add();
    sqlmodel_teachers->refresh();
}

void MainWindow::on_pushButton_del_teachers_clicked()
{
    int row = ui->tableView_2->currentIndex().row();
    sqlmodel_teachers->del( sqlmodel_teachers->data( sqlmodel_teachers->index(row,0), Qt::DisplayRole ).toString() );
    sqlmodel_teachers->refresh();
}

void MainWindow::on_action_4_activated()
{
    settings->set_tab(0);
    settings->exec();
}

void MainWindow::on_action_5_activated()
{
    settings->set_tab(1);
    settings->exec();
}

void MainWindow::on_pushButton_clicked(){
// отмена удаления преподавателя
    if (sqlmodel_teachers->save_removed()){
        sqlmodel_teachers->cancel_del();
    }
    sqlmodel_teachers->refresh();
}

void MainWindow::on_pushButton_add_student_clicked()
{
    QSqlQuery query;
    QString speciality_id;
    query.exec("SELECT speciality_id FROM students;");

    query.last();
    speciality_id = query.value(0).toString();

    sqlmodel_students->add(speciality_id, "1", "1", "1", "0");
    sqlmodel_students->refresh();
}

void MainWindow::on_pushButton_del_student_clicked()
{
    sqlmodel_students->del(sqlmodel_students->data( sqlmodel_students->index(ui->tableView_3->currentIndex().row(),0), Qt::DisplayRole ).toString());
    sqlmodel_students->refresh();
}

void MainWindow::on_pushButton_add_curriculum_clicked()
{
    if (!sqlmodel_curriculum->add()){
        QMessageBox::warning(this, tr("Error querry"),"");
    }
    sqlmodel_curriculum->refresh();
}

void MainWindow::on_pushButton_del_curriculum_clicked()
{
    sqlmodel_curriculum->del(sqlmodel_curriculum->data( sqlmodel_curriculum->index(ui->tableView_4->currentIndex().row(),0), Qt::DisplayRole ).toString());
    sqlmodel_curriculum->refresh();
}

void MainWindow::on_pushButton_add_subjects_in_semmester_clicked(){
    if (!sqlmodel_subinsem->add()){
        QMessageBox::warning(this, tr("Error querry"),"");
    }
    sqlmodel_subinsem->refresh();
}

void MainWindow::on_pushButton_del_subjects_in_semmester_clicked(){
    sqlmodel_subinsem->del(sqlmodel_subinsem->data( sqlmodel_subinsem->index(ui->tableView_5->currentIndex().row(),0), Qt::DisplayRole ).toString());
    sqlmodel_subinsem->refresh();
}

void MainWindow::on_pushButton_add_distribution_clicked()
{
    sqlmodel_distribution->add();
    sqlmodel_distribution->refresh();
}

void MainWindow::on_pushButton_del_distribution_clicked()
{
    sqlmodel_distribution->del(sqlmodel_distribution->data( sqlmodel_distribution->index(ui->tableView_8->currentIndex().row(),0), Qt::DisplayRole ).toString());
    sqlmodel_distribution->check_entry();
    sqlmodel_distribution->refresh();
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
        update_subinsem();
        break;
    case 5:
        update_distribution();
        break;
    case 6:
        //qDebug() << "update_report()";
        sqlmodel_teachers_report->refresh();
        update_report_name();
        set_design_reports();
        break;
    default:

        break;
    }
}
void MainWindow::update_subject()
{
    sqlmodel_subject->refresh();
    set_design_subject();
}

void MainWindow::update_teachers()
{
    sqlmodel_teachers->refresh();
    set_design_teachers();
    if (ui->pushButton_8->isChecked()){
        teachers_list->update();
    }
}

void MainWindow::update_students()
{
    sqlmodel_students->refresh();
    set_design_students();
}

void MainWindow::update_curriculum()
{
    sqlmodel_curriculum->setspeciality_id(ui->comboBox->get_id());
    sqlmodel_curriculum->refresh();
    set_design_curriculum();
}

void MainWindow::update_subinsem()
{
    sqlmodel_subinsem->setspeciality_id(ui->comboBox_2->get_id());
    sqlmodel_subinsem->refresh();
    set_design_subjects_in_semmester();
}

void MainWindow::update_distribution()
{
    update_sins_to_distribution_preview();
    update_sins_to_distribution_detail();
    update_sqlmodel_distribution();
    if (ui->pushButton_8->isChecked()){
        teachers_list->update();
    }
    set_design_distribution();
}

void MainWindow::update_sins_to_distribution_preview()
{
    if (ui->radioButton_3->isChecked()){
        sinstodistrib_preview->setsemester(0);
    } else if (ui->radioButton_2->isChecked()){
        sinstodistrib_preview->setsemester(2);
    } else if (ui->radioButton->isChecked()){
        sinstodistrib_preview->setsemester(1);
    }
    sinstodistrib_preview->setspeciality_id(ui->comboBox_3->get_id());
    sinstodistrib_preview->refresh();
    ui->tableView_6->update_ids();
}

void MainWindow::update_sins_to_distribution_detail()
{
    sinstodistrib_detail->setsins(ui->tableView_6->get_id());
    sinstodistrib_detail->refresh();
}

void MainWindow::update_sqlmodel_distribution()
{
    sqlmodel_distribution->setsins(ui->tableView_6->get_id());
    sqlmodel_distribution->check_entry();
    sqlmodel_distribution->refresh();
}




void MainWindow::set_design_all_tab()
{
    set_design_subject();
    set_design_teachers();
    set_design_students();
    set_design_curriculum();
    set_design_subjects_in_semmester();
    set_design_distribution();
    set_design_reports();
}

void MainWindow::set_design_subject()
{
    // Subjects
    int i = 0;
    ui->tableView->setColumnWidth(0,400);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    sqlmodel_subject->setHeaderData(0, Qt::Horizontal, QObject::tr("Название"));
    do{ ui->tableView->setRowHeight(i++,25); }while(i<=10);

}

void MainWindow::set_design_teachers()
{
    // Teachers
    ui->tableView_2->setColumnWidth(0,0);   //id
    ui->tableView_2->setColumnWidth(1,180);
    ui->tableView_2->setColumnWidth(2,180);
    ui->tableView_2->setColumnWidth(3,180);
    ui->tableView_2->setColumnWidth(4,120);
    ui->tableView_2->setColumnWidth(5,60);
    ui->tableView_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);

    sqlmodel_teachers->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    sqlmodel_teachers->setHeaderData(1, Qt::Horizontal, QObject::tr("Фамилия"));
    sqlmodel_teachers->setHeaderData(2, Qt::Horizontal, QObject::tr("Имя"));
    sqlmodel_teachers->setHeaderData(3, Qt::Horizontal, QObject::tr("Отчество"));
    sqlmodel_teachers->setHeaderData(4, Qt::Horizontal, QObject::tr("Должность"));
    sqlmodel_teachers->setHeaderData(5, Qt::Horizontal, QObject::tr("Ставка"));
    sqlmodel_teachers->setHeaderData(6, Qt::Horizontal, QObject::tr("Штат"));


}

void MainWindow::set_design_students()
{
    // Students
    ui->tableView_3->setColumnWidth(0,0);  //id
    ui->tableView_3->setColumnWidth(1,150);
    ui->tableView_3->setColumnWidth(2,145);
    ui->tableView_3->setColumnWidth(3,145);
    ui->tableView_3->setColumnWidth(4,145);
    ui->tableView_3->setColumnWidth(5,145);
    ui->tableView_3->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_3->setSelectionBehavior(QAbstractItemView::SelectRows);

    sqlmodel_students->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    sqlmodel_students->setHeaderData(1, Qt::Horizontal, QObject::tr("Специальность"));
    sqlmodel_students->setHeaderData(2, Qt::Horizontal, QObject::tr("Курс"));
    sqlmodel_students->setHeaderData(3, Qt::Horizontal, QObject::tr("Кол-во групп"));
    sqlmodel_students->setHeaderData(4, Qt::Horizontal, QObject::tr("Кол-во подгрупп"));
    sqlmodel_students->setHeaderData(5, Qt::Horizontal, QObject::tr("Кол-во человек"));


}

void MainWindow::set_design_curriculum()
{
    // Curriculum
    int h = 85;
    ui->tableView_4->setColumnWidth(0,0);  //id
    ui->tableView_4->setColumnWidth(1,130);
    ui->tableView_4->setColumnWidth(2,330);
    ui->tableView_4->setColumnWidth(3,h);
    ui->tableView_4->setColumnWidth(4,h);
    ui->tableView_4->setColumnWidth(5,h);
    ui->tableView_4->setColumnWidth(6,h);
    ui->tableView_4->setColumnWidth(7,h);
    ui->tableView_4->setColumnWidth(8,60);
    ui->tableView_4->setColumnWidth(9,60);
    ui->tableView_4->setColumnWidth(10,60);
    ui->tableView_4->setColumnWidth(11,60);
    ui->tableView_4->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_4->setSelectionBehavior(QAbstractItemView::SelectRows);

    int i = 0;
    sqlmodel_curriculum->setHeaderData(i++, Qt::Horizontal, QObject::tr("ID"));
    sqlmodel_curriculum->setHeaderData(i++, Qt::Horizontal, QObject::tr("Специальность"));
    sqlmodel_curriculum->setHeaderData(i++, Qt::Horizontal, QObject::tr("Предмет"));
    sqlmodel_curriculum->setHeaderData(i++, Qt::Horizontal, QObject::tr("Семестр"));
    sqlmodel_curriculum->setHeaderData(i++, Qt::Horizontal, QObject::tr("Лекции"));
    sqlmodel_curriculum->setHeaderData(i++, Qt::Horizontal, QObject::tr("Лаборат."));
    sqlmodel_curriculum->setHeaderData(i++, Qt::Horizontal, QObject::tr("Практич."));
    sqlmodel_curriculum->setHeaderData(i++, Qt::Horizontal, QObject::tr("Контр. раб."));
    sqlmodel_curriculum->setHeaderData(i++, Qt::Horizontal, QObject::tr("КСР"));
    sqlmodel_curriculum->setHeaderData(i++, Qt::Horizontal, QObject::tr("Экз."));
    sqlmodel_curriculum->setHeaderData(i++, Qt::Horizontal, QObject::tr("Зач."));
    sqlmodel_curriculum->setHeaderData(i++, Qt::Horizontal, QObject::tr("Курс."));


}

void MainWindow::set_design_subjects_in_semmester()
{
    // Subjects_in_semmester
    ui->tableView_5->setColumnWidth(0,0); //id
    ui->tableView_5->setColumnWidth(1,330);
    ui->tableView_5->setColumnWidth(2,60);

    int i = 9;
    ui->tableView_5->setColumnWidth(i++,70);
    ui->tableView_5->setColumnWidth(i++,70);
    ui->tableView_5->setColumnWidth(i++,70);
    ui->tableView_5->setColumnWidth(i++,70);
    ui->tableView_5->setColumnWidth(i++,70);
    ui->tableView_5->setColumnWidth(i++,70);
    ui->tableView_5->setColumnWidth(i++,70);
    ui->tableView_5->setColumnWidth(i++,70);
    ui->tableView_5->setColumnWidth(i++,70);
    ui->tableView_5->setColumnWidth(i++,70);
    ui->tableView_5->setColumnWidth(i++,70);
    ui->tableView_5->setColumnWidth(i++,70);
    ui->tableView_5->setColumnWidth(i++,70);
    ui->tableView_5->setColumnWidth(i++,70);
    ui->tableView_5->setColumnWidth(i++,70);
    ui->tableView_5->setColumnWidth(i++,70);
    ui->tableView_5->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_5->setSelectionBehavior(QAbstractItemView::SelectRows);

    i=0;
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("ID"));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Предмет"));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Семестр"));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Специальность"));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Форма обучения"));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Курс"));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Кол-во групп"));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Кол-во подгрупп"));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Кол-во студентов"));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Лекции"));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Лаборат."));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Практич."));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Индивид."));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Контр. раб"));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Консульт."));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Зачеты"));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Экзамены"));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Курс. раб"));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Дипл. раб"));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Практика"));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("ГАК"));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Прочее1"));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Прочее2"));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Прочее3"));
    sqlmodel_subinsem->setHeaderData(i++, Qt::Horizontal, QObject::tr("Итого"));


}

void MainWindow::set_design_distribution()
{
    // Distribution
    ui->tableView_6->setColumnWidth(0,0);  // id
    ui->tableView_6->setColumnWidth(1,173);
    ui->tableView_6->setColumnWidth(2,32);
    ui->tableView_6->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_6->setSelectionBehavior(QAbstractItemView::SelectRows);

    sinstodistrib_preview->setHeaderData(0, Qt::Horizontal, QObject::tr("Предмет"));
    sinstodistrib_preview->setHeaderData(1, Qt::Horizontal, QObject::tr("Сем."));

    int i=0;
    ui->tableView_7->setColumnWidth(i++,0);
    ui->tableView_7->setColumnWidth(i++,220);
    ui->tableView_7->setColumnWidth(i++,34);
    ui->tableView_7->setColumnWidth(i++,65);
    while (i<24){
        ui->tableView_7->setColumnWidth(i++,43);
    }
    ui->tableView_7->setColumnWidth(24,42);
    ui->tableView_7->setSelectionMode(QAbstractItemView::SingleSelection);


    i=1;
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Предмет"));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Семестр"));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Специальность"));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Форма обучения"));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Курс"));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Кол-во групп"));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Кол-во подгрупп"));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Кол-во студентов"));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Лекции"));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Лаборат."));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Практич."));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Индивид."));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Контр. раб"));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Консульт."));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Зачеты"));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Экзамены"));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Курс. раб"));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Дипл. раб"));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Практика"));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("ГАК"));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Прочее1"));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Прочее2"));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Прочее3"));
    sinstodistrib_detail->setHeaderData(i++, Qt::Horizontal, QObject::tr("Итого"));


    // sqlmodel_distribution
    i=0;
    ui->tableView_8->setColumnWidth(i++,0);
    ui->tableView_8->setColumnWidth(i++,180);
    ui->tableView_8->setColumnWidth(i++,33);
    ui->tableView_8->setColumnWidth(i++,180);
    while (i<20){
        ui->tableView_8->setColumnWidth(i++,38);
    }
    ui->tableView_8->setSelectionMode(QAbstractItemView::SingleSelection);

    i=0;
    sqlmodel_distribution->setHeaderData(++i, Qt::Horizontal, QObject::tr("Предмет"));
    sqlmodel_distribution->setHeaderData(++i, Qt::Horizontal, QObject::tr("Сем."));
    sqlmodel_distribution->setHeaderData(++i, Qt::Horizontal, QObject::tr("ФИО"));
    sqlmodel_distribution->setHeaderData(++i, Qt::Horizontal, QObject::tr("Лек."));
    sqlmodel_distribution->setHeaderData(++i, Qt::Horizontal, QObject::tr("Лаб."));
    sqlmodel_distribution->setHeaderData(++i, Qt::Horizontal, QObject::tr("Прак."));
    sqlmodel_distribution->setHeaderData(++i, Qt::Horizontal, QObject::tr("Инд."));
    sqlmodel_distribution->setHeaderData(++i, Qt::Horizontal, QObject::tr("Контр. раб"));
    sqlmodel_distribution->setHeaderData(++i, Qt::Horizontal, QObject::tr("Консульт."));
    sqlmodel_distribution->setHeaderData(++i, Qt::Horizontal, QObject::tr("Зачеты"));
    sqlmodel_distribution->setHeaderData(++i, Qt::Horizontal, QObject::tr("Экзамены"));
    sqlmodel_distribution->setHeaderData(++i, Qt::Horizontal, QObject::tr("Курс. раб"));
    sqlmodel_distribution->setHeaderData(++i, Qt::Horizontal, QObject::tr("Дипл. раб"));
    sqlmodel_distribution->setHeaderData(++i, Qt::Horizontal, QObject::tr("Практика"));
    sqlmodel_distribution->setHeaderData(++i, Qt::Horizontal, QObject::tr("ГАК"));
    sqlmodel_distribution->setHeaderData(++i, Qt::Horizontal, QObject::tr("Прочее1"));
    sqlmodel_distribution->setHeaderData(++i, Qt::Horizontal, QObject::tr("Прочее2"));
    sqlmodel_distribution->setHeaderData(++i, Qt::Horizontal, QObject::tr("Прочее3"));

}

void MainWindow::set_design_reports()
{
    // Reports
    ui->tableView_9->setColumnWidth(0,0);
    ui->tableView_9->setColumnWidth(1,300);
    ui->tableView_9->setColumnWidth(2,100);
    ui->tableView_9->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView_9->setSelectionBehavior(QAbstractItemView::SelectRows);

    sqlmodel_teachers_report->setHeaderData(1, Qt::Horizontal, QObject::tr("ФИО"));
    sqlmodel_teachers_report->setHeaderData(2, Qt::Horizontal, QObject::tr("должность"));
}

void MainWindow::on_pushButton_4_clicked()
{
    QString directory = QFileDialog::getOpenFileName(this,
                               tr("Find Files"), QDir::currentPath());

    if (!directory.isEmpty()) {
        ui->lineEdit->setText(directory);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QFile file(ui->lineEdit->text());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString line;
    QSqlQuery query;
    while (!file.atEnd()) {
        line = file.readLine();
        //qDebug() << line.trimmed();
        sqlmodel_subject->add(QString(line.trimmed()));
    }
    sqlmodel_subject->refresh();
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "идет пересчет...";
    // перерасчет таблицы "предметы в семместре"

    QSqlQuery query, query2, query3;
    QString curriculum_id, speciality_id, subjects_in_semmester_id;
    int semmester, course,
    lection_hr, labs_hr,
    practice_hr, is_examen, KCR_hr,
    is_offset,
    is_coursework,
    controlwork, num_group, num_undergroup, quantity_course;
    QString students_id, squery = "";

    //query.exec("DELETE FROM distribution");
    //query.exec("DELETE FROM subjects_in_semmester");
    // ищем запись (пока алгоритм будет добавлять и обновлять существующие)

    query.exec("SELECT curriculum.id, speciality_id, "
               "subject_name, semmester, lection_hr, labs_hr, practice_hr, "
               "controlwork, KCP_hr, is_examen, is_offset, is_coursework "
               "FROM curriculum");
    while (query.next()) {
        curriculum_id = query.value(0).toString();
        speciality_id = query.value(1).toString();
        semmester = query.value(3).toInt();
        lection_hr = query.value(4).toInt();
        labs_hr = query.value(5).toInt();
        practice_hr = query.value(6).toInt();
        controlwork = query.value(7).toInt();
        KCR_hr = query.value(8).toInt();
        is_examen = query.value(9).toInt();
        is_offset = query.value(10).toInt();
        is_coursework = query.value(11).toInt();
        course = (semmester+1)/2;
        query2.exec("SELECT students.id, speciality_id, "
                    "course, num_group, num_undergroup, quantity_course "
                    "FROM students "
                    "WHERE speciality_id = '"+ speciality_id +"' AND"
                    " course = '"+ QString::number(course, 10) + "';");

            while (query2.next()){
                students_id = query2.value(0).toString();
                num_group = query2.value(3).toInt();
                num_undergroup = query2.value(4).toInt();
                quantity_course = query2.value(5).toInt();

                QString new_lection_hr = QString::number(lection_hr*1, 10);              // "lection_hr INTEGER NOT NULL, "
                QString new_labs_hr = QString::number(labs_hr*num_undergroup, 10);       // "labs_hr INTEGER NOT NULL, "
                QString new_practice_hr = QString::number(practice_hr*num_group, 10);    // "practice_hr INTEGER NOT NULL, "
                QString new_individ_hr = QString::number(KCR_hr*1, 10);                  // "individ_hr REAL NOT NULL, "
                QString new_kontr_rab_hr = QString::number((int)ceil(controlwork*quantity_course/4), 10);         // "kontr_rab_hr REAL NOT NULL, "
                QString new_consultation_hr = consultation_get(lection_hr, speciality_id, num_group, is_examen);  // "consultation_hr REAL NOT NULL, "
                QString new_offset_hr = offset_get((int)ceil(quantity_course/4), is_offset);       // "offset_hr REAL NOT NULL, "
                QString new_examen_hr = examen_get((int)ceil(quantity_course/3), is_examen);       // "examen_hr REAL NOT NULL, "
                QString new_coursework_hr = QString::number(is_coursework*quantity_course*3, 10);  // "coursework_hr



                squery = "SELECT subjects_in_semmester.id FROM subjects_in_semmester "
                         "WHERE subjects_in_semmester.curriculum_id = '" + curriculum_id + "' AND "
                         "subjects_in_semmester.students_id = '" + students_id + "';";
                if (!query2.exec(squery)){
                    qDebug() << "error 0x001";
                }

                if (query2.next()){
                    // есть первая запись, обновить
                    subjects_in_semmester_id = query2.value(0).toString();

                    if (query2.next()){
                        qDebug() << "error 0x002 есть более одной записи";
                    }

                    squery = "UPDATE subjects_in_semmester SET "
                             "lection_hr = '" + new_lection_hr +"', "
                             "labs_hr = '" + new_labs_hr +"', "
                             "practice_hr = '" + new_practice_hr +"', "
                             "individ_hr = '" + new_individ_hr +"', "
                             "kontr_rab_hr = '" + new_kontr_rab_hr +"', "
                             "consultation_hr = '" + new_consultation_hr +"', "
                             "offset_hr = '" + new_offset_hr +"', "
                             "examen_hr = '" + new_examen_hr +"', "
                             "coursework_hr = '" + new_coursework_hr +"' "
                             "WHERE id = '"+ subjects_in_semmester_id + "';";
                } else {
                    // нет ни одной записи, добавляем новую
                    squery =    "insert into subjects_in_semmester values("
                                "NULL, "+                   // "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                curriculum_id + ", "+       // "curriculum_id INTEGER NOT NULL, "
                                students_id   + ", "+       // "students_id INTEGER NOT NULL, "
                                new_lection_hr + ", "+      // "lection_hr INTEGER NOT NULL, "
                                new_labs_hr+", "+           // "labs_hr INTEGER NOT NULL, "
                                new_practice_hr +", "+      // "practice_hr INTEGER NOT NULL, "
                                new_individ_hr + ", "+      // "individ_hr REAL NOT NULL, "
                                new_kontr_rab_hr + ", "+    // "kontr_rab_hr REAL NOT NULL, "
                                new_consultation_hr + ", "+ // "consultation_hr REAL NOT NULL, "
                                new_offset_hr + ", "+       // "offset_hr REAL NOT NULL, "
                                new_examen_hr + ", "+       // "examen_hr REAL NOT NULL, "
                                new_coursework_hr + ", "+   // "coursework_hr REAL NOT NULL, "
                                "0" + ", "+                 // "diplomwork_hr REAL NOT NULL, "
                                "0" + ", "+                 // "praktika_hr REAL NOT NULL, "
                                "0" + ", "+                 // "gak_hr REAL NOT NULL, "
                                "0" + ", "+                 // "other1 REAL NOT NULL, "
                                "0" + ", "+                 // "other2 REAL NOT NULL, "
                                "0" +                       // "other3 REAL NOT NULL, "
                                ");";
                }

                //qDebug() << squery;

                if (!query3.exec(squery)){QMessageBox::warning(this, tr("Error querry"), "");}
            }
    }

    update_subinsem();
    qDebug() << "готово";
}

QString MainWindow::offset_get(int hours, int is_exists){
    if (is_exists == 0){
        return QString("0");
    } else {
        return QString::number(hours, 10);
    }
}

QString MainWindow::examen_get(int hours, int is_exists){
    if (is_exists == 0){
        return QString("0");
    } else {
        return QString::number(hours, 10);
    }
}


QString MainWindow::consultation_get(int lection_hr, QString speciality_id, int num_group, int is_examen)
{
    int percent = 0;
    double res = 0;
    QSqlQuery query;
    query.exec("SELECT form_training_name "
               "FROM speciality WHERE id = " + speciality_id + ";");
    query.next();
    if (query.value(0).toString() == "оч")
    {
        percent = 5;
    } else if (query.value(0).toString() == "оч-заоч")
        {
            percent = 10;
        } else if (query.value(0).toString() == "заоч")
            {
                percent = 15;
            }
     res = (int)ceil((lection_hr*percent)/100);

     if (is_examen == 1)
     {
        res+= 2*num_group;
     }

     return QString::number(res, 'g', 6);
}




void MainWindow::on_action_txt_triggered()
{
    qDebug() << "backup";

    QFile file(applicationDirPath + "/nagruzka_backup.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){

        QTextStream out(&file);
//        out << "Backup database ksu-ivt-nagruzka " << version << ",  " << QDate::currentDate().toString() << " " << QTime::currentTime().toString() << "\n";
        QSqlQuery query, query2;
        QString s;
        int i;

        query.exec("SELECT name FROM form_training");
//        out << "\n" << "Table name : form_training" << "\n";
        while(query.next()){
            out << "form_training values( "<< query.value(0).toString() << " )\n";
        }

        query.exec("SELECT name FROM subject");
//        out << "\n" << "Table name : subject" << "\n";
        while(query.next()){
            out << "subject values( "<< query.value(0).toString() << " )\n";
        }

        query.exec("SELECT id, faculty_name, special_name, form_training_name FROM speciality");
//        out << "\n" << "Table name : speciality" << "\n";
        while(query.next()){
            i = 0;
            s = query.value(i).toString();
            while (i<3){
                s += ", " + query.value(++i).toString();
            }

            out << "speciality values( "<< s << " )\n";
        }

        query.exec("SELECT id, speciality_id, course, num_group, num_undergroup, quantity_course FROM students");
//        out << "\n" << "Table name : students" << "\n";
        while(query.next()){
            i = 0;
            s = query.value(i).toString();
            while (i<5){
                s += ", " + query.value(++i).toString();
            }

            out << "students values( " << s << " )\n";
        }

        query.exec("SELECT name,hours FROM status");
//        out << "\n" << "Table name : status" << "\n";
        while(query.next()){
            i = 0;
            s = query.value(i).toString();
            while (i<1){
                s += ", " + query.value(++i).toString();
            }

            out << "status values ( " << s << " )\n";
        }

        query.exec("SELECT id,name FROM staff");
//        out << "\n" << "Table name : staff" << "\n";
        while(query.next()){
            i = 0;
            s = query.value(i).toString();
            while (i<1){
                s += ", " + query.value(++i).toString();
            }

            out << "staff values ( " << s << " )\n";
        }

        query.exec("SELECT id, f, i, o, status_name, rate, staff_id FROM teachers");
//        out << "\n" << "Table name : teachers" << "\n";
        while(query.next()){
            i = 0;
            s = query.value(i).toString();
            while (i<6){
                s += ", " + query.value(++i).toString();
            }

            out << "teachers values ( " << s << " )\n";
        }


        query.exec("SELECT id, speciality_id, subject_name, semmester, lection_hr, labs_hr, practice_hr, controlwork, KCP_hr, is_examen, is_offset, is_coursework FROM curriculum");
//        out << "\n" << "Table name : curriculum" << "\n";
        while(query.next()){
            i = 0;
            s = query.value(i).toString();
            while (i<11){
                s += ", " + query.value(++i).toString();
            }

            out << "curriculum values ( " << s << " )\n";
        }

        query.exec("SELECT id, curriculum_id, students_id, lection_hr, labs_hr, practice_hr, individ_hr, kontr_rab_hr, consultation_hr, offset_hr, "
                   "examen_hr, coursework_hr, diplomwork_hr, praktika_hr, gak_hr, other1, other2, other3 FROM subjects_in_semmester");
//        out << "\n" << "Table name : subjects_in_semmester" << "\n";
        while(query.next()){
            i = 0;
            s = query.value(i).toString();
            while (i<17){
                s += ", " + query.value(++i).toString();
            }

            out << "subjects_in_semmester values ( " << s << " )\n";
        }

        query.exec("SELECT id, teachers_id, subjects_in_semmester_id, lection_hr, labs_hr, practice_hr, individ_hr, kontr_rab_hr, consultation_hr, "
                   "offset_hr, examen_hr, coursework_hr, diplomwork_hr, praktika_hr, gak_hr, other1, other2, other3 FROM distribution");
//        out << "\n" << "Table name : distribution" << "\n";
        while(query.next()){
            i = 0;
            s = query.value(i).toString();
            while (i<17){
                s += ", " + query.value(++i).toString();
            }

            out << "distribution values ( " << s << " )\n";
        }

        file.close();
    }

qDebug() << "ok";
}

void MainWindow::on_action_txt_2_triggered()
{
    QFile file(applicationDirPath + "/nagruzka_backup_zhmakin.txt");
    if (!file.open(QFile::ReadOnly))
        return;

    create_all_tables();
    insert_main_data();

//    std::cout << std::endl;
//    QRegExp rx ("#include (<|\").*\\..*(>|\").*");
    QRegExp rx("#.*");
    QByteArray line;
    QString string;
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON;");


    while (!file.atEnd()) {
        line = file.readLine();
        string = line;
        string = string.simplified();
        if (!string.contains(rx)){
//            qDebug() << string;
            query.exec("insert into " + string);

        }
    }

    file.close();
    load_db();
}

void MainWindow::on_action_6_triggered()
{

}

void MainWindow::update_report_name()
{
    if (ui->radioButton_4->isChecked()){
        report_format = "xlsx";
    } else{
        report_format = "ods";
    }

    if (ui->radioButton_6->isChecked()){
        QSqlQuery query;
        query.exec("SELECT f FROM teachers WHERE id = " + ui->tableView_9->get_id() + ";");
        query.next();
        ui->lineEdit_2->setText(report_path + "/" + translit(query.value(0).toString()) + "." + report_format);
        //   qDebug() << "get_id: " << ui->tableView_9->get_id() ;
    }else{
        //report_format;
        ui->lineEdit_2->setText(report_path + "/all_teachers." + report_format);
    }
}

QString MainWindow::translit(QString s){
    QString out = "";

    QMap<QString, QString> map;
    map.insert("а", "a");
    map.insert("б", "b");
    map.insert("в", "v");
    map.insert("г", "g");
    map.insert("д", "d");
    map.insert("е", "e");
    map.insert("ё", "jo");
    map.insert("ж", "zh");
    map.insert("з", "z");
    map.insert("и", "i");
    map.insert("й", "i");
    map.insert("к", "k");
    map.insert("л", "l");
    map.insert("м", "m");
    map.insert("н", "n");
    map.insert("о", "o");
    map.insert("п", "p");
    map.insert("р", "r");
    map.insert("с", "s");
    map.insert("т", "t");
    map.insert("у", "u");
    map.insert("ф", "f");
    map.insert("х", "h");
    map.insert("ц", "tc");
    map.insert("ч", "ch");
    map.insert("ш", "sh");
    map.insert("щ", "xh");
    map.insert("ь", "");
    map.insert("ы", "y");
    map.insert("ъ", "");
    map.insert("э", "je");
    map.insert("ю", "ju");
    map.insert("я", "ja");

    s = s.toLower();

    for (int i=0; i<s.length(); ++i){
        out+=map[s.at(i)];
    }

    return out;
}

void MainWindow::on_pushButton_9_clicked()
{
    QStringList teachers_id_list;
    QSqlQuery query;

    // заполнить teachers_id_list
    teachers_id_list.clear();

    if (ui->radioButton_6->isChecked()){
        QModelIndexList indexes = ui->tableView_9->selectionModel()->selectedRows();
        QModelIndex index;
        for (int i = 0; i < indexes.count(); ++i){
            index = indexes.at(i);
            teachers_id_list << sqlmodel_teachers_report->data( sqlmodel_teachers_report->index(index.row(),0), Qt::DisplayRole ).toString();
        }
    } else {
        query.exec("SELECT teachers.id "
                   "FROM teachers WHERE teachers.id != '0'");
        while(query.next()){
            teachers_id_list << query.value(0).toString();
        }
    }

// create report (QList(teachers.id), path_report+name_report, ods,)
    if (report_format == "xlsx"){
        create_report(teachers_id_list, "", ui->lineEdit_2->text(),report_format);
    } else if(report_format == "ods"){
        create_report(teachers_id_list, applicationDirPath + "/template.ods", ui->lineEdit_2->text(),report_format);
    }
}



void MainWindow::on_pushButton_8_clicked(bool checked)
{
    if (checked){
    //открыть окно список преподователей
        teachers_list->show();
        teachers_list->update();
    } else {
        teachers_list->close();
    }
}


void MainWindow::on_pushButton_5_clicked()
{// создание отчета нагрузка на кафедре
    QSqlQuery query;
    QString s;
    unsigned int sum;
    query.exec("SELECT curriculum.subject_name, curriculum.semmester, "
                           "speciality.special_name, "
                           "speciality.form_training_name, students.course, "
                           "students.num_group, students.num_undergroup, "
                           "students.quantity_course, subjects_in_semmester.lection_hr, "
                           "subjects_in_semmester.labs_hr, subjects_in_semmester.practice_hr,"
                           "individ_hr, kontr_rab_hr, consultation_hr, "
                           "offset_hr,  examen_hr, coursework_hr, diplomwork_hr, praktika_hr, gak_hr, "
                           "other1,  other2, other3, "
                           "subjects_in_semmester.lection_hr+subjects_in_semmester.labs_hr+subjects_in_semmester.practice_hr+"
                           "individ_hr+kontr_rab_hr+consultation_hr+"
                           "offset_hr+examen_hr+coursework_hr+diplomwork_hr+praktika_hr+gak_hr+"
                           "other1+other2+other3 AS sum "
                           "FROM subjects_in_semmester, curriculum, students, speciality "
                           "WHERE subjects_in_semmester.curriculum_id = curriculum.id AND "
                           "subjects_in_semmester.students_id = students.id AND "
                           "students.speciality_id = speciality.id "
                           "ORDER BY speciality.special_name, speciality.form_training_name, curriculum.semmester, curriculum.subject_name, subjects_in_semmester.id;");

    QFile file(ui->lineEdit_3->text());
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){

        QTextStream out(&file);

        s =    "Название предмета;"
               "Семместр;"
               "Специальность;"
               "Форма обучения;"
               "Курс;"
               "Количество групп;"
               "Количество подгрупп;"
               "Студентов на курсе;"
               "Лекции;"
               "Лабораторные;"
               "Практические;"
               "Индивидуальные;"
               "Контрольные работы;"
               "Консультации;"
               "Зачет;"
               "Экзамен;"
               "Курсовая работа;"
               "Дипломная работа;"
               "Практика;"
               "ГАК;"
               "Прочее;"
               "Прочее;"
               "Прочее;"
               "Всего;";  //24

        out << s << "\n";
        sum = 0;
        while(query.next()){
            s="";
            for (int i=0; i<24; ++i){
                s += query.value(i).toString() + ";";
            }
            sum += query.value(23).toUInt();
            out << s << "\n";
        }
        out << QString("Общая сумма:;;;;;;;;;;;;;;;;;;;;;;;") << QString::number(sum) << QString(";\n");

    } else {
        QMessageBox::warning(this, tr("Error"), "Невозможно создать файл");
    }
}

void MainWindow::on_pushButton_clear_subinsemmester_clicked()
{
    MessageDialog dialog(this);
    dialog.setMessage(QString("Будут удалены все записи из таблиц 'Предметы в семместре' и 'Распределение'"));

    if (dialog.exec() == 1){
        sqlmodel_subinsem->clearTable();
        update_subinsem();
        update_distribution();
    }
}

void MainWindow::on_pushButton_clear_distribution_clicked()
{
    MessageDialog dialog(this);
    dialog.setMessage(QString("Будут удалены все записи из таблицы 'Распределение'"));

    if (dialog.exec() == 1){
        sqlmodel_distribution->clearTable();
        update_distribution();
    }

}
