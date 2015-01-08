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

    
    bool select(DB_TABLES tbl, const QString &filter, int col, Qt::SortOrder order);
    bool select(DB_TABLES tbl, const QString &filter);
    int rowCount(DB_TABLES tbl);
    QSqlRecord record(DB_TABLES tbl, int row);
    bool insertRow(DB_TABLES tbl, const QSqlRecord &record);
    bool updateRow(DB_TABLES tbl, int row, const QSqlRecord &record);
    bool deleteRow(DB_TABLES tbl, int row);

    int getNextID(DB_TABLES tbl, const QString &colName);
    
private:
    QSqlDatabase myDB;

    QSqlTableModel *tmAnalyst;
    QSqlTableModel *tmEmployer;
    QSqlTableModel *tmCorporation;
    QSqlTableModel *tmFactory;
    QSqlTableModel *tmRecording;
    QSqlTableModel *tmRecordingObservesLine;
    QSqlTableModel *tmRecordingObservesWorkplace;
    QSqlTableModel *tmWorkplace;
    QSqlTableModel *tmLine;
    QSqlTableModel *tmComment;
    QSqlTableModel *tmEmployee;
    QSqlTableModel *tmEmployeeWorksShift;
    QSqlTableModel *tmProduct;
    QSqlTableModel *tmShift;
    QSqlTableModel *tmBreak;


    QHash<DB_TABLES, QSqlTableModel*> htSqlTableModels;

    QSqlTableModel* getTableModelRef(DB_TABLES tbl);
};

#endif // DBHANDLER_H
