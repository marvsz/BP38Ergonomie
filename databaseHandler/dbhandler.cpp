#include "dbhandler.h"
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QStandardPaths>
#include <QSqlError>
#include <QDebug>

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

    tmEmployer = new QSqlTableModel(0, myDB);
    tmEmployer->setTable(DBConstants::TBL_EMPLOYER);
    tmEmployer->setEditStrategy(QSqlTableModel::OnRowChange);

    tmCorporation = new QSqlTableModel(0, myDB);
    tmCorporation->setTable(DBConstants::TBL_CORPORATION);
    tmCorporation->setEditStrategy(QSqlTableModel::OnRowChange);

    tmFactory = new QSqlTableModel(0, myDB);
    tmFactory->setTable(DBConstants::TBL_FACTORY);
    tmFactory->setEditStrategy(QSqlTableModel::OnRowChange);

    tmRecording = new QSqlTableModel(0, myDB);
    tmRecording->setTable(DBConstants::TBL_RECORDING);
    tmRecording->setEditStrategy(QSqlTableModel::OnRowChange);

    tmRecordingObservesLine = new QSqlTableModel(0, myDB);
    tmRecordingObservesLine->setTable(DBConstants::TBL_RECORDING_OB_LINE);
    tmRecordingObservesLine->setEditStrategy(QSqlTableModel::OnRowChange);

    tmRecordingObservesWorkplace = new QSqlTableModel(0, myDB);
    tmRecordingObservesWorkplace->setTable(DBConstants::TBL_RECORDING_OB_WORKPLACE);
    tmRecordingObservesWorkplace->setEditStrategy(QSqlTableModel::OnRowChange);

    tmLine = new QSqlTableModel(0, myDB);
    tmLine->setTable(DBConstants::TBL_LINE);
    tmLine->setEditStrategy(QSqlTableModel::OnRowChange);

    tmWorkplace = new QSqlTableModel(0, myDB);
    tmWorkplace->setTable(DBConstants::TBL_WORKPLACE);
    tmWorkplace->setEditStrategy(QSqlTableModel::OnRowChange);

    htSqlTableModels = QHash<DB_TABLES, QSqlTableModel*>();
    htSqlTableModels.insert(DB_TABLES::ANALYST, tmAnalyst);
    htSqlTableModels.insert(DB_TABLES::EMPLOYER, tmEmployer);
    htSqlTableModels.insert(DB_TABLES::CORPORATION, tmCorporation);
    htSqlTableModels.insert(DB_TABLES::FACTORY, tmFactory);
    htSqlTableModels.insert(DB_TABLES::RECORDING, tmRecording);
    htSqlTableModels.insert(DB_TABLES::RECORDING_OBSERVES_LINE, tmRecordingObservesLine);
    htSqlTableModels.insert(DB_TABLES::RECORDING_OBSERVES_WORKPLACE, tmRecordingObservesWorkplace);
    htSqlTableModels.insert(DB_TABLES::LINE, tmLine);
    htSqlTableModels.insert(DB_TABLES::WORKPLACE, tmWorkplace);

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
    QSqlError e = tm->lastError();
    qDebug()<< e;
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
    return htSqlTableModels.value(tbl);
}


