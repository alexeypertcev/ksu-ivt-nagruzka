#include "components.h"
#include <QDebug>

//***************************************************************
//  Class  SaveIdComboBox
//***************************************************************


SaveIdComboBox::SaveIdComboBox(QWidget *parent) :
    QComboBox(parent)
{
}

void SaveIdComboBox::setModel( QAbstractItemModel * model )
{
    QComboBox::setModel(model);

    for (int i = 0; i<model->rowCount(); ++i)
    {
        ids << model->data(model->index(i,1)).toString();
    }
}

QString SaveIdComboBox::get_id()
{
    // -1
    if (this->currentIndex() != -1){
        return ids.at(this->currentIndex());
    } else {
        return ids.at(0);
    }

}

//***************************************************************
//  Class  SaveIdTableView
//***************************************************************

SaveIdTableView::SaveIdTableView(QWidget *parent) :
    QTableView(parent)
{
}

QString SaveIdTableView::get_id()
{
    if (ids.isEmpty()){
        return "NULL";
    } else {
        QModelIndexList indexes = this->selectionModel()->selectedRows();
        int selected_row;
        if (indexes.length() == 0){
            selected_row = 0;
        } else {
            selected_row = indexes.at(0).row();
        }
        return ids.at(selected_row);
    }
}

void SaveIdTableView::update_ids()
{
    ids.clear();
    QAbstractItemModel* temp_model = this->model();
    if (temp_model != NULL){
        for (int i = 0; i < temp_model->rowCount(); ++i)
        {
            ids << temp_model->data(temp_model->index(i,0)).toString();
        }
    } else {
        qDebug() << "temp_model is NULL";

    }
}

void SaveIdTableView::setModel( QAbstractItemModel * model )
{
    QTableView::setModel(model);
    this->update_ids();
}
