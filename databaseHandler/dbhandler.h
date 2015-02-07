#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QHash>
#include <QSql>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>
#include "dbconstants.h"

class DBHandler
{
public:
    DBHandler();
    ~DBHandler();

    
    int select(DB_TABLES tbl, const QString &filter, int col, Qt::SortOrder order);
    int select(DB_TABLES tbl, const QString &filter);
    int rowCount(DB_TABLES tbl);
    QSqlRecord record(DB_TABLES tbl, int row);
    bool insertRow(DB_TABLES tbl, const QSqlRecord &record);
    bool updateRow(DB_TABLES tbl, int row, const QSqlRecord &record);
    bool updateAll(DB_TABLES tbl, const QString &filter, const QSqlRecord &record);
    bool deleteRow(DB_TABLES tbl, int row);
    bool deleteAll(DB_TABLES tbl, const QString &filter);

    int getNextID(DB_TABLES tbl, const QString &colName, const QString &filter = "");
    
private:
    QSqlDatabase database;

    QHash<DB_TABLES, QSqlTableModel*> htSqlTableModels;

    QSqlTableModel* getTableModelRef(DB_TABLES tbl);

    void registerTable(const QString &tblName, const DB_TABLES tblType);
};

#endif // DBHANDLER_H
