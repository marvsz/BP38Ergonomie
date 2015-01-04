#include "dbhandler.h"
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QStandardPaths>

DBHandler::DBHandler()
{
    QString tmpString = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QFileInfo databaseFileInfo = QFileInfo(QString("%1/%2").arg(tmpString).arg("ergoAppDB.sqlite"));
    QString databaseOriginPath = QString(":/android/assets/ergoAppDB.sqlite");

    #if defined(Q_OS_ANDROID)
        databaseOriginPath = QString(":/android/assets/ergoAppDB.sqlite");
        tmpString = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        databaseFileInfo = QFileInfo(QString("%1/%2").arg(tmpString).arg("ergoAppDB.sqlite"));
    #endif


    #if defined(Q_OS_IOS)
        databaseOriginPath = QString("%1/%2/%3").arg(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)).arg("Documents").arg("ergoAppDB.sqlite");
        tmpString = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        databaseFileInfo = QFileInfo(QString("%1/%2").arg(tmpString).arg("ergoAppDB.sqlite"));
    #endif

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

    myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName(databasePath);
    if(!myDB.open())
        QMessageBox::critical(0, "Error:", "Could not open database!");

    tmAnalyst = new QSqlTableModel(0, myDB);
    tmAnalyst->setTable(DBConstants::TBL_ANALYST);
    tmAnalyst->setEditStrategy(QSqlTableModel::OnRowChange);

}

DBHandler::~DBHandler(){
    myDB.close();
}

bool DBHandler::select(DB_TABLES tbl, const QString &filter, int col, Qt::SortOrder order){
    QSqlTableModel *model = getTableModelRef(tbl);
    model->setFilter(filter);
    model->setSort(col, order);
    return model->select();
}

bool DBHandler::select(DB_TABLES tbl, const QString &filter){
    return select(tbl, filter, 0, Qt::AscendingOrder);
}

int DBHandler::rowCount(DB_TABLES tbl){
    return getTableModelRef(tbl)->rowCount();
}

QSqlRecord DBHandler::record(DB_TABLES tbl, int row){
    return getTableModelRef(tbl)->record(row);
}

bool DBHandler::insertRow(DB_TABLES tbl, const QSqlRecord &record){
    QSqlTableModel* tm = getTableModelRef(tbl);
    bool success = tm->insertRecord(-1, record);
    tm->submitAll();
    return success;
}

bool DBHandler::updateRow(DB_TABLES tbl, int row, const QSqlRecord &record){
    return getTableModelRef(tbl)->setRecord(row, record);
}

bool DBHandler::deleteRow(DB_TABLES tbl, int row){
    return getTableModelRef(tbl)->removeRow(row);
}

int DBHandler::getNextID(DB_TABLES tbl, const QString &colName){
    QSqlQuery query;
    query.prepare(QString("SELECT MAX(%1) AS max_ID FROM %2;").arg(colName).arg(getTableModelRef(tbl)->tableName()));
    if(query.exec()){
       query.next();
       return query.value("max_ID").toInt() + 1;
    }
    return -1;
}



QSqlTableModel *DBHandler::getTableModelRef(DB_TABLES tbl){
    switch(tbl){
    case DB_TABLES::ANALYST: return tmAnalyst; break;
    default: return NULL; break;
    }
}


