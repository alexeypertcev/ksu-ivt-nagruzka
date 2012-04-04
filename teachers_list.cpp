#include "teachers_list.h"
#include "ui_teachers_list.h"
#include <QDebug>

Teachers_list::Teachers_list(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Teachers_list)
{
    ui->setupUi(this);

    sqlmodel_teachers_list = new Teachers_list_model();
    sqlmodel_teachers_list->refresh();
    ui->tableView->setModel(sqlmodel_teachers_list);
    ui->tableView->update();

    HierarchicalHeaderView* hv = new HierarchicalHeaderView(Qt::Horizontal, ui->tableView);

    hv->setHighlightSections(true);
    hv->setClickable(true);

    ui->tableView->setHorizontalHeader(hv);

    ui->tableView->setColumnWidth(0,0);
    ui->tableView->setColumnWidth(1,200);
    ui->tableView->setColumnWidth(2,70);
    ui->tableView->setColumnWidth(3,55);
    ui->tableView->setColumnWidth(4,55);
    ui->tableView->setColumnWidth(5,55);
    ui->tableView->setColumnWidth(6,55);
    ui->tableView->setColumnWidth(7,55);
    ui->tableView->setColumnWidth(8,55);
    //headerview.
}

Teachers_list::~Teachers_list()
{
    //sqlmodel_teachers_list->clear();
    delete ui;
}

void Teachers_list::update()
{
    sqlmodel_teachers_list->refresh();
}


/***********************************************************
*   Teachers_list_model
************************************************************/


Teachers_list_model::Teachers_list_model(QObject *parent) :
    QSqlQueryModel(parent)
{
    QStandardItem* rootItem = new QStandardItem("Осень");
    QList<QStandardItem*> l;
    QStandardItem* cell_1;
    QStandardItem* cell_2;

    rootItem = new QStandardItem("id");
    _horizontalHeaderModel.setItem(0, 0, rootItem);
    rootItem = new QStandardItem("ФИО");
    _horizontalHeaderModel.setItem(0, 1, rootItem);
    rootItem = new QStandardItem("Ставка");
    _horizontalHeaderModel.setItem(0, 2, rootItem);

//--------------------------------------------
    rootItem = new QStandardItem("Осень");

    l.clear();
    cell_1 = new QStandardItem("Часы");
    l.push_back(cell_1);
    rootItem->appendColumn(l);
    l.clear();

    cell_2 = new QStandardItem("% ауд");
    l.push_back(cell_2);
    rootItem->appendColumn(l);

    _horizontalHeaderModel.setItem(0, 3, rootItem);
//--------------------------------------------
    rootItem = new QStandardItem("Весна");

    l.clear();
    cell_1 = new QStandardItem("Часы");
    l.push_back(cell_1);
    rootItem->appendColumn(l);
    l.clear();

    cell_2 = new QStandardItem("% ауд");
    l.push_back(cell_2);
    rootItem->appendColumn(l);

    _horizontalHeaderModel.setItem(0, 4, rootItem);
//--------------------------------------------
    rootItem = new QStandardItem("Год");

    l.clear();
    cell_1 = new QStandardItem("Часы");
    l.push_back(cell_1);
    rootItem->appendColumn(l);
    l.clear();

    cell_2 = new QStandardItem("% ауд");
    l.push_back(cell_2);
    rootItem->appendColumn(l);

    _horizontalHeaderModel.setItem(0, 5, rootItem);
//--------------------------------------------


}

Qt::ItemFlags Teachers_list_model::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    /*if (index.column() > 8 && index.column() < 24 )
    {
        flags |= Qt::ItemIsEditable;
    }*/
    return flags;
}


