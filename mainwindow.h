#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class QSqlTableModel;
QT_END_NAMESPACE

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
    QSqlRelationalTableModel* tablemodel_subject;
    QSqlRelationalTableModel* tablemodel_teachers;
private slots:
    void on_action_4_activated();
    void on_pushButton_del_teachers_clicked();
    void on_pushButton_add_teachers_clicked();
    void on_pushButton_del_subject_clicked();
    void on_pushButton_add_subject_clicked();
    void on_action_6_activated();
};

#endif // MAINWINDOW_H
