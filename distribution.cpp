#include "distribution.h"
#include <QDebug>
#include <QMessageBox>
#include <QtSql>

//********************************************************************************
//  class DistributionSqlModel
//********************************************************************************

DistributionSqlModel::DistributionSqlModel(QObject *parent) :
    QSqlQueryModel(parent)
{
    subjects_in_semmestre_id = '1';
}

Qt::ItemFlags DistributionSqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);

    if (index.column() > 2 && index.column() < 19 && index.row() < rowsCountDB)
    {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

void DistributionSqlModel::setsins(QString id)
{
    subjects_in_semmestre_id = id;
}

void DistributionSqlModel::check_entry()
{
    QSqlQuery query;
    QString s = "SELECT id FROM distribution WHERE distribution.subjects_in_semmester_id = " + subjects_in_semmestre_id + ";";
    query.exec(s);

    if(!query.next()){
        QString id,lection_hr,labs_hr,practice_hr,individ_hr,kontr_rab_hr,consultation_hr,
                offset_hr,examen_hr,coursework_hr,diplomwork_hr,praktika_hr,gak_hr,
                other1,other2,other3;
        s = "SELECT id,lection_hr,labs_hr,practice_hr,individ_hr,kontr_rab_hr,consultation_hr, "
            " offset_hr,examen_hr,coursework_hr,diplomwork_hr,praktika_hr,gak_hr, "
            " other1,other2,other3 FROM subjects_in_semmester WHERE subjects_in_semmester.id = " + subjects_in_semmestre_id + ";";

        if (!query.exec(s)){
            qDebug() << "error select";
        }
        if (query.next()){

            id              = query.value(0).toString();
            lection_hr      = query.value(1).toString();
            labs_hr         = query.value(2).toString();
            practice_hr     = query.value(3).toString();
            individ_hr      = query.value(4).toString();
            kontr_rab_hr    = query.value(5).toString();
            consultation_hr = query.value(6).toString();
            offset_hr       = query.value(7).toString();
            examen_hr       = query.value(8).toString();
            coursework_hr   = query.value(9).toString();
            diplomwork_hr   = query.value(10).toString();
            praktika_hr     = query.value(11).toString();
            gak_hr          = query.value(12).toString();
            other1          = query.value(13).toString();
            other2          = query.value(14).toString();
            other3          = query.value(15).toString();

            s =    "insert into distribution values("
                   "NULL, "                             // "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "0, "+                               // "teachers_id INTEGER, "
                    subjects_in_semmestre_id + ", "+    // "subjects_in_semmester_id INTEGER NOT NULL, "
                    lection_hr + ", "+                  // "lection_hr INTEGER NOT NULL, "
                    labs_hr + ", "+                     // "labs_hr INTEGER NOT NULL, "
                    practice_hr + ", "+                 // "practice_hr INTEGER NOT NULL, "
                    individ_hr + ", "+                  // "individ_hr REAL NOT NULL, "
                    kontr_rab_hr + ", "+                // "kontr_rab_hr REAL NOT NULL, "
                    consultation_hr + ", "+             // "consultation_hr REAL NOT NULL, "
                    offset_hr + ", "+                   // "offset_hr REAL NOT NULL, "
                    examen_hr + ", "+                   // "examen_hr REAL NOT NULL, "
                    coursework_hr + ", "+               // "coursework_hr REAL NOT NULL, "
                    diplomwork_hr + ", "+               // "diplomwork_hr REAL NOT NULL, "
                    praktika_hr + ", "+                 // "praktika_hr REAL NOT NULL, "
                    gak_hr + ", "+                      // "gak_hr REAL NOT NULL, "
                    other1 + ", "+                      // "other1 REAL NOT NULL, "
                    other2 + ", "+                      // "other2 REAL NOT NULL, "
                    other3 +                            // "other3 REAL NOT NULL, "
                    ");";

            if (!query.exec(s)){
                qDebug() << "fail insert to distribution";
            }
        } else{
            qDebug() << "error next";
        }
    }
}

bool DistributionSqlModel::add()
{
QString s;
QSqlQuery query;
    s =    "insert into distribution values("
           "NULL, "                             // "id INTEGER PRIMARY KEY AUTOINCREMENT, "
           "0, "+                               // "teachers_id INTEGER, "
            subjects_in_semmestre_id + ", "     // "subjects_in_semmester_id INTEGER NOT NULL, "
            "0, "                  // "lection_hr INTEGER NOT NULL, "
            "0, "                  // "labs_hr INTEGER NOT NULL, "
            "0, "                  // "practice_hr INTEGER NOT NULL, "
            "0, "                  // "individ_hr REAL NOT NULL, "
            "0, "                  // "kontr_rab_hr REAL NOT NULL, "
            "0, "                  // "consultation_hr REAL NOT NULL, "
            "0, "                  // "offset_hr REAL NOT NULL, "
            "0, "                  // "examen_hr REAL NOT NULL, "
            "0, "                  // "coursework_hr REAL NOT NULL, "
            "0, "                  // "diplomwork_hr REAL NOT NULL, "
            "0, "                  // "praktika_hr REAL NOT NULL, "
            "0, "                  // "gak_hr REAL NOT NULL, "
            "0, "                  // "other1 REAL NOT NULL, "
            "0, "                  // "other2 REAL NOT NULL, "
            "0 "                   // "other3 REAL NOT NULL, "
            ");";

    return query.exec(s);
}

bool DistributionSqlModel::del(QString id)
{
    QString s = "DELETE FROM distribution WHERE id = '" + id + "';";
    QSqlQuery query;

    return query.exec(s);
}

void DistributionSqlModel::refresh()
{
    rowsCountDB = rowCountDB();
    QString s;
    QSqlQuery query;
    s = "SELECT id,lection_hr,labs_hr,practice_hr,individ_hr,kontr_rab_hr,consultation_hr, "
        " offset_hr,examen_hr,coursework_hr,diplomwork_hr,praktika_hr,gak_hr, "
        " other1,other2,other3 FROM subjects_in_semmester WHERE subjects_in_semmester.id = " + subjects_in_semmestre_id + ";";
    query.exec(s);
    query.next();

    not_used_lection_hr  = query.value(1).toInt() - sum_field("lection_hr");
    not_used_labs_hr     = query.value(2).toInt() - sum_field("labs_hr");
    not_used_practice_hr = query.value(3).toInt() - sum_field("practice_hr");
    not_used_individ_hr  = query.value(4).toInt() - sum_field("individ_hr");
    not_used_kontr_rab_hr    = query.value(5).toInt() - sum_field("kontr_rab_hr");
    not_used_consultation_hr = query.value(6).toInt() - sum_field("consultation_hr");
    not_used_offset_hr     = query.value(7).toInt() - sum_field("offset_hr");
    not_used_examen_hr     = query.value(8).toInt() - sum_field("examen_hr");
    not_used_coursework_hr = query.value(9).toInt() - sum_field("coursework_hr");
    not_used_diplomwork_hr = query.value(10).toInt() - sum_field("diplomwork_hr");
    not_used_praktika_hr   = query.value(11).toInt() - sum_field("praktika_hr");
    not_used_gak_hr = query.value(12).toInt() - sum_field("gak_hr");
    not_used_other1 = query.value(13).toInt() - sum_field("other1");
    not_used_other2 = query.value(14).toInt() - sum_field("other2");
    not_used_other3 = query.value(15).toInt() - sum_field("other3");


    query.exec("SELECT teachers_id FROM distribution WHERE distribution.subjects_in_semmester_id = " + subjects_in_semmestre_id + ";");
    query.next();

    if (!query.isNull(0)){

        this->setQuery("SELECT "
                   "distribution.id, "
                   "curriculum.subject_name, "
                   "curriculum.semmester, "
                   "teachers.f || ' ' || teachers.i || ' ' || teachers.o AS 'FIO', "
                   "distribution.lection_hr, "
                   "distribution.labs_hr, "
                   "distribution.practice_hr, "
                   "distribution.individ_hr, "
                   "distribution.kontr_rab_hr, "
                   "distribution.consultation_hr, "
                   "distribution.offset_hr, "
                   "distribution.examen_hr, "
                   "distribution.coursework_hr, "
                   "distribution.diplomwork_hr, "
                   "distribution.praktika_hr, "
                   "distribution.gak_hr, "
                   "distribution.other1, "
                   "distribution.other2, "
                   "distribution.other3 "
                   "FROM distribution,teachers,subjects_in_semmester,curriculum "
                   "WHERE "
                   "distribution.teachers_id = teachers.id AND "
                   "distribution.subjects_in_semmester_id = subjects_in_semmester.id AND "
                   "subjects_in_semmester.curriculum_id = curriculum.id AND "
                   "distribution.subjects_in_semmester_id = " + subjects_in_semmestre_id + "; ");
    }
    // испустить сигнал для списка преподавателей
    table_changed();
}

int DistributionSqlModel::rowCount (const QModelIndex & parent) const
{
    if (parent.isValid()) return 0;
    return QSqlQueryModel::rowCount(parent) + 1;
}

QVariant DistributionSqlModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);

    switch (role)
    {
    case Qt::DisplayRole:
        if (index.row() == rowsCountDB)
        {
            switch(index.column()){
            case 3:
               return "Неиспользованные часы: ";
            case 4:
               return QString::number( not_used_lection_hr );
            case 5:
               return QString::number( not_used_labs_hr );
            case 6:
               return QString::number( not_used_practice_hr );
            case 7:
               return QString::number( not_used_individ_hr );
            case 8:
               return QString::number( not_used_kontr_rab_hr );
            case 9:
               return QString::number( not_used_consultation_hr );
            case 10:
               return QString::number( not_used_offset_hr );
            case 11:
               return QString::number( not_used_examen_hr );
            case 12:
               return QString::number( not_used_coursework_hr );
            case 13:
               return QString::number( not_used_diplomwork_hr );
            case 14:
               return QString::number( not_used_praktika_hr );
            case 15:
               return QString::number( not_used_gak_hr );
            case 16:
               return QString::number( not_used_other1 );
            case 17:
               return QString::number( not_used_other2 );
            case 18:
               return QString::number( not_used_other3 );
            default:
               return "";
            }
        }
        break;
    case Qt::BackgroundColorRole:
        {
            if (index.row() == rowsCountDB) return qVariantFromValue(QColor(224, 255, 193));
            else return value;
        }
        break;
    case Qt::FontRole:
        if (index.row() == rowsCountDB)
        {
            QFont fnt = QFont(qvariant_cast<QFont>(value));
            fnt.setBold(true);

            return qVariantFromValue(fnt);
        }
        else return value;
        break;
    case Qt::TextColorRole:


        break;
    }
    return value;
}

