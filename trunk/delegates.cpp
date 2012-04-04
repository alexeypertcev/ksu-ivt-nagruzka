/****************************************************************************
**
**
****************************************************************************/

#include <QtGui>
#include <QtSql>
#include <QSqlTableModel>

#include "delegates.h"
#include "components.h"



//**********************************************************
//  class  SpinBoxDelegate
//**********************************************************

SpinBoxDelegate::SpinBoxDelegate(int min, int max, QObject *parent)
    : QItemDelegate(parent)
{
    range_min = min;
    range_max = max;
}

QWidget *SpinBoxDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &/* index */) const
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setMinimum(range_min);
    editor->setMaximum(range_max);

    return editor;
}

void SpinBoxDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    int value = index.model()->data(index, Qt::EditRole).toInt();

    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->setValue(value);
}

void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->interpretText();
    int value = spinBox->value();

    model->setData(index, value, Qt::EditRole);
}

void SpinBoxDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}



//**********************************************************
//  class  ComboBoxDelegate
//**********************************************************

ComboBoxDelegate::ComboBoxDelegate(QString table_name, QObject *parent)
    : QItemDelegate(parent)
{
    table = table_name;
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &/* index */) const
{
    QComboBox *editor = new QComboBox(parent);
    QSqlTableModel* tablemodel = new QSqlTableModel(parent);
    tablemodel->setTable(table);
    tablemodel->setSort(0, Qt::AscendingOrder);
    tablemodel->setEditStrategy(QSqlTableModel::OnFieldChange);
    tablemodel->select();
    editor->setModel(tablemodel);

    return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();

    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    int i;
    // тк. данные из модели ошибок быть не должно
    for (i = 0; i<comboBox->count(); ++i)
    {
        if ( comboBox->itemText(i) == value ){ break; }
    }
    //
    comboBox->setCurrentIndex(i);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{

    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString value = comboBox->currentText();

    model->setData(index, value, Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}



//**********************************************************
//  class  SpecialityDelegate
//**********************************************************

SpecialityDelegate::SpecialityDelegate(QObject *parent)
    : QItemDelegate(parent)
{
}

QWidget *SpecialityDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &/* index */) const
{
    SaveIdComboBox *editor = new SaveIdComboBox(parent);
    QSqlQueryModel* sqlmodel = new QSqlQueryModel(parent);
    sqlmodel->setQuery("SELECT special_name || '(' || form_training_name || ')', id "
                       "FROM speciality;");
    editor->setModel(sqlmodel);
    return editor;
}

void SpecialityDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();

    SaveIdComboBox *saveIdBox = static_cast<SaveIdComboBox*>(editor);
    int i;
    for (i = 0; i<saveIdBox->count(); ++i)
    {
        if ( saveIdBox->itemText(i) == value ){ break; }
    }

    saveIdBox->setCurrentIndex(i);
}

void SpecialityDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{

    SaveIdComboBox *comboBox = static_cast<SaveIdComboBox*>(editor);
    QString value = comboBox->get_id();

    model->setData(index, value, Qt::EditRole);
}

void SpecialityDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}



//**********************************************************
//  class  CheckBoxDelegate
//**********************************************************

CheckBoxDelegate::CheckBoxDelegate(QObject *parent)
    : QItemDelegate(parent)
{
}

QWidget *CheckBoxDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &/* index */) const
{
    QCheckBox *editor = new QCheckBox(parent);
    return editor;
}

void CheckBoxDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    int value = index.model()->data(index, Qt::EditRole).toInt();

    QCheckBox *checkBox = static_cast<QCheckBox*>(editor);

    if (value == 0){
        checkBox->setCheckState(Qt::Unchecked);
    } else {
        checkBox->setCheckState(Qt::Checked);
    }
}

void CheckBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QCheckBox *checkBox = static_cast<QCheckBox*>(editor);
    int value = 0;
    if (checkBox->checkState() == Qt::Checked){
        value = 1;
    }

    model->setData(index, value, Qt::EditRole);
}

void CheckBoxDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}



//**********************************************************
//  class  StatusDelegate
//**********************************************************


StatusDelegate::StatusDelegate(QObject *parent)
    : QItemDelegate(parent)
{
}

QWidget *StatusDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &/* index */) const
{
    QComboBox *editor = new QComboBox(parent);
    QSqlQueryModel* sqlmodel = new QSqlQueryModel(parent);
    sqlmodel->setQuery("SELECT name "
                       "FROM status WHERE name != 'выберите..';");
    editor->setModel(sqlmodel);
    return editor;
}

void StatusDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();

    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    int i;
    // тк. данные из модели ошибок быть не должно
    for (i = 0; i<comboBox->count(); ++i)
    {
        if ( comboBox->itemText(i) == value ){ break; }
    }
    comboBox->setCurrentIndex(i);
}

void StatusDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{

    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString value = comboBox->currentText();

    model->setData(index, value, Qt::EditRole);
}

void StatusDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}


//**********************************************************
//  class  FioDelegate
//**********************************************************

FioDelegate::FioDelegate(QObject *parent)
    : QItemDelegate(parent)
{
}

QWidget *FioDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &/* index */) const
{
    SaveIdComboBox *editor = new SaveIdComboBox(parent);
    QSqlQueryModel* sqlmodel = new QSqlQueryModel(parent);
    sqlmodel->setQuery("SELECT f || ' ' || i || ' ' || o AS 'FIO', id "
                       "FROM teachers WHERE id != '0' "
                       "ORDER BY f, i, o;");
    editor->setModel(sqlmodel);
    return editor;
}

void FioDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();

    SaveIdComboBox *saveIdBox = static_cast<SaveIdComboBox*>(editor);
    int i;
    for (i = 0; i<saveIdBox->count(); ++i)
    {
        if ( saveIdBox->itemText(i) == value ){ break; }
    }

    saveIdBox->setCurrentIndex(i);
}

void FioDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{

    SaveIdComboBox *comboBox = static_cast<SaveIdComboBox*>(editor);
    if (comboBox->currentIndex() != -1){
        model->setData(index, comboBox->get_id(), Qt::EditRole);
    }
}

void FioDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}

//**********************************************************
//  class  StaffDelegate
//**********************************************************

StaffDelegate::StaffDelegate(QObject *parent)
    : QItemDelegate(parent)
{
}

QWidget *StaffDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &/* index */) const
{
    SaveIdComboBox *editor = new SaveIdComboBox(parent);
    QSqlQueryModel* sqlmodel = new QSqlQueryModel(parent);
    sqlmodel->setQuery("SELECT name, id "
                       "FROM staff;");
    editor->setModel(sqlmodel);
    return editor;
}

void StaffDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();

    SaveIdComboBox *saveIdBox = static_cast<SaveIdComboBox*>(editor);
    int i;
    for (i = 0; i<saveIdBox->count(); ++i)
    {
        if ( saveIdBox->itemText(i) == value ){ break; }
    }

    saveIdBox->setCurrentIndex(i);
}

void StaffDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{

    SaveIdComboBox *comboBox = static_cast<SaveIdComboBox*>(editor);
    QString value = comboBox->get_id();
    qDebug() << "value: " << value;
    model->setData(index, value, Qt::EditRole);
}

void StaffDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}


