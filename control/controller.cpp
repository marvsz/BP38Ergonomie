#include "controller.h"
#include <QDebug>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include "../ftpHandler/ftphandler.h"


Controller::Controller(QObject *parent, QApplication *app, Translator *trans) :
    QObject(parent),
    application(app),
    translator(trans),
    dbHandler(new DBHandler()),
    viewCon(new ViewController()),
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
    employeeView(new EmployeeView()),
    employeeListView(new EmployeeListView()),
    bodyMeasurementView(new BodyMeasurementView()),
    shiftView(new ShiftView()),
    shiftCalendarView(new ShiftCalendar()),
    rotationGroupView(new RotationGroupView()),
    rotationGroupListView(new RotationGroupListView()),
    settingsView(new SettingsView()),
    documentationView(new DocumentationView()),
    workProcessMetaDataView(new WorkProcessMetaDataView()),
    appliedForceView(new AppliedForceView()),
    bodyPostureView(new BodyPostureView()),
    loadHandlingView(new LoadHandlingView()),
    executionConditionView(new ExecutionConditionView()),
    gantTimerView(new GantTimerView()),
    timerViewController(new TimerViewController()),
    feedbackPopUp(new FeedbackPopUp()),
    equipmentPopUp(new EquipmentPopUp()),
    transportationPopUp(new TransporationPopUp()),
    sendDatabasePopUp(new SendDatabasePopUp()),
    analystPopUp(new AnalystPopUp()),
    productPopUp(new ProductPopUp()),
    activityPopUp(new ActivityPopUp()),
    languagePopUp(new LanguagePopUp()),
    themePopUp(new ThemePopUp()),
    workplacePopUp(new WorkplacePopUp()),
    importDataPopUp(new ImportDataPopUp()),
    resetPopUp(new ResetPopUp()),
    employeePopUp(new EmployeePopUp()),
    factorySettingsPopUp(new FactorySettingsPopUp())
{
    analyst_ID = 0;
    recording_ID = 1;
    workplace_ID = 0;
    workcondition_ID = 0;
    factory_ID = 0;
    activity_ID = 0;
    appliedforce_ID = 0;
    loadhandling_ID = 0;
    workprocess_Type = AVType::BASIC;
    workprocess_ID = 0;
    bodyMeasurement_ID = 1;
    employee_ID = 1;

    connect(viewCon, SIGNAL(update(ViewType)), this, SLOT(update(ViewType)));
    connect(viewCon, SIGNAL(save(ViewType)), this, SLOT(save(ViewType)));
    connect(viewCon, SIGNAL(update(PopUpType)), this, SLOT(update(PopUpType)));

    connect(analystSelectionView, SIGNAL(remove(int)), this, SLOT(removeAnalyst(int)));
    connect(analystSelectionView, SIGNAL(select(int)), this, SLOT(selectAnalyst(int)));
    connect(analystPopUp, SIGNAL(confirm()), this, SLOT(createAnalyst()));

    connect(mainMenuView, SIGNAL(createBlankRecording()), this, SLOT(createBlankRecording()));

    connect(workplaceListView, SIGNAL(remove(int)), this, SLOT(deleteWorkplace(int)));
    connect(workplaceListView, SIGNAL(create()), this, SLOT(createWorkplace()));
    connect(workplaceListView, SIGNAL(selected(int)), this, SLOT(updateWorkplaceView(int)));
    connect(workplacePopUp, SIGNAL(confirm()), this, SLOT(createWorkplacePopup()));

    connect(this, SIGNAL(clearEmployees()), employeeListView, SLOT(clear()));
    connect(this, SIGNAL(clearAll()), employeeListView, SLOT(clear()));
    connect(employeeListView, SIGNAL(deleteEmployee(int)), this, SLOT(deleteEmployee(int)));
    connect(this, SIGNAL(removedEmployee(int)), employeeListView, SLOT(removeEmployee(int)));
    connect(this, SIGNAL(removedEmployee(int)), employeePopUp, SLOT(removeEmployee(int)));
    connect(employeeListView, SIGNAL(createEmployee(QHash<QString,QVariant>)), this, SLOT(createEmployee(QHash<QString,QVariant>)));
    connect(this, SIGNAL(createdEmployee(QHash<QString,QVariant>)), employeeListView, SLOT(addEmployee(QHash<QString,QVariant>)));
    connect(this, SIGNAL(createdEmployee(QHash<QString,QVariant>)), employeePopUp, SLOT(addEmployee(QHash<QString,QVariant>)));
    connect(employeeListView, SIGNAL(selectEmployee(int)), this, SLOT(selectEmployee(int)));
    connect(this, SIGNAL(updatedEmployee(QHash<QString,QVariant>)), employeeListView, SLOT(updateEmployee(QHash<QString,QVariant>)));
    connect(this, SIGNAL(updatedEmployee(QHash<QString,QVariant>)), employeePopUp, SLOT(updateEmployee(QHash<QString,QVariant>)));
    connect(this, SIGNAL(selectedEmployee(QHash<QString,QVariant>)), employeeView, SLOT(setEmployee(QHash<QString,QVariant>)));
    connect(employeeView, SIGNAL(saveEmployee(QHash<QString,QVariant>)), this, SLOT(saveEmployee(QHash<QString,QVariant>)));

    connect(bodyMeasurementView, SIGNAL(saveBodyMeasurement(QHash<QString,QVariant>)), this, SLOT(saveBodyMeasurement(QHash<QString,QVariant>)));
    connect(this, SIGNAL(selectedBodyMeasurement(QHash<QString,QVariant>)), bodyMeasurementView, SLOT(setBodyMeasurement(QHash<QString,QVariant>)));
    //connect(employeePopUp, SIGNAL(confirm()), this, SLOT(employeeSelected()));

    connect(lineView, SIGNAL(saveLine()), this, SLOT(createLine()));
    connect(lineView, SIGNAL(saveSelectedLine(int)), SLOT(saveSelectedLine(int)));
    connect(lineView, SIGNAL(deleteLine(int)), SLOT(deleteLine(int)));

    connect(productView, SIGNAL(saveProduct()), this, SLOT(createProduct()));
    connect(productView, SIGNAL(deleteProduct(int)), this, SLOT(deleteProduct(int)));
    connect(productPopUp, SIGNAL(confirm()), this, SLOT(createProductPopUp()));

    connect(equipmentView, SIGNAL(saveEquipment()), this, SLOT(createEquipment()));
    connect(equipmentView, SIGNAL(deleteEquipment(int)), this, SLOT(deleteEquipment(int)));
    connect(equipmentPopUp, SIGNAL(confirm()), this, SLOT(createEquipmentPopUp()));

    connect(transportationView, SIGNAL(saveTransportation()), this, SLOT(createTransportation()));
    connect(transportationView, SIGNAL(deleteTransportation(int)), this, SLOT(deleteTransportation(int)));
    connect(transportationPopUp, SIGNAL(confirm()), this, SLOT(createTransportationPopUp()));

    connect(activityView, SIGNAL(createActivity()), this, SLOT(createActivity()));
    connect(activityView, SIGNAL(selectActivity(int)), this, SLOT(selectActivity(int)));
    connect(activityView, SIGNAL(deleteActivity(int)), this, SLOT(deleteActivity(int)));
    connect(activityView, SIGNAL(editActivity(int)), this, SLOT(updateActivityPopUp(int)));
    connect(activityPopUp, SIGNAL(confirm()), this, SLOT(updateActivity()));

    connect(documentationView, SIGNAL(update(ViewType)), this, SLOT(update(ViewType)));
    connect(documentationView, SIGNAL(save(ViewType)), this, SLOT(save(ViewType)));

    connect(gantTimerView, SIGNAL(workProcessSelected(int,AVType)), this, SLOT(setSelectedWorkProcess(int, AVType)));

    connect(gantTimerView, SIGNAL(entered()), timerViewController, SLOT(gantViewShown()));
    connect(gantTimerView, SIGNAL(left()), timerViewController, SLOT(gantViewHidden()));
    connect(timerViewController, SIGNAL(createWorkProcess(AVType,QTime,QTime)), this, SLOT(createWorkprocess(AVType,QTime,QTime)));
    connect(timerViewController, SIGNAL(nextWorkProcess()), this, SLOT(selectNextWorkProcess()));
    connect(timerViewController, SIGNAL(previousWorkProcess()), this, SLOT(selectPreviousWorkProcess()));
    connect(timerViewController, SIGNAL(workProcessTypeChanged(AVType)), this, SLOT(workProcessTypeChanged(AVType)));
    connect(timerViewController, SIGNAL(resetWorkProcesses()), this, SLOT(resetWorkProcesses()));
    connect(timerViewController, SIGNAL(durationChanged(QTime)), this, SLOT(workProcessDurationChanged(QTime)));

    connect(sendDatabasePopUp, SIGNAL(create(IFTPConnections*)), this, SLOT(createConnection(IFTPConnections*)));
    connect(sendDatabasePopUp, SIGNAL(edit(IFTPConnections*,int)), this, SLOT(editConnection(IFTPConnections*,int)));
    connect(sendDatabasePopUp, SIGNAL(selected(IFTPConnections*,int)), this, SLOT(selectedConnectionChanged(IFTPConnections*,int)));

    connect(importDataPopUp, SIGNAL(create(IFTPConnections*)), this, SLOT(createConnection(IFTPConnections*)));
    connect(importDataPopUp, SIGNAL(edit(IFTPConnections*,int)), this, SLOT(editConnection(IFTPConnections*,int)));
    connect(importDataPopUp, SIGNAL(selected(IFTPConnections*,int)), this, SLOT(selectedConnectionChanged(IFTPConnections*,int)));
    connect(importDataPopUp, SIGNAL(confirm()), this, SLOT(parseImportData()));

    connect(languagePopUp, SIGNAL(confirm()), this, SLOT(languageChanged()));
    connect(themePopUp, SIGNAL(confirm()), this, SLOT(themeChanged()));
    connect(resetPopUp, SIGNAL(confirm()), this, SLOT(resetSelectedEntries()));
    connect(factorySettingsPopUp, SIGNAL(confirm()), this, SLOT(resetDatabaseFactory()));

    // Register Documentation Views
    documentationView->registerView(workProcessMetaDataView, ViewType::WORK_PROCESS_META_DATA_VIEW);
    documentationView->registerView(bodyPostureView, ViewType::BODY_POSTURE_VIEW);
    documentationView->registerView(loadHandlingView, ViewType::LOAD_HANDLING_VIEW);
    documentationView->registerView(appliedForceView, ViewType::APPLIED_FORCE_VIEW);
    documentationView->registerView(executionConditionView, ViewType::WORKING_CONDITION_VIEW);
    documentationView->registerView(gantTimerView, ViewType::GANT_VIEW);
    documentationView->setTimerViewController(timerViewController);

    // Register ViewContoller Views
    viewCon->registerView(analystSelectionView, ViewType::ANALYST_SELECTION_VIEW);
    viewCon->registerView(mainMenuView, ViewType::MAIN_MENU_VIEW);
    viewCon->registerView(metaDataView, ViewType::METADATA_VIEW);
    viewCon->registerView(workplaceListView, ViewType::WORKPLACELIST_VIEW);
    viewCon->registerView(settingsView, ViewType::SETTINGS_VIEW);
    viewCon->registerView(activityView, ViewType::ACTIVITY_VIEW);
    viewCon->registerView(commentView, ViewType::COMMENT_VIEW);
    viewCon->registerView(lineView, ViewType::LINE_VIEW);
    viewCon->registerView(workplaceView, ViewType::WORKPLACE_VIEW);
    viewCon->registerView(transportationView, ViewType::TRANSPORTATION_VIEW);
    viewCon->registerView(ressourceManagementView, ViewType::RESSOURCE_MANAGMENT_VIEW);
    viewCon->registerView(productView, ViewType::PRODUCT_VIEW);
    viewCon->registerView(equipmentView, ViewType::EQUIPMENT_VIEW);
    viewCon->registerView(shiftView, ViewType::SHIFT_VIEW);
    viewCon->registerView(shiftCalendarView, ViewType::SHIFT_CALENDAR_VIEW);
    viewCon->registerView(rotationGroupView, ViewType::ROTATION_GROUP_VIEW);
    viewCon->registerView(rotationGroupListView, ViewType::ROTATION_GROUP_LIST_VIEW);
    viewCon->registerView(employeeView, ViewType::EMPLOYEE_VIEW);
    viewCon->registerView(employeeListView, ViewType::EMPLOYEE_LIST_VIEW);
    viewCon->registerView(bodyMeasurementView, ViewType::BODY_MEASUREMENT_VIEW);
    viewCon->registerView(documentationView, ViewType::DOCUMENTATION_VIEW);

    // Register PopUps on ViewController
    viewCon->registerPopUp(feedbackPopUp, PopUpType::FEEDBACK_POPUP);
    viewCon->registerPopUp(equipmentPopUp, PopUpType::EQUIPMENT_POPUP);
    viewCon->registerPopUp(sendDatabasePopUp, PopUpType::DB_SEND_POPUP);
    viewCon->registerPopUp(transportationPopUp, PopUpType::TRANSPORTATION_POPUP);
    viewCon->registerPopUp(productPopUp, PopUpType::PRODUCT_POPUP);
    viewCon->registerPopUp(analystPopUp, PopUpType::ANALYST_POPUP);
    viewCon->registerPopUp(activityPopUp, PopUpType::ACTIVITY_POPUP);
    viewCon->registerPopUp(languagePopUp, PopUpType::LANGUAGE_POPUP);
    viewCon->registerPopUp(themePopUp, PopUpType::THEME_POPUP);
    viewCon->registerPopUp(workplacePopUp, PopUpType::WORKPLACE_POPUP);
    viewCon->registerPopUp(importDataPopUp, PopUpType::IMPORT_DATA_POPUP);
    viewCon->registerPopUp(resetPopUp, PopUpType::RESET_POPUP);
    viewCon->registerPopUp(employeePopUp,PopUpType::EMPlOYEE_POPUP);
    viewCon->registerPopUp(factorySettingsPopUp, PopUpType::FACTORYSETTINGS_POPUP);

    //Set the start Views
    documentationView->showStartView(ViewType::BODY_POSTURE_VIEW);
    viewCon->showStartView(ViewType::ANALYST_SELECTION_VIEW);

    initializeEmployees();
}
//PRIVATE SLOTS

