/****************************************************************************
** Alexey Pertcev alexey.pertcev@gmail.com
****************************************************************************/

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtGui>
#include <QtSql>
#include "errors.h"

QSqlDatabase current_db;

const QString foreign_keys_ON = "PRAGMA foreign_keys = ON;";
const QString create_table_form_training =
        "CREATE TABLE form_training ( "
        "name TEXT NOT NULL, "
        "CONSTRAINT name PRIMARY KEY (name))";
const QString create_table_subject =
        "CREATE TABLE subject ( "
        "name TEXT NOT NULL, "
        "CONSTRAINT name PRIMARY KEY (name))";
const QString create_table_speciality =
        "CREATE TABLE speciality ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "faculty_name TEXT NOT NULL,"
        "special_name TEXT NOT NULL, "
        "form_training_name TEXT NOT NULL,"
        "CONSTRAINT form_training_name FOREIGN KEY (form_training_name) "
        "REFERENCES form_training (name))";
const QString create_table_students =
        "CREATE TABLE students ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "speciality_id INTEGER NOT NULL, "
        "course INTEGER NOT NULL, "
        "num_group INTEGER NOT NULL, "
        "num_undergroup INTEGER NOT NULL, "
        "quantity_course INTEGER NOT NULL, "
        "CONSTRAINT speciality_id FOREIGN KEY (speciality_id) "
        "REFERENCES speciality (id))";
const QString create_table_status =
        "CREATE TABLE status ( "
        "name TEXT NOT NULL, "
        "hours INTEGER NOT NULL, "
        "CONSTRAINT name PRIMARY KEY (name))";
const QString create_table_staff =
        "CREATE TABLE staff ( "
        "id INTEGER NOT NULL, "
        "name TEXT NOT NULL, "
        "CONSTRAINT id PRIMARY KEY (id))";
const QString create_table_teachers =
        "CREATE TABLE teachers ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "f TEXT NOT NULL, "
        "i TEXT NOT NULL, "
        "o TEXT NOT NULL, "
        "status_name TEXT, "
        "rate REAL NOT NULL, "
        "staff_id INTEGER NOT NULL, "
        "CONSTRAINT staff_id FOREIGN KEY (staff_id) "
        " REFERENCES staff (id), "
        "CONSTRAINT status_name FOREIGN KEY (status_name) "
        " REFERENCES status (name)) ";
const QString create_table_curriculum =
        "CREATE TABLE curriculum ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "speciality_id INTEGER NOT NULL, "
        "subject_name TEXT NOT NULL, "
        "semmester INTEGER NOT NULL, "
        "lection_hr INTEGER NOT NULL, "
        "labs_hr INTEGER NOT NULL, "
        "practice_hr INTEGER NOT NULL, "
        "controlwork INTEGER NOT NULL, "
        "KCP_hr INTEGER NOT NULL, "
        "is_examen INTEGER NOT NULL, "
        "is_offset INTEGER NOT NULL, "
        "is_coursework INTEGER NOT NULL, "
        "CONSTRAINT subject_name FOREIGN KEY (subject_name) "
        " REFERENCES subject (name), "
        "CONSTRAINT speciality_id FOREIGN KEY (speciality_id) "
        " REFERENCES speciality (id))";
const QString create_table_subjects_in_semmester =
        "CREATE TABLE subjects_in_semmester ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "curriculum_id INTEGER NOT NULL, "
        "students_id INTEGER NOT NULL, "
        "lection_hr INTEGER NOT NULL, "
        "labs_hr INTEGER NOT NULL, "
        "practice_hr INTEGER NOT NULL, "
        "individ_hr REAL NOT NULL, "
        "kontr_rab_hr REAL NOT NULL, "
        "consultation_hr REAL NOT NULL, "
        "offset_hr REAL NOT NULL, "
        "examen_hr REAL NOT NULL, "
        "coursework_hr REAL NOT NULL, "
        "diplomwork_hr REAL NOT NULL, "
        "praktika_hr REAL NOT NULL, "
        "gak_hr REAL NOT NULL, "
        "other1 REAL NOT NULL, "
        "other2 REAL NOT NULL, "
        "other3 REAL NOT NULL, "
        "CONSTRAINT students_id FOREIGN KEY (students_id) "
        " REFERENCES students (id), "
        "CONSTRAINT curriculum_id FOREIGN KEY (curriculum_id) "
        " REFERENCES curriculum (id)) ";