void Teachers_list_model::refresh()
{
    QSqlQuery query, query2;
    unsigned int buf_all_hours;
    unsigned int buf_aud_hours;

    QString staff_hour;
    QString rate;
    QString rate_staff_hour;

    rate_list.clear();
    osen_hours.clear();
    osen_p_ayd.clear();
    vesna_hours.clear();
    vesna_p_ayd.clear();
    year_hours.clear();
    year_p_ayd.clear();

    //**********************************************************
    // error
    // Ошибка после закрытия программы из-за этой конструкции
    this->setQuery("SELECT teachers.id, f || ', ' || i || ', ' || o, status_name, status_name, status_name, status_name, status_name, status_name, status_name "
                   "FROM teachers WHERE teachers.id != '0' "
                   "ORDER BY f,i,o");
    //
    //**********************************************************

    query.exec("SELECT teachers.id, status_name, rate "
               "FROM teachers WHERE teachers.id != '0'"
               "ORDER BY f,i,o");
    while(query.next()){

        query2.exec("SELECT hours FROM status WHERE name = '"+ query.value(1).toString() +"';");
        query2.next();
        rate = query.value(2).toString();
        staff_hour = query2.value(0).toString();
        rate_staff_hour = QString::number( query.value(2).toDouble() * query2.value(0).toDouble() );

        rate_list << rate + "/" + rate_staff_hour;

    //--- для нечетных семместров(весны)-------------------------------------------
        buf_all_hours = 0;
        buf_aud_hours = 0;
        query2.exec("SELECT distribution.lection_hr, "
                    "distribution.labs_hr, "
                    "distribution.practice_hr, "
                    "distribution.individ_hr, "
                    "distribution.kontr_rab_hr, "
                    "distribution.consultation_hr, "
                    "distribution.offset_hr, "
                    "distribution.examen_hr, "
                    "distribution.coursework_hr, "
                    "distribution.diplomwork_hr, "
                    "distribution.praktika_hr, "
                    "distribution.gak_hr, "
                    "distribution.other1, "
                    "distribution.other2, "
                    "distribution.other3 "
                    "FROM distribution, subjects_in_semmester, curriculum "
                    "WHERE teachers_id = '" + query.value(0).toString() + "' AND "
                    "distribution.subjects_in_semmester_id = subjects_in_semmester.id AND "
                    "subjects_in_semmester.curriculum_id = curriculum.id AND "
                    "( curriculum.semmester = '1' "
                    "OR curriculum.semmester = '3' "
                    "OR curriculum.semmester = '5' "
                    "OR curriculum.semmester = '7' "
                    "OR curriculum.semmester = '9' "
                    "OR curriculum.semmester = '11' )");

        while(query2.next()){

            for (int i = 0; i<15; ++i){
                if (i<4){
                    buf_aud_hours += query2.value(i).toUInt();
                }
                    buf_all_hours += query2.value(i).toUInt();
            }
        }

        //query2.exec("SELECT hours FROM status WHERE name = '"+ query.value(1).toString() +"';");

        //if (query2.next()){
            vesna_hours << QString::number(buf_all_hours);
            vesna_p_ayd << (QString::number(buf_aud_hours) + "/" + rate_staff_hour);
        //}

        //--- для четных семместров(осени)-------------------------------------------
            buf_all_hours = 0;
            buf_aud_hours = 0;
            query2.exec("SELECT distribution.lection_hr, "
                        "distribution.labs_hr, "
                        "distribution.practice_hr, "
                        "distribution.individ_hr, "
                        "distribution.kontr_rab_hr, "
                        "distribution.consultation_hr, "
                        "distribution.offset_hr, "
                        "distribution.examen_hr, "
                        "distribution.coursework_hr, "
                        "distribution.diplomwork_hr, "
                        "distribution.praktika_hr, "
                        "distribution.gak_hr, "
                        "distribution.other1, "
                        "distribution.other2, "
                        "distribution.other3 "
                        "FROM distribution, subjects_in_semmester, curriculum "
                        "WHERE teachers_id = '" + query.value(0).toString() + "' AND "
                        "distribution.subjects_in_semmester_id = subjects_in_semmester.id AND "
                        "subjects_in_semmester.curriculum_id = curriculum.id AND "
                        "( curriculum.semmester = '2' "
                        "OR curriculum.semmester = '4' "
                        "OR curriculum.semmester = '6' "
                        "OR curriculum.semmester = '8' "
                        "OR curriculum.semmester = '10' "
                        "OR curriculum.semmester = '12' )");

            while(query2.next()){

                for (int i = 0; i<15; ++i){
                    if (i<4){
                        buf_aud_hours += query2.value(i).toUInt();
                    }
                        buf_all_hours += query2.value(i).toUInt();
                }
            }

            //query2.exec("SELECT hours FROM status WHERE name = '"+ query.value(1).toString() +"';");
            //if (query2.next()){
                osen_hours << QString::number(buf_all_hours);
                osen_p_ayd << (QString::number(buf_aud_hours) + "/" + rate_staff_hour);
            //}

            //--- для всех семместров(года)-------------------------------------------
                buf_all_hours = 0;
                buf_aud_hours = 0;
                query2.exec("SELECT lection_hr, labs_hr, practice_hr, individ_hr, "
                            "kontr_rab_hr, consultation_hr, offset_hr, examen_hr, "
                            "coursework_hr, diplomwork_hr, praktika_hr, gak_hr, "
                            "other1, other2, other3 "
                            "FROM distribution WHERE teachers_id = "+ query.value(0).toString() +";");

                while(query2.next()){

                    for (int i = 0; i<15; ++i){
                        if (i<4){
                            buf_aud_hours += query2.value(i).toUInt();
                        }
                            buf_all_hours += query2.value(i).toUInt();
                    }
                }

                //query2.exec("SELECT hours FROM status WHERE name = '"+ query.value(1).toString() +"';");
                //if (query2.next()){
                    year_hours << QString::number(buf_all_hours);
                    year_p_ayd << (QString::number(buf_aud_hours) + "/" + rate_staff_hour);
                //}
        }



}

QVariant Teachers_list_model::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    QString buf;
    switch (role)
    {
    case Qt::DisplayRole:
        switch (index.column())
        {
            case 2:  //
            if (index.row() < rate_list.size()){
                return rate_list.at(index.row());
            }
            break;

            case 3:
            if (index.row() < osen_hours.size()){
                return osen_hours.at(index.row());
            }
            break;

            case 4:
            if (index.row() < osen_p_ayd.size()){
                return osen_p_ayd.at(index.row());
            }

            case 5:
            if (index.row() < vesna_hours.size()){
                return vesna_hours.at(index.row());
            }
            break;

            case 6:
            if (index.row() < vesna_p_ayd.size()){
                return vesna_p_ayd.at(index.row());
            }
            break;

            case 7:
            if (index.row() < year_hours.size()){
                return year_hours.at(index.row());
            }
            break;

            case 8:
            if (index.row() < year_p_ayd.size()){
                return year_p_ayd.at(index.row());
            }
            break;


        }
        break;
    case HierarchicalHeaderView::HorizontalHeaderDataRole:
        value.setValue((QObject*)&_horizontalHeaderModel);
        break;
    }
    return value;
}
