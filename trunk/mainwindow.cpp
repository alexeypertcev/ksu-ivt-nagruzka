//---------------------------------------------
//  alexey.pertcev@gmail.com  Alexey Pertcev
//
//---------------------------------------------

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "delegates.h"
#include "settings.h"
#include "curriculum_sqlmodel.h"
#include "students.h"
#include "teachers.h"
#include "subjectinsemester_sqlmodel.h"
#include "distribution.h"
#include "workzip.cpp"

#include <QtGui>
#include <QtSql>
#include <QMessageBox>
#include <QStatusBar>


MainWindow::MainWindow(QString apppath, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    applicationDirPath = apppath;
    path_db = applicationDirPath + "/nagruzka.db";

    if (createConnection(path_db)){

        QSqlQuery query;
        query.exec("PRAGMA foreign_keys = ON;");

        tablemodel_spec = new QSqlRelationalTableModel(this);
        tablemodel_spec->setTable("speciality");
        tablemodel_spec->setEditStrategy(QSqlTableModel::OnFieldChange);
        tablemodel_spec->select();

        sqlmodel_spec = new QSqlQueryModel(this);
        sqlmodel_spec->setQuery("SELECT special_name || '(' || form_training_name || ')', id "
                                "FROM speciality ORDER BY id;");

        ui->comboBox->setModel(sqlmodel_spec);
        ui->comboBox_2->setModel(sqlmodel_spec);
        ui->comboBox_3->setModel(sqlmodel_spec);

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
        sqlmodel_teachers = new TeachersSqlModel(this);
        sqlmodel_teachers->refresh();
        ui->tableView_2->setModel(sqlmodel_teachers);

        StatusDelegate *status_delegate = new StatusDelegate(this);
        ui->tableView_2->setItemDelegateForColumn(4, status_delegate);
        ui->tableView_2->update();

        // students table
        sqlmodel_students = new StudentsSqlModel(this);
        sqlmodel_students->refresh();
        ui->tableView_3->setModel(sqlmodel_students);


        SpecialityDelegate *speciality_delegate = new SpecialityDelegate(this);
        SpinBoxDelegate *course_delegate = new SpinBoxDelegate(1,6,this);

        ui->tableView_3->setItemDelegateForColumn(1, speciality_delegate);
        ui->tableView_3->setItemDelegateForColumn(2, course_delegate);

        ui->tableView_3->update();

        // curriculum table
        sqlmodel_curriculum = new CurriculumSqlModel(this);
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

        //subjects_in_semmester table
        sqlmodel_subinsem = new SubjectinsemesterSqlModel(this);
        update_subinsem();
        ui->tableView_5->setModel(sqlmodel_subinsem);


        //distribution tables

        sinstodistrib_preview = new Sins_to_distrib_preview_SqlModel(this);
        update_sins_to_distribution_preview();
        ui->tableView_6->setModel(sinstodistrib_preview);

        sinstodistrib_detail = new Sins_to_distrib_detail_SqlModel(this);
        update_sins_to_distribution_detail();
        ui->tableView_7->setModel(sinstodistrib_detail);

        sqlmodel_distribution = new DistributionSqlModel(this);
        update_sqlmodel_distribution();
        ui->tableView_8->setModel(sqlmodel_distribution);

        FioDelegate *fio_delegate = new FioDelegate(this);
        ui->tableView_8->setItemDelegateForColumn(2, fio_delegate);
        ui->tableView_8->update();



        ui->lineEdit->setText("/home/perec/Загрузки/ПОиАИС_utf8.txt");
        settings = new Settings(this, tablemodel_spec, tablemodel_stat);
        set_design_window();

        QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update_curriculum()));
        QObject::connect(ui->comboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(update_subinsem()));
        QObject::connect(ui->comboBox_3, SIGNAL(currentIndexChanged(int)), this, SLOT(update_distribution()));
        QObject::connect(ui->tableView_6, SIGNAL(activated(QModelIndex)), this, SLOT(update_sins_to_distribution_detail()));
        QObject::connect(ui->tableView_6, SIGNAL(activated(QModelIndex)), this, SLOT(update_sqlmodel_distribution()));
        QObject::connect(ui->radioButton_3, SIGNAL(clicked()), this, SLOT(update_distribution()));
        QObject::connect(ui->radioButton_2, SIGNAL(clicked()), this, SLOT(update_distribution()));
        QObject::connect(ui->radioButton, SIGNAL(clicked()), this, SLOT(update_distribution()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
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
    QString s = "insert into subject values('')";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        QMessageBox::warning(this, tr("Error querry"),
                             tr("The database reported an error: %1").arg(tablemodel_subject->lastError().text()));
    }

    tablemodel_subject->select();
    QModelIndex index = tablemodel_subject->index(tablemodel_subject->rowCount()-1,0);
    ui->tableView->setCurrentIndex(index);
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
    QString s = "insert into teachers values(NULL, 'f', 'i', 'o', 'выберите..', 1.0 );";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        qDebug() << "error exec";
    }
    sqlmodel_teachers->refresh();
}

