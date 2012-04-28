#include "cspreadsheet.h"

CSpreadSheet::CSpreadSheet(const base& it):
    base( it )
{
TRow row = (*this)->operator [] ( 0 );
row[ 0 ] = "";
}

TRow CSpreadSheet::operator [] (int index)
{
return (*this)->operator [] ( index );
}

CSpreadSheet::operator IRelationShipObject& ()
{
return this->operator *();
}

