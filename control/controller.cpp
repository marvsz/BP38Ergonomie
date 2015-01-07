#include "controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{
    dbHandler = new DBHandler();

    viewCon = new ViewController();
    viewCon->show();

    connect(viewCon, SIGNAL(updateMetaData()), this, SLOT(updateMetaDataView()));
    connect(viewCon, SIGNAL(saveMetaData()), this, SLOT(saveMetaDataView()));
    recording_ID = 1;
}


//MetaDataView
void Controller::updateMetaDataView(){
    updateRecording(recording_ID);
}

void Controller::saveMetaDataView(){
    recording_ID = saveRecording();
}

//WorkplacesView
void Controller::updateWorkplacesView(){

}

//WorkplaceView
void Controller::updateWorkplaceView(int id){

}

void Controller::saveWorkplaceView(){

}

//Line
void Controller::updateLines(){

}

void Controller::updateLine(int id){

}

int Controller::saveLine(){

}

//Product
void Controller::updateProducts(){

}

void Controller::updateProduct(int id){

}

int Controller::saveProduct(){

}

//Break
void Controller::updateBreaks(){

}

void Controller::updateBreak(int id){

}

int Controller::saveBreak(){

}

//Comment
void Controller::updateComment(int id){

}

int Controller::saveComment(){

}


//Employee
void Controller::updateEmployee(){

}

int Controller::saveEmployee(int id){

}

//PRIVATE METHODS
int Controller::save(DB_TABLES tbl, const QString &filter, const QString &colID, const QStringList &colNames, const QList<QVariant::Type> &colTypes, QHash<QString, QVariant> &colMapNameValue){
    dbHandler->select(tbl, filter);
    int id;
    QSqlRecord record;
    bool toInsert = false;
    if(dbHandler->rowCount(tbl) == 0){
        toInsert = true;
        id = dbHandler->getNextID(tbl, colID);
        for(int i = 0; i < colNames.count(); ++i){
            record.append(QSqlField(colNames.at(i), colTypes.at(i)));
        }
    }
    else {
        record = dbHandler->record(tbl, 0);
        id = record.value(colID).toInt();
    }

    colMapNameValue.insert(colID, id);
    for(int i = 0; i < colNames.count(); ++i){
        QString colName = colNames.at(i);
        record.setValue(colName, colMapNameValue.value(colName));
    }

    if(toInsert)
        dbHandler->insertRow(tbl, record);
    else
        dbHandler->updateRow(tbl, 0, record);
    return id;
}



void Controller::updateAnalyst(int id){
    if(id <= 0){
        viewCon->setAnalyst("","","");
    }
    else {
        dbHandler->select(DB_TABLES::ANALYST, QString("%1 = %2").arg(DBConstants::COL_ANALYST_ID).arg(QString::number(id)));
        QSqlRecord record = dbHandler->record(DB_TABLES::ANALYST, 0);

        updateEmployer(record.value(DBConstants::COL_EMPLOYER_ID).toInt());

        viewCon->setAnalyst(record.value(DBConstants::COL_ANALYST_LASTNAME).toString(),
                            record.value(DBConstants::COL_ANALYST_FIRSTNAME).toString(),
                            record.value(DBConstants::COL_ANALYST_EXPERIENCE).toString());
    }
}

int Controller::saveAnalyst(){
    QString filter = QString("%1 = '%2' AND %3 = '%4'").arg(DBConstants::COL_ANALYST_LASTNAME).arg(viewCon->getAnalystLastName()).arg(DBConstants::COL_ANALYST_FIRSTNAME).arg(viewCon->getAnalystFirstName());

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_ANALYST_LASTNAME, viewCon->getAnalystLastName());
    values.insert(DBConstants::COL_ANALYST_FIRSTNAME, viewCon->getAnalystFirstName());
    values.insert(DBConstants::COL_ANALYST_EXPERIENCE, viewCon->getAnalystExperience());
    values.insert(DBConstants::COL_ANALYST_EMPLOYER_ID, saveEmployer());
    return save(DB_TABLES::ANALYST, filter, DBConstants::COL_ANALYST_ID, DBConstants::LIST_ANALYST_COLS, DBConstants::LIST_ANALYST_TYPES, values);
}

