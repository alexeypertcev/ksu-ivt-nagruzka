#include "tab_reports.h"
//#include "workzip.cpp"


bool Reports::create_report_teacherscard(QStringList teachers_id_list, QString template_patch, QString report_patch, QString type_report, bool split_kard){
    //qDebug() << "split_card: " << split_kard;
    // тут запрос к БД на все данные, подсчет суммарных данных
    QSqlQuery query, query2, query3, query4;
    Tabledata temp_tabledata;
    Tabledata temp_tabledata1;
    Tabledata temp_tabledata2;
    QList<Tabledata> list_tabledata;
    QStringList temp;
    QStringList temp_header;
    QList<QStringList> temp_list_of_stringlist;
    int temp_of_int1[24];

    int temp_of_int_sins[16];
    int temp_of_int_dist[16];
    int temp_of_int_vacansion[16];
    int temp_of_int_vacansion_sum[16];
    bool flag;

    double boundary_amount = 1.02;

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

    QString order_by = " ORDER BY speciality.faculty_name, speciality.special_name, speciality.form_training_name, curriculum.semmester, curriculum.subject_name";

    QString select_sins_hours = "SELECT "
                            "subjects_in_semmester.id, "
                            "subjects_in_semmester.lection_hr, "
                            "subjects_in_semmester.practice_hr, "
                            "subjects_in_semmester.labs_hr, "
                            "subjects_in_semmester.individ_hr, "
                            "subjects_in_semmester.kontr_rab_hr, "
                            "subjects_in_semmester.consultation_hr, "
                            "subjects_in_semmester.offset_hr, "
                            "subjects_in_semmester.examen_hr, "
                            "subjects_in_semmester.coursework_hr, "
                            "subjects_in_semmester.diplomwork_hr, "
                            "subjects_in_semmester.praktika_hr, "
                            "subjects_in_semmester.gak_hr, "
                            "subjects_in_semmester.other1, "
                            "subjects_in_semmester.other2, "
                            "subjects_in_semmester.other3, "
                            "subjects_in_semmester.lection_hr + "
                            "subjects_in_semmester.practice_hr + "
                            "subjects_in_semmester.labs_hr + "
                            "subjects_in_semmester.individ_hr + "
                            "subjects_in_semmester.kontr_rab_hr + "
                            "subjects_in_semmester.consultation_hr + "
                            "subjects_in_semmester.offset_hr + "
                            "subjects_in_semmester.examen_hr + "
                            "subjects_in_semmester.coursework_hr + "
                            "subjects_in_semmester.diplomwork_hr + "
                            "subjects_in_semmester.praktika_hr + "
                            "subjects_in_semmester.gak_hr + "
                            "subjects_in_semmester.other1 + "
                            "subjects_in_semmester.other2 + "
                            "subjects_in_semmester.other3 AS sum  "
                            "FROM subjects_in_semmester, curriculum, students, speciality "
                            "WHERE subjects_in_semmester.curriculum_id = curriculum.id AND "
                            "subjects_in_semmester.students_id = students.id AND "
                            "students.speciality_id = speciality.id ";

    QString select_dist_hours = "SELECT "
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
                                "FROM distribution , subjects_in_semmester "
                                "WHERE distribution.subjects_in_semmester_id = subjects_in_semmester.id ";

    QString select_sins_names = "SELECT "
                                "curriculum.subject_name, "
                                "speciality.faculty_name, "
                                "speciality.special_name, "
                                "speciality.form_training_name, "
                                "students.course, "
                                "students.num_group, "
                                "students.num_undergroup, "
                                "students.quantity_course "
                                "FROM subjects_in_semmester , curriculum, students , speciality "
                                "WHERE "
                                "subjects_in_semmester.curriculum_id = curriculum.id AND "
                                "subjects_in_semmester.students_id = students.id AND "
                                "students.speciality_id = speciality.id ";

    QString current_status_name;
    int current_status_hours;
    int current_all_hours;
    for (int i=0; i<teachers_id_list.length(); ++i){

        if (teachers_id_list.at(i) != "0") {

            // temp_tabledata.header_sheet
            query.exec("SELECT teachers.f, teachers.i, teachers.o, teachers.status_name "
                       "FROM teachers WHERE teachers.id = " + teachers_id_list.at(i));
            query.next();
            temp_header.clear();
            temp_header << query.value(0).toString();
            temp_header << query.value(1).toString();
            temp_header << query.value(2).toString();
            temp_header << query.value(3).toString();
            current_status_name = query.value(3).toString();

            temp_tabledata.set_name_table_fam(query.value(0).toString());

            query.exec("SELECT name, value FROM other_data;");
            while(query.next()){
                if (query.value(0).toString() == "academic_year"){
                    temp_header <<  query.value(1).toString();
                } else if (query.value(0).toString() == "name_kafedry_faculty"){
                    temp_header <<  query.value(1).toString();
                } else if (query.value(0).toString() == "business_base_of_training"){
                    temp_header <<  query.value(1).toString();
                } else if (query.value(0).toString() == "vice_rector_on_education_work"){
                    temp_header <<  query.value(1).toString();
                }
            }
            query.exec("SELECT status.hours "
                       "FROM status WHERE name = '" + current_status_name +"';");
            query.next();
            current_status_hours = query.value(0).toInt();

            // temp_tabledata.list_two  temp_tabledata.list_one
            current_all_hours = 0;
            for (int z=0; z<2; ++z){
                query2.exec(select_list_data + teachers_id_list.at(i) +
                            " AND ( "
                            " curriculum.semmester % 2 = " + QString::number(z) +
                            " ) " + order_by);

                temp_list_of_stringlist.clear();
                for(int j=0; j<24; ++j){
                    temp_of_int1[j] =  0;
                }

                while (query2.next()){
                    temp.clear();
                    for(int j=0; j<24; ++j){
                        if (j == 12){
                            temp << "";
                        }
                        temp << query2.value(j).toString();
                        temp_of_int1[j] += query2.value(j).toInt();
                    }
                    temp << "";
                    temp_list_of_stringlist << temp;
                }

                temp.clear();
                for(int j=0; j<24; ++j){
                    if (j == 12){
                        temp << "";
                    }
                    QString s="";
                    if ( j>7 && temp_of_int1[j] != 0){
                        s.setNum(temp_of_int1[j]);
                    }
                    temp << s;
                }
                temp << "";
                current_all_hours += temp_of_int1[23];

                if(z == 0){
                    temp_tabledata.set_list_two(temp_list_of_stringlist);
                } else {
                    temp_tabledata.set_list_one(temp_list_of_stringlist);
                }
            }

            // объем учебной нагрузки
            temp_header << QString::number((double)current_all_hours / (double)current_status_hours, 'f', 2);

            temp_tabledata.set_header_sheet(temp_header);
        } else {
            //teachers_id_list.at(i) = "0"
//            qDebug() << "Вакансии подсчет";
            temp_tabledata.set_name_table_fam("Вакансии");

            query.exec("DELETE FROM distribution WHERE distribution.teachers_id = '0';");

            // temp_tabledata.header_sheet
            temp.clear();
            temp << "Вакансии";
            temp << "";
            temp << "";
            temp << "";

            query.exec("SELECT name, value FROM other_data;");
            while(query.next()){
                if (query.value(0).toString() == "academic_year"){
                    temp <<  query.value(1).toString();
                } else if (query.value(0).toString() == "name_kafedry_faculty"){
                    temp <<  query.value(1).toString();
                } else if (query.value(0).toString() == "business_base_of_training"){
                    temp <<  query.value(1).toString();
                } else if (query.value(0).toString() == "vice_rector_on_education_work"){
                    temp <<  query.value(1).toString();
                }
            }

            temp << "";
            temp_tabledata.set_header_sheet(temp);


            // temp_tabledata.list_one
            for (int sem=0; sem<2; ++sem){
                query2.exec(select_sins_hours +
                            "AND curriculum.semmester % 2 = " + QString::number(sem) + order_by);

                temp_list_of_stringlist.clear();
                for(int j=0; j<16; ++j){
                    temp_of_int_vacansion_sum[j] = 0;
                }
                while (query2.next()){
                    temp.clear();

                    for(int j=0; j<16; ++j){
                        temp_of_int_sins[j] = query2.value(j+1).toInt();
                    }

                    query3.exec(select_dist_hours +
                                " AND subjects_in_semmester.id = '" + query2.value(0).toString() + "'; ");

                    temp.clear();
                    // в temp_of_int_dist заносим все распределенные часы по предмету
                    for(int j=0; j<16; ++j){
                        temp_of_int_dist[j] = 0;
                    }
                    while (query3.next()){
                        for(int j=0; j<16; ++j){
                            temp_of_int_dist[j] += query3.value(j).toInt();
                        }
                    }

                    flag = false;
                    for(int j=0; j<16; ++j){
                        temp_of_int_vacansion[j] = temp_of_int_sins[j] - temp_of_int_dist[j];
                        if (temp_of_int_vacansion[j] != 0){
                            flag = true;
                        }
                    }

                    if (flag){
                        // мини запрос
                        query4.exec(select_sins_names +
                                    " AND subjects_in_semmester.id = '" + query2.value(0).toString() + "'; ");
                        query4.next();

                        for(int j=0; j<24; ++j){
                            if (j == 12){
                                temp << "";
                            }
                            if (j < 8){
                                temp << query4.value(j).toString();
                            } else {
                                temp_of_int_vacansion_sum[j-8] += temp_of_int_vacansion[j-8];
                                if (temp_of_int_vacansion[j-8] == 0){
                                    temp << "";
                                } else {
                                    temp << QString::number(temp_of_int_vacansion[j-8]);
                                }
                            }
                        }
                        temp << "";
                        temp_list_of_stringlist << temp;
                    }
                }

                temp.clear();
                for(int j=0; j<24; ++j){
                    if (j == 12){
                        temp << "";
                    }
                    QString s="";
                    if ( j>7 && temp_of_int_vacansion_sum[j-8] != 0){
                        s.setNum(temp_of_int_vacansion_sum[j-8]);
                    }
                    temp << s;
                }
                temp << "";

                if(sem == 0){
                    temp_tabledata.set_list_one(temp_list_of_stringlist);
                } else {
                    temp_tabledata.set_list_two(temp_list_of_stringlist);
                }
            }
        }

        if (split_kard)
        if (temp_tabledata.get_header_obiem().toDouble() > boundary_amount){
            // проверка итогового объема, разбиение карточки на сплиты

        }

        list_tabledata << temp_tabledata;
    }

    //------------------------------------------------------------
    // поиск и замена одинаковых фамилий/названий листов

    QList<int> equal;
    QList<int> equal1;
    int buf;
    for (int i = 0; i<list_tabledata.length(); ++i){
        equal.clear();
        for (int j = i+1; j<list_tabledata.length(); ++j){
            temp_tabledata1 = list_tabledata.at(i);
            temp_tabledata2 = list_tabledata.at(j);
            if (temp_tabledata1.get_name_table_fam() == temp_tabledata2.get_name_table_fam()){
                if (temp_tabledata1.get_name_table_all() == temp_tabledata2.get_name_table_all()){
                    equal << j;
                }
            }
        }
        if (!equal.isEmpty()){
            equal << i;
            for (int k = 0; k<equal.length(); ++k){
                temp_tabledata  = list_tabledata.at(equal.at(k));
                list_tabledata[equal.at(k)].set_name_table_fam(temp_tabledata.get_header_Family_I_O());
            }
            for (int i1=0; i1<equal.length(); ++i1){
                equal1.clear();
                for (int j1=i1+1; j1<equal.length(); ++j1){
                    temp_tabledata1 = list_tabledata.at(equal.at(i1));
                    temp_tabledata2 = list_tabledata.at(equal.at(j1));
                    if (temp_tabledata1.get_name_table_fam() == temp_tabledata2.get_name_table_fam()){
                        equal1 << equal.at(j1);
                    }
                }
                if (!equal1.isEmpty()){
                    equal1 << equal.at(i1);
                    for (int i3 = 0; i3< equal1.length(); ++i3){
                        for (int j3 = i3+1; j3<equal1.length(); ++j3){
                            if (equal1.at(i3) > equal1.at(j3)){
                                buf = equal1.at(i3);
                                equal1[i3] = equal1.at(j3);
                                equal1[j3] = buf;
                            }
                        }
                    }
                    for (int k1 = 0; k1 < equal1.length(); ++k1){
                        list_tabledata[equal1.at(k1)].set_name_table_fam( list_tabledata[equal1.at(k1)].get_name_table_fam() + " 0" + QString::number(k1+1));
                    }
                }
            }
        }
    }
    //------------------------------------------------------------

    if(type_report == "xlsx"){
        return write_report_teacherscard_xlsx(list_tabledata,template_patch, report_patch);
    } else if (type_report == "ods"){
//        return create_report_ods(list_tabledata,template_patch, report_patch);
    } else {
        return false;
    }
    return true;
}

