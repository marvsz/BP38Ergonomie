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
    bool updateAll(DB_TABLES tbl, const QString &filter, const QSqlRecord &record);
    bool deleteRow(DB_TABLES tbl, int row);
    bool deleteAll(DB_TABLES tbl, const QString &filter);

    int getNextID(DB_TABLES tbl, const QString &colName, const QString &filter = "");
    
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
    QSqlTableModel *tmActivity;
    QSqlTableModel *tmBodyPosture;
    QSqlTableModel *tmWorkProcess;
    QSqlTableModel *tmLoadHandlingType;
    QSqlTableModel *tmLoadHandling;
    QSqlTableModel *tmAppliedForce;
    QSqlTableModel *tmTransportation;
    QSqlTableModel *tmTypeOfGrasping;
    QSqlTableModel *tmEquipment;
    QSqlTableModel *tmWorkCondition;
    QSqlTableModel *tmBranchOfIndustry;


    QHash<DB_TABLES, QSqlTableModel*> htSqlTableModels;

    QSqlTableModel* getTableModelRef(DB_TABLES tbl);
};

#endif // DBHANDLER_H
