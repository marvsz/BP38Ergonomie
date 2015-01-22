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
    QString databaseOriginPath = QString(":/assets/ergoAppDB.sqlite");

    /*#if defined(Q_OS_WIN)
        tmpString = "C:\\Database\\";
        databaseFileInfo = QFileInfo(QString("%1\\%2").arg(tmpString).arg("ergoAppDB.sqlite"));
    #endif*/

    #if defined(Q_OS_ANDROID)
        databaseOriginPath = QString(":/assets/ergoAppDB.sqlite");
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

    tmBranchOfIndustry = new QSqlTableModel(0, myDB);
    tmBranchOfIndustry->setTable(DBConstants::TBL_BRANCH_OF_INDUSTRY);
    tmBranchOfIndustry->setEditStrategy(QSqlTableModel::OnRowChange);

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

    tmComment = new QSqlTableModel(0, myDB);
    tmComment->setTable(DBConstants::TBL_COMMENT);
    tmComment->setEditStrategy(QSqlTableModel::OnRowChange);

    tmEmployee = new QSqlTableModel(0, myDB);
    tmEmployee->setTable(DBConstants::TBL_EMPLOYEE);
    tmEmployee->setEditStrategy(QSqlTableModel::OnRowChange);

    tmEmployeeWorksShift = new QSqlTableModel(0, myDB);
    tmEmployeeWorksShift->setTable(DBConstants::TBL_EMPLOYEE_WORKS_SHIFT);
    tmEmployeeWorksShift->setEditStrategy(QSqlTableModel::OnRowChange);

    tmProduct = new QSqlTableModel(0, myDB);
    tmProduct->setTable(DBConstants::TBL_PRODUCT);
    tmProduct->setEditStrategy(QSqlTableModel::OnRowChange);

    tmShift = new QSqlTableModel(0, myDB);
    tmShift->setTable(DBConstants::TBL_SHIFT);
    tmShift->setEditStrategy(QSqlTableModel::OnRowChange);

    tmBreak = new QSqlTableModel(0, myDB);
    tmBreak->setTable(DBConstants::TBL_BREAK);
    tmBreak->setEditStrategy(QSqlTableModel::OnRowChange);

    tmActivity = new QSqlTableModel(0, myDB);
    tmActivity->setTable(DBConstants::TBL_ACTIVITY);
    tmActivity->setEditStrategy(QSqlTableModel::OnRowChange);

    tmBodyPosture = new QSqlTableModel(0, myDB);
    tmBodyPosture->setTable(DBConstants::TBL_BODY_POSTURE);
    tmBodyPosture->setEditStrategy(QSqlTableModel::OnRowChange);

    tmWorkProcess = new QSqlTableModel(0, myDB);
    tmWorkProcess->setTable(DBConstants::TBL_WORK_PROCESS);
    tmWorkProcess->setEditStrategy(QSqlTableModel::OnRowChange);

    tmLoadHandlingType = new QSqlTableModel(0, myDB);
    tmLoadHandlingType->setTable(DBConstants::TBL_LOAD_HANDLING_TYPE);
    tmLoadHandlingType->setEditStrategy(QSqlTableModel::OnRowChange);

    tmLoadHandling = new QSqlTableModel(0, myDB);
    tmLoadHandling->setTable(DBConstants::TBL_LOAD_HANDLING);
    tmLoadHandling->setEditStrategy(QSqlTableModel::OnRowChange);

    tmAppliedForce = new QSqlTableModel(0, myDB);
    tmAppliedForce->setTable(DBConstants::TBL_APPLIED_FORCE);
    tmAppliedForce->setEditStrategy(QSqlTableModel::OnRowChange);

    tmTransportation = new QSqlTableModel(0, myDB);
    tmTransportation->setTable(DBConstants::TBL_TRANSPORTATION);
    tmTransportation->setEditStrategy(QSqlTableModel::OnRowChange);

    tmTypeOfGrasping = new QSqlTableModel(0, myDB);
    tmTypeOfGrasping->setTable(DBConstants::TBL_TYPE_OF_GRASPING);
    tmTypeOfGrasping->setEditStrategy(QSqlTableModel::OnRowChange);

    tmEquipment = new QSqlTableModel(0, myDB);
    tmEquipment->setTable(DBConstants::TBL_EQUIPMENT);
    tmEquipment->setEditStrategy(QSqlTableModel::OnRowChange);

    tmWorkCondition = new QSqlTableModel(0, myDB);
    tmWorkCondition->setTable(DBConstants::TBL_WORK_CONDITION);
    tmWorkCondition->setEditStrategy(QSqlTableModel::OnRowChange);

    htSqlTableModels = QHash<DB_TABLES, QSqlTableModel*>();
    htSqlTableModels.insert(DB_TABLES::ANALYST, tmAnalyst);
    htSqlTableModels.insert(DB_TABLES::EMPLOYER, tmEmployer);
    htSqlTableModels.insert(DB_TABLES::CORPORATION, tmCorporation);
    htSqlTableModels.insert(DB_TABLES::BRANCH_OF_INDUSTRY, tmBranchOfIndustry);
    htSqlTableModels.insert(DB_TABLES::FACTORY, tmFactory);
    htSqlTableModels.insert(DB_TABLES::RECORDING, tmRecording);
    htSqlTableModels.insert(DB_TABLES::RECORDING_OBSERVES_LINE, tmRecordingObservesLine);
    htSqlTableModels.insert(DB_TABLES::RECORDING_OBSERVES_WORKPLACE, tmRecordingObservesWorkplace);
    htSqlTableModels.insert(DB_TABLES::LINE, tmLine);
    htSqlTableModels.insert(DB_TABLES::WORKPLACE, tmWorkplace);
    htSqlTableModels.insert(DB_TABLES::COMMENT, tmComment);
    htSqlTableModels.insert(DB_TABLES::EMPLOYEE, tmEmployee);
    htSqlTableModels.insert(DB_TABLES::EMPLOYEE_WORKS_SHIFT, tmEmployeeWorksShift);
    htSqlTableModels.insert(DB_TABLES::PRODUCT, tmProduct);
    htSqlTableModels.insert(DB_TABLES::SHIFT, tmShift);
    htSqlTableModels.insert(DB_TABLES::BREAK, tmBreak);
    htSqlTableModels.insert(DB_TABLES::ACTIVITY, tmActivity);
    htSqlTableModels.insert(DB_TABLES::BODY_POSTURE, tmBodyPosture);
    htSqlTableModels.insert(DB_TABLES::WORK_PROCESS, tmWorkProcess);
    htSqlTableModels.insert(DB_TABLES::LOAD_HANDLING_TYPE, tmLoadHandlingType);
    htSqlTableModels.insert(DB_TABLES::LOAD_HANDLING, tmLoadHandling);
    htSqlTableModels.insert(DB_TABLES::APPLIED_FORCE, tmAppliedForce);
    htSqlTableModels.insert(DB_TABLES::TRANSPORTATION, tmTransportation);
    htSqlTableModels.insert(DB_TABLES::TYPE_OF_GRASPING, tmTypeOfGrasping);
    htSqlTableModels.insert(DB_TABLES::EQUIPMENT, tmEquipment);
    htSqlTableModels.insert(DB_TABLES::WORK_CONDITION, tmWorkCondition);
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



QSqlTableModel *DBHandler::getTableModelRef(DB_TABLES tbl){
    return htSqlTableModels.value(tbl);
}


