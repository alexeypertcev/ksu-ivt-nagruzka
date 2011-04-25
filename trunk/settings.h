#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
QT_END_NAMESPACE

namespace Ui {
    class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

private:
    Ui::Settings *ui;
    QSqlRelationalTableModel* tablemodel_spec;
    QSqlRelationalTableModel* tablemodel_stat;
private slots:


private slots:
    void on_pushButton_del_dolj_clicked();
    void on_pushButton_add_dolj_clicked();
    void on_pushButton_del_spec_clicked();
    void on_pushButton_add_spec_clicked();
};

#endif // SETTINGS_H