bool DistributionSqlModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
    if (index.column() < 3 || index.column() > 18)
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    QString field = ";";
    switch (index.column()){

        case 3:
            field = "teachers_id";
            break;
        case 4:
            field = "lection_hr";
            break;
        case 5:
            field = "labs_hr";
            break;
        case 6:
            field = "practice_hr";
            break;
        case 7:
            field = "individ_hr";
            break;
        case 8:
            field = "kontr_rab_hr";
            break;
        case 9:
            field = "consultation_hr";
            break;
        case 10:
            field = "offset_hr";
            break;
        case 11:
            field = "examen_hr";
            break;
        case 12:
            field = "coursework_hr";
            break;
        case 13:
            field = "diplomwork_hr";
            break;
        case 14:
            field = "praktika_hr";
            break;
        case 15:
            field = "gak_hr";
            break;
        case 16:
            field = "other1";
            break;
        case 17:
            field = "other2";
            break;
        case 18:
            field = "other3";
            break;
        }

    QString s = "update distribution set "+ field +" = "+ value.toString() +" where id = "+ data(primaryKeyIndex, Qt::DisplayRole).toString();
    qDebug() << s;

    QSqlQuery query;
    if (!query.exec(s)){
        return false;
    }
    this->refresh();
    return true;
}