void Controller::databaseError(QString error){
    viewCon->showMessage(error, NotificationMessage::ERROR, NotificationMessage::PERSISTENT);
}

void Controller::update(ViewType type)
{
    switch(type)
        {
        case ViewType::ANALYST_SELECTION_VIEW:
            updateAnalystSelectionView();
            break;
        case ViewType::METADATA_VIEW:
            updateMetaDataView();
            break;
        case ViewType::WORKPLACELIST_VIEW:
            updateWorkplacesView();
            break;
        case ViewType::WORKPLACE_VIEW:
            updateWorkplaceView();
            break;
        case ViewType::LINE_VIEW:
            updateLineView();
            break;
        case ViewType::COMMENT_VIEW:
            updateComment();
            break;
        case ViewType::ACTIVITY_VIEW:
            updateActivityView();
            break;
        case ViewType::DOCUMENTATION_VIEW:
            updateDocumentationViewRessources();
            break;
        case ViewType::EQUIPMENT_VIEW:
            updateEquipmentView();
            break;
        case ViewType::TRANSPORTATION_VIEW:
            updateTransportationView();
            break;
        case ViewType::PRODUCT_VIEW:
            updateProductView();
            break;
        case ViewType::BODY_POSTURE_VIEW:
            updateBodyPostureView();
            break;
        case ViewType::APPLIED_FORCE_VIEW:
            updateAppliedForceView();
            break;
        case ViewType::LOAD_HANDLING_VIEW:
            updateLoadHandlingView();
            break;
        case ViewType::WORKING_CONDITION_VIEW:
            updateExecutionConditionView();
            break;
        case ViewType::WORK_PROCESS_META_DATA_VIEW:
            updateWorkProcessMetaDataView();
            break;
        case ViewType::SETTINGS_VIEW:
            break;
        default:
            break;
        }
}

void Controller::update(PopUpType type)
{
    switch(type)
        {
        case PopUpType::DB_SEND_POPUP:
            updateFTPConnectionPopUp(sendDatabasePopUp);
            break;
        case PopUpType::IMPORT_DATA_POPUP:
            updateFTPConnectionPopUp(importDataPopUp);
        default:
            break;
        }
}

void Controller::save(ViewType type)
{
    switch(type)
        {
        case ViewType::METADATA_VIEW:
            saveMetaDataView();
            break;
        case ViewType::WORKPLACE_VIEW:
            saveWorkplaceView();
            break;
        case ViewType::LINE_VIEW:
            updateLineView();
            break;
        case ViewType::COMMENT_VIEW:
            saveComment();
            break;
        case ViewType::DOCUMENTATION_VIEW:
            saveCurrentWorkProcess();
            break;
        case ViewType::BODY_POSTURE_VIEW:
            saveBodyPostureView();
            break;
        case ViewType::APPLIED_FORCE_VIEW:
            saveAppliedForceView();
            break;
        case ViewType::LOAD_HANDLING_VIEW:
            saveLoadHandlingView();
            break;
        case ViewType::WORKING_CONDITION_VIEW:
            saveExecutionConditionView();
            break;
        case ViewType::WORK_PROCESS_META_DATA_VIEW:
            saveCurrentWorkProcess();
            break;
        default:
            break;
        }
}


//AnalystSelectionView
void Controller::updateAnalystSelectionView()
{
    analystSelectionView->clear();
    QList<QHash<QString, QVariant>> values = dbHandler->select(DBConstants::TBL_ANALYST, QString(""));
    for(int i = 0; i < values.count(); ++i){
        QHash<QString, QVariant> row = values.at(i);
        analystSelectionView->add(row.value(DBConstants::COL_ANALYST_ID).toInt(),
                                  row.value(DBConstants::COL_ANALYST_LASTNAME).toString(),
                                  row.value(DBConstants::COL_ANALYST_FIRSTNAME).toString());
    }
}

void Controller::createAnalyst()
{
    QString filter = QString("%1 = %2").arg(DBConstants::COL_EMPLOYER_NAME).arg(analystPopUp->getAnalystEmployer());
    QHash<QString, QVariant> valuesEmployer = QHash<QString, QVariant>();
    valuesEmployer.insert(DBConstants::COL_EMPLOYER_NAME, analystPopUp->getAnalystEmployer());
    int emp_ID = dbHandler->save(DBConstants::TBL_EMPLOYER, DBConstants::HASH_EMPLOYER_TYPES, valuesEmployer, filter, DBConstants::COL_EMPLOYER_ID);

    QHash<QString, QVariant> valuesAnalyst = QHash<QString, QVariant>();
    valuesAnalyst.insert(DBConstants::COL_ANALYST_LASTNAME, analystPopUp->getAnalystLastName());
    valuesAnalyst.insert(DBConstants::COL_ANALYST_FIRSTNAME, analystPopUp->getAnalystFirstName());
    valuesAnalyst.insert(DBConstants::COL_ANALYST_EMPLOYER_ID, emp_ID);
    valuesAnalyst.insert(DBConstants::COL_ANALYST_EXPERIENCE, analystPopUp->getAnalystExperience());
    dbHandler->insert(DBConstants::TBL_ANALYST, DBConstants::HASH_ANALYST_TYPES, valuesAnalyst, DBConstants::COL_ANALYST_ID);
    updateAnalystSelectionView();
    viewCon->closePopUp();
    viewCon->showMessage(tr("Created analyst"), NotificationMessage::ACCEPT);
}

void Controller::removeAnalyst(int id)
{
    dbHandler->deleteAll(DBConstants::TBL_ANALYST, QString("%1 = %2").arg(DBConstants::COL_ANALYST_ID).arg(id));
    viewCon->showMessage(tr("Deleted analyst"), NotificationMessage::ACCEPT);
    updateAnalystSelectionView();
}

void Controller::selectAnalyst(int id)
{
    analyst_ID = id;
    viewCon->showMessage(tr("Hello  ") + dbHandler->select(DBConstants::TBL_ANALYST, QString("")).
                         at(id -1).value(DBConstants::COL_ANALYST_FIRSTNAME).toString() + "! ",
                         NotificationMessage::WELCOME, NotificationMessage::LONG);
}

//MainMenuView
void Controller::createBlankRecording(){
    documentationView->showStartView(ViewType::BODY_POSTURE_VIEW);

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_WORKPLACE_NAME, tr("Autogenerated workplace"));
    workplace_ID = dbHandler->insert(DBConstants::TBL_WORKPLACE, DBConstants::HASH_WORKPLACE_TYPES, values, DBConstants::COL_WORKPLACE_ID);

    values.clear();
    values.insert(DBConstants::COL_ACTIVITY_DESCRIPTION, tr("Autogenerated activity"));
    values.insert(DBConstants::COL_ACTIVITY_WORKPLACE_ID, workplace_ID);
    activity_ID = dbHandler->insert(DBConstants::TBL_ACTIVITY, DBConstants::HASH_ACTIVITY_TYPES, values, DBConstants::COL_ACTIVITY_ID);

    QList<ViewType> prevViews = QList<ViewType>();
    prevViews.append(ViewType::WORKPLACE_VIEW);
    prevViews.append(ViewType::ACTIVITY_VIEW);

    viewCon->showView(ViewType::DOCUMENTATION_VIEW, &prevViews);
    setSelectedWorkProcess(1, AVType::BASIC);
    initializeRecording();
}

//MetaDataView
void Controller::updateMetaDataView()
{
    QHash<QString, QVariant> row = dbHandler->selectFirst(DBConstants::TBL_RECORDING, QString("%1 = %2").arg(DBConstants::COL_RECORDING_ID).arg(QString::number(recording_ID)));
    QString dtFormat = "dd.MM.yyyy hh:mm:ss.zzz";
    QDateTime begin = QDateTime();
    begin = begin.fromString(row.value(DBConstants::COL_RECORDING_START).toString(), dtFormat);
    QDateTime end = QDateTime();
    end = end.fromString(row.value(DBConstants::COL_RECORDING_END).toString(), dtFormat);
    metaDataView->setRecordTime(begin,end);
    if(!begin.isValid())
        viewCon->showMessage(begin.toString(dtFormat));

    factory_ID = row.value(DBConstants::COL_RECORDING_FACTORY_ID).toInt();
    row = dbHandler->selectFirst(DBConstants::TBL_FACTORY, QString("%1 = %2").arg(DBConstants::COL_FACTORY_ID).arg(QString::number(factory_ID)));
    metaDataView->setFactory(row.value(DBConstants::COL_FACTORY_NAME).toString(),
                             row.value(DBConstants::COL_FACTORY_STREET).toString(),
                             row.value(DBConstants::COL_FACTORY_ZIP).toInt(),
                             row.value(DBConstants::COL_FACTORY_CITY).toString(),
                             row.value(DBConstants::COL_FACTORY_COUNTRY).toString(),
                             row.value(DBConstants::COL_FACTORY_CONTACT_PERSON).toString(),
                             row.value(DBConstants::COL_FACTORY_HEADCOUNT).toInt());

    int corp_ID = row.value(DBConstants::COL_FACTORY_CORPORATION_ID).toInt();
    row = dbHandler->selectFirst(DBConstants::TBL_CORPORATION, QString("%1 = %2").arg(DBConstants::COL_CORPORATION_ID).arg(QString::number(corp_ID)));
    metaDataView->setCorporation(row.value(DBConstants::COL_CORPORATION_NAME).toString());

    int boi_ID = row.value(DBConstants::COL_CORPORATION_BRANCH_OF_INDUSTRY_ID).toInt();
    row = dbHandler->selectFirst(DBConstants::TBL_BRANCH_OF_INDUSTRY, QString("%1 = %2").arg(DBConstants::COL_BRANCH_OF_INDUSTRY_ID).arg(boi_ID));
    metaDataView->setBranchOfIndustry(row.value(DBConstants::COL_BRANCH_OF_INDUSTRY_NAME).toString(),
                                      row.value(DBConstants::COL_BRANCH_OF_INDUSTRY_DESCRIPTION).toString());
}

void Controller::saveMetaDataView()
{
    QString filter = QString("%1 = '%2'").arg(DBConstants::COL_BRANCH_OF_INDUSTRY_NAME).arg(metaDataView->getBranchOfIndustryName());
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_BRANCH_OF_INDUSTRY_NAME, metaDataView->getBranchOfIndustryName());
    values.insert(DBConstants::COL_BRANCH_OF_INDUSTRY_DESCRIPTION, metaDataView->getBranchOfIndustryDescription());
    int boi_ID = dbHandler->save(DBConstants::TBL_BRANCH_OF_INDUSTRY, DBConstants::HASH_BRANCH_OF_INDUSTRY_TYPES, values, filter, DBConstants::COL_BRANCH_OF_INDUSTRY_ID);

    filter = QString("%1 = '%2'").arg(DBConstants::COL_CORPORATION_NAME).arg(metaDataView->getCorporationName());
    values.clear();
    values.insert(DBConstants::COL_CORPORATION_NAME, metaDataView->getCorporationName());
    values.insert(DBConstants::COL_CORPORATION_BRANCH_OF_INDUSTRY_ID, boi_ID);
    int corp_ID = dbHandler->save(DBConstants::TBL_CORPORATION, DBConstants::HASH_CORPORATION_TYPES, values, filter, DBConstants::COL_CORPORATION_ID);

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
    factory_ID = dbHandler->save(DBConstants::TBL_FACTORY, DBConstants::HASH_FACTORY_TYPES, values, filter, DBConstants::COL_FACTORY_ID);


    filter = QString("");
    QString dtFormat = "dd.MM.yyyy hh:mm:ss.zzz";
    values.clear();
    values.insert(DBConstants::COL_RECORDING_START, metaDataView->getRecordTimeBegin().toString(dtFormat));
    values.insert(DBConstants::COL_RECORDING_END, metaDataView->getRecordTimeEnd().toString(dtFormat));
    values.insert(DBConstants::COL_RECORDING_FACTORY_ID, factory_ID);
    values.insert(DBConstants::COL_RECORDING_ANALYST_ID, analyst_ID);
    dbHandler->save(DBConstants::TBL_RECORDING, DBConstants::HASH_RECORDING_TYPES, values, filter, DBConstants::COL_RECORDING_ID);
}

