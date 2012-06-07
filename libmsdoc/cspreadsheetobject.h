#ifndef CSPREADSHEETOBJECTH
#define CSPREADSHEETOBJECTH

#include <map>
#include <QStringList>

class CSpreadSheetObject;
typedef CSpreadSheetObject TSpreadSheetObject;

#include "cstring.h"
#include "cbaserelationshipobject.h"
#include "cspreadsheets.h"
#include "crow.h"

class CSpreadSheetObject : public TBaseRelationShipObject
{
private:
    /* you can't do that */
    CSpreadSheetObject& operator = (const CSpreadSheetObject&);

    QStringList widht_col_data;
    QStringList merged_cells;
protected:
    TRows           m_rows;
    TString         m_dir;

    const TString   filename() const;
    ECONTENTTYPE    type() const;
public:
    CSpreadSheetObject(const TString& dir, TRelationShips& relationships);
    CSpreadSheetObject(const CSpreadSheetObject& origin);
    ~CSpreadSheetObject();

    void set_collum_widht(int col_begin, int col_end, int widht);
    void set_row_height(int row, std::string s);
    void set_merge(QString s);
    TRow operator [] (int index);
    int save(TZip& archive, TContent& content) const;
};

#endif

