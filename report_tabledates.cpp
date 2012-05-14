#include "report_tabledates.h"

Tabledata::Tabledata()
{
}

void Tabledata::set_header_sheet(QStringList hs){
    header_sheet = hs;
}
void Tabledata::set_list_one(QList<QStringList> lo){
    list_one = lo;
}
void Tabledata::set_list_two(QList<QStringList> lt){
    list_two = lt;
}
void Tabledata::set_list_one_sum(QStringList lon){
    list_one_sum = lon;
}
void Tabledata::set_list_two_sum(QStringList lts){
    list_two_sum = lts;
}
void Tabledata::set_list_all_sum(QStringList las){
    list_all_sum = las;
}

QStringList Tabledata::get_header_sheet(){
    return header_sheet;
}
QList<QStringList> Tabledata::get_list_one(){
    return list_one;
}
QList<QStringList> Tabledata::get_list_two(){
    return list_two;
}
QStringList Tabledata::get_list_one_sum(){
    return list_one_sum;
}
QStringList Tabledata::get_list_two_sum(){
    return list_two_sum;
}
QStringList Tabledata::get_list_all_sum(){
    return list_all_sum;
}

QString Tabledata::get_header_FIO(){
    QString temp;
    if (header_sheet.length() < 3){
        return "";
    }
    temp = header_sheet.at(0) + ", " + header_sheet.at(1) + " " + header_sheet.at(2);
    return temp;
}

QString Tabledata::get_header_degre_and_status(){
    int i = 3;
    if (header_sheet.length() < (i+1)){
        return "";
    }
    return header_sheet.at(i);
}

QString Tabledata::get_header_academic_year()
{
    int i = 4;
    if (header_sheet.length() < (i+1)){
        return "";
    }
    return header_sheet.at(i);
}

QString Tabledata::get_header_name_kafedry_faculty(){
    int i = 5;
    if (header_sheet.length() < (i+1)){
        return "";
    }
    return header_sheet.at(i);
}

QString Tabledata::get_header_business_base_of_training()
{
    int i = 6;
    if (header_sheet.length() < (i+1)){
        return "";
    }
    return header_sheet.at(i);
}

QString Tabledata::get_header_vice_rector_on_education_work()
{
    int i = 7;
    if (header_sheet.length() < (i+1)){
        return "";
    }
    return header_sheet.at(i);
}

QString Tabledata::get_header_obiem(){
    int i = 8;
    if (header_sheet.length() < (i+1)){
        return "";
    }
    return header_sheet.at(i);
}
