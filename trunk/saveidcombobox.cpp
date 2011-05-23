#include "saveidcombobox.h"

SaveIdComboBox::SaveIdComboBox(QWidget *parent) :
    QComboBox(parent)
{
}

void SaveIdComboBox::setModel( QAbstractItemModel * model )
{
    QComboBox::setModel(model);



}

QString SaveIdComboBox::get_id(){

return QString('1');
}
