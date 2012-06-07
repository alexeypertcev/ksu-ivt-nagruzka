#include "crow.h"

CRow::CRow(const base& it):
    base( it )
{
}

TCell CRow::operator [] (int index)
{
return (*this)->second.operator [] ( index );
}

TCell CRow::operator [] (const TString& name)
{
    return (*this)->second.operator [] ( name );
}
/*
void CRow::set_row_height(int row, std::string s)
{
    (*this)->set_row_height(row, s);
}
*/