void Controller::updateEmployer(int id){
    if(id <= 0){
        viewCon->setEmployer("");
    }
    else{
        dbHandler->select(DB_TABLES::EMPLOYER, QString("%1 = %2").arg(DBConstants::COL_EMPLOYER_ID).arg(QString::number(id)));
        QSqlRecord record = dbHandler->record(DB_TABLES::EMPLOYER, 0);
        viewCon->setEmployer(record.value(DBConstants::COL_EMPLOYER_NAME).toString());
    }
}

int Controller::saveEmployer(){
    QString filter = QString("%1 = '%2'").arg(DBConstants::COL_EMPLOYER_NAME).arg(viewCon->getAnalystEmployer());

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_EMPLOYER_NAME, viewCon->getAnalystEmployer());
    return save(DB_TABLES::EMPLOYER, filter, DBConstants::COL_EMPLOYER_ID, DBConstants::LIST_EMPLOYER_COLS, DBConstants::LIST_EMPLOYER_TYPES, values);
}

void Controller::updateCorporation(int id){
    if(id <= 0){
        viewCon->setCorporation("");
    }
    else{
        dbHandler->select(DB_TABLES::CORPORATION, QString("%1 = %2").arg(DBConstants::COL_CORPORATION_ID).arg(QString::number(id)));
        QSqlRecord record = dbHandler->record(DB_TABLES::CORPORATION, 0);
        viewCon->setCorporation(record.value(DBConstants::COL_CORPORATION_NAME).toString());
    }
}

int Controller::saveCorporation(){
    QString filter = QString("%1 = '%2'").arg(DBConstants::COL_CORPORATION_NAME).arg(viewCon->getCorporationName());

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_CORPORATION_NAME, viewCon->getCorporationName());
    return save(DB_TABLES::CORPORATION, filter, DBConstants::COL_CORPORATION_ID, DBConstants::LIST_CORPORATION_COLS, DBConstants::LIST_CORPORATION_TYPES, values);
}

void Controller::updateFactory(int id){
    if(id <= 0){
        viewCon->setFactory("", "", 0, "", "Deutschland", "", 1);
        updateCorporation(0);
    }
    else{
        dbHandler->select(DB_TABLES::FACTORY, QString("%1 = %2").arg(DBConstants::COL_FACTORY_ID).arg(QString::number(id)));
        QSqlRecord record = dbHandler->record(DB_TABLES::FACTORY, 0);
        updateCorporation(record.value(DBConstants::COL_FACTORY_CORPORATION_ID).toInt());
        viewCon->setFactory(record.value(DBConstants::COL_FACTORY_NAME).toString(),
                            record.value(DBConstants::COL_FACTORY_STREET).toString(),
                            record.value(DBConstants::COL_FACTORY_ZIP).toInt(),
                            record.value(DBConstants::COL_FACTORY_CITY).toString(),
                            record.value(DBConstants::COL_FACTORY_COUNTRY).toString(),
                            record.value(DBConstants::COL_FACTORY_CONTACT_PERSON).toString(),
                            record.value(DBConstants::COL_FACTORY_HEADCOUNT).toInt());
    }
}

