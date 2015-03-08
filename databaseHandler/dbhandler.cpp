#include "dbhandler.h"
#include "standardpaths.h"


DBHandler::DBHandler()
{
    QFileInfo databaseFileInfo = QFileInfo(StandardPaths::databasePath());
    QString databaseOriginPath = StandardPaths::originDatabasePath();
    QString databasePath = databaseFileInfo.absoluteFilePath();

    if ( !databaseFileInfo.exists() ){
           bool copySuccess = QFile::copy( databaseOriginPath, databasePath );
           if ( !copySuccess ){
               QMessageBox::critical(0, "Error:", QString("Could not copy database from \n %1 to \n %2").arg(databaseOriginPath).arg(databasePath));
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

    htSqlTableModels = QHash<const QString, QSqlTableModel*>();
    QList<QString> tblNames = DBConstants::LIST_TABLE_NAMES;
    for(int i = 0; i < tblNames.size(); ++i)
        registerTable(tblNames.at(i));
}

DBHandler::~DBHandler(){
    database.close();
}


void DBHandler::registerTable(const QString &tblName){
    QSqlTableModel *tbl = new QSqlTableModel(0, database);
    tbl->setTable(tblName);
    tbl->setEditStrategy(QSqlTableModel::OnRowChange);

    htSqlTableModels.insert(tblName, tbl);
}


int DBHandler::insert(const QString &tbl, const QHash<QString, QVariant::Type> &colMapNameType, QHash<QString, QVariant> &colMapNameValue, const QString &colID){
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

int DBHandler::update(const QString &tbl, const QHash<QString, QVariant::Type> &colMapNameType, QHash<QString, QVariant> &colMapNameValue, const QString &filter){
    QSqlRecord record;

    foreach(QString colName, colMapNameValue.keys()){
        record.append(QSqlField(colName, colMapNameType.value(colName)));
        record.setValue(colName, colMapNameValue.value(colName));
    }

    updateAll(tbl, filter, record);
    return -1;
}

int DBHandler::save(const QString &tbl, const QHash<QString, QVariant::Type> &colMapNameType, QHash<QString, QVariant> &colMapNameValue, const QString &filter, const QString &colID){
    if(isSelectEmpty(tbl, filter)){
        return insert(tbl, colMapNameType, colMapNameValue, colID);
    }
    else {
        return update(tbl, colMapNameType, colMapNameValue, filter);
    }
}

QList<QHash<QString, QVariant>> DBHandler::select(const QString &tbl, const QString &filter, Qt::SortOrder order){
    QList<QHash<QString, QVariant>> selectValues = QList<QHash<QString, QVariant>>();
    QSqlTableModel *model = getTableModelRef(tbl);
    model->setFilter(filter);
    model->setSort(0, order);
    if(model->select()) {
        for(int i = 0; i < model->rowCount(); ++i){
            QSqlRecord record = model->record(i);
            QHash<QString, QVariant> rowValues = QHash<QString, QVariant>();
            for(int k = 0; k < record.count(); ++k)
                rowValues.insert(record.fieldName(k), record.value(k));
            selectValues.append(rowValues);
        }
    }

    return selectValues;
}

QHash<QString, QVariant> DBHandler::selectFirst(const QString &tbl, const QString &filter, Qt::SortOrder order){
    QList<QHash<QString, QVariant>> selectValues = select(tbl, filter, order);
    if(selectValues.isEmpty())
        return QHash<QString, QVariant>();
    return selectValues.at(0);
}

int DBHandler::selectCount(const QString &tbl, const QString &filter, Qt::SortOrder order){
    QSqlTableModel *model = getTableModelRef(tbl);
    model->setFilter(filter);
    model->setSort(0, order);
    if(model->select())
        return model->rowCount();
    return 0;
}

bool DBHandler::isSelectEmpty(const QString &tbl, const QString &filter, Qt::SortOrder order){
    return selectCount(tbl, filter, order) == 0;
}


//DEPRECATED
bool DBHandler::insertRow(const QString &tbl, const QSqlRecord &record){
    QSqlTableModel* tm = getTableModelRef(tbl);
    bool success = tm->insertRecord(-1, record);
    tm->submitAll();
    return success;
}

bool DBHandler::updateRow(const QString &tbl, int row, const QSqlRecord &record){
    return getTableModelRef(tbl)->setRecord(row, record);
}

bool DBHandler::updateAll(const QString &tbl, const QString &filter, const QSqlRecord &record){
    bool success = true;
    int count = selectCount(tbl, filter);
    QSqlTableModel *tblModel = getTableModelRef(tbl);
    for(int i = 0; i < count; ++i)
        success &= tblModel->setRecord(i, record);
    return success;
}
//END DEPRECATED

bool DBHandler::deleteRow(const QString &tbl, int row){
    return getTableModelRef(tbl)->removeRow(row);
}

bool DBHandler::deleteAll(const QString &tbl, const QString &filter){
    bool success = true;
    for(int i = selectCount(tbl, filter) - 1; i >= 0; --i)
        success &= deleteRow(tbl, i);
    return success;
}

int DBHandler::getNextID(const QString &tbl, const QString &colName, const QString &filter){
    QSqlQuery query;
    QString fil("");
    if(!filter.isEmpty())
        fil = QString("WHERE %1").arg(filter);
    if (query.prepare(QString("SELECT MAX(%1) AS max_ID FROM %2 %3;").arg(colName).arg(getTableModelRef(tbl)->tableName()).arg(fil))){
        if(query.exec()){
           query.next();
           return query.value("max_ID").toInt() + 1;
        }
    }
    return -1;
}

//PRIVATE METHODS
QSqlTableModel *DBHandler::getTableModelRef(const QString &tbl){
    return htSqlTableModels.value(tbl);
}




