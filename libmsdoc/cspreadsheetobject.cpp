#include <sstream>
#include "cspreadsheetobject.h"

CSpreadSheetObject::CSpreadSheetObject(const TString& dir, TRelationShips& relationships):
    TBaseRelationShipObject( relationships ), m_dir( dir )
{
}

CSpreadSheetObject::CSpreadSheetObject(const CSpreadSheetObject& origin):
    TBaseRelationShipObject( origin ), m_dir( origin.m_dir )   
{
}

CSpreadSheetObject::~CSpreadSheetObject()
{
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

    sheet << "<cols>\n";
    sheet << "<col min='1' max='1' width='45' customWidth='1'/>\n";
    sheet << "<col min='2' max='24' width='5' customWidth='1'/>\n";
    sheet << "<col min='25' max='25' width='7' customWidth='1'/>\n";
    sheet << "<col min='26' max='26' width='5' customWidth='1'/>\n";
    sheet << "</cols>\n";

    sheet << "<sheetData>\n";
    //rows
    TRows::const_iterator it = m_rows.begin();
    TRows::const_iterator end = m_rows.end();
    for (; it != end; ++it)
    {
        it->second.save( sheet );
    }

    sheet << "</sheetData>\n";
    sheet << "<mergeCells count=\"21\">";
    sheet << "<mergeCell ref=\"A11:A12\"/>";
    sheet << "<mergeCell ref=\"B11:B12\"/>";
    sheet << "<mergeCell ref=\"C11:C12\"/>";
    sheet << "<mergeCell ref=\"D11:D12\"/>";
    sheet << "<mergeCell ref=\"E11:E12\"/>";
    sheet << "<mergeCell ref=\"F11:F12\"/>";
    sheet << "<mergeCell ref=\"G11:G12\"/>";
    sheet << "<mergeCell ref=\"H11:H12\"/>";
    sheet << "<mergeCell ref=\"I11:K11\"/>";
    sheet << "<mergeCell ref=\"L11:M11\"/>";
    sheet << "<mergeCell ref=\"N11:N12\"/>";
    sheet << "<mergeCell ref=\"O11:O12\"/>";
    sheet << "<mergeCell ref=\"P11:P12\"/>";
    sheet << "<mergeCell ref=\"Q11:Q12\"/>";
    sheet << "<mergeCell ref=\"R11:R12\"/>";
    sheet << "<mergeCell ref=\"S11:S12\"/>";
    sheet << "<mergeCell ref=\"T11:T12\"/>";
    sheet << "<mergeCell ref=\"U11:U12\"/>";
    sheet << "<mergeCell ref=\"V11:X11\"/>";
    sheet << "<mergeCell ref=\"Y11:Y12\"/>";
    sheet << "<mergeCell ref=\"Z11:Z12\"/>";
    sheet << "</mergeCells>";

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

