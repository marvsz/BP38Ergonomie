#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlField>
#include <QSqlRecord>
#include <QFile>
#include <QFileInfo>
#include "dbconstants.h"

class DBHandler
{
public:
    DBHandler();
    ~DBHandler();

    void setDatabasePath(const QString &originPath, const QString &path);
    void registerTable(const QString &tblName);

    int getNextID(const QString &tbl, const QString &colName, const QString &filter = "");

    QList<QHash<QString, QVariant>> select(const QString &tbl, const QString &filter, Qt::SortOrder order = Qt::SortOrder::AscendingOrder);
    QHash<QString, QVariant> selectFirst(const QString &tbl, const QString &filter, Qt::SortOrder order = Qt::SortOrder::AscendingOrder);
    int selectCount(const QString &tbl, const QString &filter, Qt::SortOrder order = Qt::SortOrder::AscendingOrder);
    bool isSelectEmpty(const QString &tbl, const QString &filter, Qt::SortOrder order = Qt::SortOrder::AscendingOrder);

    int insert(const QString &tbl, const QHash<QString, QVariant::Type> &colMapNameType, QHash<QString, QVariant> &colMapNameValue, const QString &colID = "");
    int save(const QString &tbl, const QHash<QString, QVariant::Type> &colMapNameType, QHash<QString, QVariant> &colMapNameValue, const QString &filter = "", const QString &colID = "");
    int update(const QString &tbl, const QHash<QString, QVariant::Type> &colMapNameType, QHash<QString, QVariant> &colMapNameValue, const QString &filter = "");
    bool deleteRow(const QString &tbl, int row);
    bool deleteAll(const QString &tbl, const QString &filter);

    //PUBLIC ONLY UNTIL BODY POSTURE UPDATE
    bool insertRow(const QString &tbl, const QSqlRecord &record);
    bool updateRow(const QString &tbl, int row, const QSqlRecord &record);

//signals:
    void databaseError(QString errorMessage){}

private:
    QSqlDatabase database;
    QHash<const QString, QSqlTableModel*> htSqlTableModels;

    QSqlTableModel* getTableModelRef(const QString &tbl);

    bool updateAll(const QString &tbl, const QString &filter, const QSqlRecord &record);

};

#endif // DBHANDLER_H
