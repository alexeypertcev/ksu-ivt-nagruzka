#ifndef SAVEIDCOMBOBOX_H
#define SAVEIDCOMBOBOX_H

#include <QComboBox>

class SaveIdComboBox : public QComboBox
{
    Q_OBJECT
public:
    SaveIdComboBox(QWidget *parent = 0);
    QString get_id();
    void setModel( QAbstractItemModel * model );
private:
    QString *ids;

};

#endif // SAVEIDCOMBOBOX_H