void MainWindow::on_pushButton_del_teachers_clicked()
{
    int row = ui->tableView_2->currentIndex().row();
    QString s = "DELETE FROM teachers WHERE id = '" + sqlmodel_teachers->data( sqlmodel_teachers->index(row,0),
                                                                                Qt::DisplayRole ).toString() + "';";
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        qDebug() << "error exec";
    }
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

void MainWindow::on_pushButton_clicked(){}

void MainWindow::on_pushButton_add_student_clicked()
{
    sqlmodel_students->add("1", "1", "1", "1", "0");
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

void MainWindow::on_pushButton_add_subjects_in_semmestre_clicked()
{

}

void MainWindow::on_pushButton_del_subjects_in_semmestre_clicked()
{

}

void MainWindow::on_pushButton_add_distribution_clicked()
{


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
        update_subinsem();
        break;
    case 5:
        update_distribution();
        break;
    case 6:

        break;
    default:

        break;
    }
}
void MainWindow::update_subject(){}

void MainWindow::update_teachers(){}

void MainWindow::update_students(){}

void MainWindow::update_curriculum()
{
    sqlmodel_curriculum->setspeciality_id(ui->comboBox->get_id());
    sqlmodel_curriculum->refresh();
}

void MainWindow::update_subinsem()
{
    sqlmodel_subinsem->setspeciality_id(ui->comboBox_2->get_id());
    sqlmodel_subinsem->refresh();
}

void MainWindow::update_subject_in_semestre()
{

}

