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

QString Tabledata::get_FIO(){
    QString temp;
    if (header_sheet.length() < 3){
        return "";
    }
    temp = header_sheet.at(0) + ", " + header_sheet.at(1) + " " + header_sheet.at(2);
    return temp;
}

QString Tabledata::get_degre_and_status(){
    if (header_sheet.length() < 4){
        return "";
    }
    return header_sheet.at(3);
}

QString Tabledata::get_kaf_faculty(){
    if (header_sheet.length() < 5){
        return "";
    }
    return header_sheet.at(4);
}
QString Tabledata::get_obiem(){
    if (header_sheet.length() < 6){
        return "";
    }
    return header_sheet.at(5);
}
