#include "functions.h"

functions::functions()
{
}

QString functions::toDataString(QString s)
{
    if (s == ""){
        return "0";
    }
    return s;
}
