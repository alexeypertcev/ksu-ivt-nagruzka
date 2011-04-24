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
    QSqlRelationalTableModel *tablemodel_subject;
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_action_6_activated();
    void on_pushButton_5_clicked();
    void on_pushButton_clicked();
    void push1();

};

#endif // MAINWINDOW_H
