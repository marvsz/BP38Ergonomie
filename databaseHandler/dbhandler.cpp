#include "dbhandler.h"
#include "../standardpaths.h"
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QSqlField>
#include <QSqlError>
#include <QDebug>

DBHandler::DBHandler()
{
    QFileInfo databaseFileInfo = QFileInfo(StandardPaths::databasePath());
    QString databaseOriginPath = StandardPaths::originDatabasePath();
    QString databasePath = databaseFileInfo.absoluteFilePath();

    if ( !databaseFileInfo.exists() ){
           bool copySuccess = QFile::copy( databaseOriginPath, databasePath );
           if ( !copySuccess ){
               QMessageBox::critical(0, "Error:", QString("Could not copy database from %1 to %2").arg(databaseOriginPath).arg(databasePath));
               databasePath.clear();
           }
           else{
                if(!QFile::setPermissions(databasePath,QFile::WriteOwner | QFile::ReadOwner)){
                   QMessageBox::critical(0, "Error:", "Could not set permissions");
                }
           }
       }

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(databasePath);
    if(!database.open())
        QMessageBox::critical(0, "Error:", "Could not open database!");

    htSqlTableModels = QHash<DB_TABLES, QSqlTableModel*>();

    QList<QString> tblNames = DBConstants::HASH_TBL_TO_DB_TABLES.keys();
    for(int i = 0; i < tblNames.size(); ++i){
        QString tblName = tblNames.at(i);
        registerTable(tblName, DBConstants::HASH_TBL_TO_DB_TABLES.value(tblName));
    }
}

DBHandler::~DBHandler(){
    database.close();
}

//PUBLIC METHODS
int DBHandler::insert(DB_TABLES tbl, const QHash<QString, QVariant::Type> &colMapNameType, QHash<QString, QVariant> &colMapNameValue, const QString &colID){
    QSqlRecord record;
    int id;
    if(colID != "" && !colMapNameValue.contains(colID)){
        id = getNextID(tbl, colID);
        colMapNameValue.insert(colID, id);
    }
    else
        id = colMapNameValue.value(colID).toInt();

    foreach(QString key, colMapNameValue.keys()){
        record.append(QSqlField(key, colMapNameType.value(key)));
        record.setValue(key, colMapNameValue.value(key));
    }

    insertRow(tbl, record);
    return id;
}

int DBHandler::update(DB_TABLES tbl, const QHash<QString, QVariant::Type> &colMapNameType, QHash<QString, QVariant> &colMapNameValue, const QString &filter){
    QSqlRecord record;

    foreach(QString colName, colMapNameValue.keys()){
        record.append(QSqlField(colName, colMapNameType.value(colName)));
        record.setValue(colName, colMapNameValue.value(colName));
    }

    updateAll(tbl, filter, record);
    return -1;
}

int DBHandler::save(DB_TABLES tbl, const QHash<QString, QVariant::Type> &colMapNameType, QHash<QString, QVariant> &colMapNameValue, const QString &filter, const QString &colID){
    int count = select(tbl, filter);

    if(count == 0){
        return insert(tbl, colMapNameType, colMapNameValue, colID);
    }
    else {

        return update(tbl, colMapNameType, colMapNameValue, filter);
    }
}

int DBHandler::select(DB_TABLES tbl, const QString &filter, int col, Qt::SortOrder order){
    QSqlTableModel *model = getTableModelRef(tbl);
    model->setFilter(filter);
    model->setSort(col, order);
    if(model->select())
        return model->rowCount();
    return 0;
}

int DBHandler::select(DB_TABLES tbl, const QString &filter){
    return select(tbl, filter, 0, Qt::AscendingOrder);
}

int DBHandler::rowCount(DB_TABLES tbl){
    return getTableModelRef(tbl)->rowCount();
}

QSqlRecord DBHandler::record(DB_TABLES tbl, int row){
    return getTableModelRef(tbl)->record(row);
}

bool DBHandler::deleteRow(DB_TABLES tbl, int row){
    return getTableModelRef(tbl)->removeRow(row);
}

bool DBHandler::deleteAll(DB_TABLES tbl, const QString &filter){
    bool success = true;
    select(tbl, filter);
    for(int i = 0; i < rowCount(tbl); ++i)
        success &= deleteRow(tbl, i);
    return success;
}

int DBHandler::getNextID(DB_TABLES tbl, const QString &colName, const QString &filter){
    QSqlQuery query;
    QString fil("");
    if(!filter.isEmpty())
        fil = QString("WHERE %1").arg(filter);
    query.prepare(QString("SELECT MAX(%1) AS max_ID FROM %2 %3;").arg(colName).arg(getTableModelRef(tbl)->tableName()).arg(fil));
    if(query.exec()){
       query.next();
       return query.value("max_ID").toInt() + 1;
    }
    return -1;
}

//PRIVATE METHODS
void DBHandler::registerTable(const QString &tblName, const DB_TABLES tblType){
    QSqlTableModel *tbl = new QSqlTableModel(0, database);
    tbl->setTable(tblName);
    tbl->setEditStrategy(QSqlTableModel::OnRowChange);

    htSqlTableModels.insert(tblType, tbl);
}

QSqlTableModel *DBHandler::getTableModelRef(DB_TABLES tbl){
    return htSqlTableModels.value(tbl);
}

bool DBHandler::insertRow(DB_TABLES tbl, const QSqlRecord &record){
    QSqlTableModel* tm = getTableModelRef(tbl);
    bool success = tm->insertRecord(-1, record);
    tm->submitAll();
    if(!success)
        qDebug()<<tm->lastError().text();
    return success;
}

bool DBHandler::updateRow(DB_TABLES tbl, int row, const QSqlRecord &record){
    return getTableModelRef(tbl)->setRecord(row, record);
}

bool DBHandler::updateAll(DB_TABLES tbl, const QString &filter, const QSqlRecord &record){
    bool success = true;
    select(tbl, filter);
    for(int i = 0; i < rowCount(tbl); ++i)
        success &= updateRow(tbl, i, record);
    return success;
}


