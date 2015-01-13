#include "controller.h"
#include <QDebug>
#include <QTime>
Controller::Controller(QObject *parent) :
    QObject(parent),
    analystSelectionView(new AnalystSelectionView()),
    mainMenuView(new MainMenu()),
    metaDataView(new MetaDataView()),
    workplaceListView(new WorkplaceListView()),
    workplaceView(new WorkplaceView()),
    lineView(new LineView()),
    activityView(new ActivityView()),
    commentView(new CommentView()),
    ressourceManagementView(new RessourceManagementView()),
    productView(new ProductView()),
    equipmentView(new EquipmentView()),
    transportationView(new TransportationView()),
    settingsView(new SettingsView()),
    documentationView(new DocumentationView()),
    workProcessMetaDataView(new WorkProcessMetaDataView()),
    appliedForceView(new AppliedForceView()),
    bodyPostureView(new BodyPostureView()),
    loadHandlingView(new LoadHandlingView()),
    executionConditionView(new ExecutionConditionView()),
    timerViewController(new TimerViewController())
{
    dbHandler = new DBHandler();

    analyst_ID = 0;
    recording_ID = 1;
    selectedWorkplaceID = 0;
    factory_ID = 0;
    activity_ID = 1;
    selectedWorkplaceID = 0;

    documentationView->setWorkprocessMetaDataView(workProcessMetaDataView);
    documentationView->setBodyPostureView(bodyPostureView);
    documentationView->setAppliedForceView(appliedForceView);
    documentationView->setExecutionConditionView(executionConditionView);
    documentationView->setLoadHandlingView(loadHandlingView);
    documentationView->setTimerViewController(timerViewController);

    viewCon = new ViewController();
    viewCon->setAnalystSelectionView(analystSelectionView);
    viewCon->setMainMenuView(mainMenuView);
    viewCon->setMetaDataView(metaDataView);
    viewCon->setWorkplaceListView(workplaceListView);
    viewCon->setWorkplaceView(workplaceView);
    viewCon->setLineView(lineView);
    viewCon->setActivityView(activityView);
    viewCon->setCommentView(commentView);
    viewCon->setDocumentationView(documentationView);
    viewCon->setRessourceManagementView(ressourceManagementView);
    viewCon->setProductView(productView);
    viewCon->setEquipmentView(equipmentView);
    viewCon->setTransportationView(transportationView);
    viewCon->setSettingsView(settingsView);


    connect(viewCon, SIGNAL(updateAnalystSelectionView()), this, SLOT(updateAnalystSelectionView()));
    connect(analystSelectionView, SIGNAL(remove(int)), this, SLOT(removeAnalyst(int)));
    connect(analystSelectionView, SIGNAL(create()), this, SLOT(createAnalyst()));
    connect(analystSelectionView, SIGNAL(select(int)), this, SLOT(selectAnalyst(int)));

    connect(viewCon, SIGNAL(updateMetaData()), this, SLOT(updateMetaDataView()));
    connect(metaDataView, SIGNAL(save()), this, SLOT(saveMetaDataView()));

    connect(viewCon, SIGNAL(updateWorkplaceList()), this, SLOT(updateWorkplacesView()));

    connect(workplaceListView, SIGNAL(deleteWorkplace(int)), this, SLOT(deleteWorkplace(int)));
    connect(viewCon, SIGNAL(createWorkplace()), this, SLOT(createWorkplace()));
    connect(workplaceListView, SIGNAL(showWorkplace(int)), this, SLOT(updateWorkplaceView(int)));
    connect(viewCon, SIGNAL(updateWorkplace()), this, SLOT(updateWorkplaceView()));
    connect(workplaceView, SIGNAL(save()), this, SLOT(saveWorkplaceView()));

    connect(viewCon, SIGNAL(updateCommentView()), this, SLOT(updateComment()));
    connect(commentView, SIGNAL(save()), this, SLOT(saveComment()));

    connect(viewCon, SIGNAL(updateLineView()), this, SLOT(updateLineView()));
    connect(lineView, SIGNAL(saveLine()), this, SLOT(saveLine()));
    connect(lineView, SIGNAL(saveSelectedLine(int)), SLOT(saveSelectedLine(int)));
    connect(lineView, SIGNAL(deleteLine(int)), SLOT(deleteLine(int)));

    connect(viewCon, SIGNAL(updateProductView()), this, SLOT(updateProductView()));
    connect(productView, SIGNAL(saveProduct()), this, SLOT(createProduct()));
    connect(productView, SIGNAL(deleteProduct(int)), this, SLOT(deleteProduct(int)));

    connect(viewCon, SIGNAL(updateEquipmentView()), this, SLOT(updateEquipmentView()));
    connect(equipmentView, SIGNAL(saveEquipment()), this, SLOT(createEquipment()));
    connect(equipmentView, SIGNAL(deleteEquipment(int)), this, SLOT(deleteEquipment(int)));

    connect(viewCon, SIGNAL(updateTransportationView()), this, SLOT(updateTransportationView()));
    connect(transportationView, SIGNAL(saveTransportation()), this, SLOT(createTransportation()));
    connect(transportationView, SIGNAL(deleteTransportation(int)), this, SLOT(deleteTransportation(int)));

    connect(timerViewController, SIGNAL(createWorkProcess(int,QTime,QTime)), this, SLOT(createWorkprocess(int,QTime,QTime)));

    documentationView->setupViews();

    viewCon->registerViews();
    viewCon->show();
}
//PRIVATE SLOTS

