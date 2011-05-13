/****************************************************************************

****************************************************************************/

#include <QtSql>

#include "curriculum_sqlmodel.h"

CurriculumSqlModel::CurriculumSqlModel(QObject *parent)
    : QSqlQueryModel(parent)
{
}


Qt::ItemFlags CurriculumSqlModel::flags(
        const QModelIndex &index) const
{
    if (index.column() == 1 || index.column() == 2 ||
        index.column() == 3 || /*index.column() == 4 ||*/
        index.column() == 5 || index.column() == 6 ||
        index.column() == 7)
    {
        return Qt::ItemIsEditable;
    } else {
        if (index.column() == 4 )
        {
            //return QAbstractItemModel::flags(index);
        }
    }
    return QSqlQueryModel::flags(index);
}

bool CurriculumSqlModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
    if (index.column() < 1 || index.column() > 2)
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    //int id = data(primaryKeyIndex).toInt();
/*
    clear();

    bool ok;
    if (index.column() == 1) {
        ok = setFirstName(id, value.toString());
    } else {
        ok = setLastName(id, value.toString());
    }
    refresh();
    return ok;
*/
    return true;
}

void CurriculumSqlModel::refresh()
{
    setQuery("select * from person");
    setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    setHeaderData(1, Qt::Horizontal, QObject::tr("First name"));
    setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));
}

bool CurriculumSqlModel::setFirstName(int personId, const QString &firstName)
{
    QSqlQuery query;
    query.prepare("update person set firstname = ? where id = ?");
    query.addBindValue(firstName);
    query.addBindValue(personId);
    return query.exec();
}

bool CurriculumSqlModel::setLastName(int personId, const QString &lastName)
{
    QSqlQuery query;
    query.prepare("update person set lastname = ? where id = ?");
    query.addBindValue(lastName);
    query.addBindValue(personId);
    return query.exec();
}

SpinBoxDelegate::SpinBoxDelegate(QObject *parent)
    : QItemDelegate(parent)
{
}

QWidget *SpinBoxDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &/* index */) const
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setMinimum(0);
    editor->setMaximum(100);

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