//WorkplacesView
void Controller::updateWorkplacesView()
{
    workplaceListView->clear();
    const QString tbl = DBConstants::TBL_WORKPLACE;
    QList<QHash<QString, QVariant>> values = dbHandler->select(tbl, QString(""));
    for(int i = 0; i < values.count(); ++i)
        {
            QHash<QString, QVariant> row = values.at(i);
            workplaceListView->addWorkplace(row.value(DBConstants::COL_WORKPLACE_ID).toInt(),
                                            row.value(DBConstants::COL_WORKPLACE_NAME).toString(),
                                            row.value(DBConstants::COL_WORKPLACE_DESCRIPTION).toString(),
                                            row.value(DBConstants::COL_WORKPLACE_CODE).toString());
        }
}

//WorkplaceView
void Controller::updateWorkplaceView(int id)
{
    workplace_ID = id;
    QString tbl = DBConstants::TBL_WORKPLACE;
    QHash<QString, QVariant> row = dbHandler->selectFirst(tbl, QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_ID).arg(QString::number(id)));

    workplaceView->setName(row.value(DBConstants::COL_WORKPLACE_NAME).toString());
    workplaceView->setDescription(row.value(DBConstants::COL_WORKPLACE_DESCRIPTION).toString());
    workplaceView->setCode(row.value(DBConstants::COL_WORKPLACE_CODE).toString());
    workplaceView->setWomanPercentage(row.value(DBConstants::COL_WORKPLACE_PERCENTAGE_WOMAN).toInt());

    QTime basicTime = QTime(0, 0);
    basicTime = basicTime.addSecs(row.value(DBConstants::COL_WORKPLACE_BASIC_TIME).toInt());
    QTime setupTime = QTime(0, 0);
    setupTime = setupTime.addSecs(row.value(DBConstants::COL_WORKPLACE_SETUP_TIME).toInt());
    QTime restTime = QTime(0, 0);
    restTime = restTime.addSecs(row.value(DBConstants::COL_WORKPLACE_REST_TIME).toInt());
    QTime allowanceTime = QTime(0, 0);
    allowanceTime = allowanceTime.addSecs(row.value(DBConstants::COL_WORKPLACE_ALLOWANCE_TIME).toInt());
    QTime cycleTime = QTime(0, 0);
    cycleTime = cycleTime.addSecs(row.value(DBConstants::COL_WORKPLACE_CYCLE_TIME).toInt());

    workplaceView->setBasicTime(basicTime);
    workplaceView->setSetupTime(setupTime);
    workplaceView->setRestTime(restTime);
    workplaceView->setAllowanceTime(allowanceTime);
    workplaceView->setCycleTime(cycleTime);

    tbl = DBConstants::TBL_LINE;
    row = dbHandler->selectFirst(tbl, QString("%1 = %2").arg(DBConstants::COL_LINE_ID).arg(row.value(DBConstants::COL_WORKPLACE_LINE_ID).toString()));
    if(!row.isEmpty()){
            workplaceView->setLine(row.value(DBConstants::COL_LINE_NAME).toString(),
                                   row.value(DBConstants::COL_LINE_DESCRIPTION).toString());
        }
    else
        workplaceView->setLine("","");

    tbl = DBConstants::TBL_COMMENT;
    row = dbHandler->selectFirst(tbl, QString("%1 = %2").arg(DBConstants::COL_COMMENT_WORKPLACE_ID).arg(workplace_ID));
    if(!row.isEmpty()){
            workplaceView->setComment(row.value(DBConstants::COL_COMMENT_PROBLEM_NAME).toString(),
                                      row.value(DBConstants::COL_COMMENT_MEASURE_NAME).toString());
        }
    else
        workplaceView->setComment("","");

}

void Controller::updateWorkplaceView()
{
    updateWorkplaceView(workplace_ID);
}

int Controller::createWorkplace()
{
    QString filter = QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_ID).arg(QString::number(0));

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    int id = dbHandler->save(DBConstants::TBL_WORKPLACE, DBConstants::HASH_WORKPLACE_TYPES, values, filter, DBConstants::COL_WORKPLACE_ID);
    updateWorkplaceView(id);
    saveRecordingObservesWorkplace(id);
    return id;
}

void Controller::saveWorkplaceView()
{
    saveWorkplace(workplace_ID);
}

void Controller::createWorkplacePopup()
{

    QString filter = QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_ID).arg(QString::number(0));
    QHash<QString, QVariant> values = QHash<QString, QVariant>();

    values.insert(DBConstants::COL_WORKPLACE_NAME, workplacePopUp->getName());
    values.insert(DBConstants::COL_WORKPLACE_DESCRIPTION, workplacePopUp->getDescription());
    values.insert(DBConstants::COL_WORKPLACE_CODE, workplacePopUp->getCode());
    values.insert(DBConstants::COL_WORKPLACE_PERCENTAGE_WOMAN, workplacePopUp->getWomanPercentage());
    values.insert(DBConstants::COL_WORKPLACE_BASIC_TIME, qTimeToSeconds(workplacePopUp->getBasicTime()));
    values.insert(DBConstants::COL_WORKPLACE_REST_TIME, qTimeToSeconds(workplacePopUp->getRestTime()));
    values.insert(DBConstants::COL_WORKPLACE_ALLOWANCE_TIME, qTimeToSeconds(workplacePopUp->getAllowanceTime()));
    values.insert(DBConstants::COL_WORKPLACE_SETUP_TIME, qTimeToSeconds(workplacePopUp->getSetupTime()));
    values.insert(DBConstants::COL_WORKPLACE_CYCLE_TIME, qTimeToSeconds(workplacePopUp->getCycleTime()));

    dbHandler->save(DBConstants::TBL_WORKPLACE, DBConstants::HASH_WORKPLACE_TYPES, values, filter, DBConstants::COL_WORKPLACE_ID);

    // TODO update rotationgroupview workplaces
    viewCon->closePopUp();
    viewCon->showMessage(tr("Created new workplace"), NotificationMessage::ACCEPT);

}

void Controller::createWorkplace(QHash<QString, QVariant> values, QList<QHash<QString, QVariant>> activityValues){
    int workplace_ID = dbHandler->insert(DBConstants::TBL_WORKPLACE, DBConstants::HASH_WORKPLACE_TYPES, values,DBConstants::COL_WORKPLACE_ID);

    for(int i = 0; i < activityValues.size(); ++i){
        QHash<QString, QVariant> curValues = activityValues.at(i);
        if(curValues.contains(DBConstants::COL_PRODUCT_NAME)){
            QString filter = QString("%1 = '%2'").arg(DBConstants::COL_PRODUCT_NAME).arg(curValues.value(DBConstants::COL_PRODUCT_NAME).toString());
            QHash<QString, QVariant> productValues = dbHandler->selectFirst(DBConstants::TBL_PRODUCT, filter);
            if(!productValues.isEmpty()){
                curValues.insert(DBConstants::COL_ACTIVITY_PRODUCT_ID, productValues.value(DBConstants::COL_PRODUCT_ID));
            }
            curValues.remove(DBConstants::COL_PRODUCT_NAME);
        }
        curValues.insert(DBConstants::COL_ACTIVITY_WORKPLACE_ID, workplace_ID);
        dbHandler->insert(DBConstants::TBL_ACTIVITY, DBConstants::HASH_ACTIVITY_TYPES, curValues, DBConstants::COL_ACTIVITY_ID);
    }
}

void Controller::deleteWorkplace(int id)
{
    QString tbl = DBConstants::TBL_WORKPLACE;
    workplace_ID = id;
    dbHandler->deleteAll(tbl, QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_ID).arg(QString::number(id)));

    QList<QHash<QString, QVariant>> values = dbHandler->select(DBConstants::TBL_ACTIVITY, QString("%1 = %2").arg(DBConstants::COL_ACTIVITY_WORKPLACE_ID).arg(id));
    for(int i = 0; i < values.count(); ++i)
        deleteActivity(values.at(i).value(DBConstants::COL_ACTIVITY_ID).toInt());

    dbHandler->deleteAll(DBConstants::TBL_COMMENT, QString("%1 = %2").arg(DBConstants::COL_COMMENT_WORKPLACE_ID).arg(id));
    viewCon->showMessage(tr("Deleted workplace"), NotificationMessage::ACCEPT);
    updateWorkplacesView();
    deleteRecordingOberservesWorkplace(id);
}


//Line

void Controller::updateLineView()
{
    /*lineView->clear();
    QString tbl = DBConstants::TBL_LINE;
    QList<QHash<QString, QVariant>> values = dbHandler->select(tbl, QString(""));
    for(int i = 0; i < values.count(); ++i)
        {
            QHash<QString, QVariant> row = values.at(i);
            lineView->addLine(row.value(DBConstants::COL_LINE_ID).toInt(),
                              row.value(DBConstants::COL_LINE_NAME).toString());
        }
    QHash<QString, QVariant> row = dbHandler->selectFirst(DBConstants::TBL_WORKPLACE, QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_ID).arg(workplace_ID));
    lineView->setSelectedLine(row.value(DBConstants::COL_WORKPLACE_LINE_ID).toInt());*/
}

int Controller::saveSelectedLine(int id)
{
    QString tbl = DBConstants::TBL_WORKPLACE;
    QString filter = QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_ID).arg(workplace_ID);
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_WORKPLACE_LINE_ID, id);
    return dbHandler->save(tbl, DBConstants::HASH_WORKPLACE_TYPES, values, filter, DBConstants::COL_WORKPLACE_ID);
}

int Controller::createLine()
{
    /*QString tbl = DBConstants::TBL_LINE;
    QString filter = QString("%1 = %2").arg(DBConstants::COL_LINE_ID).arg(QString::number(0));
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_LINE_NAME, lineView->getName());
    values.insert(DBConstants::COL_LINE_DESCRIPTION, lineView->getDescription());
    values.insert(DBConstants::COL_LINE_NUMBER_OF_WORKPLACES, lineView->getWorkplaceCount());
    values.insert(DBConstants::COL_LINE_FACTORY_ID, factory_ID);
    int lineID = dbHandler->save(tbl, DBConstants::HASH_LINE_TYPES, values, filter, DBConstants::COL_LINE_ID);
    saveRecordingObservesLine(lineID);
    viewCon->showMessage(tr("Created line"), NotificationMessage::ACCEPT);
    updateLineView();
    return lineID;*/
}

void Controller::deleteLine(int id)
{
    deleteRecordingObservesLine(id);
    QString filter = QString("%1 = %2").arg(DBConstants::COL_LINE_ID).arg(QString::number(id));
    dbHandler->deleteAll(DBConstants::TBL_LINE, filter);
    filter = QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_LINE_ID).arg(QString::number(id));
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_WORKPLACE_LINE_ID, 0);
    dbHandler->update(DBConstants::TBL_WORKPLACE, DBConstants::HASH_WORKPLACE_TYPES, values, filter);
    viewCon->showMessage(tr("Deleted line"), NotificationMessage::ACCEPT);
    updateLineView();
}

//Product
void Controller::updateProductView()
{
    productView->clear();
    QString tbl = DBConstants::TBL_PRODUCT;
    QList<QHash<QString, QVariant>> values = dbHandler->select(tbl, QString(""));
    for(int i = 0; i < values.count(); ++i){
            QHash<QString, QVariant> row = values.at(i);
            productView->addProduct(row.value(DBConstants::COL_PRODUCT_ID).toInt(),
                                    row.value(DBConstants::COL_PRODUCT_NAME).toString(),
                                    row.value(DBConstants::COL_PRODUCT_NUMBER).toString(),
                                    row.value(DBConstants::COL_PRODUCT_TOTAL_PERCENTAGE).toInt());
        }
}

void Controller::createProduct()
{
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_PRODUCT_NAME, productView->getName());
    values.insert(DBConstants::COL_PRODUCT_NUMBER, productView->getNumber());
    values.insert(DBConstants::COL_PRODUCT_TOTAL_PERCENTAGE, productView->getTotalPercentage());
    dbHandler->insert(DBConstants::TBL_PRODUCT, DBConstants::HASH_PRODUCT_TYPES, values, DBConstants::COL_PRODUCT_ID);
    viewCon->showMessage(tr("Created new product"), NotificationMessage::ACCEPT);
    updateProductView();
}

void Controller::createProductPopUp()
{
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_PRODUCT_NAME, productPopUp->getName());
    values.insert(DBConstants::COL_PRODUCT_NUMBER, productPopUp->getNumber());
    values.insert(DBConstants::COL_PRODUCT_TOTAL_PERCENTAGE, productPopUp->getTotalPercentage());
    dbHandler->insert(DBConstants::TBL_PRODUCT, DBConstants::HASH_PRODUCT_TYPES, values, DBConstants::COL_PRODUCT_ID);
    viewCon->closePopUp();
    viewCon->showMessage(tr("Created new product"), NotificationMessage::ACCEPT);
    updateActivityView();
}

void Controller::createProduct(QHash<QString, QVariant> values){
    dbHandler->insert(DBConstants::TBL_PRODUCT, DBConstants::HASH_PRODUCT_TYPES, values, DBConstants::COL_PRODUCT_ID);
}

