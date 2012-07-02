#include "cspreadsheet.h"

CSpreadSheet::CSpreadSheet(const base& it):
    base( it )
{
    TRow row = (*this)->operator [] ( 0 );
    row[ 0 ] = "";
}

void CSpreadSheet::set_column_width(int col_begin, int col_end, int width)
{
    (*this)->set_collum_widht(col_begin,col_end,width);
}

void CSpreadSheet::set_column_width(int col_begin, int col_end, QString width)
{
    (*this)->set_collum_widht(col_begin,col_end,width);
}

void CSpreadSheet::set_row_height(int row, QString h)
{
    (*this)->set_row_height(row, h.toStdString());
}

void CSpreadSheet::set_row_height(int row, int h)
{
    (*this)->set_row_height(row, QString::number(h).toStdString());
}

void CSpreadSheet::set_merge(QString s)
{
    (*this)->set_merge(s);
}

void CSpreadSheet::set_zoom(QString z)
{
    (*this)->set_zoom(z);
}

void CSpreadSheet::set_orientation_tag(QString paperSize, QString s)
{
    (*this)->set_orientation_tag(paperSize, s);
}

TRow CSpreadSheet::operator [] (int index)
{
    return (*this)->operator [] ( index );
}

CSpreadSheet::operator IRelationShipObject& ()
{
    return this->operator *();
}

