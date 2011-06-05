#include "components.h"

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
    return ids.at(this->currentIndex());
}


SaveIdTableView::SaveIdTableView(QWidget *parent) :
    QTableView(parent)
{
}

QString SaveIdTableView::get_id()
{
    return ids.at(this->currentIndex().row());;
}

void SaveIdTableView::setModel( QAbstractItemModel * model )
{
    QTableView::setModel(model);

    for (int i = 0; i<model->rowCount(); ++i)
    {
        ids << model->data(model->index(i,2)).toString();
    }
}