void Controller::deleteProduct(int id)
{
    dbHandler->deleteAll(DBConstants::TBL_PRODUCT, QString("%1 = %2").arg(DBConstants::COL_PRODUCT_ID).arg(QString::number(id)));
    viewCon->showMessage(tr("Deleted product"), NotificationMessage::ACCEPT);
    updateProductView();
}

//Equipment View
void Controller::updateEquipmentView()
{
    equipmentView->clear();
    QString tbl = DBConstants::TBL_EQUIPMENT;
    QList<QHash<QString, QVariant>> values = dbHandler->select(tbl, QString(""));
    for(int i = 0; i < values.count(); ++i)
        {
            QHash<QString, QVariant> row = values.at(i);
            equipmentView->addEquipment(row.value(DBConstants::COL_EQUIPMENT_ID).toInt(),
                                        row.value(DBConstants::COL_EQUIPMENT_NAME).toString(),
                                        row.value(DBConstants::COL_EQUIPMENT_RECOIL_COUNT).toInt(),
                                        row.value(DBConstants::COL_EQUIPMENT_RECOIL_INTENSITY).toInt(),
                                        row.value(DBConstants::COL_EQUIPMENT_VIBRATION_COUNT).toInt(),
                                        row.value(DBConstants::COL_EQUIPMENT_VIBRATION_INTENSITY).toInt());
        }
}

void Controller::createEquipment()
{
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_EQUIPMENT_NAME, equipmentView->getName());
    values.insert(DBConstants::COL_EQUIPMENT_RECOIL_COUNT, equipmentView->getRecoilCount());
    values.insert(DBConstants::COL_EQUIPMENT_RECOIL_INTENSITY, equipmentView->getRecoilIntensity());
    values.insert(DBConstants::COL_EQUIPMENT_VIBRATION_COUNT, equipmentView->getVibrationCount());
    values.insert(DBConstants::COL_EQUIPMENT_VIBRATION_INTENSITY, equipmentView->getVibrationIntensity());
    dbHandler->insert(DBConstants::TBL_EQUIPMENT, DBConstants::HASH_EQUIPMENT_TYPES, values, DBConstants::COL_EQUIPMENT_ID);
    viewCon->showMessage(tr("Created new equipment"), NotificationMessage::ACCEPT);
    updateEquipmentView();
}

void Controller::deleteEquipment(int id)
{
    dbHandler->deleteAll(DBConstants::TBL_EQUIPMENT, QString("%1 = %2").arg(DBConstants::COL_EQUIPMENT_ID).arg(id));
    viewCon->showMessage(tr("Deleted equipment"), NotificationMessage::ACCEPT);
    updateEquipmentView();
}

void Controller::createEquipmentPopUp()
{
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_EQUIPMENT_NAME, equipmentPopUp->getName());
    values.insert(DBConstants::COL_EQUIPMENT_RECOIL_COUNT, equipmentPopUp->getRecoilCount());
    values.insert(DBConstants::COL_EQUIPMENT_RECOIL_INTENSITY, equipmentPopUp->getRecoilIntensity());
    values.insert(DBConstants::COL_EQUIPMENT_VIBRATION_COUNT, equipmentPopUp->getVibrationCount());
    values.insert(DBConstants::COL_EQUIPMENT_VIBRATION_INTENSITY, equipmentPopUp->getVibrationIntensity());
    dbHandler->insert(DBConstants::TBL_EQUIPMENT, DBConstants::HASH_EQUIPMENT_TYPES, values, DBConstants::COL_EQUIPMENT_ID);
    viewCon->showMessage(tr("Created new Equipment"), NotificationMessage::ACCEPT);
    viewCon->closePopUp();
}
void Controller::createEquipment(QHash<QString, QVariant> values){
    dbHandler->insert(DBConstants::TBL_EQUIPMENT, DBConstants::HASH_EQUIPMENT_TYPES, values, DBConstants::COL_EQUIPMENT_ID);
}

//ActivityView
void Controller::updateActivityView()
{
    activityView->clearProducts();
    QString tbl = DBConstants::TBL_PRODUCT;
    QList<QHash<QString, QVariant>> values = dbHandler->select(tbl, QString(""));
    for(int i = 0; i < values.count(); ++i)
        {
            QHash<QString, QVariant> row = values.at(i);
            activityView->addProduct(row.value(DBConstants::COL_PRODUCT_ID).toInt(),
                                     row.value(DBConstants::COL_PRODUCT_NAME).toString(),
                                     row.value(DBConstants::COL_PRODUCT_NUMBER).toString());
        }
    updateActivityViewActivities();
}

void Controller::updateActivityViewActivities()
{
    activityView->clearActivities();
    QString tbl = DBConstants::TBL_ACTIVITY;
    QList<QHash<QString, QVariant>> values = dbHandler->select(tbl, QString("%1 == %2").arg(DBConstants::COL_ACTIVITY_WORKPLACE_ID).arg(workplace_ID));

    for(int i = 0; i < values.count(); ++i){
            QHash<QString, QVariant> row = values.at(i);
            activityView->addActivity(row.value(DBConstants::COL_ACTIVITY_ID).toInt(),
                                      row.value(DBConstants::COL_ACTIVITY_DESCRIPTION).toString(),
                                      row.value(DBConstants::COL_ACTIVITY_REPETITIONS).toInt());
        }
}


void Controller::createActivity()
{
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_ACTIVITY_DESCRIPTION, activityView->getDescription());
    values.insert(DBConstants::COL_ACTIVITY_PRODUCT_ID, activityView->getSelectedProduct());
    values.insert(DBConstants::COL_ACTIVITY_REPETITIONS, activityView->getRepetitions());
    values.insert(DBConstants::COL_ACTIVITY_WORKPLACE_ID, workplace_ID);
    dbHandler->insert(DBConstants::TBL_ACTIVITY, DBConstants::HASH_ACTIVITY_TYPES, values, DBConstants::COL_ACTIVITY_ID);
    viewCon->showMessage(tr("Created activity"), NotificationMessage::ACCEPT);
    updateActivityViewActivities();
}

void Controller::deleteActivity(int id)
{
    dbHandler->deleteAll(DBConstants::TBL_ACTIVITY, QString("%1 = %2").arg(DBConstants::COL_ACTIVITY_ID).arg(id));
    deleteWorkProcesses(id);
    viewCon->showMessage(tr("Deleted activity"), NotificationMessage::ACCEPT);
    updateActivityViewActivities();
}

void Controller::selectActivity(int id)
{
    activity_ID = id;
    workProcessTypeChanged(AVType::BASIC);
    initializeRecording();
}

void Controller::updateActivityPopUp(int id)
{
    activityPopUp->clearProducts();

    QString tbl = DBConstants::TBL_ACTIVITY;
    QHash<QString, QVariant> row = dbHandler->selectFirst(tbl, QString("%1 = %2").arg(DBConstants::COL_ACTIVITY_ID).arg(id));
    if(!row.isEmpty())
        {
            activity_ID = id;

            tbl = DBConstants::TBL_PRODUCT;
            QList<QHash<QString, QVariant>> products = dbHandler->select(tbl, QString(""));
            for(int i = 0; i < products.count(); ++i){
                    QHash<QString, QVariant> product = products.at(i);
                    activityPopUp->addProduct(product.value(DBConstants::COL_PRODUCT_ID).toInt(),
                                              product.value(DBConstants::COL_PRODUCT_NAME).toString(),
                                              product.value(DBConstants::COL_PRODUCT_NUMBER).toString());
                }

            activityPopUp->setActivity(row.value(DBConstants::COL_ACTIVITY_DESCRIPTION).toString(),
                                       row.value(DBConstants::COL_ACTIVITY_REPETITIONS).toInt(),
                                       row.value(DBConstants::COL_ACTIVITY_PRODUCT_ID).toInt());
        }
}

void Controller::updateActivity()
{
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_ACTIVITY_ID, activity_ID);
    values.insert(DBConstants::COL_ACTIVITY_DESCRIPTION, activityPopUp->getDescription());
    values.insert(DBConstants::COL_ACTIVITY_REPETITIONS, activityPopUp->getRepetitions());
    values.insert(DBConstants::COL_ACTIVITY_PRODUCT_ID, activityPopUp->getSelectedProduct());
    dbHandler->update(DBConstants::TBL_ACTIVITY, DBConstants::HASH_ACTIVITY_TYPES, values, QString("%1 = %2").arg(DBConstants::COL_ACTIVITY_ID).arg(activity_ID));
    viewCon->showMessage(tr("Updated activity"), NotificationMessage::ACCEPT);
    viewCon->closePopUp();
    updateActivityViewActivities();
}



//CommentView
void Controller::updateComment()
{
    QString tbl = DBConstants::TBL_COMMENT;
    QString filter = QString("%1 = %2").arg(DBConstants::COL_COMMENT_WORKPLACE_ID).arg(workplace_ID);
    QHash<QString, QVariant> row = dbHandler->selectFirst(tbl, filter);
    commentView->setComment(row.value(DBConstants::COL_COMMENT_PROBLEM_NAME).toString(),
                            row.value(DBConstants::COL_COMMENT_PROBLEM_DESCRIPTION).toString(),
                            row.value(DBConstants::COL_COMMENT_MEASURE_NAME).toString(),
                            row.value(DBConstants::COL_COMMENT_MEASURE_DESCRIPTION).toString(),
                            row.value(DBConstants::COL_COMMENT_WORKER_PERCEPTION).toString());
}

int Controller::saveComment()
{
    QString filter = QString("%1 = %2").arg(DBConstants::COL_COMMENT_WORKPLACE_ID).arg(workplace_ID);

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_COMMENT_PROBLEM_NAME, commentView->getProblemName());
    values.insert(DBConstants::COL_COMMENT_PROBLEM_DESCRIPTION, commentView->getProblemDescription());
    values.insert(DBConstants::COL_COMMENT_MEASURE_NAME, commentView->getMeasureName());
    values.insert(DBConstants::COL_COMMENT_MEASURE_DESCRIPTION, commentView->getMeasureDescription());
    values.insert(DBConstants::COL_COMMENT_WORKER_PERCEPTION, commentView->getWorkerPerception());
    values.insert(DBConstants::COL_COMMENT_WORKPLACE_ID, workplace_ID);
    return dbHandler->save(DBConstants::TBL_COMMENT, DBConstants::HASH_COMMENT_TYPES, values, filter, DBConstants::COL_COMMENT_ID);
}

//TransportationView
void Controller::updateTransportationView()
{
    transportationView->clear();
    QString tbl = DBConstants::TBL_TRANSPORTATION;
    QList<QHash<QString, QVariant>> values = dbHandler->select(tbl, QString(""));
    for(int i = 0; i < values.count(); ++i){
        QHash<QString, QVariant> row = values.at(i);
        transportationView->addTransportation(row.value(DBConstants::COL_TRANSPORTATION_ID).toInt(),
                                                  row.value(DBConstants::COL_TRANSPORTATION_NAME).toString(),
                                                  row.value(DBConstants::COL_TRANSPORTATION_EMPTY_WEIGHT).toInt(),
                                                  row.value(DBConstants::COL_TRANSPORTATION_MAX_LOAD).toInt(),
                                                  row.value(DBConstants::COL_TRANSPORTATION_FIXED_ROLLER).toBool(),
                                                  row.value(DBConstants::COL_TRANSPORTATION_BRAKES).toBool());
    }
}

void Controller::createTransportation()
{
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_TRANSPORTATION_NAME, transportationView->getName());
    values.insert(DBConstants::COL_TRANSPORTATION_EMPTY_WEIGHT, transportationView->getWeight());
    values.insert(DBConstants::COL_TRANSPORTATION_MAX_LOAD, transportationView->getMaxLoad());
    values.insert(DBConstants::COL_TRANSPORTATION_BRAKES, transportationView->hasBrakes());
    values.insert(DBConstants::COL_TRANSPORTATION_FIXED_ROLLER, transportationView->hasFixedRoller());
    int id = dbHandler->insert(DBConstants::TBL_TRANSPORTATION, DBConstants::HASH_TRANSPORTATION_TYPES, values, DBConstants::COL_TRANSPORTATION_ID);
    transportationView->addTransportation(id, values.value(DBConstants::COL_TRANSPORTATION_NAME).toString(),
                                          values.value(DBConstants::COL_TRANSPORTATION_EMPTY_WEIGHT).toInt(),
                                          values.value(DBConstants::COL_TRANSPORTATION_MAX_LOAD).toInt(),
                                          values.value(DBConstants::COL_TRANSPORTATION_FIXED_ROLLER).toBool(),
                                          values.value(DBConstants::COL_TRANSPORTATION_BRAKES).toBool());
    viewCon->showMessage(tr("Created new transportation"), NotificationMessage::ACCEPT);
}

void Controller::createTransportationPopUp()
{
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_TRANSPORTATION_NAME, transportationPopUp->getName());
    values.insert(DBConstants::COL_TRANSPORTATION_EMPTY_WEIGHT, transportationPopUp->getWeight());
    values.insert(DBConstants::COL_TRANSPORTATION_MAX_LOAD, transportationPopUp->getMaxLoad());
    values.insert(DBConstants::COL_TRANSPORTATION_BRAKES, transportationPopUp->getHasBrakes());
    values.insert(DBConstants::COL_TRANSPORTATION_FIXED_ROLLER, transportationPopUp->getHasFixedRoller());
    dbHandler->insert(DBConstants::TBL_TRANSPORTATION, DBConstants::HASH_TRANSPORTATION_TYPES, values, DBConstants::COL_TRANSPORTATION_ID);
    viewCon->closePopUp();
    viewCon->showMessage(tr("Created new transporation"), NotificationMessage::ACCEPT);
}

