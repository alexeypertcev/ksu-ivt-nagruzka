#include "tab_reports.h"
//#include "workzip.cpp"


bool create_report(QStringList teachers_id_list, QString template_patch, QString report_patch, QString type_report){

    // тут запрос к БД на все данные, подсчет суммарных данных
    QSqlQuery query, query2;
    Tabledata temp_tabledata;
    QList<Tabledata> list_tabledata;
    QStringList temp;
    QList<QStringList> temp_list_of_stringlist;
    int temp_of_int1[24];
    int temp_of_int2[24];

    QString select_list_data = "SELECT curriculum.subject_name, "
            "speciality.faculty_name, "
            "speciality.special_name, "
            "speciality.form_training_name, "
            "students.course, "
            "students.num_group, "
            "students.num_undergroup, "
            "students.quantity_course, "
            "distribution.lection_hr, "
            "distribution.practice_hr, "
            "distribution.labs_hr, "
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
            "distribution.other3, "
            "distribution.lection_hr + "
            "distribution.practice_hr + "
            "distribution.labs_hr + "
            "distribution.individ_hr + "
            "distribution.kontr_rab_hr + "
            "distribution.consultation_hr + "
            "distribution.offset_hr + "
            "distribution.examen_hr + "
            "distribution.coursework_hr + "
            "distribution.diplomwork_hr + "
            "distribution.praktika_hr + "
            "distribution.gak_hr + "
            "distribution.other1 + "
            "distribution.other2 + "
            "distribution.other3 AS sum  "
            "FROM distribution , subjects_in_semmester , curriculum, students , speciality "
            "WHERE distribution.subjects_in_semmester_id = subjects_in_semmester.id AND "
            "subjects_in_semmester.curriculum_id = curriculum.id AND "
            "subjects_in_semmester.students_id = students.id AND "
            "students.speciality_id = speciality.id AND "
            "distribution.teachers_id = ";


    for (int i=0; i<teachers_id_list.length(); ++i){

        // temp_tabledata.header_sheet
        query.exec("SELECT teachers.f, teachers.i, teachers.o, teachers.status_name "
                   "FROM teachers WHERE teachers.id = " + teachers_id_list.at(i));
        query.next();
        temp.clear();
        temp << query.value(0).toString();
        temp << query.value(1).toString();
        temp << query.value(2).toString();
        temp << query.value(3).toString();
        temp << "  Кафедра Факультет";
        temp << "  Объем";
        temp_tabledata.set_header_sheet(temp);

        // temp_tabledata.list_one

        query2.exec(select_list_data + teachers_id_list.at(i) +
                    " AND ( "
                    " curriculum.semmester = '1' "
                    "OR curriculum.semmester = '3' "
                    "OR curriculum.semmester = '5' "
                    "OR curriculum.semmester = '7' "
                    "OR curriculum.semmester = '9' "
                    "OR curriculum.semmester = '11' "
                    " )");

        temp_list_of_stringlist.clear();
        for(int j=0; j<24; ++j){
            temp_of_int1[j] =  0;
        }

        while (query2.next()){
            temp.clear();
            for(int j=0; j<24; ++j){
                if (query2.value(j).toInt() == 0){
                    temp << "";
                } else {
                    temp << query2.value(j).toString();
                }
//                query2.value(j).toInt()
                temp_of_int1[j] += query2.value(j).toInt();


            }
            temp_list_of_stringlist << temp;
        }
        temp_tabledata.set_list_one(temp_list_of_stringlist);
        temp.clear();
        for(int j=0; j<24; ++j){
            QString s="";
            if (temp_of_int1[j] != 0){
                s.setNum(temp_of_int1[j]);
            }
            temp << s;
        }
        temp_tabledata.set_list_one_sum(temp);


        // temp_tabledata.list_two
        query2.exec(select_list_data + teachers_id_list.at(i) +
                    " AND ( "
                    " curriculum.semmester = '2' "
                    "OR curriculum.semmester = '4' "
                    "OR curriculum.semmester = '6' "
                    "OR curriculum.semmester = '8' "
                    "OR curriculum.semmester = '10' "
                    "OR curriculum.semmester = '12' "
                    " )");

        temp_list_of_stringlist.clear();
        for(int j=0; j<24; ++j){
            temp_of_int2[j] =  0;
        }
        while (query2.next()){
            temp.clear();
            for(int j=0; j<24; ++j){
                if (query2.value(j).toInt() == 0){
                    temp << "";
                } else {
                    temp << query2.value(j).toString();
                }
                temp_of_int2[j] += query2.value(j).toInt();
            }
            temp_list_of_stringlist << temp;
        }
        temp_tabledata.set_list_two(temp_list_of_stringlist);
        temp.clear();
        for(int j=0; j<24; ++j){
            QString s = "";
            if (temp_of_int2[j] != 0){
                s.setNum(temp_of_int2[j]);
            }
            temp << s;
        }
        temp_tabledata.set_list_two_sum(temp);

        //   set  temp_tabledata.set_list_all_sum
        temp.clear();
        for(int j=0; j<24; ++j){
            QString s = "";
            if (temp_of_int1[j] + temp_of_int2[j] != 0){
                s.setNum(temp_of_int1[j] + temp_of_int2[j]);
            }
            temp << s;
        }

        temp_tabledata.set_list_all_sum(temp);

        list_tabledata << temp_tabledata;
    }

    if(type_report == "xlsx"){
        return create_report_xlsx(list_tabledata,template_patch, report_patch);
    } else if (type_report == "ods"){
        return create_report_ods(list_tabledata,template_patch, report_patch);
    } else {
        return false;
    }
    return true;
}

bool create_report_ods(QList<Tabledata> list_tabledata, QString template_patch, QString report_patch)
{
/*  Tabledata temp_tabledata;

    CardOdsWriter cardOdsWriter;
    // пакует - распаковывает нормально

    cardOdsWriter.open(template_patch);

    for (int i=0; i<list_tabledata.length(); ++i){
        temp_tabledata = list_tabledata.at(i);
        cardOdsWriter.writeSheet(temp_tabledata, i);
    }

    cardOdsWriter.save(report_patch);
*/
    return false;
}

bool create_report_xlsx(QList<Tabledata> list_tabledata, QString template_patch, QString report_patch)
{

    return true;
}



reports_creater::reports_creater()
{
}


