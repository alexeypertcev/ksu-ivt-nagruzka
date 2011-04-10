#ifndef TABLE_EDITOR_H
#define TABLE_EDITOR_H

#include <QtGui>
#include <QtSql>

class table_editor
{
public:
    table_editor(QTableView table, QString name_table_db);
    void update();
    void commit();
    void add();
    void remove(int id);
};

#endif // TABLE_EDITOR_H
