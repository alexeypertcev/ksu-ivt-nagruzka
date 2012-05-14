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

        if (teachers_id_list.at(i) != "0") {

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
                        " curriculum.semmester % 2 = 1 "
                        " )");

            temp_list_of_stringlist.clear();
            for(int j=0; j<24; ++j){
                temp_of_int1[j] =  0;
            }

            while (query2.next()){
                temp.clear();
                for(int j=0; j<24; ++j){
                    if (j < 9){
                        temp << query2.value(j).toString();
                    } else {
                        if (query2.value(j).toInt() == 0){
                            temp << "";
                        } else {
                            temp << query2.value(j).toString();
                        }
                    }
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
                        " curriculum.semmester % 2 = 0 "
                        " )");

            temp_list_of_stringlist.clear();
            for(int j=0; j<24; ++j){
                temp_of_int2[j] =  0;
            }
            while (query2.next()){
                temp.clear();
                for(int j=0; j<24; ++j){
                    if (j < 9){
                        temp << query2.value(j).toString();
                    } else {
                        if (query2.value(j).toInt() == 0){
                            temp << "";
                        } else {
                            temp << query2.value(j).toString();
                        }
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

        } else {
            //teachers_id_list.at(i) = "0"


        }

    }
/*
    for (int i=0; i<list_tabledata.length(); ++i){
        temp_tabledata = list_tabledata.at(i);
        qDebug() << temp_tabledata.get_header_sheet();
        qDebug() << "table_data:";
        qDebug() << "--- osen:";
        qDebug() << temp_tabledata.get_list_one();
        qDebug() << "- sum:";
        qDebug() << temp_tabledata.get_list_one_sum();
        qDebug() << "--- vesna:";
        qDebug() << temp_tabledata.get_list_two();
        qDebug() << "- sum:";
        qDebug() << temp_tabledata.get_list_two_sum();
        qDebug() << "- all sum:";
        qDebug() << temp_tabledata.get_list_all_sum();
    }
*/
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
    return false;
}

bool create_report_xlsx(QList<Tabledata> list_tabledata, QString template_patch, QString report_patch)
{
    Tabledata temp_tabledata;
    QFile::remove(report_patch);

    TDocXLSX doc;
    TWorkBook& book = doc.m_workbook;

    for (int i=0; i<list_tabledata.length(); ++i){
        temp_tabledata = list_tabledata.at(i);
        // проверить длину списков


        TSpreadSheet sheet1 = book.m_spreadsheets.insert();

        TFont font_tnr_8_normal = book.m_stylesheet.m_fonts.insert( "Times New Roman", 8, EFF_NONE );
        TFont font_tnr_8_bold = book.m_stylesheet.m_fonts.insert( "Times New Roman", 8, EFF_BOLD );
        TFont font_tnr_10_normal = book.m_stylesheet.m_fonts.insert( "Times New Roman", 10, EFF_NONE );
        TFont font_tnr_12_normal = book.m_stylesheet.m_fonts.insert( "Times New Roman", 12, EFF_NONE );

                                                                         /* left right top bottom*/
        TBorder border_all_medium = book.m_stylesheet.m_borders.insert( TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine(), false, false, false );

        TBorder border_left_top_bottom_double = book.m_stylesheet.m_borders.insert( TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine(), false, false, false );
        TBorder border_right_top_bottom_double = book.m_stylesheet.m_borders.insert( TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine(), false, false, false );
        TBorder border_top_double = book.m_stylesheet.m_borders.insert( TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine(), false, false, false );
        TBorder border_buttom_double = book.m_stylesheet.m_borders.insert( TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine(), false, false, false );
        TBorder border_top_bottom_double = book.m_stylesheet.m_borders.insert( TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_MEDIUM ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine( EBORDERSTYLE_DOUBLE ), TBorderLine(), false, false, false );


        TCellXF cellformat_header0 = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_normal, TAlignment( EHORIZONTAL_LEFT, EVERTICAL_CENTER, false, false, 0, 0 ), TBorder(), TFill() );
        TCellXF cellformat_header0_wrap = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_normal, TAlignment( EHORIZONTAL_LEFT, EVERTICAL_CENTER, true, false, 0, 0 ), TBorder(), TFill() );
        TCellXF cellformat_header1 = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_bold, TAlignment( EHORIZONTAL_LEFT, EVERTICAL_CENTER, false, false, 0, 0 ), TBorder(), TFill() );
        TCellXF cellformat_header2 = book.m_stylesheet.m_cellxfs.insert( font_tnr_10_normal, TAlignment( EHORIZONTAL_RIGHT, EVERTICAL_CENTER, false, false, 0, 0 ), TBorder(), TFill() );
        TCellXF cellformat_header3 = book.m_stylesheet.m_cellxfs.insert( font_tnr_12_normal, TAlignment( EHORIZONTAL_RIGHT, EVERTICAL_CENTER, false, false, 0, 0 ), TBorder(), TFill() );
        TCellXF cellformat_header4 = book.m_stylesheet.m_cellxfs.insert( font_tnr_10_normal, TAlignment( EHORIZONTAL_LEFT, EVERTICAL_CENTER, false, false, 0, 0 ), TBorder(), TFill() );
        TCellXF cellformat_header4_border = book.m_stylesheet.m_cellxfs.insert( font_tnr_10_normal, TAlignment( EHORIZONTAL_LEFT, EVERTICAL_CENTER, false, false, 0, 0 ), border_all_medium, TFill() );
        TCellXF cellformat_header5 = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 0, 0 ), TBorder(), TFill() );
        TCellXF cellformat_header6 = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 90, 0 ), TBorder(), TFill() );
        TCellXF cellformat_header6_wrap = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, true, false, 90, 0 ), TBorder(), TFill() );

        TCellXF cellformat_header0_b_t = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_normal, TAlignment( EHORIZONTAL_LEFT, EVERTICAL_CENTER, false, false, 0, 0 ), border_top_double, TFill() );
        TCellXF cellformat_header0_wrap_b_t = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_normal, TAlignment( EHORIZONTAL_LEFT, EVERTICAL_CENTER, true, false, 0, 0 ), border_top_double, TFill() );
        TCellXF cellformat_header5_b_ltb = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 0, 0 ), border_left_top_bottom_double, TFill() );
        TCellXF cellformat_header6_b_tb = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 90, 0 ), border_top_bottom_double, TFill() );

        TCellXF cellformat_header6_b_b = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 90, 0 ), border_buttom_double, TFill() );
        TCellXF cellformat_header6_wrap_b_b = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, true, false, 90, 0 ), border_buttom_double, TFill() );
        TCellXF cellformat_header6_b_rtb = book.m_stylesheet.m_cellxfs.insert( font_tnr_8_normal, TAlignment( EHORIZONTAL_CENTER, EVERTICAL_CENTER, false, false, 90, 0 ), border_right_top_bottom_double, TFill() );

             /*row collumn*/
        sheet1[ 0 ][ 0 ] = "Министерство образования и науки Российской Федерации";
        sheet1[ 0 ][ 0 ] = cellformat_header0;
        sheet1[ 1 ][ 0 ] = "Государсвенное образовательное учреждение";
        sheet1[ 1 ][ 0 ] = cellformat_header0;
        sheet1[ 2 ][ 0 ] = "высшего профессионального образования";
        sheet1[ 2 ][ 0 ] = cellformat_header0;
        sheet1[ 3 ][ 0 ] = "«Курский государственный университет»";
        sheet1[ 3 ][ 0 ] = cellformat_header1;

        sheet1[ 0 ][ 24 ] = "УТВЕРЖДАЮ:";
        sheet1[ 0 ][ 24 ] = cellformat_header2;
        sheet1[ 1 ][ 24 ] = "Проректор по учебной работе";
        sheet1[ 1 ][ 24 ] = cellformat_header2;
        sheet1[ 3 ][ 24 ] = "____________________/Худин А.Н.";
        sheet1[ 3 ][ 24 ] = cellformat_header2;

        sheet1[ 4 ][ 16 ] = "КАРТОЧКА УЧЕБНЫХ ПОРУЧЕНИЙ НА 2011/2012 УЧЕБНЫЙ ГОД (бюджет)";
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
        sheet1[ 7 ][ 1 ] = temp_tabledata.get_header_kaf_faculty().toStdString();
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

        int current_row = 12;
        int i, j, shift;
        QList<QStringList> temp_list_stringlist;
        QStringList temp_stringlist;

        temp_list_stringlist.clear();
        temp_stringlist.clear();


        temp_list_stringlist = temp_tabledata.get_list_one();
        for (i = 0; i < temp_list_stringlist.length(); ++i){
            temp_stringlist = temp_list_stringlist.at(i);
            shift = 0;
            for (j = 0; j < temp_stringlist.length(); ++j){
                if ( j == 12){
                    shift = 1;
                    sheet1[ current_row ][j] = " ";
                    sheet1[ current_row ][j] = cellformat_header4;
                }
                sheet1[ current_row ][j + shift] = temp_stringlist.at(j).toStdString();
                sheet1[ current_row ][j + shift] = cellformat_header4;
            }
            ++current_row;
        }

        ++current_row;
        temp_stringlist = temp_tabledata.get_list_one_sum();

        shift = 0;
        for (j = 0; j < temp_stringlist.length(); ++j){
            if ( j == 12){
                shift = 1;
                sheet1[ current_row ][j] = " ";
                sheet1[ current_row ][j] = cellformat_header4_border;
            }
            sheet1[ current_row ][j + shift] = temp_stringlist.at(j).toStdString();
            sheet1[ current_row ][j + shift] = cellformat_header4_border;
        }

        sheet1[ current_row ][0] = "Итого за 1е полугодие:";
        ++current_row;

        ++current_row;
        temp_list_stringlist = temp_tabledata.get_list_two();

        for (i = 0; i < temp_list_stringlist.length(); ++i){
            temp_stringlist = temp_list_stringlist.at(i);
            shift = 0;
            for (j = 0; j < temp_stringlist.length(); ++j){
                if ( j == 12){
                    shift = 1;
                    sheet1[ current_row ][j] = " ";
                    sheet1[ current_row ][j] = cellformat_header4;
                }
                sheet1[ current_row ][j + shift] = temp_stringlist.at(j).toStdString();
                sheet1[ current_row ][j + shift] = cellformat_header4;

            }
            ++current_row;
        }

        ++current_row;
        temp_stringlist = temp_tabledata.get_list_two_sum();

        shift = 0;
        for (j = 0; j < temp_stringlist.length(); ++j){
            if ( j == 12){
                shift = 1;
                sheet1[ current_row ][j] = " ";
                sheet1[ current_row ][j] = cellformat_header4_border;
            }
            sheet1[ current_row ][j + shift] = temp_stringlist.at(j).toStdString();
            sheet1[ current_row ][j + shift] = cellformat_header4_border;
        }
        sheet1[ current_row ][0] = "Итого за 2е полугодие:";
        ++current_row;

        ++current_row;
        temp_stringlist = temp_tabledata.get_list_all_sum();

        shift = 0;
        for (j = 0; j < temp_stringlist.length(); ++j){
            if ( j == 12){
                shift = 1;
                sheet1[ current_row ][j] = " ";
                sheet1[ current_row ][j] = cellformat_header4_border;
            }
            sheet1[ current_row ][j + shift] = temp_stringlist.at(j).toStdString();
            sheet1[ current_row ][j + shift] = cellformat_header4_border;
        }
        sheet1[ current_row ][0] = "Итого за год:";

        book.insert( sheet1, temp_tabledata.get_header_sheet().at(0).toStdString() );
    }

    doc.save(report_patch.toStdString());
    return true;
}



reports_creater::reports_creater()
{
}


