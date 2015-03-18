#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlField>
#include <QSqlRecord>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include "dbconstants.h"

class DBHandler
{

public:
    DBHandler();
    ~DBHandler();

    void registerTable(const QString &tblName);

    int getNextID(const QString &tbl, const QString &colName, const QString &filter = "");

    QList<QHash<QString, QVariant>> select(const QString &tbl, const QString &filter, Qt::SortOrder order = Qt::SortOrder::AscendingOrder);
    QHash<QString, QVariant> selectFirst(const QString &tbl, const QString &filter, Qt::SortOrder order = Qt::SortOrder::AscendingOrder);
    int selectCount(const QString &tbl, const QString &filter, Qt::SortOrder order = Qt::SortOrder::AscendingOrder);
    bool isSelectEmpty(const QString &tbl, const QString &filter, Qt::SortOrder order = Qt::SortOrder::AscendingOrder);

    int insert(const QString &tbl, const QHash<QString, QVariant::Type> &colMapNameType, QHash<QString, QVariant> &colMapNameValue, const QString &colID = "");
    int save(const QString &tbl, const QHash<QString, QVariant::Type> &colMapNameType, QHash<QString, QVariant> &colMapNameValue, const QString &filter = "", const QString &colID = "");
    int update(const QString &tbl, const QHash<QString, QVariant::Type> &colMapNameType, QHash<QString, QVariant> &colMapNameValue, const QString &filter = "", const QString &colID = "");
    bool deleteAll(const QString &tbl, const QString &filter);

//signals:
    void databaseError(QString errorMessage){
        QMessageBox::critical(0, "Error:", errorMessage);
    }

private:
    QSqlDatabase database;
    QHash<const QString, QSqlTableModel*> htSqlTableModels;

    QSqlTableModel* getTableModelRef(const QString &tbl);

    bool updateAll(const QString &tbl, const QString &filter, const QSqlRecord &record);

};

#endif // DBHANDLER_H