void Controller::createTransportation(QHash<QString, QVariant> values){
    dbHandler->insert(DBConstants::TBL_TRANSPORTATION, DBConstants::HASH_TRANSPORTATION_TYPES, values, DBConstants::COL_TRANSPORTATION_ID);
}

void Controller::deleteTransportation(int id)
{
    dbHandler->deleteAll(DBConstants::TBL_TRANSPORTATION, QString("%1 = %2").arg(DBConstants::COL_TRANSPORTATION_ID).arg(id));
    viewCon->showMessage(tr("Deleted transportation"), NotificationMessage::ACCEPT);
    updateTransportationView();
}

//EMPLOYEE
void Controller::initializeEmployees(){
    QList<QHash<QString, QVariant>> values = dbHandler->select(DBConstants::TBL_EMPLOYEE, QString(""));
    for(int i = 0; i < values.count(); ++i)
        emit createdEmployee(values.at(i));
}

void Controller::createEmployee(QHash<QString, QVariant> values){
    QHash<QString, QVariant> bmValues = QHash<QString, QVariant>();
    int bmID = dbHandler->insert(DBConstants::TBL_BODY_MEASUREMENT, DBConstants::HASH_BODY_MEASUREMENT_TYPES, bmValues, DBConstants::COL_BODY_MEASUREMENT_ID);
    values.insert(DBConstants::COL_EMPLOYEE_BODY_MEASUREMENT_ID, bmID);
    int id = dbHandler->insert(DBConstants::TBL_EMPLOYEE, DBConstants::HASH_EMPLOYEE_TYPES, values, DBConstants::COL_EMPLOYEE_ID);
    values.insert(DBConstants::COL_EMPLOYEE_ID, id);
    emit createdEmployee(values);
}

void Controller::createEmployee(QHash<QString, QVariant> values, QHash<QString, QVariant> bodyMeasurementValues){
    int bmID = dbHandler->insert(DBConstants::TBL_BODY_MEASUREMENT, DBConstants::HASH_BODY_MEASUREMENT_TYPES, bodyMeasurementValues, DBConstants::COL_BODY_MEASUREMENT_ID);
    values.insert(DBConstants::COL_EMPLOYEE_BODY_MEASUREMENT_ID, bmID);
    int empID = dbHandler->insert(DBConstants::TBL_EMPLOYEE, DBConstants::HASH_EMPLOYEE_TYPES, values, DBConstants::COL_EMPLOYEE_ID);
    values.insert(DBConstants::COL_EMPLOYEE_ID, empID);
    emit createEmployee(values);
}

void Controller::deleteEmployee(int id){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_EMPLOYEE_ID).arg(id);
    QHash<QString, QVariant> values = dbHandler->selectFirst(DBConstants::TBL_EMPLOYEE, filter);
    dbHandler->deleteAll(DBConstants::TBL_EMPLOYEE, filter);
    emit removedEmployee(id);
    filter = QString("%1 = %2").arg(DBConstants::COL_EMPLOYEE_BODY_MEASUREMENT_ID).arg(values.value(DBConstants::COL_EMPLOYEE_BODY_MEASUREMENT_ID).toInt());
    dbHandler->deleteAll(DBConstants::TBL_BODY_MEASUREMENT, filter);
}

void Controller::selectEmployee(int id){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_EMPLOYEE_ID).arg(id);
    QHash<QString, QVariant> values = dbHandler->selectFirst(DBConstants::TBL_EMPLOYEE, filter);
    employee_ID = id;
    bodyMeasurement_ID = values.value(DBConstants::COL_EMPLOYEE_BODY_MEASUREMENT_ID).toInt();
    emit selectedEmployee(values);
    filter = QString("%1 = %2").arg(DBConstants::COL_BODY_MEASUREMENT_ID).arg(bodyMeasurement_ID);
    values = dbHandler->selectFirst(DBConstants::TBL_BODY_MEASUREMENT, filter);
    emit selectedBodyMeasurement(values);
}

void Controller::saveEmployee(QHash<QString, QVariant> values){
    values.insert(DBConstants::COL_EMPLOYEE_ID, employee_ID);
    QString filter = QString("%1 = %2").arg(DBConstants::COL_EMPLOYEE_ID, employee_ID).arg(employee_ID);
    dbHandler->save(DBConstants::TBL_EMPLOYEE, DBConstants::HASH_EMPLOYEE_TYPES, values, filter, DBConstants::COL_EMPLOYEE_ID);
    emit updatedEmployee(values);
}


//BodyMeasurement
void Controller::saveBodyMeasurement(QHash<QString, QVariant> values){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_BODY_MEASUREMENT_ID).arg(bodyMeasurement_ID);
    dbHandler->save(DBConstants::TBL_BODY_MEASUREMENT, DBConstants::HASH_BODY_MEASUREMENT_TYPES, values, filter, DBConstants::COL_BODY_MEASUREMENT_ID);
}


//WORKPROCESS
int Controller::createWorkprocess(AVType type, const QTime &start, const QTime &end)
{
    QString filter = QString("%1 = %2 AND %3 = %4").arg(DBConstants::COL_WORK_PROCESS_ACTIVITY_ID).arg(activity_ID).arg(DBConstants::COL_WORK_PROCESS_TYPE).arg(type);

    int id = dbHandler->getNextID(DBConstants::TBL_WORK_PROCESS, DBConstants::COL_WORK_PROCESS_ID, filter);
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_WORK_PROCESS_ID, id);
    values.insert(DBConstants::COL_WORK_PROCESS_ACTIVITY_ID, activity_ID);
    values.insert(DBConstants::COL_WORK_PROCESS_TYPE, type);
    values.insert(DBConstants::COL_WORK_PROCESS_BEGIN, start.toString());
    values.insert(DBConstants::COL_WORK_PROCESS_END, end.toString());
    dbHandler->insert(DBConstants::TBL_WORK_PROCESS, DBConstants::HASH_WORK_PROCESS_TYPES, values, DBConstants::COL_WORK_PROCESS_ID);
    if(type == workprocess_Type && id == workprocess_ID + 1 )
        timerViewController->setHasNextAV(true);
    gantTimerView->add(id, type, start, end);
    if(workprocess_ID == 0)
        {
            setSelectedWorkProcess(id, type);
        }
    return id;
}


void Controller::setSelectedWorkProcess(int id , AVType type)
{
    if(workplace_ID > 0)
        {
            saveCurrentWorkProcess();
            save(documentationView->getCurrentView());
        }
    QString absFilter = QString("%1 = %2 AND %3 = %4 AND %5 = %6").arg(DBConstants::COL_WORK_PROCESS_ACTIVITY_ID).arg(activity_ID).arg(DBConstants::COL_WORK_PROCESS_TYPE).arg(type).arg(DBConstants::COL_WORK_PROCESS_ID);
    QString filter = absFilter.arg(id);

    QString tbl = DBConstants::TBL_WORK_PROCESS;
    QHash<QString, QVariant> row = dbHandler->selectFirst(tbl, filter);
    if(!row.isEmpty()){
        bodyPosture_ID = row.value(DBConstants::COL_WORK_PROCESS_POSTURE_ID).toInt();
        appliedforce_ID = row.value(DBConstants::COL_WORK_PROCESS_APPLIED_FORCE_ID).toInt();
        loadhandling_ID = row.value(DBConstants::COL_WORK_PROCESS_LOAD_HANDLING_ID).toInt();
        workcondition_ID = row.value(DBConstants::COL_WORK_PROCESS_CONDITION_ID).toInt();
        QTime duration = QTime(0,0).addSecs(row.value(DBConstants::COL_WORK_PROCESS_BEGIN).toTime().secsTo(row.value(DBConstants::COL_WORK_PROCESS_END).toTime()));
        workprocess_ID = id;
        workprocess_Type = type;
        update(documentationView->getCurrentView());
        timerViewController->setSelectedType(type);
        timerViewController->setSelectedAV(id, duration);
        gantTimerView->setSelectedWorkProcess(id, type, row.value(DBConstants::COL_WORK_PROCESS_FREQUENCY).toInt());
        timerViewController->setHasPreviousAV(!dbHandler->isSelectEmpty(tbl, absFilter.arg(id - 1)));
        timerViewController->setHasNextAV(!dbHandler->isSelectEmpty(tbl, absFilter.arg(id + 1)));

    }
    else{
        timerViewController->setSelectedType(type);
        timerViewController->setSelectedAV(0, QTime(0,0));
        timerViewController->setSelectedAVNone();
        timerViewController->setHasPreviousAV(false);
        timerViewController->setHasNextAV(false);
        workprocess_ID = 0;
    }
}

void Controller::selectNextWorkProcess()
{
    setSelectedWorkProcess(workprocess_ID + 1, workprocess_Type);
}

void Controller::selectPreviousWorkProcess()
{
    setSelectedWorkProcess(workprocess_ID - 1, workprocess_Type);
}

void Controller::workProcessTypeChanged(AVType type)
{
    setSelectedWorkProcess(1, type);
}

void Controller::resetWorkProcesses()
{
    deleteWorkProcesses(activity_ID);
    setSelectedWorkProcess(1, AVType::BASIC);
    initializeRecording();
}

void Controller::saveCurrentWorkProcess()
{
    QString filter = QString("%1 = %2 AND %3 = %4 AND %5 = %6").arg(DBConstants::COL_WORK_PROCESS_ACTIVITY_ID).arg(activity_ID).arg(DBConstants::COL_WORK_PROCESS_ID).arg(workprocess_ID).arg(DBConstants::COL_WORK_PROCESS_TYPE).arg(workprocess_Type);

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_WORK_PROCESS_DESCRIPTION, workProcessMetaDataView->getDescription());
    values.insert(DBConstants::COL_WORK_PROCESS_FREQUENCY, gantTimerView->getFrequenz());
    values.insert(DBConstants::COL_WORK_PROCESS_MTM_CODE, workProcessMetaDataView->getMTMCode());
    values.insert(DBConstants::COL_WORK_PROCESS_WORKING_HEIGHT, workProcessMetaDataView->getWorkingHeight());
    values.insert(DBConstants::COL_WORK_PROCESS_DISTANCE, workProcessMetaDataView->getDistance());
    values.insert(DBConstants::COL_WORK_PROCESS_IMPULSE_COUNT, workProcessMetaDataView->getImpulseCount());
    values.insert(DBConstants::COL_WORK_PROCESS_IMPULSE_INTENSITY, workProcessMetaDataView->getImpulseIntensity());
    values.insert(DBConstants::COL_WORK_PROCESS_EQUIPMENT_ID, workProcessMetaDataView->getSelectedEquipment());
    values.insert(DBConstants::COL_WORK_PROCESS_POSTURE_ID, bodyPosture_ID);
    values.insert(DBConstants::COL_WORK_PROCESS_LOAD_HANDLING_ID, loadhandling_ID);
    values.insert(DBConstants::COL_WORK_PROCESS_APPLIED_FORCE_ID, appliedforce_ID);
    values.insert(DBConstants::COL_WORK_PROCESS_CONDITION_ID, workcondition_ID);
    dbHandler->save(DBConstants::TBL_WORK_PROCESS, DBConstants::HASH_WORK_PROCESS_TYPES, values, filter);
}

void Controller::workProcessDurationChanged(QTime time)
{
    QString tbl = DBConstants::TBL_WORK_PROCESS;
    QString filter = QString("%1 = %2 AND %3 = %4 AND %5 >= %6").arg(DBConstants::COL_WORK_PROCESS_ACTIVITY_ID).arg(activity_ID).arg(DBConstants::COL_WORK_PROCESS_TYPE).arg(workprocess_Type).arg(DBConstants::COL_WORK_PROCESS_ID).arg(workprocess_ID);
    QList<QHash<QString, QVariant>> rows = dbHandler->select(tbl, filter);
    if(!rows.isEmpty())
        {
            QHash<QString, QVariant> row = rows.at(0);
            filter = QString("%1 = %2 AND %3 = %4 AND %5 = %6").arg(DBConstants::COL_WORK_PROCESS_ACTIVITY_ID).arg(activity_ID).arg(DBConstants::COL_WORK_PROCESS_TYPE).arg(workprocess_Type).arg(DBConstants::COL_WORK_PROCESS_ID);
            QTime begin = row.value(DBConstants::COL_WORK_PROCESS_BEGIN).toTime();
            QTime end = row.value(DBConstants::COL_WORK_PROCESS_END).toTime();
            int diff = QTime(0, 0).addSecs(begin.secsTo(end)).secsTo(time);
            row.insert(DBConstants::COL_WORK_PROCESS_END, end.addSecs(diff));
            dbHandler->update(tbl, DBConstants::HASH_WORK_PROCESS_TYPES, row, filter.arg(workprocess_ID));
            for(int i = 1; i < rows.count(); ++i)
                {
                    row = rows.at(i);
                    begin = row.value(DBConstants::COL_WORK_PROCESS_BEGIN).toTime();
                    end = row.value(DBConstants::COL_WORK_PROCESS_END).toTime();
                    row.insert(DBConstants::COL_WORK_PROCESS_BEGIN, begin.addSecs(diff));
                    row.insert(DBConstants::COL_WORK_PROCESS_END, end.addSecs(diff));
                    dbHandler->update(tbl, DBConstants::HASH_WORK_PROCESS_TYPES, row, filter.arg(row.value(DBConstants::COL_WORK_PROCESS_ID).toInt()));
                }
            initializeRecording();
        }
}