//AnalystSelectionView
void Controller::updateAnalystSelectionView(){
    analystSelectionView->clear();
    DB_TABLES tbl = DB_TABLES::ANALYST;
    dbHandler->select(tbl, QString(""));
    for(int i = 0; i < dbHandler->rowCount(tbl); ++i){
        QSqlRecord record = dbHandler->record(tbl, i);
        analystSelectionView->add(record.value(DBConstants::COL_ANALYST_ID).toInt(),
                                  record.value(DBConstants::COL_ANALYST_LASTNAME).toString(),
                                  record.value(DBConstants::COL_ANALYST_FIRSTNAME).toString());
    }
}

void Controller::createAnalyst(){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_EMPLOYER_NAME).arg(analystSelectionView->getAnalystEmployer());
    QHash<QString, QVariant> valuesEmployer = QHash<QString, QVariant>();
    valuesEmployer.insert(DBConstants::COL_EMPLOYER_NAME, analystSelectionView->getAnalystEmployer());
    int emp_ID = save(DB_TABLES::EMPLOYER, filter, DBConstants::COL_EMPLOYER_ID, DBConstants::HASH_EMPLOYER_TYPES, valuesEmployer);

    QHash<QString, QVariant> valuesAnalyst = QHash<QString, QVariant>();
    valuesAnalyst.insert(DBConstants::COL_ANALYST_LASTNAME, analystSelectionView->getAnalystLastName());
    valuesAnalyst.insert(DBConstants::COL_ANALYST_FIRSTNAME, analystSelectionView->getAnalystFirstName());
    valuesAnalyst.insert(DBConstants::COL_ANALYST_EMPLOYER_ID, emp_ID);
    valuesAnalyst.insert(DBConstants::COL_ANALYST_EXPERIENCE, analystSelectionView->getAnalystExperience());
    insert(DB_TABLES::ANALYST, DBConstants::COL_ANALYST_ID, DBConstants::HASH_ANALYST_TYPES, valuesAnalyst);
    updateAnalystSelectionView();
}

void Controller::removeAnalyst(int id){
    dbHandler->deleteAll(DB_TABLES::ANALYST, QString("%1 = %2").arg(DBConstants::COL_ANALYST_ID).arg(id));
    updateAnalystSelectionView();
}

void Controller::selectAnalyst(int id){
    analyst_ID = id;
}