int DistributionSqlModel::rowCountDB(){
    QSqlQuery query;
    QString s = "SELECT COUNT(*) FROM distribution WHERE distribution.subjects_in_semmester_id = " + subjects_in_semmestre_id + ";";
    query.exec(s);
    query.next();
    return query.value(0).toInt();
}

int DistributionSqlModel::sum_field(QString field){
    QSqlQuery query;
    QString s = "SELECT SUM(distribution."+ field +") FROM distribution WHERE distribution.subjects_in_semmester_id = " + subjects_in_semmestre_id + ";";
    query.exec(s);
    query.next();
    return query.value(0).toInt();
}

//********************************************************************************
//  class Sins_to_distrib_preview_SqlModel
//********************************************************************************

Sins_to_distrib_preview_SqlModel::Sins_to_distrib_preview_SqlModel(QObject *parent) :
    QSqlQueryModel(parent)
{
    semester = " 1 ";
    speciality_id = '1';
}

Qt::ItemFlags Sins_to_distrib_preview_SqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    /*if (index.column() > 8 && index.column() < 24 )
    {
        flags |= Qt::ItemIsEditable;
    }*/
    return flags;
}

void Sins_to_distrib_preview_SqlModel::refresh()
{
    this->setQuery("SELECT subjects_in_semmester.id, subject_name, semmester FROM subjects_in_semmester, curriculum "
                   "WHERE (subjects_in_semmester.curriculum_id = curriculum.id AND "
                   "curriculum.speciality_id = " + speciality_id + ") AND ("
                   + semester + " );");
}