const QString create_table_distribution =
        "CREATE TABLE distribution ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "teachers_id INTEGER NOT NULL, "
        "subjects_in_semmester_id INTEGER NOT NULL, "
        "lection_hr INTEGER NOT NULL, "
        "labs_hr INTEGER NOT NULL, "
        "practice_hr INTEGER NOT NULL, "
        "individ_hr REAL NOT NULL, "
        "kontr_rab_hr REAL NOT NULL, "
        "consultation_hr REAL NOT NULL, "
        "offset_hr REAL NOT NULL, "
        "examen_hr REAL NOT NULL, "
        "coursework_hr REAL NOT NULL, "
        "diplomwork_hr REAL NOT NULL, "
        "praktika_hr REAL NOT NULL, "
        "gak_hr REAL NOT NULL, "
        "other1 REAL NOT NULL, "
        "other2 REAL NOT NULL, "
        "other3 REAL NOT NULL, "
        "CONSTRAINT subjects_in_semmester_id FOREIGN KEY (subjects_in_semmester_id) "
        " REFERENCES subjects_in_semmester (id), "
        "CONSTRAINT teachers_id FOREIGN KEY (teachers_id) "
        " REFERENCES teachers (id))";
const QString create_table_coefficients =
        "CREATE TABLE coefficients ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "speciality_id INTEGER NOT NULL, "
        "value REAL NOT NULL, "
        "CONSTRAINT speciality_id FOREIGN KEY (speciality_id) "
        " REFERENCES speciality (id))";
const QString create_table_other_data =
        "CREATE TABLE other_data ( "
        "name TEXT NOT NULL, "
        "value TEXT NOT NULL, "
        "CONSTRAINT name PRIMARY KEY (name))";

const QString drop_table_distribution          = "DROP TABLE distribution";
const QString drop_table_subjects_in_semmester = "DROP TABLE subjects_in_semmester";
const QString drop_table_curriculum = "DROP TABLE curriculum";
const QString drop_table_students   = "DROP TABLE students";
const QString drop_table_teachers   = "DROP TABLE teachers";
const QString drop_table_speciality = "DROP TABLE speciality";
const QString drop_table_subject    = "DROP TABLE subject";
const QString drop_table_status     = "DROP TABLE status";
const QString drop_table_form_training = "DROP TABLE form_training";
const QString drop_table_staff         = "DROP TABLE staff";
const QString drop_table_coefficients  = "DROP TABLE coefficients";
const QString drop_table_other_data    = "DROP TABLE other_data";

static bool createConnection(QString path_db)
{
    current_db = QSqlDatabase::addDatabase("QSQLITE");
    current_db.setDatabaseName(path_db);
    return current_db.open();
}

static bool create_all_tables(){

    if (!current_db.open()) {
        return false;
    } else{
        QSqlQuery query;
        query.exec(foreign_keys_ON);
        query.exec(create_table_form_training);
        query.exec(create_table_subject);
        query.exec(create_table_speciality);
        query.exec(create_table_students);
        query.exec(create_table_status);
        query.exec(create_table_staff);
        query.exec(create_table_teachers);
        query.exec(create_table_curriculum);
        query.exec(create_table_subjects_in_semmester);
        query.exec(create_table_distribution);
        query.exec(create_table_coefficients);
        query.exec(create_table_other_data);
    }
    return true;
}