//MetaDataView
void Controller::updateMetaDataView(){
    if(recording_ID <= 0){
        metaDataView->setRecordTime(QDateTime::currentDateTime(), QDateTime::currentDateTime());
    }
    else{
        dbHandler->select(DB_TABLES::RECORDING, QString("%1 = %2").arg(DBConstants::COL_RECORDING_ID).arg(QString::number(recording_ID)));
        QSqlRecord record = dbHandler->record(DB_TABLES::RECORDING, 0);
        metaDataView->setRecordTime(record.value(DBConstants::COL_RECORDING_START).toDateTime(),
                                record.value(DBConstants::COL_RECORDING_END).toDateTime());

        factory_ID = record.value(DBConstants::COL_RECORDING_FACTORY_ID).toInt();
        dbHandler->select(DB_TABLES::FACTORY, QString("%1 = %2").arg(DBConstants::COL_FACTORY_ID).arg(QString::number(factory_ID)));
        record = dbHandler->record(DB_TABLES::FACTORY, 0);
        metaDataView->setFactory(record.value(DBConstants::COL_FACTORY_NAME).toString(),
                            record.value(DBConstants::COL_FACTORY_STREET).toString(),
                            record.value(DBConstants::COL_FACTORY_ZIP).toInt(),
                            record.value(DBConstants::COL_FACTORY_CITY).toString(),
                            record.value(DBConstants::COL_FACTORY_COUNTRY).toString(),
                            record.value(DBConstants::COL_FACTORY_CONTACT_PERSON).toString(),
                            record.value(DBConstants::COL_FACTORY_HEADCOUNT).toInt());

        int corp_ID = record.value(DBConstants::COL_FACTORY_CORPORATION_ID).toInt();
        dbHandler->select(DB_TABLES::CORPORATION, QString("%1 = %2").arg(DBConstants::COL_CORPORATION_ID).arg(QString::number(corp_ID)));
        record = dbHandler->record(DB_TABLES::CORPORATION, 0);
        metaDataView->setCorporation(record.value(DBConstants::COL_CORPORATION_NAME).toString());

        int boi_ID = record.value(DBConstants::COL_CORPORATION_BRANCH_OF_INDUSTRY_ID).toInt();
        dbHandler->select(DB_TABLES::BRANCH_OF_INDUSTRY, QString("%1 = %2").arg(DBConstants::COL_BRANCH_OF_INDUSTRY_ID).arg(boi_ID));
        record = dbHandler->record(DB_TABLES::BRANCH_OF_INDUSTRY, 0);
        metaDataView->setBranchOfIndustry(record.value(DBConstants::COL_BRANCH_OF_INDUSTRY_NAME).toString(),
                                          record.value(DBConstants::COL_BRANCH_OF_INDUSTRY_DESCRIPTION).toString());
    }
}

void Controller::saveMetaDataView(){
    QString filter = QString("%1 = '%2'").arg(DBConstants::COL_BRANCH_OF_INDUSTRY_NAME).arg(metaDataView->getBranchOfIndustryName());
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_BRANCH_OF_INDUSTRY_NAME, metaDataView->getBranchOfIndustryName());
    values.insert(DBConstants::COL_BRANCH_OF_INDUSTRY_DESCRIPTION, metaDataView->getBranchOfIndustryDescription());
    int boi_ID = save(DB_TABLES::BRANCH_OF_INDUSTRY, filter, DBConstants::COL_BRANCH_OF_INDUSTRY_ID, DBConstants::HASH_BRANCH_OF_INDUSTRY_TYPES, values);

    filter = QString("%1 = '%2'").arg(DBConstants::COL_CORPORATION_NAME).arg(metaDataView->getCorporationName());
    values.clear();
    values.insert(DBConstants::COL_CORPORATION_NAME, metaDataView->getCorporationName());
    values.insert(DBConstants::COL_CORPORATION_BRANCH_OF_INDUSTRY_ID, boi_ID);
    int corp_ID = save(DB_TABLES::CORPORATION, filter, DBConstants::COL_CORPORATION_ID, DBConstants::HASH_CORPORATION_TYPES, values);

    filter = QString("%1 = '%2' AND %3 = '%4'").arg(DBConstants::COL_FACTORY_NAME).arg(metaDataView->getFactoryName()).arg(DBConstants::COL_FACTORY_STREET).arg(metaDataView->getFactoryStreet());
    values.clear();
    values.insert(DBConstants::COL_FACTORY_NAME, metaDataView->getFactoryName());
    values.insert(DBConstants::COL_FACTORY_STREET, metaDataView->getFactoryStreet());
    values.insert(DBConstants::COL_FACTORY_ZIP, metaDataView->getFactoryZip());
    values.insert(DBConstants::COL_FACTORY_CITY, metaDataView->getFactoryCity());
    values.insert(DBConstants::COL_FACTORY_COUNTRY, metaDataView->getFactoryCountry());
    values.insert(DBConstants::COL_FACTORY_CONTACT_PERSON, metaDataView->getFactoryContact());
    values.insert(DBConstants::COL_FACTORY_HEADCOUNT, metaDataView->getFactoryEmployeeCount());
    values.insert(DBConstants::COL_FACTORY_CORPORATION_ID, corp_ID);
    factory_ID = save(DB_TABLES::FACTORY, filter, DBConstants::COL_FACTORY_ID, DBConstants::HASH_FACTORY_TYPES, values);


    filter = QString("");
    QString dtFormat = "dd.MM.yyyy hh:mm";
    values.clear();
    values.insert(DBConstants::COL_RECORDING_START, metaDataView->getRecordTimeBegin().toString(dtFormat));
    values.insert(DBConstants::COL_RECORDING_END, metaDataView->getRecordTimeEnd().toString(dtFormat));
    values.insert(DBConstants::COL_RECORDING_FACTORY_ID, factory_ID);
    values.insert(DBConstants::COL_RECORDING_ANALYST_ID, analyst_ID);
    recording_ID = save(DB_TABLES::RECORDING, filter, DBConstants::COL_RECORDING_ID, DBConstants::HASH_RECORDING_TYPES, values);
}