void Controller::initializeRecording()
{
    gantTimerView->clear();
    QVector<QVariant> *leftWorkProcesses = new QVector<QVariant>();
    QVector<QVariant> *rightWorkProcesses = new QVector<QVariant>();
    QVector<QVariant> *basicWorkProcesses = new QVector<QVariant>();
    QList<QHash<QString, QVariant>> values = dbHandler->select(DBConstants::TBL_WORK_PROCESS, QString("%1 = %2").arg(DBConstants::COL_WORK_PROCESS_ACTIVITY_ID).arg(activity_ID));
    for(int i = 0; i < values.count(); ++i){
        QHash<QString, QVariant> row = values.at(i);
        int type = row.value(DBConstants::COL_WORK_PROCESS_TYPE).toInt();
        QVariant id = row.value(DBConstants::COL_WORK_PROCESS_ID);
        QVariant start = row.value(DBConstants::COL_WORK_PROCESS_BEGIN);
        QVariant end = row.value(DBConstants::COL_WORK_PROCESS_END);
        if(type == 1){
            leftWorkProcesses->append(id);
            leftWorkProcesses->append(start);
            leftWorkProcesses->append(end);
        }
        else if(type == 2){
            rightWorkProcesses->append(id);
            rightWorkProcesses->append(start);
            rightWorkProcesses->append(end);
        }
        else{
            basicWorkProcesses->append(id);
            basicWorkProcesses->append(start);
            basicWorkProcesses->append(end);
        }

    }
    gantTimerView->setWorkProcessLists(leftWorkProcesses, rightWorkProcesses, basicWorkProcesses);
    timerViewController->setWorkProcessLists(leftWorkProcesses, rightWorkProcesses, basicWorkProcesses);
}


// BodyPostureView
void Controller::updateBodyPostureView()
{
    QString tbl = DBConstants::TBL_BODY_POSTURE;
    QString filter = QString("%1 = %2").arg(DBConstants::COL_BODY_POSTURE_ID).arg(bodyPosture_ID);
    QHash<QString, QVariant> row = dbHandler->selectFirst(tbl, filter);
    if(!row.isEmpty()){
        foreach(QString key, DBConstants::HASH_BODY_POSTURE_TYPES.keys())
            row.insert(key, DBConstants::HASH_BODY_POSTURE_TYPES.value(key));
    }
    //bodyPostureView->setRecord(record);
}

void Controller::saveBodyPostureView()
{
    /*DB_TABLES tbl = DBConstants::TBL_BODY_POSTURE;
    QString filter = QString("%1 = %2").arg(DBConstants::COL_BODY_POSTURE_ID).arg(bodyPosture_ID);
    dbHandler->select(tbl, filter);
    if(activity_ID != 0)
        {
            QSqlRecord record = bodyPostureView->getRecord();
            if(dbHandler->rowCount(tbl) == 0)
                {
                    int id = dbHandler->getNextID(tbl, DBConstants::COL_BODY_POSTURE_ID);
                    record.setValue(DBConstants::COL_BODY_POSTURE_ID, id);
                    dbHandler->insertRow(tbl, record);
                    bodyPosture_ID = id;
                }
            else
                {
                    dbHandler->updateRow(tbl, 0, record);
                }
            bodyPosture_ID = record.value(DBConstants::COL_BODY_POSTURE_ID).toInt();
        }*/
}

// ExecutionConditionView
void Controller::updateExecutionConditionView()
{
    QString tbl = DBConstants::TBL_WORK_CONDITION;
    QString filter = QString("%1 = %2").arg(DBConstants::COL_WORK_CONDITION_ID).arg(workcondition_ID);
    QHash<QString, QVariant> row = dbHandler->selectFirst(tbl, filter);
    executionConditionView->setArmSupports(row.value(DBConstants::COL_WORK_CONDITION_RIGHT_UPPER_ARM_SUPPORTED).toInt(),
                                           row.value(DBConstants::COL_WORK_CONDITION_LEFT_UPPER_ARM_SUPPORTED).toInt(),
                                           row.value(DBConstants::COL_WORK_CONDITION_RIGHT_FOREARM_SUPPORTED).toInt(),
                                           row.value(DBConstants::COL_WORK_CONDITION_LEFT_FOREARM_SUPPORTED).toInt(),
                                           row.value(DBConstants::COL_WORK_CONDITION_RIGHT_HAND_SUPPORTED).toInt(),
                                           row.value(DBConstants::COL_WORK_CONDITION_LEFT_HAND_SUPPORTED).toInt());
    executionConditionView->setBodySupports(row.value(DBConstants::COL_WORK_CONDITION_HEAD_SUPPORTED).toInt(),
                                            row.value(DBConstants::COL_WORK_CONDITION_TRUNK_SUPPORT).toInt());
    executionConditionView->setLegSupports(row.value(DBConstants::COL_WORK_CONDITION_RIGHT_THIGH_SUPPORTED).toInt(),
                                           row.value(DBConstants::COL_WORK_CONDITION_LEFT_THIGH_SUPPORTED).toInt(),
                                           row.value(DBConstants::COL_WORK_CONDITION_RIGHT_LOWER_LEG_SUPPORTED).toInt(),
                                           row.value(DBConstants::COL_WORK_CONDITION_LEFT_LOWER_LEG_SUPPORTED).toInt());
    executionConditionView->setResultingConstraints(row.value(DBConstants::COL_WORK_CONDITION_GRIP_CONDITION).toInt(),
                                                    row.value(DBConstants::COL_WORK_CONDITION_ACCESSIBILITY).toInt(),
                                                    row.value(DBConstants::COL_WORK_CONDITION_GROUND).toInt(),
                                                    row.value(DBConstants::COL_WORK_CONDITION_LIGHTING).toInt(),
                                                    row.value(DBConstants::COL_WORK_CONDITION_CLIMATE).toInt(),
                                                    row.value(DBConstants::COL_WORK_CONDITION_WIND).toInt(),
                                                    row.value(DBConstants::COL_WORK_CONDITION_CLOTHING).toInt(),
                                                    row.value(DBConstants::COL_WORK_CONDITION_ROOM_TO_MOVE).toInt());
    executionConditionView->setConditionAttributes(row.value(DBConstants::COL_WORK_CONDITION_PRECISION).toInt(),
                                                   row.value(DBConstants::COL_WORK_CONDITION_VELOCITY).toInt(),
                                                   row.value(DBConstants::COL_WORK_CONDITION_ACCELERATION).toInt(),
                                                   row.value(DBConstants::COL_WORK_CONDITION_VIBRATION).toInt());
}

void Controller::saveExecutionConditionView()
{
    QString filter = QString("%1 = %2").arg(DBConstants::COL_WORK_CONDITION_ID).arg(workcondition_ID);

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_WORK_CONDITION_ACCELERATION, executionConditionView->getAcceleration());
    values.insert(DBConstants::COL_WORK_CONDITION_ACCESSIBILITY, executionConditionView->getAccessibility());
    values.insert(DBConstants::COL_WORK_CONDITION_CLIMATE, executionConditionView->getClimate());
    values.insert(DBConstants::COL_WORK_CONDITION_CLOTHING, executionConditionView->getClothing());
    values.insert(DBConstants::COL_WORK_CONDITION_GRIP_CONDITION, executionConditionView->getGraspingType());
    values.insert(DBConstants::COL_WORK_CONDITION_GROUND, executionConditionView->getGround());
    values.insert(DBConstants::COL_WORK_CONDITION_HEAD_SUPPORTED, executionConditionView->getHeadSupport());
    values.insert(DBConstants::COL_WORK_CONDITION_LEFT_FOREARM_SUPPORTED, executionConditionView->getLeftForearmSupport());
    values.insert(DBConstants::COL_WORK_CONDITION_LEFT_HAND_SUPPORTED, executionConditionView->getLeftHandSupport());
    values.insert(DBConstants::COL_WORK_CONDITION_LEFT_LOWER_LEG_SUPPORTED, executionConditionView->getLeftLowerLegSupport());
    values.insert(DBConstants::COL_WORK_CONDITION_LEFT_THIGH_SUPPORTED, executionConditionView->getLeftThighSupport());
    values.insert(DBConstants::COL_WORK_CONDITION_LEFT_UPPER_ARM_SUPPORTED, executionConditionView->getLeftUpperArmSupport());
    values.insert(DBConstants::COL_WORK_CONDITION_LIGHTING, executionConditionView->getLighting());
    values.insert(DBConstants::COL_WORK_CONDITION_PRECISION, executionConditionView->getPrecision());
    values.insert(DBConstants::COL_WORK_CONDITION_RIGHT_FOREARM_SUPPORTED, executionConditionView->getRightForearmSupport());
    values.insert(DBConstants::COL_WORK_CONDITION_RIGHT_HAND_SUPPORTED, executionConditionView->getRightHandSupport());
    values.insert(DBConstants::COL_WORK_CONDITION_RIGHT_LOWER_LEG_SUPPORTED, executionConditionView->getRightLowerLegSupport());
    values.insert(DBConstants::COL_WORK_CONDITION_RIGHT_THIGH_SUPPORTED, executionConditionView->getRightThighSupport());
    values.insert(DBConstants::COL_WORK_CONDITION_RIGHT_UPPER_ARM_SUPPORTED, executionConditionView->getRightUpperArmSupport());
    values.insert(DBConstants::COL_WORK_CONDITION_ROOM_TO_MOVE, executionConditionView->getRoomToMove());
    values.insert(DBConstants::COL_WORK_CONDITION_TRUNK_SUPPORT, executionConditionView->getTrunkSupport());
    values.insert(DBConstants::COL_WORK_CONDITION_VELOCITY, executionConditionView->getVelocity());
    values.insert(DBConstants::COL_WORK_CONDITION_VIBRATION, executionConditionView->getVibration());
    values.insert(DBConstants::COL_WORK_CONDITION_WIND, executionConditionView->getWind());
    values.insert(DBConstants::COL_WORK_CONDITION_ID, workcondition_ID);
    workcondition_ID = dbHandler->save(DBConstants::TBL_WORK_CONDITION, DBConstants::HASH_COMMENT_TYPES, values, filter, DBConstants::COL_WORK_CONDITION_ID);
}

// AppliedForceView
void Controller::updateAppliedForceView()
{
    QString tbl = DBConstants::TBL_APPLIED_FORCE;
    QString filter = QString("%1 = %2").arg(DBConstants::COL_APPLIED_FORCE_ID).arg(appliedforce_ID);
    QHash<QString, QVariant> row = dbHandler->selectFirst(tbl, filter);
    appliedForceView->setOrgan(row.value(DBConstants::COL_APPLIED_FORCE_ORGAN).toString());
    appliedForceView->setDirection(row.value(DBConstants::COL_APPLIED_FORCE_DIRECTION).toString());
    appliedForceView->setIntensity(row.value(DBConstants::COL_APPLIED_FORCE_INTENSITY).toInt());
}

void Controller::saveAppliedForceView()
{
    QString filter = QString("%1 = %2").arg(DBConstants::COL_APPLIED_FORCE_ID).arg(appliedforce_ID);

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_APPLIED_FORCE_ORGAN, appliedForceView->getOrgan());
    values.insert(DBConstants::COL_APPLIED_FORCE_DIRECTION, appliedForceView->getDirection());
    values.insert(DBConstants::COL_APPLIED_FORCE_INTENSITY, appliedForceView->getIntensity());
    values.insert(DBConstants::COL_APPLIED_FORCE_ID, appliedforce_ID);
    appliedforce_ID = dbHandler->save(DBConstants::TBL_APPLIED_FORCE, DBConstants::HASH_COMMENT_TYPES, values, filter, DBConstants::COL_APPLIED_FORCE_ID);
}

// LoadHandlingView
void Controller::updateLoadHandlingView()
{
    QString tbl = DBConstants::TBL_LOAD_HANDLING;
    QString filter = QString("%1 = %2").arg(DBConstants::COL_LOAD_HANDLING_ID).arg(loadhandling_ID);
    QHash<QString, QVariant> row = dbHandler->selectFirst(tbl, filter);
    loadHandlingView->setGraspType(row.value(DBConstants::COL_LOAD_HANDLING_TYPE_OF_GRASPING).toString());
    loadHandlingView->setWeight(row.value(DBConstants::COL_LOAD_HANDLING_LOAD).toInt());
    loadHandlingView->setDistance(row.value(DBConstants::COL_LOAD_HANDLING_DISTANCE).toInt());
    int grasp_ID = row.value(DBConstants::COL_TYPE_OF_GRASPING_ID).toInt();
    int handlingType_ID = row.value(DBConstants::COL_LOAD_HANDLING_LOAD_HANDLING_TYPE_ID).toInt();
    int trans_ID = row.value(DBConstants::COL_LOAD_HANDLING_TRANSPORTATION_ID).toInt();

    tbl = DBConstants::TBL_LOAD_HANDLING_TYPE;
    row = dbHandler->selectFirst(tbl, QString("%1 = %2").arg(DBConstants::COL_LOAD_HANDLING_TYPE_ID).arg(handlingType_ID));
    loadHandlingView->setHandlingType(row.value(DBConstants::COL_LOAD_HANDLING_TYPE_NAME).toString());

    tbl = DBConstants::TBL_TYPE_OF_GRASPING;
    row = dbHandler->selectFirst(tbl, QString("%1 = %2").arg(DBConstants::COL_TYPE_OF_GRASPING_ID).arg(grasp_ID));
    loadHandlingView->setGraspType(row.value(DBConstants::COL_TYPE_OF_GRASPING_NAME).toString());
    updateLoadHandlingTransportations();
    loadHandlingView->setSelectedTransportation(trans_ID);
}