static bool insert_main_data_to_coefficients()
{
    if (current_db.open()) {
        QSqlQuery query;
        // main data
        query.exec(foreign_keys_ON);

        query.exec("insert into coefficients values(NULL, '00_coef_lection_hr', 0, 1)");
        query.exec("insert into coefficients values(NULL, '01_coef_labs_for_undergroup_hr', 0, 1)");
        query.exec("insert into coefficients values(NULL, '02_coef_practice_for_group_hr',  0, 1)");
        query.exec("insert into coefficients values(NULL, '03_coef_individ_for_KCR_hr',     0, 1)");
        query.exec("insert into coefficients values(NULL, '04_coef_kontr_rab_for_quantitycourse_min', 0, 15)");
        query.exec("insert into coefficients values(NULL, '05_coef_offset_for_quantitycourse_min',    0, 15)");
        query.exec("insert into coefficients values(NULL, '06_coef_examen_for_quantitycourse_min',    0, 20)");
        query.exec("insert into coefficients values(NULL, '07_coef_coursework_for_quantitycourse_hr', 0, 3)");
        query.exec("insert into coefficients values(NULL, '08_coef_consultation_ochnui_percent',      0, 5)");
        query.exec("insert into coefficients values(NULL, '09_coef_consultation_zaochnui_percent',    0, 15)");
        query.exec("insert into coefficients values(NULL, '10_coef_consultation_och_zaoch_percent',   0, 10)");
        query.exec("insert into coefficients values(NULL, '11_coef_consultation_add_is_examen_for_group', 0, 2)");
        query.exec("insert into coefficients values(NULL, '12_coef_ruk_vo_kurs_work_hr', 0, 5)");
        query.exec("insert into coefficients values(NULL, '13_coef_ruk_vo_VKR_spec_hr',  0, 20)");
        query.exec("insert into coefficients values(NULL, '14_coef_ruk_vo_VKR_bak_hr',   0, 12)");
        query.exec("insert into coefficients values(NULL, '15_coef_zachita_kurs_rab_na_kommis_min', 0, 15)");
        query.exec("insert into coefficients values(NULL, '16_coef_ruk_vo_VKR_mag_hr',     0, 28)");
        query.exec("insert into coefficients values(NULL, '17_coef_recenzir_VKR_hr',       0, 1)");
        query.exec("insert into coefficients values(NULL, '18_coef_normokontrol_hr',       0, 1)");
        query.exec("insert into coefficients values(NULL, '19_coef_ychastie_work_GAK_min', 0, 30)");
        query.exec("insert into coefficients values(NULL, '20_coef_ruk_vo_aspirants_hr',   0, 50)");
        return true;
     }
    return false;
}

static bool insert_main_data()
{

    if (current_db.open()) {
        QSqlQuery query;

        // main data
        query.exec(foreign_keys_ON);

        query.exec("insert into form_training values('оч')");
        query.exec("insert into form_training values('оч-заоч')");
        query.exec("insert into form_training values('заоч')");
        query.exec("insert into speciality values(0, 'все','', 'оч')");

        query.exec("insert into status values('выберите..', 0)");
        query.exec("insert into status values('профессор', 680)");
        query.exec("insert into status values('доцент', 730)");
        query.exec("insert into status values('ст. препод.', 780)");
        query.exec("insert into status values('ассистент', 830)");
        query.exec("insert into status values('декан', 500)");
        query.exec("insert into status values('зав. кафедрой', 700)");

        query.exec("insert into staff values(0, 'штатный')");
        query.exec("insert into staff values(1, 'внешний совместитель')");
        query.exec("insert into staff values(2, 'внутр.')");

        query.exec("insert into teachers values(0, 'выберите..', ' ', ' ', 'выберите..', 1 , 0);");

        insert_main_data_to_coefficients();
        query.exec("insert into other_data values('academic_year', '2011/2012')");
        query.exec("insert into other_data values('name_kafedry_faculty', 'Программного обеспечения и администрирования информационных систем')");
        query.exec("insert into other_data values('name_kafedry_smail', 'ПОиАИС')");
        query.exec("insert into other_data values('business_base_of_training', 'бюджет')");
        query.exec("insert into other_data values('vice_rector_on_education_work', 'Захаров В.В.')");
        query.exec("insert into other_data values('boundary_amount', '1.02')");
        return true;
     }
     return false;
}

static bool drop_all_tables()
{

    if (!current_db.open()) {
        return false;
    } else{
        QSqlQuery query;
        query.exec(drop_table_distribution);
        query.exec(drop_table_subjects_in_semmester);
        query.exec(drop_table_curriculum);
        query.exec(drop_table_students);
        query.exec(drop_table_teachers);
        query.exec(drop_table_speciality);
        query.exec(drop_table_subject);
        query.exec(drop_table_status);
        query.exec(drop_table_form_training);
        query.exec(drop_table_staff);
        query.exec(drop_table_coefficients);
        query.exec(drop_table_other_data);
    }
    return true;
}

#endif
