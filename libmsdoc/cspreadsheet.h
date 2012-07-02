#ifndef CSPREADSHEETH
#define CSPREADSHEETH

#include <list>

class CSpreadSheet;
typedef CSpreadSheet TSpreadSheet;

#include "ccontent.h"
#include "cspreadsheets.h"
#include "cspreadsheetobject.h"
#include "crow.h"

class CSpreadSheet:
    public std::list<CSpreadSheetObject>::iterator
{
private:
    /* you can't do that */
    CSpreadSheet&   operator = (const CSpreadSheet&);

protected:
    typedef std::list<CSpreadSheetObject>::iterator base;
    using base::operator ->;

public:
    CSpreadSheet(const base& it);
    void set_column_width(int col_begin, int col_end, int width);
    void set_column_width(int col_begin, int col_end, QString width);
    void set_row_height(int row, QString h);
    void set_row_height(int row, int h);
    void set_merge(QString s);
    void set_zoom(QString z);
    void set_orientation_tag(QString paperSize, QString s);
    TRow operator [] (int index);

    operator IRelationShipObject& ();
};

#endif

