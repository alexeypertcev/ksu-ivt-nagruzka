#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class QSqlQueryModel;
class CurriculumSqlModel;
class Settings;
class StudentsSqlModel;
class SpecialityDelegate;
class SubjectinsemesterSqlModel;
class Sins_to_distribSqlModel;
class DistributionSqlModel;
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

    Settings* settings;
    QString path_db;
    QSqlDatabase db;
    QSqlRelationalTableModel* tablemodel_subject;
    QSqlRelationalTableModel* tablemodel_teachers;
    QSqlRelationalTableModel* tablemodel_curriculum;

    QSqlRelationalTableModel* tablemodel_spec;
    QSqlRelationalTableModel* tablemodel_stat;

    QSqlQueryModel* sqlmodel_spec;
    StudentsSqlModel* sqlmodel_students;
    CurriculumSqlModel* sqlmodel_curriculum;
    SubjectinsemesterSqlModel* sqlmodel_subinsem;
    Sins_to_distribSqlModel* sinstodistrib;
    QSqlQueryModel *select_subjects;
    DistributionSqlModel *sqlmodel_distribution;

    void update_subjectlist();
    void update_subject();
    void update_teachers();
    void update_students();
    void update_subject_in_semestre();
    void update_sins_to_distribution();
    void update_sqlmodel_distribution();

    QString consultation_get(int lection_hr, QString speciality_id, int num_group, int is_examen);

private slots:
    void on_tabWidget_currentChanged(int index);
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

    void update_distribution();
    void update_curriculum();
    void update_subinsem();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
};

#endif // MAINWINDOW_H
