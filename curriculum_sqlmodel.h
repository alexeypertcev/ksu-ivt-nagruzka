/****************************************************************************

****************************************************************************/

#ifndef CURRICULUMSQLMODEL_H
#define CURRICULUMSQLMODEL_H

#include <QSqlQueryModel>
#include <QItemDelegate>
#include <QSpinBox>

class CurriculumSqlModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    CurriculumSqlModel(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    bool setFirstName(int personId, const QString &firstName);
    bool setLastName(int personId, const QString &lastName);
    void refresh();
};

class SpinBoxDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    SpinBoxDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif
