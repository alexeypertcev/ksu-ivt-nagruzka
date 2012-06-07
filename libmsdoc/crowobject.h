#ifndef CROWOBJECTH
#define CROWOBJECTH

#include <sstream>
#include <map>
#include <QMap>
#include <QString>

class CRowObject;
typedef CRowObject TRowObject;
typedef std::map<int,TRowObject> TRows;

#include "cstring.h"
#include "ccell.h"

class CRowObject
{
private:
    /* you can't do that */
    CRowObject& operator = (const CRowObject&);

protected:
    int     m_id;
    TCells  m_cells;
    std::string height;
public:
    CRowObject(int id);
    CRowObject();
    int     id() const;
    int     row() const;
    TCell   operator [] (int index);
    TCell   operator [] (const TString& name);

    void set_height(std::string s);
    int     save(std::stringstream& sheet) const;
};

#endif

