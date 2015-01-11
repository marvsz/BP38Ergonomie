#include "controller.h"
#include <QDebug>
#include <QTime>
Controller::Controller(QObject *parent) :
    QObject(parent)
{
    dbHandler = new DBHandler();

    viewCon = new ViewController();
    viewCon->show();

    connect(viewCon, SIGNAL(updateMetaData()), this, SLOT(updateMetaDataView()));
    connect(viewCon, SIGNAL(saveMetaData()), this, SLOT(saveMetaDataView()));

    connect(viewCon, SIGNAL(updateWorkplaceList()), this, SLOT(updateWorkplacesView()));

    connect(viewCon, SIGNAL(deleteWorkplace(int)), this, SLOT(deleteWorkplace(int)));
    connect(viewCon, SIGNAL(createWorkplace()), this, SLOT(createWorkplace()));
    connect(viewCon, SIGNAL(updateWorkplace(int)), this, SLOT(updateWorkplaceView(int)));
    connect(viewCon, SIGNAL(updateWorkplace()), this, SLOT(updateWorkplaceView()));
    connect(viewCon, SIGNAL(saveWorkplace()), this, SLOT(saveWorkplaceView()));

    connect(viewCon, SIGNAL(updateCommentView()), this, SLOT(updateComment()));
    connect(viewCon, SIGNAL(saveComment()), this, SLOT(saveComment()));

    connect(viewCon, SIGNAL(updateLineView()), this, SLOT(updateLineView()));
    connect(viewCon, SIGNAL(saveLine()), this, SLOT(saveLine()));
    connect(viewCon, SIGNAL(saveSelectedLine(int)), SLOT(saveSelectedLine(int)));
    connect(viewCon, SIGNAL(deleteLine(int)), SLOT(deleteLine(int)));

    /*connect(viewCon, SIGNAL(updateProductView()), this, SLOT(updateProductView()));
    connect(viewCon, SIGNAL(saveProduct()), this, SLOT(saveProduct()));
    connect(viewCon, SIGNAL(saveSelectedProducts()), this, SLOT(saveSelectedProducts()));
    connect(viewCon, SIGNAL(deleteProduct(int)), this, SLOT(deleteProduct(int)));*/

    connect(viewCon, SIGNAL(createWorkprocess(int,QTime,QTime)), this, SLOT(createWorkprocess(int,QTime,QTime)));

    recording_ID = 1;
    selectedWorkplaceID = 0;
    factory_ID = 0;
    activity_ID = 1;
    selectedWorkplaceID = 0;
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
    viewCon->clearWorkplaceList();
    DB_TABLES tbl = DB_TABLES::WORKPLACE;
    dbHandler->select(tbl, QString(""));
    for(int i = 0; i < dbHandler->rowCount(tbl); ++i){
        QSqlRecord record = dbHandler->record(tbl, i);
        viewCon->addWorkplace(record.value(DBConstants::COL_WORKPLACE_ID).toInt(), record.value(DBConstants::COL_WORKPLACE_NAME).toString(), record.value(DBConstants::COL_WORKPLACE_DESCRIPTION).toString(), record.value(DBConstants::COL_WORKPLACE_CODE).toString());
    }
}

