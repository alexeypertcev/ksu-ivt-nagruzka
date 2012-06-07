#include <sstream>
#include "cspreadsheetobject.h"

CSpreadSheetObject::CSpreadSheetObject(const TString& dir, TRelationShips& relationships):
    TBaseRelationShipObject( relationships ), m_dir( dir )
{
    widht_col_data.clear();
    merged_cells.clear();
    zoom = "100";
}

CSpreadSheetObject::CSpreadSheetObject(const CSpreadSheetObject& origin):
    TBaseRelationShipObject( origin ), m_dir( origin.m_dir )   
{
    widht_col_data.clear();
    merged_cells.clear();
    zoom = "100";
}

CSpreadSheetObject::~CSpreadSheetObject()
{
}

void CSpreadSheetObject::set_collum_widht(int col_begin, int col_end, int widht)
{
    widht_col_data << "<col min='" + QString::number(col_begin) + "' max='" + QString::number(col_end) + "' width='" + QString::number(widht) + "' customWidth='1'/>";
}

void CSpreadSheetObject::set_collum_widht(int col_begin, int col_end, QString widht)
{
    widht_col_data << "<col min='" + QString::number(col_begin) + "' max='" + QString::number(col_end) + "' width='" + widht + "' customWidth='1'/>";
}

void CSpreadSheetObject::set_row_height(int row, std::string s)
{
    CRowObject *r_o = &m_rows[row];
    r_o->set_height(s);
}

void CSpreadSheetObject::set_merge(QString s)
{
    merged_cells << "<mergeCell ref=\"" + s + "\"/>";
}

void CSpreadSheetObject::set_zoom(QString z)
{
    zoom = z;
}

TRow CSpreadSheetObject::operator [] (int index)
{
    std::pair<TRows::iterator,bool> row = m_rows.insert( std::make_pair( index, TRowObject( index ) ) );
    return row.first;
}

int CSpreadSheetObject::save(TZip& archive, TContent& content) const
{
    content.insert( filename(), ECT_WORKSHEET );
    std::stringstream sheet;
    sheet << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n";
    sheet << "<worksheet ";
    sheet << "xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\">\n";
    //sheet << "xmlns:r=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships\">\n";
    //TODO default settings

    if (zoom != "100"){
        sheet << "<sheetViews>\n";
        sheet << QString("<sheetView tabSelected=\"1\" zoomScale=\"" + zoom + "\" zoomScaleNormal=\"" + zoom + "\" workbookViewId=\"0\">").toStdString();
        sheet << "</sheetView>\n";
        sheet << "</sheetViews>\n";
    }

    if (!widht_col_data.isEmpty()){
        sheet << "<cols>\n";
        for (int i=0; i<widht_col_data.length(); ++i){
            sheet << widht_col_data.at(i).toStdString();
            sheet << "\n";
        }
        sheet << "</cols>\n";
    }
    sheet << "<sheetData>\n";
    //rows
    TRows::const_iterator it = m_rows.begin();
    TRows::const_iterator end = m_rows.end();
    for (; it != end; ++it)
    {
        it->second.save( sheet );
    }

    sheet << "</sheetData>\n";

    if (!merged_cells.isEmpty()){
        sheet << QString("<mergeCells count=\"" + QString::number(merged_cells.length()) + "\">").toStdString();

        for (int i = 0; i<merged_cells.length(); ++i){
            sheet << merged_cells.at(i).toStdString();
            sheet << "\n";
        }
    sheet << "</mergeCells>";
    }

    sheet << "</worksheet>\n";
    archive.add_file( filename(), sheet.str() );

    return 0;
}

const TString CSpreadSheetObject::filename() const
{
    std::stringstream filename;
    filename << m_dir << "/sheet" << m_relationship.rid() << ".xml";
    return filename.str();
}

ECONTENTTYPE CSpreadSheetObject::type() const
{
    return ECT_WORKSHEET;
}