bool Reports::write_report_teacherscard_xlsx(QList<Tabledata> list_tabledata, QString template_path, QString report_path)
{
    Tabledata temp_tabledata;
    QFile::remove(report_path);

    TDocXLSX doc;
    TWorkBook& book = doc.m_workbook;

   // ---------------------------

    for (int i_sheet=0; i_sheet<list_tabledata.length(); ++i_sheet){
        temp_tabledata = list_tabledata.at(i_sheet);
        // проверить длину списков
        //
        // -----------------------

        TSpreadSheet sheet1 = book.m_spreadsheets.insert();

        sheet1.set_column_width(1,1,"45");
        sheet1.set_column_width(2,2,"6");
        sheet1.set_column_width(3,3,"11.7109375");
        sheet1.set_column_width(4,24,"5");
        sheet1.set_column_width(25,25,"7");
        sheet1.set_column_width(26,26,"5");


        TFont font_tnr_8_normal = book.m_stylesheet.m_fonts.insert( "Times New Roman", 8, EFF_NONE );
        TFont font_tnr_8_bold = book.m_stylesheet.m_fonts.insert( "Times New Roman", 8, EFF_BOLD );
        TFont font_tnr_10_normal = book.m_stylesheet.m_fonts.insert( "Times New Roman", 10, EFF_NONE );
        TFont font_tnr_12_normal = book.m_stylesheet.m_fonts.insert( "Times New Roman", 12, EFF_NONE );
        TFont font_arial_10_normal = book.m_stylesheet.m_fonts.insert( "Arial Cyr", 10, EFF_NONE );

                                                                          /* left right top bottom*/
        TBorder border_all_medium = book.m_stylesheet.m_borders.insert( TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine(), false, false, false );
        TBorder border_top_but_double = book.m_stylesheet.m_borders.insert( TBorderLine( EBORDERSTYLE_THIN ), TBorderLine( EBORDERSTYLE_THIN ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine(), false, false, false );
        TBorder border_top_but_right_double = book.m_stylesheet.m_borders.insert( TBorderLine( EBORDERSTYLE_THIN ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine(), false, false, false );
        TBorder border_all_thin = book.m_stylesheet.m_borders.insert( TBorderLine( EBORDERSTYLE_THIN ), TBorderLine( EBORDERSTYLE_THIN ), TBorderLine( EBORDERSTYLE_THIN ), TBorderLine( EBORDERSTYLE_THIN ), TBorderLine(), false, false, false );
        TBorder border_all_thin_right_double = book.m_stylesheet.m_borders.insert( TBorderLine( EBORDERSTYLE_THIN ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine( EBORDERSTYLE_THIN ), TBorderLine( EBORDERSTYLE_THIN ), TBorderLine(), false, false, false );

        TBorder border_left_top_bottom_double = book.m_stylesheet.m_borders.insert( TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine(), false, false, false );
        TBorder border_right_top_bottom_double = book.m_stylesheet.m_borders.insert( TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine(), false, false, false );
        TBorder border_top_double = book.m_stylesheet.m_borders.insert( TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine(), false, false, false );
        TBorder border_buttom_double = book.m_stylesheet.m_borders.insert( TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine(), false, false, false );
        TBorder border_top_bottom_double = book.m_stylesheet.m_borders.insert( TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine(), false, false, false );

        TCellXF cellformat_header0 = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_normal, TAlignment( EHORIZONTAL_LEFT, EVERTICAL_CENTER, false, false, 0, 0 ), TBorder(), TFill() );
        TCellXF cellformat_header1 = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_bold, TAlignment( EHORIZONTAL_LEFT, EVERTICAL_CENTER, false, false, 0, 0 ), TBorder(), TFill() );
        TCellXF cellformat_header2 = book.m_stylesheet.m_cellxfs.insert( font_tnr_10_normal, TAlignment( EHORIZONTAL_RIGHT, EVERTICAL_CENTER, false, false, 0, 0 ), TBorder(), TFill() );
        TCellXF cellformat_header3 = book.m_stylesheet.m_cellxfs.insert( font_tnr_12_normal, TAlignment( EHORIZONTAL_RIGHT, EVERTICAL_CENTER, false, false, 0, 0 ), TBorder(), TFill() );
        TCellXF cellformat_header4 = book.m_stylesheet.m_cellxfs.insert( font_tnr_10_normal, TAlignment( EHORIZONTAL_LEFT, EVERTICAL_CENTER, false, false, 0, 0 ), TBorder(), TFill() );

        TCellXF cellformat_header0_b_t = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_normal, TAlignment( EHORIZONTAL_LEFT, EVERTICAL_CENTER, false, false, 0, 0 ), border_top_double, TFill() );
        TCellXF cellformat_header0_wrap_b_t = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_normal, TAlignment( EHORIZONTAL_LEFT, EVERTICAL_CENTER, true, false, 0, 0 ), border_top_double, TFill() );
        TCellXF cellformat_header5_b_ltb = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 0, 0 ), border_left_top_bottom_double, TFill() );
        TCellXF cellformat_header6_b_tb = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 90, 0 ), border_top_bottom_double, TFill() );

        TCellXF cellformat_header6_b_b = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 90, 0 ), border_buttom_double, TFill() );
        TCellXF cellformat_header6_wrap_b_b = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, true, false, 90, 0 ), border_buttom_double, TFill() );
        TCellXF cellformat_header6_b_rtb = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 90, 0 ), border_right_top_bottom_double, TFill() );

        TCellXF cf_sum_left = book.m_stylesheet.m_cellxfs.insert( font_tnr_10_normal, TAlignment( EHORIZONTAL_LEFT, EVERTICAL_CENTER, false, false, 0, 0 ), border_top_but_double, TFill() );
        TCellXF cf_sum = book.m_stylesheet.m_cellxfs.insert( font_tnr_10_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 0, 0 ), border_top_but_double, TFill() );
        TCellXF cf_sum_right = book.m_stylesheet.m_cellxfs.insert( font_tnr_10_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 0, 0 ), border_top_but_right_double, TFill() );

        TCellXF cf_body_left = book.m_stylesheet.m_cellxfs.insert( font_tnr_10_normal, TAlignment( EHORIZONTAL_LEFT, EVERTICAL_CENTER, false, false, 0, 0 ), border_all_thin, TFill() );
        TCellXF cf_body = book.m_stylesheet.m_cellxfs.insert( font_tnr_10_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 0, 0 ), border_all_thin, TFill() );
        TCellXF cf_body_right = book.m_stylesheet.m_cellxfs.insert( font_tnr_10_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 0, 0 ), border_all_thin_right_double, TFill() );
        TCellXF cf_arial_10_center = book.m_stylesheet.m_cellxfs.insert( font_arial_10_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 0, 0 ), TBorder(), TFill() );
        TCellXF cf_arial_10_left = book.m_stylesheet.m_cellxfs.insert( font_arial_10_normal, TAlignment( EHORIZONTAL_LEFT, EVERTICAL_CENTER, false, false, 0, 0 ), TBorder(), TFill() );

            /*[row][collumn]*/
        sheet1[ 0 ][ 0 ] = "Министерство образования и науки Российской Федерации";
        sheet1[ 0 ][ 0 ] = cellformat_header0;
        sheet1[ 1 ][ 0 ] = "Федеральное государственное бюджетное образовательное учреждение";
        sheet1[ 1 ][ 0 ] = cellformat_header0;
        sheet1[ 2 ][ 0 ] = "высшего профессионального образования";
        sheet1[ 2 ][ 0 ] = cellformat_header0;
        sheet1[ 3 ][ 0 ] = "«Курский государственный университет»";
        sheet1[ 3 ][ 0 ] = cellformat_header1;

        sheet1[ 0 ][ 24 ] = "УТВЕРЖДАЮ:";
        sheet1[ 0 ][ 24 ] = cellformat_header2;
        sheet1[ 1 ][ 24 ] = "Проректор по учебной работе";
        sheet1[ 1 ][ 24 ] = cellformat_header2;
        sheet1[ 3 ][ 24 ] = "____________________/" + temp_tabledata.get_header_vice_rector_on_education_work().toStdString();
        sheet1[ 3 ][ 24 ] = cellformat_header2;
        sheet1[ 4 ][ 16 ] = "КАРТОЧКА УЧЕБНЫХ ПОРУЧЕНИЙ НА " + temp_tabledata.get_header_academic_year().toStdString() + " УЧЕБНЫЙ ГОД (" + temp_tabledata.get_header_business_base_of_training().toStdString() + ")";
        sheet1[ 4 ][ 16 ] = cellformat_header3;

        sheet1[ 5 ][ 0 ] = "Фамилия, имя, отчество преподавателя:  ";
        sheet1[ 5 ][ 0 ] = cellformat_header2;
        sheet1[ 6 ][ 0 ] = "Ученая степень, звание должность:  ";
        sheet1[ 6 ][ 0 ] = cellformat_header2;
        sheet1[ 7 ][ 0 ] = "Кафедра, факультет:  ";
        sheet1[ 7 ][ 0 ] = cellformat_header2;
        sheet1[ 8 ][ 5 ] = "Объем и вид нагрузки (штатный, совместитель, почасовая оплата):  ";
        sheet1[ 8 ][ 5 ] = cellformat_header2;

        sheet1[ 5 ][ 1 ] = temp_tabledata.get_header_FIO().toStdString();
        sheet1[ 5 ][ 1 ] = cellformat_header4;
        sheet1[ 6 ][ 1 ] = temp_tabledata.get_header_degre_and_status().toStdString();
        sheet1[ 6 ][ 1 ] = cellformat_header4;
        sheet1[ 7 ][ 1 ] = temp_tabledata.get_header_name_kafedry_faculty().toStdString();
        sheet1[ 7 ][ 1 ] = cellformat_header4;
        sheet1[ 8 ][ 6 ] = temp_tabledata.get_header_obiem().toStdString();
        sheet1[ 8 ][ 6 ] = cellformat_header4;
        sheet1[ 10 ][ 0 ] = "Наименование учебной дисциплины или учебных поручений";
        sheet1[ 10 ][ 0 ] = cellformat_header5_b_ltb;
        sheet1[ 11 ][ 0 ] = " ";
        sheet1[ 11 ][ 0 ] = cellformat_header5_b_ltb;

        sheet1[ 10 ][ 1 ] = "Факультет";
        sheet1[ 10 ][ 1 ] = cellformat_header6_b_tb;
        sheet1[ 11 ][ 1 ] = " ";
        sheet1[ 11 ][ 1 ] = cellformat_header6_b_tb;
        sheet1[ 10 ][ 2 ] = "Специальность";
        sheet1[ 10 ][ 2 ] = cellformat_header6_b_tb;
        sheet1[ 11 ][ 2 ] = " ";
        sheet1[ 11 ][ 2 ] = cellformat_header6_b_tb;
        sheet1[ 10 ][ 3 ] = "Форма обучения";
        sheet1[ 10 ][ 3 ] = cellformat_header6_b_tb;
        sheet1[ 11 ][ 3 ] = " ";
        sheet1[ 11 ][ 3 ] = cellformat_header6_b_tb;
        sheet1[ 10 ][ 4 ] = "Курс";
        sheet1[ 10 ][ 4 ] = cellformat_header6_b_tb;
        sheet1[ 11 ][ 4 ] = " ";
        sheet1[ 11 ][ 4 ] = cellformat_header6_b_tb;
        sheet1[ 10 ][ 5 ] = "Количество групп";
        sheet1[ 10 ][ 5 ] = cellformat_header6_b_tb;
        sheet1[ 11 ][ 5 ] = " ";
        sheet1[ 11 ][ 5 ] = cellformat_header6_b_tb;
        sheet1[ 10 ][ 6 ] = "Количество подгрупп";
        sheet1[ 10 ][ 6 ] = cellformat_header6_b_tb;
        sheet1[ 11 ][ 6 ] = " ";
        sheet1[ 11 ][ 6 ] = cellformat_header6_b_tb;
        sheet1[ 10 ][ 7 ] = "Количество студентов";
        sheet1[ 10 ][ 7 ] = cellformat_header6_b_tb;
        sheet1[ 11 ][ 7 ] = " ";
        sheet1[ 11 ][ 7 ] = cellformat_header6_b_tb;

        sheet1[ 10 ][ 8 ] = "По учебному плану";
        sheet1[ 10 ][ 8 ] = cellformat_header0_b_t;
        sheet1[ 10 ][ 9 ] = " ";
        sheet1[ 10 ][ 9 ] = cellformat_header0_b_t;
        sheet1[ 10 ][ 10 ] = " ";
        sheet1[ 10 ][ 10 ] = cellformat_header0_b_t;

        sheet1[ 11 ][ 8 ] = "Лекции";
        sheet1[ 11 ][ 8 ] = cellformat_header6_b_b;
        sheet1[ 11 ][ 9 ] = "Семинары и практич. Работы";
        sheet1[ 11 ][ 9 ] = cellformat_header6_wrap_b_b;
        sheet1[ 11 ][ 10 ] = "Лабораторные работы";
        sheet1[ 11 ][ 10 ] = cellformat_header6_wrap_b_b;

        sheet1[ 10 ][ 11 ] = "Рук-во сам. Раб";
        sheet1[ 10 ][ 11 ] = cellformat_header0_wrap_b_t;
        sheet1[ 10 ][ 12 ] = " ";
        sheet1[ 10 ][ 12 ] = cellformat_header0_wrap_b_t;

        sheet1[ 11 ][ 11 ] = "индивидуальная";
        sheet1[ 11 ][ 11 ] = cellformat_header6_b_b;
        sheet1[ 11 ][ 12 ] = "аудиторная";
        sheet1[ 11 ][ 12 ] = cellformat_header6_b_b;

        sheet1[ 10 ][ 13 ] = "Контрольные работы";
        sheet1[ 10 ][ 13 ] = cellformat_header6_b_tb;
        sheet1[ 11 ][ 13 ] = " ";
        sheet1[ 11 ][ 13 ] = cellformat_header6_b_tb;
        sheet1[ 10 ][ 14 ] = "Консультации";
        sheet1[ 10 ][ 14 ] = cellformat_header6_b_tb;
        sheet1[ 11 ][ 14 ] = " ";
        sheet1[ 11 ][ 14 ] = cellformat_header6_b_tb;
        sheet1[ 10 ][ 15 ] = "Зачеты";
        sheet1[ 10 ][ 15 ] = cellformat_header6_b_tb;
        sheet1[ 11 ][ 15 ] = " ";
        sheet1[ 11 ][ 15 ] = cellformat_header6_b_tb;
        sheet1[ 10 ][ 16 ] = "Экзамены";
        sheet1[ 10 ][ 16 ] = cellformat_header6_b_tb;
        sheet1[ 11 ][ 16 ] = " ";
        sheet1[ 11 ][ 16 ] = cellformat_header6_b_tb;
        sheet1[ 10 ][ 17 ] = "Курсовые работы";
        sheet1[ 10 ][ 17 ] = cellformat_header6_b_tb;
        sheet1[ 11 ][ 17 ] = " ";
        sheet1[ 11 ][ 17 ] = cellformat_header6_b_tb;
        sheet1[ 10 ][ 18 ] = "Дипломные работы";
        sheet1[ 10 ][ 18 ] = cellformat_header6_b_tb;
        sheet1[ 11 ][ 18 ] = " ";
        sheet1[ 11 ][ 18 ] = cellformat_header6_b_tb;
        sheet1[ 10 ][ 19 ] = "Практика";
        sheet1[ 10 ][ 19 ] = cellformat_header6_b_tb;
        sheet1[ 11 ][ 19 ] = " ";
        sheet1[ 11 ][ 19 ] = cellformat_header6_b_tb;
        sheet1[ 10 ][ 20 ] = "ГАК";
        sheet1[ 10 ][ 20 ] = cellformat_header6_b_tb;
        sheet1[ 11 ][ 20 ] = " ";
        sheet1[ 11 ][ 20 ] = cellformat_header6_b_tb;

        sheet1[ 10 ][ 21 ] = "Прочие виды работ";
        sheet1[ 10 ][ 21 ] = cellformat_header0_b_t;
        sheet1[ 10 ][ 22 ] = " ";
        sheet1[ 10 ][ 22 ] = cellformat_header0_b_t;
        sheet1[ 10 ][ 23 ] = " ";
        sheet1[ 10 ][ 23 ] = cellformat_header0_b_t;
        sheet1[ 11 ][ 21 ] = " ";
        sheet1[ 11 ][ 21 ] = cellformat_header6_b_b;
        sheet1[ 11 ][ 22 ] = " ";
        sheet1[ 11 ][ 22 ] = cellformat_header6_b_b;
        sheet1[ 11 ][ 23 ] = " ";
        sheet1[ 11 ][ 23 ] = cellformat_header6_b_b;

        sheet1[ 10 ][ 24 ] = "Итого";
        sheet1[ 10 ][ 24 ] = cellformat_header6_b_tb;
        sheet1[ 11 ][ 24 ] = " ";
        sheet1[ 11 ][ 24 ] = cellformat_header6_b_tb;
        sheet1[ 10 ][ 25 ] = "Примечания";
        sheet1[ 10 ][ 25 ] = cellformat_header6_b_rtb;
        sheet1[ 11 ][ 25 ] = " ";
        sheet1[ 11 ][ 25 ] = cellformat_header6_b_rtb;

        sheet1.set_row_height(10, "23");
        sheet1.set_row_height(11, "64");

        sheet1.set_merge("A11:A12");
        sheet1.set_merge("B11:B12");
        sheet1.set_merge("C11:C12");
        sheet1.set_merge("D11:D12");
        sheet1.set_merge("E11:E12");
        sheet1.set_merge("F11:F12");
        sheet1.set_merge("G11:G12");
        sheet1.set_merge("H11:H12");
        sheet1.set_merge("I11:K11");
        sheet1.set_merge("L11:M11");
        sheet1.set_merge("N11:N12");
        sheet1.set_merge("O11:O12");
        sheet1.set_merge("P11:P12");
        sheet1.set_merge("Q11:Q12");
        sheet1.set_merge("R11:R12");
        sheet1.set_merge("S11:S12");
        sheet1.set_merge("T11:T12");
        sheet1.set_merge("U11:U12");
        sheet1.set_merge("V11:X11");
        sheet1.set_merge("Y11:Y12");
        sheet1.set_merge("Z11:Z12");

        int current_row = 12;
        int i, j, shift;
        QList<QStringList> temp_list_stringlist;
        QStringList temp_stringlist;

        temp_list_stringlist.clear();
        temp_stringlist.clear();

    // ------------- both semmester -------------
        for (int sem = 1; sem<=2; ++sem){
            temp_list_stringlist = temp_tabledata.get_list(sem);
            for (i = 0; i < temp_list_stringlist.length(); ++i){
                temp_stringlist = temp_list_stringlist.at(i);
                shift = 0;
                for (j = 0; j < temp_stringlist.length(); ++j){
                    if ((j > 3) && (j != 12) && (j < temp_stringlist.length()-1)) {
                        sheet1[current_row][j] = temp_stringlist.at(j).toInt();
                    } else {
                        sheet1[current_row][j] = temp_stringlist.at(j).toStdString();
                    }
                    if (j < 4){
                        sheet1[current_row][j] = cf_body_left;
                    } else if (j == temp_stringlist.length()-1){
                        sheet1[current_row][j] = cf_body_right;
                    } else {
                        sheet1[current_row][j] = cf_body;
                    }
                }
                ++current_row;
            }
            // --------------- промежуток
            for (j = 0; j < 26; ++j){
                sheet1[current_row][j] = "";
                if (j == temp_stringlist.length()-1){
                    sheet1[current_row][j] = cf_body_right;
                } else {
                    sheet1[current_row][j] = cf_body;
                }
            }
            // ---------
            ++current_row;

            temp_stringlist = temp_tabledata.get_list_sum(sem);

            shift = 0;
            for (j = 0; j < temp_stringlist.length(); ++j){
                if ((j > 7) && (j != 12) && (j < temp_stringlist.length()-1)){
                    sheet1[current_row][j] = temp_stringlist.at(j).toInt();
                } else {
                    sheet1[current_row][j] = temp_stringlist.at(j).toStdString();
                }
                if (j < 4){
                    sheet1[current_row][j] = cf_sum_left;
                } else if (j == temp_stringlist.length()-1){
                    sheet1[current_row][j] = cf_sum_right;
                } else {
                    sheet1[current_row][j] = cf_sum;
                }
            }
            sheet1[current_row][0] = QString("Итого за "+ QString::number(sem)+"е полугодие:").toStdString();

            ++current_row;
            // --------------- промежуток
            for (j = 0; j < 26; ++j){
                sheet1[current_row][j] = "";
                if (j == temp_stringlist.length()-1){
                    sheet1[current_row][j] = cf_body_right;
                } else {
                    sheet1[current_row][j] = cf_body;
                }
            }
            // ---------
            ++current_row;
            // --------------- промежуток
            for (j = 0; j < 26; ++j){
                sheet1[current_row][j] = "";
                if (j == temp_stringlist.length()-1){
                    sheet1[current_row][j] = cf_body_right;
                } else {
                    sheet1[current_row][j] = cf_body;
                }
            }
            // ---------
        }
    // ------------------------------------

        temp_stringlist = temp_tabledata.get_list_all_sum();
        shift = 0;
        for (j = 0; j < temp_stringlist.length(); ++j){
            if ((j > 7) && (j != 12) && (j < temp_stringlist.length()-1)){
                sheet1[current_row][j] = temp_stringlist.at(j).toInt();
            } else {
                sheet1[current_row][j] = temp_stringlist.at(j).toStdString();
            }
            if (j < 4){
                sheet1[current_row][j] = cf_sum_left;
            } else if (j == temp_stringlist.length()-1){
                sheet1[current_row][j] = cf_sum_right;
            } else {
                sheet1[current_row][j] = cf_sum;
            }
        }
        sheet1[ current_row ][0] = "Итого за год:";

        ++current_row;
        ++current_row;
        sheet1[current_row][0] = "Декан";
        sheet1[current_row][0] = cf_arial_10_center;
        sheet1[current_row][3] = "Зав. кафедрой";
        sheet1[current_row][3] = cf_arial_10_left;
        sheet1[current_row][15] = "Преподаватель";
        sheet1[current_row][15] = cf_arial_10_left;

        //book.insert( sheet1, names_sheets.at(i_sheet).toStdString() );
        book.insert( sheet1, temp_tabledata.get_name_table_all().toStdString() );

    }

    doc.save(report_path.toStdString());
    return true;
}