int Controller::saveFactory(){
    QString filter = QString("%1 = '%2' AND %3 = '%4'").arg(DBConstants::COL_FACTORY_NAME).arg(viewCon->getFactoryName()).arg(DBConstants::COL_FACTORY_STREET).arg(viewCon->getFactoryStreet());

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_FACTORY_NAME, viewCon->getFactoryName());
    values.insert(DBConstants::COL_FACTORY_STREET, viewCon->getFactoryStreet());
    values.insert(DBConstants::COL_FACTORY_ZIP, viewCon->getFactoryZip());
    values.insert(DBConstants::COL_FACTORY_CITY, viewCon->getFactoryCity());
    values.insert(DBConstants::COL_FACTORY_COUNTRY, viewCon->getFactoryCountry());
    values.insert(DBConstants::COL_FACTORY_CONTACT_PERSON, viewCon->getFactoryContact());
    values.insert(DBConstants::COL_FACTORY_HEADCOUNT, viewCon->getFactoryEmployeeCount());
    values.insert(DBConstants::COL_FACTORY_CORPORATION_ID, saveCorporation());
    return save(DB_TABLES::FACTORY, filter, DBConstants::COL_FACTORY_ID, DBConstants::LIST_FACTORY_COLS, DBConstants::LIST_FACTORY_TYPES, values);
}

void Controller::updateRecording(int id){
    if(id <= 0){
        updateAnalyst(0);
        updateFactory(0);
        viewCon->setRecordTime(QDateTime::currentDateTime(), QDateTime::currentDateTime());
    }
    else{
        dbHandler->select(DB_TABLES::RECORDING, QString("%1 = %2").arg(DBConstants::COL_RECORDING_ID).arg(QString::number(id)));
        QSqlRecord record = dbHandler->record(DB_TABLES::RECORDING, 0);
        updateAnalyst(record.value(DBConstants::COL_RECORDING_ANALYST_ID).toInt());
        updateFactory(record.value(DBConstants::COL_RECORDING_FACTORY_ID).toInt());
        viewCon->setRecordTime(record.value(DBConstants::COL_RECORDING_START).toDateTime(),
                                record.value(DBConstants::COL_RECORDING_END).toDateTime());
    }
}

int Controller::saveRecording(){
    QString filter = QString("");
    QString dtFormat = "dd.mm.yyyy hh:mm";

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_RECORDING_START, viewCon->getRecordTimeBegin().toString(dtFormat));
    values.insert(DBConstants::COL_RECORDING_END, viewCon->getRecordTimeEnd().toString(dtFormat));
    values.insert(DBConstants::COL_RECORDING_FACTORY_ID, saveFactory());
    values.insert(DBConstants::COL_RECORDING_ANALYST_ID, saveAnalyst());
    return save(DB_TABLES::RECORDING, filter, DBConstants::COL_RECORDING_ID, DBConstants::LIST_RECORDING_COLS, DBConstants::LIST_RECORDING_TYPES, values);
}

void Controller::saveRecordingObservesLine(int recID, int lineID){
    QString filter = QString("%1 = %2 AND %3 = %4").arg(DBConstants::COL_RECORDING_OB_LINE_RECORDING_ID).arg(recID);

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_RECORDING_OB_LINE_LINE_ID, lineID);
    save(DB_TABLES::RECORDING_OBSERVES_LINE, filter, DBConstants::COL_RECORDING_OB_LINE_LINE_ID, DBConstants::LIST_RECORDING_OB_LINE_COLS, DBConstants::LIST_RECORDING_OB_LINE_TYPES, values);
}

void Controller::saveRecordingObservesWorkplace(int recID, int workplaceID){
    QString filter = QString("%1 = %2 AND %3 = %4").arg(DBConstants::COL_RECORDING_OB_WORKPLACE_RECORDING_ID).arg(recID);

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_RECORDING_OB_WORKPLACE_WORKPLACE_ID, workplaceID);
    save(DB_TABLES::RECORDING_OBSERVES_WORKPLACE, filter, DBConstants::COL_RECORDING_OB_WORKPLACE_WORKPLACE_ID, DBConstants::LIST_RECORDING_OB_WORKPLACE_COLS, DBConstants::LIST_RECORDING_OB_WORKPLACE_TYPES, values);
}
