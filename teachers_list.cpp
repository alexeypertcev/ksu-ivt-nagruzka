#include "teachers_list.h"
#include "ui_teachers_list.h"
#include <QDebug>
#include <QHBoxLayout>

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

    int i = 0;
    ui->tableView->setColumnWidth(i,0);
    ui->tableView->setColumnWidth(++i,200);
    ui->tableView->setColumnWidth(++i,70);

    while (i < 11){
        ui->tableView->setColumnWidth(++i,55);
    }
    //headerview.
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(ui->tableView);
    setLayout(layout);
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
    QStandardItem* cell_3;

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
    cell_1 = new QStandardItem("Лекции");
    l.push_back(cell_1);
    rootItem->appendColumn(l);
    l.clear();

    cell_2 = new QStandardItem("Часы");
    l.push_back(cell_2);
    rootItem->appendColumn(l);
    l.clear();

    cell_3 = new QStandardItem("% ауд");
    l.push_back(cell_3);
    rootItem->appendColumn(l);

    _horizontalHeaderModel.setItem(0, 5, rootItem);
//--------------------------------------------
    rootItem = new QStandardItem("Доля \nставки");
    _horizontalHeaderModel.setItem(0, 6, rootItem);

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
    unsigned int buf_lection_hours;

    QString rate;
    unsigned int staff_hour;
    unsigned int rate_staff_hour;

    rate_list.clear();
    osen_hours.clear();
    osen_p_ayd.clear();
    vesna_hours.clear();
    vesna_p_ayd.clear();
    year_hours.clear();
    year_p_ayd.clear();
    rate_dole.clear();
    year_lection.clear();

    //**********************************************************
    // error
    // Ошибка после закрытия программы из-за этой конструкции
    this->setQuery("SELECT teachers.id, f || ', ' || i || ' ' || o, status_name, status_name, status_name, status_name, status_name, status_name, status_name, status_name, status_name "
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
        staff_hour = query2.value(0).toUInt();
        rate_staff_hour =  query.value(2).toDouble() * query2.value(0).toDouble();

        rate_list << rate + "/" + QString::number(rate_staff_hour);

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
                    "( curriculum.semmester % 2 = 0 )");

        while(query2.next()){

            for (int i = 0; i<15; ++i){
                if (i<4){
                    buf_aud_hours += query2.value(i).toUInt();
                }
                    buf_all_hours += query2.value(i).toUInt();
            }
        }

        vesna_hours << QString::number(buf_all_hours);
        //vesna_p_ayd << (QString::number(buf_aud_hours) + "/" + QString::number(buf_all_hours));
        if (buf_all_hours != 0){
            vesna_p_ayd << QString::number((double)buf_aud_hours / (double)buf_all_hours,'f',2);
        } else {
            vesna_p_ayd << " ";
        }

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
                        "( curriculum.semmester % 2 = 1 )");

            while(query2.next()){

                for (int i = 0; i<15; ++i){
                    if (i<4){
                        buf_aud_hours += query2.value(i).toUInt();
                    }
                        buf_all_hours += query2.value(i).toUInt();
                }
            }

            osen_hours << QString::number(buf_all_hours);
            //osen_p_ayd << (QString::number(buf_aud_hours) + "/" + QString::number(buf_all_hours));
            if (buf_all_hours != 0){
                osen_p_ayd << QString::number((double)buf_aud_hours / (double)buf_all_hours,'f',2);
            } else {
                osen_p_ayd << " ";
            }

            //--- для всех семместров(года)-------------------------------------------
                buf_all_hours = 0;
                buf_aud_hours = 0;
                buf_lection_hours = 0;
                query2.exec("SELECT lection_hr, labs_hr, practice_hr, individ_hr, "
                            "kontr_rab_hr, consultation_hr, offset_hr, examen_hr, "
                            "coursework_hr, diplomwork_hr, praktika_hr, gak_hr, "
                            "other1, other2, other3 "
                            "FROM distribution WHERE teachers_id = "+ query.value(0).toString() +";");

                while(query2.next()){
                    buf_lection_hours += query2.value(0).toUInt();
                    for (int i = 0; i<15; ++i){
                        if (i<4){
                            buf_aud_hours += query2.value(i).toUInt();
                        }
                        buf_all_hours += query2.value(i).toUInt();
                    }
                }
                year_lection << QString::number(buf_lection_hours);
                year_hours << QString::number(buf_all_hours);
                //year_p_ayd << (QString::number(buf_aud_hours) + "/" + QString::number(buf_all_hours));
                if (buf_all_hours != 0){
                    year_p_ayd << QString::number((double)buf_aud_hours / (double)buf_all_hours,'f',2);
                } else {
                    year_p_ayd << " ";
                }

                if (rate_staff_hour != 0){
                    rate_dole << QString::number(((double)buf_all_hours / (double)staff_hour), 'f', 2);
                } else {
                    rate_dole << " ";
                }
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
            if (index.row() < year_lection.size()){
                return year_lection.at(index.row());
            }
            break;

            case 8:
            if (index.row() < year_hours.size()){
                return year_hours.at(index.row());
            }
            break;

            case 9:
            if (index.row() < year_p_ayd.size()){
                return year_p_ayd.at(index.row());
            }
            break;

            case 10:
            if (index.row() < rate_dole.size()){
                return rate_dole.at(index.row());
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