//WorkplacesView
void Controller::updateWorkplacesView(){
    workplaceListView->clear();
    DB_TABLES tbl = DB_TABLES::WORKPLACE;
    dbHandler->select(tbl, QString(""));
    for(int i = 0; i < dbHandler->rowCount(tbl); ++i){
        QSqlRecord record = dbHandler->record(tbl, i);
        workplaceListView->addWorkplace(record.value(DBConstants::COL_WORKPLACE_ID).toInt(), record.value(DBConstants::COL_WORKPLACE_NAME).toString(), record.value(DBConstants::COL_WORKPLACE_DESCRIPTION).toString(), record.value(DBConstants::COL_WORKPLACE_CODE).toString());
    }
}

//WorkplaceView
void Controller::updateWorkplaceView(int id){
    selectedWorkplaceID = id;
    DB_TABLES tbl = DB_TABLES::WORKPLACE;
    dbHandler->select(tbl, QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_ID).arg(QString::number(id)));
    QSqlRecord record = dbHandler->record(tbl, 0);
    workplaceView->setWorkplaceMetaData(record.value(DBConstants::COL_WORKPLACE_NAME).toString(),
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

    workplaceView->setWorkplaceTimes(basicTime, setupTime, restTime, allowanceTime, cycleTime);

    tbl = DB_TABLES::LINE;
    dbHandler->select(tbl, QString("%1 = %2").arg(DBConstants::COL_LINE_ID).arg(record.value(DBConstants::COL_WORKPLACE_LINE_ID).toString()));
    if(dbHandler->rowCount(tbl) > 0){
        QSqlRecord line = dbHandler->record(tbl, 0);
        workplaceView->setLine(line.value(DBConstants::COL_LINE_NAME).toString(),
                                  line.value(DBConstants::COL_LINE_DESCRIPTION).toString());
    }
    else
        workplaceView->setLine("","");

    tbl = DB_TABLES::COMMENT;
    dbHandler->select(tbl, QString("%1 = %2").arg(DBConstants::COL_COMMENT_WORKPLACE_ID).arg(selectedWorkplaceID));
    if(dbHandler->rowCount(tbl) > 0){
        QSqlRecord comment = dbHandler->record(tbl, 0);
        workplaceView->setComment(comment.value(DBConstants::COL_COMMENT_PROBLEM_NAME).toString(),
                                     comment.value(DBConstants::COL_COMMENT_MEASURE_NAME).toString());
    }
    else
        workplaceView->setComment("","");

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
    lineView->clear();
    DB_TABLES tbl = DB_TABLES::LINE;
    dbHandler->select(tbl, QString(""));
    for(int i = 0; i < dbHandler->rowCount(tbl); ++i){
        QSqlRecord record = dbHandler->record(tbl, i);
        lineView->addLine(record.value(DBConstants::COL_LINE_ID).toInt(), record.value(DBConstants::COL_LINE_NAME).toString());
    }

    dbHandler->select(DB_TABLES::WORKPLACE, QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_ID).arg(selectedWorkplaceID));
    lineView->setSelectedLine(dbHandler->record(DB_TABLES::WORKPLACE, 0).value(DBConstants::COL_WORKPLACE_LINE_ID).toInt());
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
    values.insert(DBConstants::COL_LINE_NAME, lineView->getName());
    values.insert(DBConstants::COL_LINE_DESCRIPTION, lineView->getDescription());
    values.insert(DBConstants::COL_LINE_NUMBER_OF_WORKPLACES, lineView->getWorkplaceCount());
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
    productView->clear();
    DB_TABLES tbl = DB_TABLES::PRODUCT;
    dbHandler->select(tbl, QString(""));
    for(int i = 0; i < dbHandler->rowCount(tbl); ++i){
        QSqlRecord record = dbHandler->record(tbl, i);
        productView->addProduct(record.value(DBConstants::COL_PRODUCT_ID).toInt(),
                            record.value(DBConstants::COL_PRODUCT_NAME).toString(),
                            record.value(DBConstants::COL_PRODUCT_NUMBER).toString(),
                            record.value(DBConstants::COL_PRODUCT_TOTAL_PERCENTAGE).toInt());
    }
}