//WorkplaceView
void Controller::updateWorkplaceView(int id){
    selectedWorkplaceID = id;
    DB_TABLES tbl = DB_TABLES::WORKPLACE;
    dbHandler->select(tbl, QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_ID).arg(QString::number(id)));
    QSqlRecord record = dbHandler->record(tbl, 0);
    viewCon->setWorkplaceMetaData(record.value(DBConstants::COL_WORKPLACE_NAME).toString(),
                                  record.value(DBConstants::COL_WORKPLACE_DESCRIPTION).toString(),
                                  record.value(DBConstants::COL_WORKPLACE_CODE).toString(),
                                  record.value(DBConstants::COL_WORKPLACE_PERCENTAGE_WOMAN).toInt());

    QTime basicTime = QTime(0, 0);
    basicTime = basicTime.addSecs(record.value(DBConstants::COL_WORKPLACE_BASIC_TIME).toInt());
    QTime setupTime = QTime(0, 0);
    setupTime = setupTime.addSecs(record.value(DBConstants::COL_WORKPLACE_SETUP_TIME).toInt());
    QTime restTime = QTime(0, 0);
    restTime = restTime.addSecs(record.value(DBConstants::COL_WORKPLACE_REST_TIME).toInt());
    QTime allowanceTime = QTime(0, 0);
    allowanceTime = allowanceTime.addSecs(record.value(DBConstants::COL_WORKPLACE_ALLOWANCE_TIME).toInt());
    QTime cycleTime = QTime(0, 0);
    cycleTime = cycleTime.addSecs(record.value(DBConstants::COL_WORKPLACE_CYCLE_TIME).toInt());

    viewCon->setShiftWorkplaceTimes(basicTime, setupTime, restTime, allowanceTime, cycleTime);

    tbl = DB_TABLES::LINE;
    dbHandler->select(tbl, QString("%1 = %2").arg(DBConstants::COL_LINE_ID).arg(record.value(DBConstants::COL_WORKPLACE_LINE_ID).toString()));
    if(dbHandler->rowCount(tbl) > 0){
        QSqlRecord line = dbHandler->record(tbl, 0);
        viewCon->setWorkplaceLine(line.value(DBConstants::COL_LINE_NAME).toString(),
                                  line.value(DBConstants::COL_LINE_DESCRIPTION).toString());
    }
    else
        viewCon->setWorkplaceLine("","");

    tbl = DB_TABLES::COMMENT;
    dbHandler->select(tbl, QString("%1 = %2").arg(DBConstants::COL_COMMENT_WORKPLACE_ID).arg(selectedWorkplaceID));
    if(dbHandler->rowCount(tbl) > 0){
        QSqlRecord comment = dbHandler->record(tbl, 0);
        viewCon->setWorkplaceComment(comment.value(DBConstants::COL_COMMENT_PROBLEM_NAME).toString(),
                                     comment.value(DBConstants::COL_COMMENT_MEASURE_NAME).toString());
    }
    else
        viewCon->setWorkplaceComment("","");

}

void Controller::updateWorkplaceView(){
    updateWorkplaceView(selectedWorkplaceID);
}

int Controller::createWorkplace(){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_ID).arg(QString::number(0));

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    int id = save(DB_TABLES::WORKPLACE, filter, DBConstants::COL_WORKPLACE_ID, DBConstants::HASH_WORKPLACE_TYPES, values);
    updateWorkplaceView(id);
    return id;
}

void Controller::saveWorkplaceView(){
   saveWorkplace(selectedWorkplaceID);
}

void Controller::deleteWorkplace(int id){
    DB_TABLES tbl = DB_TABLES::WORKPLACE;
    dbHandler->select(tbl, QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_ID).arg(QString::number(id)));
    dbHandler->deleteRow(tbl, 0);
    updateWorkplacesView();
}


//Line

void Controller::updateLineView(){
    viewCon->clearLines();
    DB_TABLES tbl = DB_TABLES::LINE;
    dbHandler->select(tbl, QString(""));
    for(int i = 0; i < dbHandler->rowCount(tbl); ++i){
        QSqlRecord record = dbHandler->record(tbl, i);
        viewCon->addLine(record.value(DBConstants::COL_LINE_ID).toInt(), record.value(DBConstants::COL_LINE_NAME).toString());
    }

    dbHandler->select(DB_TABLES::WORKPLACE, QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_ID).arg(selectedWorkplaceID));
    viewCon->setSelectedLine(dbHandler->record(DB_TABLES::WORKPLACE, 0).value(DBConstants::COL_WORKPLACE_LINE_ID).toInt());
}

int Controller::saveSelectedLine(int id){
    DB_TABLES tbl = DB_TABLES::WORKPLACE;
    QString filter = QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_ID).arg(selectedWorkplaceID);
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_WORKPLACE_LINE_ID, id);
    return save(tbl, filter, DBConstants::COL_WORKPLACE_ID, DBConstants::HASH_WORKPLACE_TYPES, values);
}

int Controller::saveLine(){
    DB_TABLES tbl = DB_TABLES::LINE;
    QString filter = QString("%1 = %2").arg(DBConstants::COL_LINE_ID).arg(QString::number(0));
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_LINE_NAME, viewCon->getLineName());
    values.insert(DBConstants::COL_LINE_DESCRIPTION, viewCon->getLineDescription());
    values.insert(DBConstants::COL_LINE_NUMBER_OF_WORKPLACES, viewCon->getLineWorkplaceCount());
    values.insert(DBConstants::COL_LINE_FACTORY_ID, factory_ID);
    int lineID = save(tbl, filter, DBConstants::COL_LINE_ID, DBConstants::HASH_LINE_TYPES, values);
    saveRecordingObservesLine(lineID);
    updateLineView();
    return lineID;
}