void MainWindow::update_subjectlist()
{
//    select_subjects->setQuery("SELECT subject_name, semmester, subjects_in_semmester.id FROM subjects_in_semmester, curriculum "
//                 "WHERE subjects_in_semmester.curriculum_id = curriculum.id;");
//    ui->tableView_6->update_ids();
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

void MainWindow::update_distribution()
{
    update_sins_to_distribution_preview();
    update_sins_to_distribution_detail();
    update_sqlmodel_distribution();
}


void MainWindow::set_design_window()
{
    int i = 0;
    ui->tableView->setColumnWidth(0,400);
    tablemodel_subject->setHeaderData(0, Qt::Horizontal, QObject::tr("Название"));
    do{ ui->tableView->setRowHeight(i++,25); }while(i<=10);

    ui->tableView_2->setColumnWidth(0,0);   //id
    ui->tableView_2->setColumnWidth(1,180);
    ui->tableView_2->setColumnWidth(2,180);
    ui->tableView_2->setColumnWidth(3,180);
    ui->tableView_2->setColumnWidth(4,120);
    ui->tableView_2->setColumnWidth(5,60);

    sqlmodel_teachers->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    sqlmodel_teachers->setHeaderData(1, Qt::Horizontal, QObject::tr("Фамилия"));
    sqlmodel_teachers->setHeaderData(2, Qt::Horizontal, QObject::tr("Имя"));
    sqlmodel_teachers->setHeaderData(3, Qt::Horizontal, QObject::tr("Отчество"));
    sqlmodel_teachers->setHeaderData(4, Qt::Horizontal, QObject::tr("Должность"));
    sqlmodel_teachers->setHeaderData(5, Qt::Horizontal, QObject::tr("Ставка"));

    ui->tableView_3->setColumnWidth(0,0);  //id
    ui->tableView_3->setColumnWidth(1,150);
    ui->tableView_3->setColumnWidth(2,145);
    ui->tableView_3->setColumnWidth(3,145);
    ui->tableView_3->setColumnWidth(4,145);
    ui->tableView_3->setColumnWidth(5,145);

    sqlmodel_students->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    sqlmodel_students->setHeaderData(1, Qt::Horizontal, QObject::tr("Специальность"));
    sqlmodel_students->setHeaderData(2, Qt::Horizontal, QObject::tr("Курс"));
    sqlmodel_students->setHeaderData(3, Qt::Horizontal, QObject::tr("Кол-во групп"));
    sqlmodel_students->setHeaderData(4, Qt::Horizontal, QObject::tr("Кол-во подгрупп"));
    sqlmodel_students->setHeaderData(5, Qt::Horizontal, QObject::tr("Кол-во человек"));

    int h=85;
    ui->tableView_4->setColumnWidth(0,0);  //id
    ui->tableView_4->setColumnWidth(1,130);
    ui->tableView_4->setColumnWidth(2,240);
    ui->tableView_4->setColumnWidth(3,h);
    ui->tableView_4->setColumnWidth(4,h);
    ui->tableView_4->setColumnWidth(5,h);
    ui->tableView_4->setColumnWidth(6,h);
    ui->tableView_4->setColumnWidth(7,h);
    ui->tableView_4->setColumnWidth(8,h/2);
    ui->tableView_4->setColumnWidth(9,h/2);
    ui->tableView_4->setColumnWidth(10,h/2);
    ui->tableView_4->setColumnWidth(11,h/2);

    i=0;
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

    ui->tableView_5->setColumnWidth(0,0); //id
    ui->tableView_5->setColumnWidth(1,330);
    ui->tableView_5->setColumnWidth(2,60);

    i=9;
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

    ui->tableView_6->setColumnWidth(0,180);
    ui->tableView_6->setColumnWidth(1,50);
    ui->tableView_6->setColumnWidth(2,0);  // id

    sinstodistrib_preview->setHeaderData(0, Qt::Horizontal, QObject::tr("Предмет"));
    sinstodistrib_preview->setHeaderData(1, Qt::Horizontal, QObject::tr("Семестр"));

    ui->tableView_7->setColumnWidth(0,0);
    ui->tableView_7->setColumnWidth(1,250);

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


    //    sqlmodel_distribution
    ui->tableView_8->setColumnWidth(0,0);
    ui->tableView_8->setColumnWidth(1,250);
    ui->tableView_8->setColumnWidth(2,250);
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
        qDebug() << line.trimmed();

        query.exec("insert into subject values('" + line.trimmed() + "')");
    }
    tablemodel_subject->select();

}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "идет пересчет...";
    // перерасчет таблицы "предметы в семместре"

    QSqlQuery query, query2, query3;
    QString curriculum_id, speciality_id;
    int semmester, course,
    lection_hr, labs_hr,
    practice_hr, is_examen,
    is_offset, is_coursework,
    controlwork, num_group, num_undergroup, quantity_course;
    QString students_id, squery = "";
    query.exec("DELETE FROM subjects_in_semmester");

    query.exec("SELECT curriculum.id, speciality_id, "
               "subject_name, semmester, lection_hr, labs_hr, practice_hr, "
               "controlwork, is_examen, is_offset, is_coursework "
               "FROM curriculum");
    while (query.next()) {
        curriculum_id = query.value(0).toString();
        speciality_id = query.value(1).toString();
        semmester = query.value(3).toInt();
        lection_hr = query.value(4).toInt();
        labs_hr = query.value(5).toInt();
        practice_hr = query.value(6).toInt();
        controlwork = query.value(7).toInt();
        is_examen = query.value(8).toInt();
        is_offset = query.value(9).toInt();
        is_coursework = query.value(10).toInt();
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

                squery =    "insert into subjects_in_semmester values("
                            "NULL, "+                                        // "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            curriculum_id + ", "+                            // "curriculum_id INTEGER NOT NULL, "
                            students_id   + ", "+                            // "students_id INTEGER NOT NULL, "
                            QString::number(lection_hr*1, 10) + ", "+        // "lection_hr INTEGER NOT NULL, "
                            QString::number(labs_hr*num_undergroup, 10)+", "+// "labs_hr INTEGER NOT NULL, "
                            QString::number(practice_hr*num_group, 10) +", "+// "practice_hr INTEGER NOT NULL, "
                            "0" + ", "+                                      // "individ_hr REAL NOT NULL, "
                            QString::number((int)ceil(controlwork*quantity_course/4), 10) + ", "+ // "kontr_rab_hr REAL NOT NULL, "
                            consultation_get(lection_hr, speciality_id, num_group, is_examen) + ", "+ // "consultation_hr REAL NOT NULL, "
  /* возможно косяк*/       QString::number((int)ceil(quantity_course/4), 10) + ", "+   // "offset_hr REAL NOT NULL, "
                            QString::number((int)ceil(quantity_course/3), 10) + ", "+   // "examen_hr REAL NOT NULL, "
                            QString::number(is_coursework*quantity_course*3, 10) + ", "+ // "coursework_hr REAL NOT NULL, "
                            "0" + ", "+                                      // "diplomwork_hr REAL NOT NULL, "
                            "0" + ", "+                                      // "praktika_hr REAL NOT NULL, "
                            "0" + ", "+                                      // "gak_hr REAL NOT NULL, "
                            "0" + ", "+                                      // "other1 REAL NOT NULL, "
                            "0" + ", "+                                      // "other2 REAL NOT NULL, "
                            "0" +                                            // "other3 REAL NOT NULL, "
                            ");";              

//                qDebug() << squery;

                if (!query3.exec(squery)){QMessageBox::warning(this, tr("Error querry"), "");}
            }
    }

    update_subinsem();
    qDebug() << "готово";
//    ui->statusBar->showMessage("готово",0);
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


void MainWindow::on_pushButton_5_clicked()//распаковать
{
    decompress("/home/perec/example_ods.ods","/home/perec/temp");
}

void MainWindow::on_pushButton_6_clicked()//упаковать
{
    compress("/home/perec/example_ods2.ods", "/home/perec/temp");
}

void MainWindow::on_pushButton_7_clicked()
{

}
