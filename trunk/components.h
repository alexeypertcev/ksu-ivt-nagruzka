#ifndef SAVEIDCOMBOBOX_H
#define SAVEIDCOMBOBOX_H

#include <QComboBox>
#include <QTableView>

class SaveIdComboBox : public QComboBox
{
    Q_OBJECT
public:
    SaveIdComboBox(QWidget *parent = 0);
    QString get_id();
    void setModel( QAbstractItemModel * model );
private:
    QStringList ids;

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

#endif // SAVEIDCOMBOBOX_H