bool Reports::create_report_for_kafedry(QString report_path)
{
    // xlsx
    QFile::remove(report_path);

    QSqlQuery query;
    QStringList header_data;
    header_data.clear();

    query.exec("SELECT value FROM other_data WHERE name = 'name_kafedry_smail'");
    if (query.next()){
        header_data << query.value(0).toString();
    } else {
        header_data << " ";
        ERROR_REPORT("0x701")
    }

    query.exec("SELECT value FROM other_data WHERE name = 'academic_year'");
    if (query.next()){
        header_data << query.value(0).toString();
    } else {
        header_data << " ";
        ERROR_REPORT("0x702")
    }

    header_data << "№";
    header_data << "Название предмета";
    header_data << "Сем";
    header_data << "Спец";
    header_data << "Форм";
    header_data << "Курс";
    header_data << "Гр";
    header_data << "П/гр";
    header_data << "Студ";
    header_data << "Лек";
    header_data << "Лаб";
    header_data << "Пр";
    header_data << "Инд";
    header_data << "К. р";
    header_data << "Конс";
    header_data << "Зач";
    header_data << "Экз";
    header_data << "Курс раб";
    header_data << "Дипл";
    header_data << "Практ";
    header_data << "ГАК";
    header_data << "Пр-1";
    header_data << "Пр-2";
    header_data << "Пр-3";
    header_data << "Всего";

    TDocXLSX doc;
    TWorkBook& book = doc.m_workbook;
    TSpreadSheet sheet1 = book.m_spreadsheets.insert();

    sheet1.set_column_width(1,1,"4.71");
    sheet1.set_column_width(2,2,57);
    sheet1.set_column_width(3,3,"4.71");
    sheet1.set_column_width(4,4,12);
    sheet1.set_column_width(5,5,"5.43");
    sheet1.set_column_width(6,24,"4.71");
    sheet1.set_column_width(25,25,8);
    sheet1.set_merge("A1:Y1");
    sheet1.set_zoom("90");

    TFont font_calibri_14_bold = book.m_stylesheet.m_fonts.insert( "Calibri", 14, EFF_BOLD );
    TFont font_calibri_11_normal = book.m_stylesheet.m_fonts.insert( "Calibri", 11, EFF_NONE );

    TBorderLine borderline_thin   = TBorderLine( EBORDERSTYLE_THIN );
    TBorderLine borderline_double = TBorderLine( EBORDERSTYLE_DOUBLE );
    TBorderLine borderline_medium = TBorderLine( EBORDERSTYLE_MEDIUM );
    TBorderLine borderline_none   = TBorderLine( EBORDERSTYLE_NONE );

    /* left right top bottom*/
    TBorder border_all_thin  = book.m_stylesheet.m_borders.insert( borderline_thin, borderline_thin, borderline_thin, borderline_thin, TBorderLine(), false, false, false );
    TBorder border_top_medium_all_thin     = book.m_stylesheet.m_borders.insert( borderline_thin, borderline_thin, borderline_medium, borderline_thin,   TBorderLine(), false, false, false );
    TBorder border_top_rig_medium_all_thin = book.m_stylesheet.m_borders.insert( borderline_thin, borderline_medium, borderline_medium, borderline_thin, TBorderLine(), false, false, false );
    TBorder border_top_double_all_thin = book.m_stylesheet.m_borders.insert( borderline_thin, borderline_thin, borderline_double, borderline_thin,   TBorderLine(), false, false, false );
    TBorder border_thin_doub_doub_thin = book.m_stylesheet.m_borders.insert( borderline_thin, borderline_double, borderline_double, borderline_thin, TBorderLine(), false, false, false );
    TBorder border_thin_doub_thin_thin = book.m_stylesheet.m_borders.insert( borderline_thin, borderline_double, borderline_thin, borderline_thin,   TBorderLine(), false, false, false );
    TBorder border_all_thin_rmedium    = book.m_stylesheet.m_borders.insert( borderline_thin, borderline_medium, borderline_thin, borderline_thin,   TBorderLine(), false, false, false );
    TBorder border_top_double_all_thin_rmedium  = book.m_stylesheet.m_borders.insert( borderline_thin, borderline_medium, borderline_double, borderline_thin, TBorderLine(), false, false, false );
    TBorder border_top_medium_all_none          = book.m_stylesheet.m_borders.insert( borderline_none, borderline_none, borderline_medium, borderline_none,   TBorderLine(), false, false, false );

    TCellXF cf_title      = book.m_stylesheet.m_cellxfs.insert( font_calibri_14_bold,   TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 0, 0 ), TBorder(), TFill() );
    TCellXF cf_header     = book.m_stylesheet.m_cellxfs.insert( font_calibri_11_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 0, 0 ), border_top_medium_all_thin, TFill() );
    TCellXF cf_header_end = book.m_stylesheet.m_cellxfs.insert( font_calibri_11_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 0, 0 ), border_top_rig_medium_all_thin, TFill() );
    TCellXF cf_all_thin_center  = book.m_stylesheet.m_cellxfs.insert( font_calibri_11_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 0, 0 ), border_all_thin, TFill() );
    TCellXF cf_all_thin_left    = book.m_stylesheet.m_cellxfs.insert( font_calibri_11_normal, TAlignment( EHORIZONTAL_LEFT,   EVERTICAL_CENTER, false, false, 0, 0 ), border_all_thin, TFill() );
    TCellXF cf_doub_thin_center = book.m_stylesheet.m_cellxfs.insert( font_calibri_11_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 0, 0 ), border_top_double_all_thin, TFill() );
    TCellXF cf_doub_thin_left   = book.m_stylesheet.m_cellxfs.insert( font_calibri_11_normal, TAlignment( EHORIZONTAL_LEFT,   EVERTICAL_CENTER, false, false, 0, 0 ), border_top_double_all_thin, TFill() );
    TCellXF cf_all_thin_rdoub_center  = book.m_stylesheet.m_cellxfs.insert( font_calibri_11_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 0, 0 ), border_thin_doub_thin_thin, TFill() );
    TCellXF cf_all_thin_right_rmed    = book.m_stylesheet.m_cellxfs.insert( font_calibri_11_normal, TAlignment( EHORIZONTAL_RIGHT,  EVERTICAL_CENTER, false, false, 0, 0 ), border_all_thin_rmedium,    TFill() );
    TCellXF cf_doub_thin_rdoub_center = book.m_stylesheet.m_cellxfs.insert( font_calibri_11_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 0, 0 ), border_thin_doub_doub_thin, TFill() );
    TCellXF cf_doub_thin_right_rmed   = book.m_stylesheet.m_cellxfs.insert( font_calibri_11_normal, TAlignment( EHORIZONTAL_RIGHT,  EVERTICAL_CENTER, false, false, 0, 0 ), border_top_double_all_thin_rmedium, TFill() );
    TCellXF cf_header_bottom_c = book.m_stylesheet.m_cellxfs.insert( font_calibri_11_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 0, 0 ), border_top_medium_all_none, TFill() );
    TCellXF cf_header_bottom_l = book.m_stylesheet.m_cellxfs.insert( font_calibri_11_normal, TAlignment( EHORIZONTAL_LEFT,   EVERTICAL_CENTER, false, false, 0, 0 ), border_top_medium_all_none, TFill() );
    TCellXF cf_header_bottom_r = book.m_stylesheet.m_cellxfs.insert( font_calibri_11_normal, TAlignment( EHORIZONTAL_RIGHT,  EVERTICAL_CENTER, false, false, 0, 0 ), border_top_medium_all_none, TFill() );

    /* [ row ][ collumn ] */
    sheet1[ 0 ][ 0 ] = QString("Нагрузка по кафедре " + header_data.at(0) + " " + header_data.at(1) + " уч. год").toStdString();
    sheet1[ 0 ][ 0 ] = cf_title;

    for (int i=0; i<24; ++i){
        sheet1[ 2 ][ i ] = header_data.at(i+2).toStdString();
        sheet1[ 2 ][ i ] = cf_header;
    }
    sheet1[ 2 ][ 24 ] = header_data.at(24+2).toStdString();
    sheet1[ 2 ][ 24 ] = cf_header_end;

    int sum = 0;
    int current_row = 3;
    QString current_spec_and_form = "";
    query.exec("SELECT curriculum.subject_name, curriculum.semmester, "
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
               "students.speciality_id = speciality.id "
               "ORDER BY speciality.special_name, speciality.form_training_name, "
               " curriculum.semmester, curriculum.subject_name, subjects_in_semmester.id;");

    while(query.next()){
        sheet1[ current_row ][ 0 ] = (int)(current_row - 3);

        for (int i=0; i<24; ++i){
            if (i == 0 || i == 2 || i == 3){
                sheet1[ current_row ][ i+1 ] = query.value(i).toString().toStdString();
            } else {
                sheet1[ current_row ][ i+1 ] = query.value(i).toInt();
            }
        }
        if (current_spec_and_form == (query.value(2).toString()+query.value(3).toString())){
            for (int i = 0; i<25; ++i){
                if (i == 1 || i == 3){
                    sheet1[ current_row ][ i ] = cf_all_thin_left;
                } else if (i == 8){
                    sheet1[ current_row ][ i ] = cf_all_thin_rdoub_center;
                } else if (i == 24){
                    sheet1[ current_row ][ i ] = cf_all_thin_right_rmed;
                } else {
                    sheet1[ current_row ][ i ] = cf_all_thin_center;
                }
            }
        } else {
            current_spec_and_form = (query.value(2).toString()+query.value(3).toString());

            for (int i = 0; i<25; ++i){
                if (i == 1 || i == 3){
                    sheet1[ current_row ][ i ] = cf_doub_thin_left;
                } else if (i == 8){
                    sheet1[ current_row ][ i ] = cf_doub_thin_rdoub_center;
                } else if (i == 24){
                    sheet1[ current_row ][ i ] = cf_doub_thin_right_rmed;
                } else {
                    sheet1[ current_row ][ i ] = cf_doub_thin_center;
                }
            }
        }
        ++current_row;
        sum += query.value(23).toUInt();
    }

    for (int i = 0; i<25; ++i){
        if (i == 1){
            sheet1[ current_row ][ i ] = QString("Общая сумма:").toStdString();
            sheet1[ current_row ][ i ] = cf_header_bottom_l;
        } else if (i == 24){
            sheet1[ current_row ][ i ] = sum;
            sheet1[ current_row ][ i ] = cf_header_bottom_r;
        } else {
            sheet1[ current_row ][ i ] = "";
            sheet1[ current_row ][ i ] = cf_header_bottom_c ;
        }
    }

    book.insert( sheet1, header_data.at(0).toStdString());
    doc.save(report_path.toStdString());
    return true;
}
