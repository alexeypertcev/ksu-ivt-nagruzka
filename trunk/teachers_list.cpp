#include "teachers_list.h"
#include "ui_teachers_list.h"
//#include <QSqlQueryModel>

Teachers_list::Teachers_list(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Teachers_list)
{
    ui->setupUi(this);

    sqlmodel_teachers_list = new Teachers_list_model();
    sqlmodel_teachers_list->refresh();
    ui->tableView->setModel(sqlmodel_teachers_list);
    ui->tableView->update();

    sqlmodel_teachers_list->setHeaderData(1, Qt::Horizontal, QObject::tr("ФИО"));
    sqlmodel_teachers_list->setHeaderData(2, Qt::Horizontal, QObject::tr("ауд/все/всего"));
//    sqlmodel_teachers_list->setHeaderData(3, Qt::Horizontal, QObject::tr("аудиторные"));
    ui->tableView->setColumnWidth(0,0);
    ui->tableView->setColumnWidth(1,200);
    ui->tableView->setColumnWidth(2,95);
    //ui->tableView->setColumnWidth(3,80);

}

Teachers_list::~Teachers_list()
{
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
{}

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
    all_hours.clear();

    //**********************************************************
    // error 0x01
    // Ошибка после закрытия программы из-за этой конструкции
    this->setQuery("SELECT teachers.id, f || ', ' || i || ', ' || o, status_name "
                   "FROM teachers WHERE teachers.id != '0' "
                   "ORDER BY f,i,o");
    //
    //**********************************************************

    query.exec("SELECT teachers.id, status_name "
               "FROM teachers WHERE teachers.id != '0'");
    while(query.next()){

        buf_all_hours = 0;
        buf_aud_hours = 0;

        query2.exec("SELECT lection_hr, labs_hr, practice_hr, individ_hr, "
                    "kontr_rab_hr, consultation_hr, offset_hr, examen_hr, "
                    "coursework_hr, diplomwork_hr, praktika_hr, gak_hr, "
                    "other1, other2, other3 "
                    "FROM distribution WHERE teachers_id = "+ query.value(0).toString() +";");

        while(query2.next()){

            //buf_aud_hours += query2.value(0).toInt() + query2.value(1).toInt() + query2.value(2).toInt() + query2.value(3).toInt();
            //buf_all_hours += buf_aud_hours + query2.value(4).toInt() + query2.value(5).toInt() + query2.value(6).toInt() + query2.value(7).toInt();
            for (int i = 0; i<15; ++i){
                if (i<4){
                    buf_aud_hours += query2.value(i).toUInt();
                }
                    buf_all_hours += query2.value(i).toUInt();
            }
        }

        query2.exec("SELECT hours FROM status WHERE name = '"+ query.value(1).toString() +"';");
        if (query2.next()){
            all_hours << (QString::number(buf_aud_hours) + "/"+ QString::number(buf_all_hours) + "/" + query2.value(0).toString()/* + "  "+ QString::number((double)buf / query2.value(0).toDouble() * 100, 'f', 0) + "%"*/);
        } else {
            //all_hours << QString::number(buf);
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
        if (index.column() == 2)
        {
            if (index.row() < all_hours.size()){
                return all_hours.at(index.row());
            }
        }
    }
    return value;
}