void Controller::createProduct(){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_PRODUCT_NAME, productView->getName());
    values.insert(DBConstants::COL_PRODUCT_NUMBER, productView->getNumber());
    values.insert(DBConstants::COL_PRODUCT_TOTAL_PERCENTAGE, productView->getTotalPercentage());
    insert(DB_TABLES::PRODUCT, DBConstants::COL_PRODUCT_ID, DBConstants::HASH_PRODUCT_TYPES, values);
    updateProductView();
}

void Controller::deleteProduct(int id){
    dbHandler->deleteAll(DB_TABLES::PRODUCT, QString("%1 = %2").arg(DBConstants::COL_PRODUCT_ID).arg(QString::number(id)));
    updateProductView();
}

//Equipment View
void Controller::updateEquipmentView(){
    equipmentView->clear();
    DB_TABLES tbl = DB_TABLES::EQUIPMENT;
    dbHandler->select(tbl, QString(""));
    for(int i = 0; i < dbHandler->rowCount(tbl); ++i){
        QSqlRecord record = dbHandler->record(tbl, i);
        equipmentView->addEquipment(record.value(DBConstants::COL_EQUIPMENT_ID).toInt(),
                                    record.value(DBConstants::COL_EQUIPMENT_NAME).toString(),
                                    record.value(DBConstants::COL_EQUIPMENT_RECOIL_COUNT).toInt(),
                                    record.value(DBConstants::COL_EQUIPMENT_RECOIL_INTENSITY).toInt(),
                                    record.value(DBConstants::COL_EQUIPMENT_VIBRATION_COUNT).toInt(),
                                    record.value(DBConstants::COL_EQUIPMENT_VIBRATION_INTENSITY).toInt());
    }
}

void Controller::createEquipment(){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_EQUIPMENT_NAME, equipmentView->getName());
    values.insert(DBConstants::COL_EQUIPMENT_RECOIL_COUNT, equipmentView->getRecoilCount());
    values.insert(DBConstants::COL_EQUIPMENT_RECOIL_INTENSITY, equipmentView->getRecoilIntensity());
    values.insert(DBConstants::COL_EQUIPMENT_VIBRATION_COUNT, equipmentView->getVibrationCount());
    values.insert(DBConstants::COL_EQUIPMENT_VIBRATION_INTENSITY, equipmentView->getVibrationIntensity());
    insert(DB_TABLES::EQUIPMENT, DBConstants::COL_EQUIPMENT_ID, DBConstants::HASH_EQUIPMENT_TYPES, values);
    updateEquipmentView();
}

void Controller::deleteEquipment(int id){
    dbHandler->deleteAll(DB_TABLES::EQUIPMENT, QString("%1 = %2").arg(DBConstants::COL_EQUIPMENT_ID).arg(id));
    updateEquipmentView();
}


//Comment
void Controller::updateComment(){
    DB_TABLES tbl = DB_TABLES::COMMENT;
    QString filter = QString("%1 = %2").arg(DBConstants::COL_COMMENT_WORKPLACE_ID).arg(selectedWorkplaceID);
    dbHandler->select(tbl, filter);
    QSqlRecord record = dbHandler->record(tbl, 0);
    commentView->setComment(record.value(DBConstants::COL_COMMENT_PROBLEM_NAME).toString(),
                        record.value(DBConstants::COL_COMMENT_PROBLEM_DESCRIPTION).toString(),
                        record.value(DBConstants::COL_COMMENT_MEASURE_NAME).toString(),
                        record.value(DBConstants::COL_COMMENT_MEASURE_DESCRIPTION).toString(),
                        record.value(DBConstants::COL_COMMENT_WORKER_PERCEPTION).toString());
}

int Controller::saveComment(){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_COMMENT_WORKPLACE_ID).arg(selectedWorkplaceID);

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_COMMENT_PROBLEM_NAME, commentView->getProblemName());
    values.insert(DBConstants::COL_COMMENT_PROBLEM_DESCRIPTION, commentView->getProblemDescription());
    values.insert(DBConstants::COL_COMMENT_MEASURE_NAME, commentView->getMeasureName());
    values.insert(DBConstants::COL_COMMENT_MEASURE_DESCRIPTION, commentView->getMeasureDescription());
    values.insert(DBConstants::COL_COMMENT_WORKER_PERCEPTION, commentView->getWorkerPerception());
    values.insert(DBConstants::COL_COMMENT_WORKPLACE_ID, selectedWorkplaceID);
    return save(DB_TABLES::COMMENT, filter, DBConstants::COL_COMMENT_ID, DBConstants::HASH_COMMENT_TYPES, values);
}