void Controller::deleteLine(int id){
    deleteRecordingObservesLine(id);
    QString filter = QString("%1 = %2").arg(DBConstants::COL_LINE_ID).arg(QString::number(id));
    dbHandler->deleteAll(DB_TABLES::LINE, filter);
    filter = QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_LINE_ID).arg(QString::number(id));
    QSqlRecord record;
    record.append(QSqlField(DBConstants::COL_WORKPLACE_LINE_ID, DBConstants::HASH_WORKPLACE_TYPES.value(DBConstants::COL_WORKPLACE_LINE_ID)));
    record.setNull(DBConstants::COL_WORKPLACE_LINE_ID);
    dbHandler->updateAll(DB_TABLES::WORKPLACE, filter, record);
    updateLineView();
}

//Product
void Controller::updateProductView(){
/*    viewCon->clearProducts();
    DB_TABLES tbl = DB_TABLES::PRODUCT;
    dbHandler->select(tbl, QString(""));
    for(int i = 0; i < dbHandler->rowCount(tbl); ++i){
        QSqlRecord record = dbHandler->record(tbl, i);
        viewCon->addProduct(record.value(DBConstants::COL_PRODUCT_ID).toInt(), record.value(DBConstants::COL_PRODUCT_NAME).toString());
    }

    dbHandler->select(DB_TABLES::ACTIVITY, QString("%1 = %2").arg(DBConstants::COL_ACTIVITY_WORKPLACE_ID).arg(selectedWorkplaceID));
    for(int i = 0; i < dbHandler->rowCount(tbl); ++i)
        viewCon->setProductSelected(dbHandler->record(DB_TABLES::ACTIVITY, 0).value(DBConstants::COL_ACTIVITY_PRODUCT_ID).toInt());*/
}

int Controller::saveSelectedProducts(){
    /*QString filter = QString("%1 = %2 AND %3 = %4").arg(DBConstants::COL_ACTIVITY_WORKPLACE_ID).arg(QString::number(selectedWorkplaceID)).arg(DBConstants::COL_ACTIVITY_PRODUCT_ID);
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_ACTIVITY_WORKPLACE_ID, selectedWorkplaceID);
    QList<int> prodIDs = viewCon->getSelectedProducts();
    foreach(int id, viewCon->getSelectedProducts()){
        values.insert(DBConstants::COL_ACTIVITY_PRODUCT_ID, id);
        save(DB_TABLES::ACTIVITY, filter.arg(QString::number(id)), DBConstants::COL_ACTIVITY_ID, DBConstants::HASH_ACTIVITY_TYPES, values);
        activity_ID = id;
    }
    return 0;*/
}
int Controller::saveProduct(){
    /*QString filter = QString("%1 = %2").arg(DBConstants::COL_PRODUCT_ID).arg(QString::number(0));
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_PRODUCT_NAME, viewCon->getProductName());
    values.insert(DBConstants::COL_PRODUCT_NUMBER, viewCon->getProductNumber());
    values.insert(DBConstants::COL_PRODUCT_TOTAL_PERCENTAGE, viewCon->getProductTotalPercentage());
    int id = save(DB_TABLES::PRODUCT, filter, DBConstants::COL_PRODUCT_ID, DBConstants::HASH_PRODUCT_TYPES, values);
    updateProductView();
    return id;*/
}

void Controller::deleteProduct(int id){
    /*dbHandler->deleteAll(DB_TABLES::PRODUCT, QString("%1 = %2").arg(DBConstants::COL_PRODUCT_ID).arg(QString::number(id)));
    updateProductView();*/
}


//Comment
void Controller::updateComment(){
    DB_TABLES tbl = DB_TABLES::COMMENT;
    QString filter = QString("%1 = %2").arg(DBConstants::COL_COMMENT_WORKPLACE_ID).arg(selectedWorkplaceID);
    dbHandler->select(tbl, filter);
    QSqlRecord record = dbHandler->record(tbl, 0);
    viewCon->setComment(record.value(DBConstants::COL_COMMENT_PROBLEM_NAME).toString(),
                        record.value(DBConstants::COL_COMMENT_PROBLEM_DESCRIPTION).toString(),
                        record.value(DBConstants::COL_COMMENT_MEASURE_NAME).toString(),
                        record.value(DBConstants::COL_COMMENT_MEASURE_DESCRIPTION).toString(),
                        record.value(DBConstants::COL_COMMENT_WORKER_PERCEPTION).toString());
}

