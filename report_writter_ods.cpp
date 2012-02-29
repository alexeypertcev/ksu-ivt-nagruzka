#include "report_writter_ods.h"
#include "workzip.cpp"

reports_writter_ods::reports_writter_ods()
{
}


OdsWriter::OdsWriter(QObject *parent){}
OdsWriter::~OdsWriter(){}

bool OdsWriter::open(QString fname){
    return true;
}
bool OdsWriter::save(QString fname){
    return true;
}
bool OdsWriter::removeDir(QString dirName){
    return true;
}


CardOdsWriter::CardOdsWriter(QObject *parent){}
CardOdsWriter::~CardOdsWriter(){}
bool CardOdsWriter::writeTable(Tabledata table_data){
    return true;
}
bool CardOdsWriter::add_sheet(){
    return true;
}
bool CardOdsWriter::remove_old_sheet(){
    return true;
}