void Controller::saveLoadHandlingView()
{
    QString filter = QString("%1 = '%2'").arg(DBConstants::COL_TYPE_OF_GRASPING_NAME).arg(loadHandlingView->getGraspType());
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_TYPE_OF_GRASPING_NAME, loadHandlingView->getGraspType());
    int grasp_ID = dbHandler->save(DBConstants::TBL_TYPE_OF_GRASPING, DBConstants::HASH_TYPE_OF_GRASPING_TYPES, values, filter, DBConstants::COL_TYPE_OF_GRASPING_ID);

    filter = QString("%1 = '%2'").arg(DBConstants::COL_LOAD_HANDLING_TYPE_NAME).arg(loadHandlingView->getHandlingType());
    values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_LOAD_HANDLING_TYPE_NAME, loadHandlingView->getHandlingType());
    int loadHandlingType_ID = dbHandler->save(DBConstants::TBL_LOAD_HANDLING_TYPE, DBConstants::HASH_LOAD_HANDLING_TYPE_TYPES, values, filter, DBConstants::COL_LOAD_HANDLING_TYPE_ID);

    filter = QString("%1 = %2").arg(DBConstants::COL_LOAD_HANDLING_ID).arg(loadhandling_ID);
    values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_LOAD_HANDLING_TYPE_OF_GRASPING, grasp_ID);
    values.insert(DBConstants::COL_LOAD_HANDLING_LOAD_HANDLING_TYPE_ID, loadHandlingType_ID);
    values.insert(DBConstants::COL_LOAD_HANDLING_TRANSPORTATION_ID, loadHandlingView->getSelectedTransportation());
    values.insert(DBConstants::COL_LOAD_HANDLING_LOAD, loadHandlingView->getWeight());
    values.insert(DBConstants::COL_LOAD_HANDLING_DISTANCE, loadHandlingView->getDistance());
    loadhandling_ID = dbHandler->save(DBConstants::TBL_LOAD_HANDLING, DBConstants::HASH_LOAD_HANDLING_TYPES, values, filter, DBConstants::COL_LOAD_HANDLING_ID);
}

void Controller::updateLoadHandlingTransportations()
{
    loadHandlingView->clearTransportation();
    QString tbl = DBConstants::TBL_TRANSPORTATION;
    QList<QHash<QString, QVariant>> values = dbHandler->select(tbl, "");
    for(int i = 0; i < values.count(); ++i)
        {
            QHash<QString, QVariant> row = values.at(i);
            loadHandlingView->addTransportation(row.value(DBConstants::COL_TRANSPORTATION_ID).toInt(),
                                                row.value(DBConstants::COL_TRANSPORTATION_NAME).toString(),
                                                row.value(DBConstants::COL_TRANSPORTATION_EMPTY_WEIGHT).toInt(),
                                                row.value(DBConstants::COL_TRANSPORTATION_MAX_LOAD).toInt(),
                                                row.value(DBConstants::COL_TRANSPORTATION_BRAKES).toBool(),
                                                row.value(DBConstants::COL_TRANSPORTATION_FIXED_ROLLER).toBool());
        }
}

//WorkProcessMetaDataView
void Controller::updateWorkProcessMetaDataView()
{
    QString tbl = DBConstants::TBL_WORK_PROCESS;
    QString filter = QString("%1 = %2 AND %3 = %4 AND %5 = %6").arg(DBConstants::COL_WORK_PROCESS_ACTIVITY_ID).arg(activity_ID).arg(DBConstants::COL_WORK_PROCESS_POSTURE_ID).arg(workprocess_ID).arg(DBConstants::COL_WORK_PROCESS_TYPE).arg(workprocess_Type);
    QHash<QString, QVariant> row = dbHandler->selectFirst(tbl, filter);
    workProcessMetaDataView->setWorkProcessMetaData(row.value(DBConstants::COL_WORK_PROCESS_DESCRIPTION).toString(),
            row.value(DBConstants::COL_WORK_PROCESS_MTM_CODE).toString(),
            row.value(DBConstants::COL_WORK_PROCESS_WORKING_HEIGHT).toInt(),
            row.value(DBConstants::COL_WORK_PROCESS_DISTANCE).toInt(),
            row.value(DBConstants::COL_WORK_PROCESS_IMPULSE_INTENSITY).toInt(),
            row.value(DBConstants::COL_WORK_PROCESS_IMPULSE_COUNT).toInt());
    updateWorkProcessMetaDataEquipment();
    workProcessMetaDataView->setSelectedEquipment(row.value(DBConstants::COL_WORK_PROCESS_EQUIPMENT_ID).toInt());
}

void Controller::updateWorkProcessMetaDataEquipment()
{
    workProcessMetaDataView->clearEquipment();
    QString tbl = DBConstants::TBL_EQUIPMENT;
    QList<QHash<QString, QVariant>> values = dbHandler->select(tbl, QString(""));
    for(int i = 0; i < values.count(); ++i){
        QHash<QString, QVariant> row = values.at(i);
        workProcessMetaDataView->addEquipment(row.value(DBConstants::COL_EQUIPMENT_ID).toInt(),
                                              row.value(DBConstants::COL_EQUIPMENT_NAME).toString(),
                                              row.value(DBConstants::COL_EQUIPMENT_RECOIL_COUNT).toInt(),
                                              row.value(DBConstants::COL_EQUIPMENT_RECOIL_INTENSITY).toInt(),
                                              row.value(DBConstants::COL_EQUIPMENT_VIBRATION_COUNT).toInt(),
                                              row.value(DBConstants::COL_EQUIPMENT_VIBRATION_INTENSITY).toInt());
    }
}

// Documentation View Ressource Lists
void Controller::updateDocumentationViewRessources()
{
    updateLoadHandlingTransportations();
    updateWorkProcessMetaDataEquipment();
}

//SendDatabasePopUp
void Controller::updateFTPConnectionPopUp(IFTPConnections *widget)
{
    widget->clear();
    QList<QHash<QString, QVariant>> values = dbHandler->select(DBConstants::TBL_CONNECTION, QString("%1 = %2").arg(DBConstants::COL_CONNECTION_ANALYST_ID).arg(analyst_ID));
    int defaultID = 0;
    for(int i = 0; i < values.count(); ++i){
        QHash<QString, QVariant> row = values.at(i);

        if(row.value(DBConstants::COL_CONNECTION_DEFAULT).toBool())
            defaultID = row.value(DBConstants::COL_CONNECTION_ID).toInt();

        widget->add(row.value(DBConstants::COL_CONNECTION_NAME).toString(),
                               row.value(DBConstants::COL_CONNECTION_ID).toInt());
    }
    widget->select(defaultID);
}

void Controller::selectedConnectionChanged(IFTPConnections *widget, int id)
{
    QHash<QString, QVariant> row = dbHandler->selectFirst(DBConstants::TBL_CONNECTION, QString("%1 = %2").arg(DBConstants::COL_CONNECTION_ID).arg(id));
    if(!row.isEmpty()){
        widget->setName(row.value(DBConstants::COL_CONNECTION_NAME).toString());
        widget->setUserName(row.value(DBConstants::COL_CONNECTION_USERNAME).toString());
        widget->setPassword(row.value(DBConstants::COL_CONNECTION_PASSWORD).toString());
        widget->setAddress(row.value(DBConstants::COL_CONNECTION_SERVER_ADDRESS).toString());
        widget->setPort(row.value(DBConstants::COL_CONNECTION_PORT).toInt());
        widget->setSetAsDefault(row.value(DBConstants::COL_CONNECTION_DEFAULT).toBool());
    }
}

void Controller::createConnection(IFTPConnections *widget)
{
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_CONNECTION_NAME, widget->getName());
    values.insert(DBConstants::COL_CONNECTION_USERNAME, widget->getUserName());
    values.insert(DBConstants::COL_CONNECTION_PASSWORD, widget->getPassword());
    values.insert(DBConstants::COL_CONNECTION_SERVER_ADDRESS, widget->getAddress());
    values.insert(DBConstants::COL_CONNECTION_PORT, widget->getPort());
    values.insert(DBConstants::COL_CONNECTION_DEFAULT, widget->getSetAsDefault());
    values.insert(DBConstants::COL_CONNECTION_ANALYST_ID, analyst_ID);
    dbHandler->insert(DBConstants::TBL_CONNECTION, DBConstants::HASH_CONNECTION_TYPES, values, DBConstants::COL_CONNECTION_ID);
}

void Controller::editConnection(IFTPConnections *widget, int id)
{
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_CONNECTION_NAME, widget->getName());
    values.insert(DBConstants::COL_CONNECTION_USERNAME, widget->getUserName());
    values.insert(DBConstants::COL_CONNECTION_PASSWORD, widget->getPassword());
    values.insert(DBConstants::COL_CONNECTION_SERVER_ADDRESS, widget->getAddress());
    values.insert(DBConstants::COL_CONNECTION_PORT, widget->getPort());
    values.insert(DBConstants::COL_CONNECTION_DEFAULT, widget->getSetAsDefault());
    values.insert(DBConstants::COL_CONNECTION_ANALYST_ID, analyst_ID);
    dbHandler->update(DBConstants::TBL_CONNECTION, DBConstants::HASH_CONNECTION_TYPES, values, QString("%1 = %2").arg(DBConstants::COL_CONNECTION_ID).arg(id));
}

//Parse import data
void Controller::parseImportData(){
    viewCon->showMessage(tr("Start parsing"));
    viewCon->closePopUp();

    if(importDataPopUp->getImportMode().compare("XML") == 0){
        XMLParser *xmlParser = new XMLParser(this);
        connect(xmlParser, SIGNAL(createTransportation(QHash<QString,QVariant>)), this, SLOT(createTransportation(QHash<QString, QVariant>)));
        connect(xmlParser, SIGNAL(createEmployee(QHash<QString,QVariant>,QHash<QString,QVariant>)), this, SLOT(createEmployee(QHash<QString,QVariant>,QHash<QString,QVariant>)));
        connect(xmlParser, SIGNAL(createEquipment(QHash<QString,QVariant>)), this, SLOT(createEquipment(QHash<QString,QVariant>)));
        connect(xmlParser, SIGNAL(createProduct(QHash<QString,QVariant>)), this, SLOT(createProduct(QHash<QString,QVariant>)));
        connect(xmlParser, SIGNAL(createWorkplace(QHash<QString,QVariant>,QList<QHash<QString,QVariant> >)), this, SLOT(createWorkplace(QHash<QString,QVariant>,QList<QHash<QString,QVariant> >)));
        parser = qobject_cast<IImportDataParser*>(xmlParser);
        downloadDir = StandardPaths::xmlDirectoryPath();
    }
    else {
        parser = 0;
        downloadDir = "";
    }

    QDir downloadDirectory = QDir(downloadDir);
    if(!downloadDirectory.exists())
        downloadDirectory.mkpath(downloadDir);

    if(parser){
        FtpHandler *ftpHandler = new FtpHandler();
        connect(ftpHandler, SIGNAL(error(QString)), this, SLOT(importDataDownloadError(QString)));
        connect(ftpHandler, SIGNAL(finished(QString)), this, SLOT(importDataDownloadFinished(QString)));
        ftpHandler->setUser(importDataPopUp->getUserName(), importDataPopUp->getPassword());
        ftpHandler->setPort(importDataPopUp->getPort());
        ftpHandler->setServer(importDataPopUp->getAddress());

        if(parser->getFileMode() == IImportDataParser::FileMode::MultiFile){
            if(importDataPopUp->importTransportations())
                ftpHandler->downloadFile(parser->getTransportationFilename(), downloadDir);
            if(importDataPopUp->importEquipments())
                ftpHandler->downloadFile(parser->getEquipmentFilename(), downloadDir);
            if(importDataPopUp->importProducts())
                ftpHandler->downloadFile(parser->getProductFilename(), downloadDir);
            if(importDataPopUp->importEmployees())
                ftpHandler->downloadFile(parser->getEmployeeFilename(), downloadDir);
            if(importDataPopUp->importWorkplaces())
                ftpHandler->downloadFile(parser->getWorkplaceFilename(), downloadDir);
        }
        else {
            ftpHandler->downloadFile(parser->getSingleFilename(), downloadDir);
        }

    }
}