void Sins_to_distrib_preview_SqlModel::setspeciality_id(QString id)
{
    speciality_id = id;
}

void Sins_to_distrib_preview_SqlModel::setsemester_0()
{
    setsemester(0);
}
void Sins_to_distrib_preview_SqlModel::setsemester_1()
{
    setsemester(1);
}
void Sins_to_distrib_preview_SqlModel::setsemester_2()
{
    setsemester(2);
}

void Sins_to_distrib_preview_SqlModel::setsemester(int sem)
{
    if (sem == 1){
        semester = " curriculum.semmester = '1' "
                "OR curriculum.semmester = '3' "
                "OR curriculum.semmester = '5' "
                "OR curriculum.semmester = '7' "
                "OR curriculum.semmester = '9' "
                "OR curriculum.semmester = '11' ";
    } else if (sem == 2){
        semester = " curriculum.semmester = '2' "
                "OR curriculum.semmester = '4' "
                "OR curriculum.semmester = '6' "
                "OR curriculum.semmester = '8' "
                "OR curriculum.semmester = '10' "
                "OR curriculum.semmester = '12' ";
    } else if (sem == 0){
        semester = " 1 ";
    }
}
//********************************************************************************
//  class Sins_to_distrib_detail_SqlModel
//********************************************************************************

Sins_to_distrib_detail_SqlModel::Sins_to_distrib_detail_SqlModel(QObject *parent) :
    QSqlQueryModel(parent)
{
    subjects_in_semmestre_id = "1";
}

Qt::ItemFlags Sins_to_distrib_detail_SqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    /*if (index.column() > 8 && index.column() < 24 )
    {
        flags |= Qt::ItemIsEditable;
    }*/
    return flags;
}

void Sins_to_distrib_detail_SqlModel::setsins(QString id)
{
    subjects_in_semmestre_id = id;
}
void Sins_to_distrib_detail_SqlModel::refresh()
{
    this->setQuery("SELECT subjects_in_semmester.id, curriculum.subject_name, curriculum.semmester, "
                   "speciality.special_name, "
                   "speciality.form_training_name, students.course, "
                   "students.num_group, students.num_undergroup, "
                   "students.quantity_course, subjects_in_semmester.lection_hr, "
                   "subjects_in_semmester.labs_hr, subjects_in_semmester.practice_hr,"
                   "individ_hr, kontr_rab_hr, consultation_hr, "
                   "offset_hr,  examen_hr, coursework_hr, diplomwork_hr, praktika_hr, gak_hr, "
                   "other1,  other2, other3, "
                   "subjects_in_semmester.lection_hr+subjects_in_semmester.labs_hr+subjects_in_semmester.practice_hr+"
                   "individ_hr+kontr_rab_hr+consultation_hr+"
                   "offset_hr+examen_hr+coursework_hr+diplomwork_hr+praktika_hr+gak_hr+"
                   "other1+other2+other3 AS sum "
                   "FROM subjects_in_semmester, curriculum, students, speciality "
                   "WHERE subjects_in_semmester.curriculum_id = curriculum.id AND "
                   "subjects_in_semmester.students_id = students.id AND "
                   "students.speciality_id = speciality.id AND "
                   "subjects_in_semmester.id = " + subjects_in_semmestre_id + ";");
}
