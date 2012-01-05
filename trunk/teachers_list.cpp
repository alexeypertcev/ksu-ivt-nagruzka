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
    sqlmodel_teachers_list->setHeaderData(2, Qt::Horizontal, QObject::tr("должность"));
    sqlmodel_teachers_list->setHeaderData(3, Qt::Horizontal, QObject::tr("аудиторные"));
    ui->tableView->setColumnWidth(0,0);
    ui->tableView->setColumnWidth(1,200);
    ui->tableView->setColumnWidth(2,80);
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
    int buf;
    auditors_hours.clear();

    this->setQuery("SELECT teachers.id, f || ', ' || i || ', ' || o, status_name "
                   "FROM teachers WHERE teachers.id != '0'");

    query.exec("SELECT teachers.id, status_name "
               "FROM teachers WHERE teachers.id != '0'");
    while(query.next()){

        buf = 0;
        query2.exec("SELECT lection_hr, labs_hr, practice_hr, individ_hr FROM distribution WHERE teachers_id = "+ query.value(0).toString() +";");
        while(query2.next()){
            buf += query2.value(0).toInt() + query2.value(1).toInt() + query2.value(2).toInt() + query2.value(3).toInt();
        }

        query2.exec("SELECT hours FROM status WHERE name = '"+ query.value(1).toString() +"';");
        if (query2.next()){
            auditors_hours << (QString::number(buf) + "/" + query2.value(0).toString()/* + "  "+ QString::number(buf / query2.value(0).toInt()) + "%"*/);
        } else {
            auditors_hours << QString::number(buf);
        }


    }


}

QVariant Teachers_list_model::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);

    switch (role)
    {
    case Qt::DisplayRole:
        if (index.column() == 2)
        {
            return auditors_hours.at(index.row());
        }

    }
    return value;
}