void Controller::importDataDownloadFinished(const QString filename){
    QString path = QString("%1/%2").arg(downloadDir);
    if(parser != 0 && parser->getFileMode() == IImportDataParser::FileMode::MultiFile){
        if(filename.compare(parser->getTransportationFilename()) == 0)
            parser->parseTransportations(path.arg(filename));
        else if(filename.compare(parser->getEquipmentFilename()) == 0)
            parser->parseEquipments(path.arg(filename));
        else if(filename.compare(parser->getProductFilename()) == 0)
            parser->parseProducts(path.arg(filename));
        else if(filename.compare(parser->getEmployeeFilename()) == 0)
            parser->parseEmployees(path.arg(filename));
        else if(filename.compare(parser->getWorkplaceFilename()) == 0)
            parser->parseWorkplaces(path.arg(filename));
    }
    else {
        if(filename.compare(parser->getSingleFilename()) == 0){
            if(importDataPopUp->importTransportations())
                parser->parseTransportations(path.arg(filename));
            if(importDataPopUp->importEquipments())
                parser->parseEquipments(path.arg(filename));
            if(importDataPopUp->importProducts())
                parser->parseProducts(path.arg(filename));
            if(importDataPopUp->importEmployees())
                parser->parseEmployees(path.arg(filename));
            if(importDataPopUp->importWorkplaces())
                parser->parseWorkplaces(path.arg(filename));
        }
    }
}

void Controller::importDataDownloadError(const QString &error){
    viewCon->showMessage(error, NotificationMessage::ERROR, NotificationMessage::PERSISTENT);
}


void Controller::resetDatabaseFactory()
{
    QString emptyFilter = QString("");
    analyst_ID = 0;
    recording_ID = 1;
    workplace_ID = 0;
    workcondition_ID = 0;
    factory_ID = 0;
    activity_ID = 0;
    appliedforce_ID = 0;
    loadhandling_ID = 0;
    workprocess_Type = AVType::BASIC;
    workprocess_ID = 0;
    employee_ID = 1;
    bodyMeasurement_ID = 1;
    dbHandler->deleteAll(DBConstants::TBL_ACTIVITY, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_APPLIED_FORCE, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_BODY_POSTURE, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_BREAK, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_COMMENT, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_EMPLOYEE, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_BODY_MEASUREMENT, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_EMPLOYEE_WORKS_SHIFT, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_EQUIPMENT, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_LINE, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_LOAD_HANDLING, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_PRODUCT, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_RECORDING, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_RECORDING_OB_LINE, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_RECORDING_OB_WORKPLACE, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_SHIFT, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_TRANSPORTATION, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_WORKPLACE, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_WORK_CONDITION, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_WORK_PROCESS, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_CONNECTION, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_ANALYST, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_BRANCH_OF_INDUSTRY, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_CORPORATION, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_EMPLOYER, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_FACTORY, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_TYPE_OF_GRASPING, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_LOAD_HANDLING_TYPE, emptyFilter);
    dbHandler->deleteAll(DBConstants::TBL_BODY_MEASUREMENT, emptyFilter);
    emit clearAll();
    viewCon->closePopUp();
    viewCon->showMessage(tr("Restored Factory Settings"), NotificationMessage::ACCEPT);
    viewCon->showView(ViewType::ANALYST_SELECTION_VIEW);
}


void Controller::languageChanged(){
    QFile file(StandardPaths::configFile());
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString line = in.readLine();
    QStringList settings = line.split(',');
    file.close();
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);

    int languageID = languagePopUp->getSelectedLanguage();
    switch(languageID){
    case(0):
         out<<"german"<<','<<settings.at(1);
         settingsView->setCurrentLanguageIcon("germanIcon");
         viewCon->showMessage(tr("Language changed"), NotificationMessage::ACCEPT);
         viewCon->showMessage(("Neustart erforderlich um die Änderungen umzusetzen"), NotificationMessage::INFORMATION, NotificationMessage::PERSISTENT);
         break;
    case(1):
         out<<"english"<<','<<settings.at(1);
         settingsView->setCurrentLanguageIcon("englishIcon");
         viewCon->showMessage(tr("Language changed"), NotificationMessage::ACCEPT);
         viewCon->showMessage(("Restart App to apply changes"), NotificationMessage::INFORMATION, NotificationMessage::PERSISTENT);
         break;
    default:
         out<<"english"<<','<<settings.at(1);
         settingsView->setCurrentLanguageIcon("englishIcon");
         break;
    }
    viewCon->closePopUp();


}

void Controller::themeChanged()
{
    QFile file(StandardPaths::configFile());
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString line = in.readLine();
    QStringList settings = line.split(',');
    file.close();
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);

    int themeID = themePopUp->getSelectedTheme();
    switch(themeID)
        {
        case(0):
            settingsView->setCurrentThemeIcon("blueIcon");
            application->setStyleSheet(stringFromResource(":/assets/stylesheet.qss"));
            out<<settings.at(0)<<','<<"blue";
            break;
        case(1):
            settingsView->setCurrentThemeIcon("greenIcon");
            application->setStyleSheet(stringFromResource(":/assets/stylesheetGreen.qss"));
            out<<settings.at(0)<<','<<"green";
            break;
        default:
            settingsView->setCurrentThemeIcon("blueIcon");
            application->setStyleSheet(stringFromResource(":/assets/stylesheet.qss"));
            out<<settings.at(0)<<','<<"blue";
            break;
        }

    viewCon->closePopUp();
    viewCon->showMessage(tr("Theme changed"), NotificationMessage::ACCEPT);
}

//PRIVATE METHODS
QString Controller::stringFromResource(const QString &resName)
{
    QFile file(resName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream ts(&file);
    return ts.readAll();
}

void Controller::saveRecordingObservesLine(int lineID)
{
    QString filter = QString("%1 = %2 AND %3 = %4").arg(DBConstants::COL_RECORDING_OB_LINE_RECORDING_ID).arg(QString::number(recording_ID)).arg(DBConstants::COL_RECORDING_OB_LINE_LINE_ID).arg(QString::number(lineID));

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_RECORDING_OB_LINE_RECORDING_ID, recording_ID);
    values.insert(DBConstants::COL_RECORDING_OB_LINE_LINE_ID, lineID);
    dbHandler->save(DBConstants::TBL_RECORDING_OB_LINE, DBConstants::HASH_RECORDING_OB_LINE_TYPES, values, filter);
}

void Controller::deleteRecordingObservesLine(int lineID)
{
    QString filter = QString("%1 = %2").arg(DBConstants::COL_RECORDING_OB_LINE_LINE_ID).arg(QString::number(lineID));
    dbHandler->deleteAll(DBConstants::TBL_RECORDING_OB_LINE, filter);
}

void Controller::saveRecordingObservesWorkplace(int workplaceID)
{
    QString filter = QString("%1 = %2 AND %3 = %4").arg(DBConstants::COL_RECORDING_OB_WORKPLACE_RECORDING_ID).arg(QString::number(recording_ID)).arg(DBConstants::COL_RECORDING_OB_WORKPLACE_WORKPLACE_ID).arg(QString::number(workplaceID));

    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_RECORDING_OB_WORKPLACE_RECORDING_ID, recording_ID);
    values.insert(DBConstants::COL_RECORDING_OB_WORKPLACE_WORKPLACE_ID, workplaceID);
    dbHandler->save(DBConstants::TBL_RECORDING_OB_WORKPLACE, DBConstants::HASH_RECORDING_OB_WORKPLACE_TYPES, values, filter);
}

void Controller::deleteRecordingOberservesWorkplace(int wpID)
{
    QString filter = QString("%1 = %2").arg(DBConstants::COL_RECORDING_OB_WORKPLACE_WORKPLACE_ID).arg(QString::number(wpID));
    dbHandler->deleteAll(DBConstants::TBL_RECORDING_OB_WORKPLACE, filter);
}

int Controller::saveWorkplace(int id)
{
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
    return dbHandler->save(DBConstants::TBL_WORKPLACE, DBConstants::HASH_WORKPLACE_TYPES, values, filter, DBConstants::COL_WORKPLACE_ID);
}

int Controller::qTimeToSeconds(const QTime &time)
{
    return time.hour() * 3600 + time.minute() * 60 + time.second();
}

void Controller::deleteWorkProcesses(int activity_ID)
{
    QString tbl = DBConstants::TBL_WORK_PROCESS;
    QString filter = QString("%1 = %2").arg(DBConstants::COL_WORK_PROCESS_ACTIVITY_ID).arg(activity_ID);
    QList<QHash<QString, QVariant>> values = dbHandler->select(tbl, filter);
    for(int i = 0; i < values.count(); ++i){
        QHash<QString, QVariant> row = values.at(i);
        dbHandler->deleteAll(DBConstants::TBL_BODY_POSTURE, QString("%1 = %2").arg(DBConstants::COL_BODY_POSTURE_ID).arg(row.value(DBConstants::COL_WORK_PROCESS_POSTURE_ID).toInt()));
        dbHandler->deleteAll(DBConstants::TBL_APPLIED_FORCE, QString("%1 = %2").arg(DBConstants::COL_APPLIED_FORCE_ID).arg(row.value(DBConstants::COL_WORK_PROCESS_APPLIED_FORCE_ID).toInt()));
        dbHandler->deleteAll(DBConstants::TBL_LOAD_HANDLING, QString("%1 = %2").arg(DBConstants::COL_LOAD_HANDLING_ID).arg(row.value(DBConstants::COL_WORK_PROCESS_LOAD_HANDLING_ID).toInt()));
        dbHandler->deleteAll(DBConstants::TBL_WORK_CONDITION, QString("%1 = %2").arg(DBConstants::COL_WORK_CONDITION_ID).arg(row.value(DBConstants::COL_WORK_PROCESS_CONDITION_ID).toInt()));
    }
    dbHandler->deleteAll(tbl, filter);
}

void Controller::resetSelectedEntries(){
    QString emptyFilter = QString("");
    if(resetPopUp->headDataSelected()){
        factory_ID = 0;
        dbHandler->deleteAll(DBConstants::TBL_BRANCH_OF_INDUSTRY, emptyFilter);
        dbHandler->deleteAll(DBConstants::TBL_CORPORATION, emptyFilter);
        dbHandler->deleteAll(DBConstants::TBL_EMPLOYER, emptyFilter);
        dbHandler->deleteAll(DBConstants::TBL_FACTORY, emptyFilter);
    }
    if(resetPopUp->workplacesSelected()){
        recording_ID = 1;
        workplace_ID = 0;
        workcondition_ID = 0;
        activity_ID = 0;
        appliedforce_ID = 0;
        loadhandling_ID = 0;
        workprocess_Type = AVType::BASIC;
        workprocess_ID = 0;
        dbHandler->deleteAll(DBConstants::TBL_ACTIVITY, emptyFilter);
        dbHandler->deleteAll(DBConstants::TBL_APPLIED_FORCE, emptyFilter);
        dbHandler->deleteAll(DBConstants::TBL_BODY_POSTURE, emptyFilter);
        dbHandler->deleteAll(DBConstants::TBL_COMMENT, emptyFilter);
        dbHandler->deleteAll(DBConstants::TBL_LINE, emptyFilter);
        dbHandler->deleteAll(DBConstants::TBL_LOAD_HANDLING, emptyFilter);
        dbHandler->deleteAll(DBConstants::TBL_RECORDING, emptyFilter);
        dbHandler->deleteAll(DBConstants::TBL_RECORDING_OB_LINE, emptyFilter);
        dbHandler->deleteAll(DBConstants::TBL_RECORDING_OB_WORKPLACE, emptyFilter);
        dbHandler->deleteAll(DBConstants::TBL_WORKPLACE, emptyFilter);
        dbHandler->deleteAll(DBConstants::TBL_WORK_CONDITION, emptyFilter);
        dbHandler->deleteAll(DBConstants::TBL_WORK_PROCESS, emptyFilter);
    }
    if(resetPopUp->equipmentSelected()){
        dbHandler->deleteAll(DBConstants::TBL_EQUIPMENT, emptyFilter);
    }
    if(resetPopUp->productsSelected()){
        dbHandler->deleteAll(DBConstants::TBL_PRODUCT, emptyFilter);
    }
    if(resetPopUp->transportationSelected()){
        dbHandler->deleteAll(DBConstants::TBL_TRANSPORTATION, emptyFilter);
    }
    if(resetPopUp->employeeSelected()){
        employee_ID = 1;
        bodyMeasurement_ID = 1;
        dbHandler->deleteAll(DBConstants::TBL_EMPLOYEE, emptyFilter);
        dbHandler->deleteAll(DBConstants::TBL_EMPLOYEE_WORKS_SHIFT, emptyFilter);
        dbHandler->deleteAll(DBConstants::TBL_BODY_MEASUREMENT, emptyFilter);
        emit clearEmployees();
    }
    if(resetPopUp->shiftDataSelected()){
        dbHandler->deleteAll(DBConstants::TBL_SHIFT, emptyFilter);
        dbHandler->deleteAll(DBConstants::TBL_BREAK, emptyFilter);
    }
    if(resetPopUp->ftpConnectionSelected()){
        dbHandler->deleteAll(DBConstants::TBL_CONNECTION, emptyFilter);
    }

    viewCon->closePopUp();
    viewCon->showMessage(tr("Reset successful"), NotificationMessage::ACCEPT);
}
