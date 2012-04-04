/****************************************************************************
** Alexey Pertcev alexey.pertcev@gmail.com
****************************************************************************/

#ifndef SAVEIDCOMBOBOX_H
#define SAVEIDCOMBOBOX_H

#include <QComboBox>
#include <QTableView>
#include <QSqlQueryModel>
#include "errors.h"

class SaveIdComboBox : public QComboBox
{
    Q_OBJECT
public:
    SaveIdComboBox(QWidget *parent = 0);
    QString get_id();
    void setModel( QAbstractItemModel * model );
protected:
    QStringList ids;

};

class SaveIdComboBoxIncudeAll : public SaveIdComboBox
{
    Q_OBJECT
public:
    SaveIdComboBoxIncudeAll(QWidget *parent = 0);
    QString get_id();
};

class SaveIdTableView : public QTableView
{
    Q_OBJECT
public:
    SaveIdTableView(QWidget *parent = 0);
    QString get_id();
    void setModel( QAbstractItemModel * model );
    void update_ids();
private:
    QStringList ids;

};

class SpecialityForComboBoxSqlModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    SpecialityForComboBoxSqlModel(QObject *parent = 0);
    int rowCount (const QModelIndex & parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void refresh();
    int rowCountDB();
private:
    unsigned int rowsCountDB;

};

#endif // SAVEIDCOMBOBOX_H
