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
//    list_all_sum = las;
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
    QStringList buf;
    buf.clear();

    if (list_one_sum.length() != list_two_sum.length()){
        return buf;
    }

    for (int i=0; i<list_one_sum.length(); ++i){
        buf << functions::toReportString(QString::number(list_one_sum.at(i).toInt() + list_two_sum.at(i).toInt()));
    }

    return buf;
}

QList<QStringList> Tabledata::get_list(int i)
{
    if (i == 1){
        return get_list_one();
    } else if (i == 2){
        return get_list_two();
    } else {
        QList<QStringList> list;
        list.clear();
        return list;
    }
}

QStringList Tabledata::get_list_sum(int i)
{
    if (i == 1){
        return get_list_one_sum();
    } else if (i == 2){
        return get_list_two_sum();
    } else {
        QStringList list;
        list.clear();
        return list;
    }
}

QString Tabledata::get_header_FIO(){
    QString temp;
    if (header_sheet.length() < 3){
        return "";
    }
    if (header_sheet.at(1) == ""){
        temp = header_sheet.at(0);
    } else {
        temp = header_sheet.at(0) + ", " + header_sheet.at(1) + " " + header_sheet.at(2);
    }
    return temp;
}

QString Tabledata::get_header_Family()
{
    if (header_sheet.length() < 1){
        return "";
    }
    return header_sheet.at(0);
}

QString Tabledata::get_header_Family_I_O()
{
    if (header_sheet.length() < 3){
        return "";
    }
    if (header_sheet.at(1) == "" || header_sheet.at(2) == ""){
        return header_sheet.at(0);
    }
    return QString(header_sheet.at(0) + " " + header_sheet.at(1).at(0) + ". " + header_sheet.at(2).at(0) + ".");
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