int Controller::saveComment(){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_COMMENT_WORKPLACE_ID).arg(selectedWorkplaceID);

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_COMMENT_PROBLEM_NAME, viewCon->getCommentProblemName());
    values.insert(DBConstants::COL_COMMENT_PROBLEM_DESCRIPTION, viewCon->getCommentProblemDescription());
    values.insert(DBConstants::COL_COMMENT_MEASURE_NAME, viewCon->getCommentMeasureName());
    values.insert(DBConstants::COL_COMMENT_MEASURE_DESCRIPTION, viewCon->getCommentMeasureDescription());
    values.insert(DBConstants::COL_COMMENT_WORKER_PERCEPTION, viewCon->getCommentWorkerPerception());
    values.insert(DBConstants::COL_COMMENT_WORKPLACE_ID, selectedWorkplaceID);
    return save(DB_TABLES::COMMENT, filter, DBConstants::COL_COMMENT_ID, DBConstants::HASH_COMMENT_TYPES, values);
}

//WORKPROCESS
int Controller::createWorkprocess(int type, const QTime &start, const QTime &end){
    QString filter = QString("%1 = %2 AND %3 = %4 AND %5 = %6").arg(DBConstants::COL_WORK_PROCESS_ID).arg(0).arg(DBConstants::COL_WORK_PROCESS_ACTIVITY_ID).arg(activity_ID).arg(DBConstants::COL_WORK_PROCESS_TYPE).arg(type);

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_WORK_PROCESS_ACTIVITY_ID, activity_ID);
    values.insert(DBConstants::COL_WORK_PROCESS_TYPE, type);
    values.insert(DBConstants::COL_WORK_PROCESS_BEGIN, start.toString());
    values.insert(DBConstants::COL_WORK_PROCESS_END, end.toString());
    return save(DB_TABLES::WORK_PROCESS, filter, DBConstants::COL_WORK_PROCESS_ID, DBConstants::HASH_WORK_PROCESS_TYPES, values);
}

void Controller::updateWorkprocessViews(){
   /* QString filter = QString("%1 = %2").arg(DBConstants::COL_WORK_PROCESS_ACTIVITY_ID).arg(activity_ID);
    DB_TABLES tbl = DB_TABLES::WORK_PROCESS;
    dbHandler->select(tbl, filter);
    for(int i = 0; i < dbHandler->rowCount(tbl); ++i){
        viewCon->add
    }*/
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
    foreach(QString colName, colMapNameValue.keys())
        record.setValue(colName, colMapNameValue.value(colName));

    if(toInsert)
        dbHandler->insertRow(tbl, record);
    else
        dbHandler->updateRow(tbl, 0, record);
    return id;
}

int Controller::save(DB_TABLES tbl, const QString &filter, const QString &colID, const QHash<QString, QVariant::Type> &colMapNameType, QHash<QString, QVariant> &colMapNameValue){
    dbHandler->select(tbl, filter);
    int id;
    QSqlRecord record;
    bool toInsert = false;
    if(dbHandler->rowCount(tbl) == 0){
        toInsert = true;
        id = dbHandler->getNextID(tbl, colID);
        colMapNameValue.insert(colID, id);
        foreach(QString key, colMapNameValue.keys())
            record.append(QSqlField(key, colMapNameType.value(key)));
    }
    else {
        record = dbHandler->record(tbl, 0);
        id = record.value(colID).toInt();
        colMapNameValue.insert(colID, id);
    }

    foreach(QString colName, colMapNameValue.keys())
        record.setValue(colName, colMapNameValue.value(colName));

    if(toInsert)
        dbHandler->insertRow(tbl, record);
    else
        dbHandler->updateRow(tbl, 0, record);
    return id;
}

void Controller::save(DB_TABLES tbl, const QString &filter, const QHash<QString, QVariant::Type> &colMapNameType, const QHash<QString, QVariant> &colMapNameValue){
    dbHandler->select(tbl, filter);
    QSqlRecord record;
    bool toInsert = false;
    if(dbHandler->rowCount(tbl) == 0){
        toInsert = true;
        foreach(QString key, colMapNameValue.keys())
            record.append(QSqlField(key, colMapNameType.value(key)));
    }
    else {
        record = dbHandler->record(tbl, 0);
    }

    foreach(QString colName, colMapNameValue.keys())
        record.setValue(colName, colMapNameValue.value(colName));

    if(toInsert)
        dbHandler->insertRow(tbl, record);
    else
        dbHandler->updateRow(tbl, 0, record);
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
    return save(DB_TABLES::ANALYST, filter, DBConstants::COL_ANALYST_ID, DBConstants::HASH_ANALYST_TYPES, values);
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
    return save(DB_TABLES::EMPLOYER, filter, DBConstants::COL_EMPLOYER_ID, DBConstants::HASH_EMPLOYER_TYPES, values);
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
    return save(DB_TABLES::CORPORATION, filter, DBConstants::COL_CORPORATION_ID, DBConstants::HASH_CORPORATION_TYPES, values);
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
    factory_ID = save(DB_TABLES::FACTORY, filter, DBConstants::COL_FACTORY_ID, DBConstants::HASH_FACTORY_TYPES, values);
    return factory_ID;
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
    QString dtFormat = "dd.MM.yyyy hh:mm";

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_RECORDING_START, viewCon->getRecordTimeBegin().toString(dtFormat));
    values.insert(DBConstants::COL_RECORDING_END, viewCon->getRecordTimeEnd().toString(dtFormat));
    values.insert(DBConstants::COL_RECORDING_FACTORY_ID, saveFactory());
    values.insert(DBConstants::COL_RECORDING_ANALYST_ID, saveAnalyst());
    return save(DB_TABLES::RECORDING, filter, DBConstants::COL_RECORDING_ID, DBConstants::HASH_RECORDING_TYPES, values);
}

