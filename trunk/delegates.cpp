/****************************************************************************
**
**
****************************************************************************/

#include <QtGui>
#include <QtSql>
#include <QSqlTableModel>

#include "delegates.h"
#include "saveidcombobox.h"

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

//---------------------------------------------------------------------------------------
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

//---------------------------------------------------------------------------------------
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

//---------------------------------------------------------------------------------------
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
