#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "students_sqlmodel.h"

QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
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
    void set_design_window();
    QSqlDatabase db;
    QSqlRelationalTableModel* tablemodel_subject;
    QSqlRelationalTableModel* tablemodel_teachers;
    QSqlRelationalTableModel* tablemodel_students;
    QSqlRelationalTableModel* tablemodel_curriculum;
    QSqlRelationalTableModel* tablemodel_subjects_in_semmestre;
    QSqlRelationalTableModel* tablemodel_distribution;

    StudentsSqlModel* sqlmodel_students;

    QString select_students;

private slots:
    void on_pushButton_del_distribution_clicked();
    void on_pushButton_add_distribution_clicked();
    void on_pushButton_del_subjects_in_semmestre_clicked();
    void on_pushButton_add_subjects_in_semmestre_clicked();
    void on_pushButton_del_curriculum_clicked();
    void on_pushButton_add_curriculum_clicked();
    void on_action_7_activated();
    void on_pushButton_del_student_clicked();
    void on_pushButton_add_student_clicked();
    void on_pushButton_clicked();
    void on_action_5_activated();
    void on_action_4_activated();
    void on_pushButton_del_teachers_clicked();
    void on_pushButton_add_teachers_clicked();
    void on_pushButton_del_subject_clicked();
    void on_pushButton_add_subject_clicked();
    void on_action_6_activated();
};

#endif // MAINWINDOW_H
