/****************************************************************************
** Alexey Pertcev alexey.pertcev@gmail.com
****************************************************************************/
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
class TeachersSqlModel;
class SpecialityDelegate;
class SubjectinsemesterSqlModel;
class Sins_to_distrib_preview_SqlModel;
class Sins_to_distrib_detail_SqlModel;
class DistributionSqlModel;
QT_END_NAMESPACE

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString apppath, QWidget *parent = 0);
    ~MainWindow();
    void set_applicationDirPath(QString app_path);
    QString get_applicationDirPath();

private:
    unsigned short status; //0 - нет БД 1 - есть БД

    Ui::MainWindow *ui;
    void set_design_window();

    Settings* settings;
    QString path_db;
    QSqlDatabase db;
    QString applicationDirPath;
    QSqlRelationalTableModel* tablemodel_subject;
    QSqlRelationalTableModel* tablemodel_teachers;
    QSqlRelationalTableModel* tablemodel_curriculum;

    QSqlRelationalTableModel* tablemodel_spec;
    QSqlRelationalTableModel* tablemodel_stat;

    QSqlQueryModel* sqlmodel_spec;
    StudentsSqlModel* sqlmodel_students;
    TeachersSqlModel* sqlmodel_teachers;
    CurriculumSqlModel* sqlmodel_curriculum;
    SubjectinsemesterSqlModel* sqlmodel_subinsem;
    Sins_to_distrib_preview_SqlModel* sinstodistrib_preview;
    Sins_to_distrib_detail_SqlModel* sinstodistrib_detail;
    QSqlQueryModel *select_subjects;
    DistributionSqlModel *sqlmodel_distribution;

    QString version;

    void load_db();
    void update_subjectlist();
    void update_subject();
    void update_teachers();
    void update_students();
    void update_subject_in_semestre();
    void update_sins_to_distribution_preview();



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

    void update_sins_to_distribution_detail();
    void update_sqlmodel_distribution();
    void update_distribution();
    void update_curriculum();
    void update_subinsem();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_action_txt_triggered();
    void on_pushButton_9_clicked();
    void on_action_txt_2_triggered();
    void on_action_6_triggered();
};

#endif // MAINWINDOW_H