//TransportationView
void Controller::updateTransportationView(){
    transportationView->clear();
    DB_TABLES tbl = DB_TABLES::TRANSPORTATION;
    dbHandler->select(tbl, QString(""));
    for(int i = 0; i < dbHandler->rowCount(tbl); ++i){
        QSqlRecord record = dbHandler->record(tbl, i);
        transportationView->addTransportation(record.value(DBConstants::COL_TRANSPORTATION_ID).toInt(),
                                              record.value(DBConstants::COL_TRANSPORTATION_NAME).toString(),
                                              record.value(DBConstants::COL_TRANSPORTATION_EMPTY_WEIGHT).toInt(),
                                              record.value(DBConstants::COL_TRANSPORTATION_MAX_LOAD).toInt(),
                                              record.value(DBConstants::COL_TRANSPORTATION_FIXED_ROLLER).toBool(),
                                              record.value(DBConstants::COL_TRANSPORTATION_BRAKES).toBool());
    }
}

void Controller::createTransportation(){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_TRANSPORTATION_NAME, transportationView->getName());
    values.insert(DBConstants::COL_TRANSPORTATION_EMPTY_WEIGHT, transportationView->getWeight());
    values.insert(DBConstants::COL_TRANSPORTATION_MAX_LOAD, transportationView->getMaxLoad());
    values.insert(DBConstants::COL_TRANSPORTATION_BRAKES, transportationView->hasBrakes());
    values.insert(DBConstants::COL_TRANSPORTATION_FIXED_ROLLER, transportationView->hasFixedRoller());
    insert(DB_TABLES::TRANSPORTATION, DBConstants::COL_TRANSPORTATION_ID, DBConstants::HASH_TRANSPORTATION_TYPES, values);
    updateTransportationView();
}

void Controller::deleteTransportation(int id){
    dbHandler->deleteAll(DB_TABLES::TRANSPORTATION, QString("%1 = %2").arg(DBConstants::COL_TRANSPORTATION_ID).arg(id));
    updateTransportationView();
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

}


//PRIVATE METHODS
int Controller::insert(DB_TABLES tbl, const QString &colID, const QHash<QString, QVariant::Type> &colMapNameType, QHash<QString, QVariant> &colMapNameValue){
    QSqlRecord record;
    int id = dbHandler->getNextID(tbl, colID);
    colMapNameValue.insert(colID, id);
    foreach(QString key, colMapNameValue.keys()){
        record.append(QSqlField(key, colMapNameType.value(key)));
        record.setValue(key, colMapNameValue.value(key));
    }

    dbHandler->insertRow(tbl, record);
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
    values.insert(DBConstants::COL_WORKPLACE_NAME, workplaceView->getName());
    values.insert(DBConstants::COL_WORKPLACE_DESCRIPTION, workplaceView->getDescription());
    values.insert(DBConstants::COL_WORKPLACE_CODE, workplaceView->getCode());
    values.insert(DBConstants::COL_WORKPLACE_PERCENTAGE_WOMAN, workplaceView->getWomanPercentage());
    values.insert(DBConstants::COL_WORKPLACE_BASIC_TIME, qTimeToSeconds(workplaceView->getBasicTime()));
    values.insert(DBConstants::COL_WORKPLACE_REST_TIME, qTimeToSeconds(workplaceView->getRestTime()));
    values.insert(DBConstants::COL_WORKPLACE_ALLOWANCE_TIME, qTimeToSeconds(workplaceView->getAllowanceTime()));
    values.insert(DBConstants::COL_WORKPLACE_SETUP_TIME, qTimeToSeconds(workplaceView->getSetupTime()));
    values.insert(DBConstants::COL_WORKPLACE_CYCLE_TIME, qTimeToSeconds(workplaceView->getCycleTime()));
    return save(DB_TABLES::WORKPLACE, filter, DBConstants::COL_WORKPLACE_ID, DBConstants::HASH_WORKPLACE_TYPES, values);
}

int Controller::qTimeToSeconds(const QTime &time){
    return time.hour() * 3600 + time.minute() * 60 + time.second();
}