void Controller::saveRecordingObservesLine(int lineID){
    QString filter = QString("%1 = %2 AND %3 = %4").arg(DBConstants::COL_RECORDING_OB_LINE_RECORDING_ID).arg(QString::number(recording_ID)).arg(DBConstants::COL_RECORDING_OB_LINE_LINE_ID).arg(QString::number(lineID));

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_RECORDING_OB_LINE_RECORDING_ID, recording_ID);
    values.insert(DBConstants::COL_RECORDING_OB_LINE_LINE_ID, lineID);
    save(DB_TABLES::RECORDING_OBSERVES_LINE, filter, DBConstants::HASH_RECORDING_OB_LINE_TYPES, values);
}

void Controller::deleteRecordingObservesLine(int lineID){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_RECORDING_OB_LINE_LINE_ID).arg(QString::number(lineID));
    dbHandler->deleteAll(DB_TABLES::RECORDING_OBSERVES_LINE, filter);
}

void Controller::saveRecordingObservesWorkplace(int workplaceID){
    QString filter = QString("%1 = %2 AND %3 = %4").arg(DBConstants::COL_RECORDING_OB_WORKPLACE_RECORDING_ID).arg(QString::number(recording_ID)).arg(DBConstants::COL_RECORDING_OB_WORKPLACE_WORKPLACE_ID).arg(QString::number(workplaceID));

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_RECORDING_OB_WORKPLACE_RECORDING_ID, recording_ID);
    values.insert(DBConstants::COL_RECORDING_OB_WORKPLACE_WORKPLACE_ID, workplaceID);
    save(DB_TABLES::RECORDING_OBSERVES_WORKPLACE, filter, DBConstants::HASH_RECORDING_OB_WORKPLACE_TYPES, values);
}

void Controller::deleteRecordingOberservesWorkplace(int wpID){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_RECORDING_OB_WORKPLACE_WORKPLACE_ID).arg(QString::number(wpID));
    dbHandler->deleteAll(DB_TABLES::RECORDING_OBSERVES_WORKPLACE, filter);
}

int Controller::saveWorkplace(int id){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_ID).arg(QString::number(id));

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_WORKPLACE_NAME, viewCon->getWorkplaceName());
    values.insert(DBConstants::COL_WORKPLACE_DESCRIPTION, viewCon->getWorkplaceDescription());
    values.insert(DBConstants::COL_WORKPLACE_CODE, viewCon->getWorkplaceCode());
    values.insert(DBConstants::COL_WORKPLACE_PERCENTAGE_WOMAN, viewCon->getWorkplaceWomanPercentage());
    values.insert(DBConstants::COL_WORKPLACE_BASIC_TIME, qTimeToSeconds(viewCon->getWorkplaceBasicTime()));
    values.insert(DBConstants::COL_WORKPLACE_REST_TIME, qTimeToSeconds(viewCon->getWorkplaceRestTime()));
    values.insert(DBConstants::COL_WORKPLACE_ALLOWANCE_TIME, qTimeToSeconds(viewCon->getWorkplaceAllowanceTime()));
    values.insert(DBConstants::COL_WORKPLACE_SETUP_TIME, qTimeToSeconds(viewCon->getWorkplaceSetupTime()));
    values.insert(DBConstants::COL_WORKPLACE_CYCLE_TIME, qTimeToSeconds(viewCon->getWorkplaceCycleTime()));
    return save(DB_TABLES::WORKPLACE, filter, DBConstants::COL_WORKPLACE_ID, DBConstants::HASH_WORKPLACE_TYPES, values);
}

int Controller::qTimeToSeconds(const QTime &time){
    return time.hour() * 3600 + time.minute() * 60 + time.second();
}

