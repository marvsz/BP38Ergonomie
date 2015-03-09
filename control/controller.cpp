#include "controller.h"
#include <QDebug>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include "../ftpHandler/ftphandler.h"


Controller::Controller(QObject *parent, QApplication *app) :
    QObject(parent),
    application(app),
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
    createProductPopUp(new CreateProductPopUp()),
    activityPopUp(new ActivityPopUp()),
    languagePopUp(new LanguagePopUp()),
    themePopUp(new ThemePopUp()),
    workplacePopUp(new WorkplacePopUp()),
    importDataPopUp(new ImportDataPopUp()),
    resetPopUp(new ResetPopUp()),
    employeePopUp(new EmployeePopUp()),
    factorySettingsPopUp(new FactorySettingsPopUp()),
    linePopUp(new LinePopUp())
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

    //WorkplaceList View signal/slots
    connect(this, SIGNAL(clearAll()), workplaceListView, SLOT(clearWorkplaces()));
    connect(this, SIGNAL(clearWorkplaces()), workplaceListView, SLOT(clearWorkplaces()));
    connect(workplaceListView, SIGNAL(createWorkplace(QHash<QString,QVariant>)), this, SLOT(createWorkplace(QHash<QString,QVariant>)));
    connect(this, SIGNAL(createdWorkplace(QHash<QString,QVariant>)), workplaceListView, SLOT(addWorkplace(QHash<QString,QVariant>)));
    connect(workplaceListView, SIGNAL(selectWorkplace(int)), this, SLOT(selectWorkplace(int)));
    connect(this, SIGNAL(selectedWorkplace(QHash<QString,QVariant>)), workplaceView, SLOT(setWorkplace(QHash<QString, QVariant>)));
    connect(workplaceListView, SIGNAL(deleteWorkplace(int)), this, SLOT(deleteWorkplace(int)));
    connect(this, SIGNAL(removedWorkplace(int)), workplaceListView, SLOT(removeWorkplace(int)));
    connect(this, SIGNAL(updatedWorkplace(QHash<QString,QVariant>)), workplaceListView, SLOT(updateWorkplace(QHash<QString,QVariant>)));

    //Workplace View signal/slots
    connect(this, SIGNAL(selectedComment(QHash<QString,QVariant>)), workplaceView, SLOT(setSavedComment(QHash<QString,QVariant>)));
    connect(this, SIGNAL(updatedComment(QHash<QString,QVariant>)), workplaceView, SLOT(setSavedComment(QHash<QString,QVariant>)));
    connect(this, SIGNAL(selectedLine(QHash<QString,QVariant>)), workplaceView, SLOT(setSavedLine(QHash<QString,QVariant>)));
    connect(this, SIGNAL(updatedLine(QHash<QString,QVariant>)), workplaceView, SLOT(setSavedLine(QHash<QString,QVariant>)));
    connect(workplaceView, SIGNAL(saveWorkplace(QHash<QString,QVariant>)), this, SLOT(saveWorkplace(QHash<QString,QVariant>)));

    //Comment View signal/slots
    connect(this, SIGNAL(selectedComment(QHash<QString,QVariant>)), commentView, SLOT(setComment(QHash<QString,QVariant>)));
    connect(commentView, SIGNAL(saveComment(QHash<QString,QVariant>)), this, SLOT(saveComment(QHash<QString,QVariant>)));

    //Employee View signal/slots
    connect(this, SIGNAL(clearEmployees()), employeeListView, SLOT(clearEmployees()));
    connect(this, SIGNAL(clearAll()), employeeListView, SLOT(clearEmployees()));
    connect(employeeListView, SIGNAL(deleteEmployee(int)), this, SLOT(deleteEmployee(int)));
    connect(this, SIGNAL(removedEmployee(int)), employeeListView, SLOT(removeEmployee(int)));
    connect(employeeListView, SIGNAL(createEmployee(QHash<QString,QVariant>)), this, SLOT(createEmployee(QHash<QString,QVariant>)));
    connect(this, SIGNAL(createdEmployee(QHash<QString,QVariant>)), employeeListView, SLOT(addEmployee(QHash<QString,QVariant>)));
    connect(employeeListView, SIGNAL(selectEmployee(int)), this, SLOT(selectEmployee(int)));
    connect(this, SIGNAL(updatedEmployee(QHash<QString,QVariant>)), employeeListView, SLOT(updateEmployee(QHash<QString,QVariant>)));
    connect(this, SIGNAL(selectedEmployee(QHash<QString,QVariant>)), employeeView, SLOT(setEmployee(QHash<QString,QVariant>)));
    connect(employeeView, SIGNAL(saveEmployee(QHash<QString,QVariant>)), this, SLOT(saveEmployee(QHash<QString,QVariant>)));

    //BodyMeasurement View signal/slots
    connect(bodyMeasurementView, SIGNAL(saveBodyMeasurement(QHash<QString,QVariant>)), this, SLOT(saveBodyMeasurement(QHash<QString,QVariant>)));
    connect(this, SIGNAL(selectedBodyMeasurement(QHash<QString,QVariant>)), bodyMeasurementView, SLOT(setBodyMeasurement(QHash<QString,QVariant>)));

    //EmployeePopUp signal/slots
    connect(employeePopUp, SIGNAL(saveEmployeeSelected(int)), this, SLOT(setSelectedEmployee(int)));
    connect(employeePopUp, SIGNAL(resetEmployeeSelection()), this, SLOT(resetEmployeeSelection()));
    connect(this, SIGNAL(employeeSelected(int)), employeePopUp, SLOT(setEmployeeSelected(int)));
    connect(this, SIGNAL(clearAll()), employeePopUp, SLOT(clearEmployees()));
    connect(this, SIGNAL(clearEmployees()), employeePopUp, SLOT(clearEmployees()));
    connect(this, SIGNAL(updatedEmployee(QHash<QString,QVariant>)), employeePopUp, SLOT(updateEmployee(QHash<QString,QVariant>)));
    connect(this, SIGNAL(createdEmployee(QHash<QString,QVariant>)), employeePopUp, SLOT(addEmployee(QHash<QString,QVariant>)));
    connect(this, SIGNAL(removedEmployee(int)), employeePopUp, SLOT(removeEmployee(int)));

    //Line View signal/slots
    connect(this, SIGNAL(clearAll()), lineView, SLOT(clearLines()));
    connect(this, SIGNAL(clearLines()), lineView, SLOT(clearLines()));
    connect(lineView, SIGNAL(createLine(QHash<QString,QVariant>)), this, SLOT(createLine(QHash<QString,QVariant>)));
    connect(this, SIGNAL(createdLine(QHash<QString,QVariant>)), lineView, SLOT(addLine(QHash<QString,QVariant>)));
    connect(lineView, SIGNAL(deleteLine(int)), this, SLOT(deleteLine(int)));
    connect(this, SIGNAL(removedLine(int)), lineView, SLOT(removeLine(int)));
    connect(lineView, SIGNAL(selectLine(int)), this, SLOT(selectLine(int)));
    connect(this, SIGNAL(selectedLine(QHash<QString,QVariant>)), lineView, SLOT(selectedLine(QHash<QString,QVariant>)));
    connect(lineView, SIGNAL(editLine(int)), this, SLOT(editLine(int)));
    connect(this, SIGNAL(updatedLine(QHash<QString,QVariant>)), lineView, SLOT(updateLine(QHash<QString,QVariant>)));

    //LinePopUp signal/slots
    connect(this, SIGNAL(editLine(QHash<QString,QVariant>)), linePopUp, SLOT(setLine(QHash<QString, QVariant>)));
    connect(linePopUp, SIGNAL(saveLine(QHash<QString, QVariant>)), this, SLOT(saveLine(QHash<QString,QVariant>)));

    //ProductView signal/slots
    connect(this, SIGNAL(clearAll()), productView, SLOT(clearProducts()));
    connect(this, SIGNAL(clearProducts()), productView, SLOT(clearProducts()));
    connect(productView, SIGNAL(createProduct(QHash<QString,QVariant>)), this, SLOT(createProduct(QHash<QString,QVariant>)));
    connect(this, SIGNAL(createdProduct(QHash<QString,QVariant>)), productView, SLOT(addProduct(QHash<QString,QVariant>)));
    connect(productView, SIGNAL(deleteProduct(int)), this, SLOT(deleteProduct(int)));
    connect(this, SIGNAL(removedProduct(int)), productView, SLOT(removeProduct(int)));
    connect(this, SIGNAL(updatedProduct(QHash<QString,QVariant>)), productView, SLOT(updateProduct(QHash<QString,QVariant>)));

    //CreateProductPopUp signal/slots
    connect(createProductPopUp, SIGNAL(saveProduct(QHash<QString, QVariant>)), this, SLOT(createProduct(QHash<QString,QVariant>)));

    //ActivityPopUp signal/slots
    connect(this, SIGNAL(clearAll()), activityPopUp, SLOT(clearProducts()));
    connect(this, SIGNAL(clearProducts()), activityPopUp, SLOT(clearProducts()));
    connect(this, SIGNAL(createdProduct(QHash<QString,QVariant>)), activityPopUp, SLOT(addProduct(QHash<QString,QVariant>)));
    connect(this, SIGNAL(removedProduct(int)), activityPopUp, SLOT(removeProduct(int)));
    connect(this, SIGNAL(updatedProduct(QHash<QString,QVariant>)), activityPopUp, SLOT(updateProduct(QHash<QString,QVariant>)));
    connect(this, SIGNAL(editActivity(QHash<QString,QVariant>)), activityPopUp, SLOT(setActivity(QHash<QString,QVariant>)));
    connect(activityPopUp, SIGNAL(saveActivity(QHash<QString,QVariant>)), this, SLOT(saveActivity(QHash<QString,QVariant>)));

    //ActivityView signal/slots
    connect(this, SIGNAL(clearAll()), activityView, SLOT(clearProducts()));
    connect(this, SIGNAL(clearProducts()), activityView, SLOT(clearProducts()));
    connect(this, SIGNAL(createdProduct(QHash<QString,QVariant>)), activityView, SLOT(addProduct(QHash<QString,QVariant>)));
    connect(this, SIGNAL(removedProduct(int)), activityView, SLOT(removeProduct(int)));
    connect(this, SIGNAL(updatedProduct(QHash<QString,QVariant>)), activityView, SLOT(updateProduct(QHash<QString,QVariant>)));
    connect(this, SIGNAL(clearAll()), activityView, SLOT(clearActivities()));
    connect(this, SIGNAL(clearActivities()), activityView, SLOT(clearActivities()));
    connect(activityView, SIGNAL(createActivity(QHash<QString,QVariant>)), this, SLOT(createActivity(QHash<QString,QVariant>)));
    connect(this, SIGNAL(createdActivity(QHash<QString,QVariant>)), activityView, SLOT(addActivity(QHash<QString,QVariant>)));
    connect(activityView, SIGNAL(deleteActivity(int)), this, SLOT(deleteActivity(int)));
    connect(this, SIGNAL(removedActivity(int)), activityView, SLOT(removeActivity(int)));
    connect(activityView, SIGNAL(editActivity(int)), this, SLOT(editActivity(int)));
    connect(this, SIGNAL(updatedActivity(QHash<QString,QVariant>)), activityView, SLOT(updateActivity(QHash<QString,QVariant>)));
    connect(activityView, SIGNAL(selectActivity(int)), this, SLOT(selectACtivity(int)));

    //Equipment View signals/slots
    connect(this, SIGNAL(clearAll()), equipmentView, SLOT(clearEquipments()));
    connect(this, SIGNAL(clearEquipments()), equipmentView, SLOT(clearEquipments()));
    connect(equipmentView, SIGNAL(createEquipment(QHash<QString,QVariant>)), this, SLOT(createEquipment(QHash<QString,QVariant>)));
    connect(this, SIGNAL(createdEquipment(QHash<QString,QVariant>)), equipmentView, SLOT(addEquipment(QHash<QString,QVariant>)));
    connect(equipmentView, SIGNAL(deleteEquipment(int)), this, SLOT(deleteEquipment(int)));
    connect(this, SIGNAL(removedEquipment(int)), equipmentView, SLOT(removeEquipment(int)));
    connect(this, SIGNAL(updatedEquipment(QHash<QString,QVariant>)), equipmentView, SLOT(updateEquipment(QHash<QString,QVariant>)));

    //EquipmentPopUp signals/slots
    connect(equipmentPopUp, SIGNAL(saveEquipment(QHash<QString,QVariant>)), this, SLOT(createEquipment(QHash<QString,QVariant>)));

    //WorkProcessMetaData View signals/slots
    connect(this, SIGNAL(clearAll()), workProcessMetaDataView, SLOT(clearEquipments()));
    connect(this, SIGNAL(clearEquipments()), workProcessMetaDataView, SLOT(clearEquipments()));
    connect(this, SIGNAL(createdEquipment(QHash<QString,QVariant>)), workProcessMetaDataView, SLOT(addEquipment(QHash<QString,QVariant>)));
    connect(this, SIGNAL(updatedEquipment(QHash<QString,QVariant>)), workProcessMetaDataView, SLOT(updateEquipment(QHash<QString,QVariant>)));
    connect(this, SIGNAL(removedEquipment(int)), workProcessMetaDataView, SLOT(removeEquipment(int)));
    connect(workProcessMetaDataView, SIGNAL(saveWorkProcess(QHash<QString, QVariant>)), this, SLOT(saveWorkProcess(QHash<QString,QVariant>)));
    connect(this, SIGNAL(setWorkProcess(QHash<QString,QVariant>)), workProcessMetaDataView, SLOT(setWorkProcess(QHash<QString, QVariant>)));

    //TransportationView signals/slots
    connect(this, SIGNAL(clearAll()), transportationView, SLOT(clearTransportations()));
    connect(this, SIGNAL(clearTransportations()), transportationView, SLOT(clearTransportations()));
    connect(transportationView, SIGNAL(createTransportation(QHash<QString,QVariant>)), this, SLOT(createTransportation(QHash<QString,QVariant>)));
    connect(this, SIGNAL(createdTransportation(QHash<QString,QVariant>)), transportationView, SLOT(addTransportation(QHash<QString,QVariant>)));
    connect(transportationView, SIGNAL(deleteTransportation(int)), this, SLOT(deleteTransportation(int)));
    connect(this, SIGNAL(removedTransportation(int)), transportationView, SLOT(removeTransportation(int)));
    connect(this, SIGNAL(updatedTransportation(QHash<QString,QVariant>)), transportationView, SLOT(updateTransportation(QHash<QString,QVariant>)));

    //TransportationPopUp signals/slots
    connect(transportationPopUp, SIGNAL(saveTransportation(QHash<QString,QVariant>)), this, SLOT(createTransportation(QHash<QString,QVariant>)));

    //LoadHandling View signals/slots
    connect(this, SIGNAL(clearAll()), loadHandlingView, SLOT(clearTransportations()));
    connect(this, SIGNAL(clearTransportations()), loadHandlingView, SLOT(clearTransportations()));
    connect(this, SIGNAL(createdTransportation(QHash<QString,QVariant>)), loadHandlingView, SLOT(addTransportation(QHash<QString,QVariant>)));
    connect(this, SIGNAL(removedTransportation(int)), loadHandlingView, SLOT(removeTransportation(int)));
    connect(this, SIGNAL(updatedTransportation(QHash<QString,QVariant>)), loadHandlingView, SLOT(updateTransportation(QHash<QString,QVariant>)));
    connect(loadHandlingView, SIGNAL(saveLoadHandling(QHash<QString,QVariant>)), this, SLOT(saveLoadHandling(QHash<QString,QVariant>)));
    connect(this, SIGNAL(setLoadHandling(QHash<QString,QVariant>)), loadHandlingView, SLOT(setLoadHandling(QHash<QString,QVariant>)));

    //AppliedForce View signals/slots
    connect(appliedForceView, SIGNAL(saveAppliedForce(QHash<QString, QVariant>)), this, SLOT(saveAppliedForce(QHash<QString,QVariant>)));
    connect(this, SIGNAL(setAppliedForce(QHash<QString,QVariant>)), appliedForceView, SLOT(setAppliedForce(QHash<QString, QVariant>)));

    //ExecutionCondition View signals/slots
    connect(executionConditionView, SIGNAL(saveExecutionCondition(QHash<QString, QVariant>)), this, SLOT(saveExecutionCondition(QHash<QString,QVariant>)));
    connect(this, SIGNAL(setExecutionCondition(QHash<QString,QVariant>)), executionConditionView, SLOT(setExecutionCondition(QHash<QString, QVariant>)));

    //BodyPosture View signals/slots
    connect(bodyPostureView, SIGNAL(saveBodyPosture(QHash<QString,QVariant>)), this, SLOT(saveBodyPosture(QHash<QString,QVariant>)));
    connect(this, SIGNAL(setBodyPosture(QHash<QString,QVariant>)), bodyPostureView, SLOT(setBodyPosture(QHash<QString,QVariant>)));

    //GanttTimer View signals/slots
    connect(gantTimerView, SIGNAL(selectWorkProcess(int, AVType)), this, SLOT(selectWorkProcess(int, AVType)));
    connect(gantTimerView, SIGNAL(saveWorkProcessFrequence(int)), this, SLOT(saveWorkProcessFrequence(int)));
    connect(this, SIGNAL(initiliazedWorkProcesses(QList<QHash<QString,QVariant> >)), gantTimerView, SLOT(initiliazeWorkProcesses(QList<QHash<QString,QVariant> >)));
    connect(this, SIGNAL(setSelectedWorkProcess(QHash<QString,QVariant>)), gantTimerView, SLOT(setSelectedWorkProcess(QHash<QString,QVariant>)));
    connect(this, SIGNAL(createdWorkProcess(QHash<QString, QVariant>)), gantTimerView, SLOT(addWorkProcess(QHash<QString,QVariant>)));
    connect(this, SIGNAL(resettedWorkProcesses()), gantTimerView, SLOT(resetWorkProcesses()));

    connect(gantTimerView, SIGNAL(entered()), timerViewController, SLOT(gantViewShown()));
    connect(gantTimerView, SIGNAL(left()), timerViewController, SLOT(gantViewHidden()));

    //WorkProcessControll
    connect(this, SIGNAL(initiliazedWorkProcesses(QList<QHash<QString,QVariant> >)), timerViewController, SLOT(initiliazedWorkProcesses(QList<QHash<QString,QVariant> >)));
    connect(timerViewController, SIGNAL(createWorkProcess(QHash<QString,QVariant>)), this, SLOT(createWorkprocess(QHash<QString,QVariant>)));
    connect(this, SIGNAL(setSelectedWorkProcess(QHash<QString,QVariant>)), timerViewController, SLOT(setSelectedWorkProcess(QHash<QString,QVariant>)));
    connect(timerViewController, SIGNAL(selectPreviousWorkProcess()), this, SLOT(selectPreviousWorkProcess()));
    connect(this, SIGNAL(setHasPreviousWorkProcess(bool)), timerViewController, SLOT(setHasPreviousWorkProcess(bool)));
    connect(this, SIGNAL(setHasNextWorkProcess(bool)), timerViewController, SLOT(setHasNextWorkProcess(bool)));
    connect(timerViewController, SIGNAL(selectNextWorkProcess()), this, SLOT(selectNextWorkProcess()));
    connect(this, SIGNAL(setSelectedWorkProcessType(AVType)), timerViewController, SLOT(setSelectedWorkProcessType(AVType)));
    connect(timerViewController, SIGNAL(workProcessTypeChanged(AVType)), this, SLOT(workProcessTypeChanged(AVType)));
    connect(timerViewController, SIGNAL(workProcessDurationChanged(QTime)), this, SLOT(workProcessDurationChanged(QTime)));
    connect(timerViewController, SIGNAL(resetWorkProcesses()), this, SLOT(resetWorkProcesses()));


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
    viewCon->registerPopUp(createProductPopUp, PopUpType::CREATE_PRODUCT_POPUP);
    viewCon->registerPopUp(analystPopUp, PopUpType::ANALYST_POPUP);
    viewCon->registerPopUp(activityPopUp, PopUpType::ACTIVITY_POPUP);
    viewCon->registerPopUp(languagePopUp, PopUpType::LANGUAGE_POPUP);
    viewCon->registerPopUp(themePopUp, PopUpType::THEME_POPUP);
    viewCon->registerPopUp(workplacePopUp, PopUpType::WORKPLACE_POPUP);
    viewCon->registerPopUp(importDataPopUp, PopUpType::IMPORT_DATA_POPUP);
    viewCon->registerPopUp(resetPopUp, PopUpType::RESET_POPUP);
    viewCon->registerPopUp(employeePopUp,PopUpType::EMPlOYEE_POPUP);
    viewCon->registerPopUp(factorySettingsPopUp, PopUpType::FACTORYSETTINGS_POPUP);
    viewCon->registerPopUp(linePopUp, PopUpType::LINE_POPUP);

    //Set the start Views
    documentationView->showStartView(ViewType::BODY_POSTURE_VIEW);
    viewCon->showStartView(ViewType::ANALYST_SELECTION_VIEW);

    initializeProducts();
    initializeTansportations();
    initializeEquipments();
    initializeEmployees();
    initializeLines();
    initializeWorkplaces();
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
    emit createdWorkplace(values);
    values.clear();
    values.insert(DBConstants::COL_ACTIVITY_DESCRIPTION, tr("Autogenerated activity"));
    values.insert(DBConstants::COL_ACTIVITY_WORKPLACE_ID, workplace_ID);
    activity_ID = dbHandler->insert(DBConstants::TBL_ACTIVITY, DBConstants::HASH_ACTIVITY_TYPES, values, DBConstants::COL_ACTIVITY_ID);

    QList<ViewType> prevViews = QList<ViewType>();
    prevViews.append(ViewType::WORKPLACE_VIEW);
    prevViews.append(ViewType::ACTIVITY_VIEW);

    selectWorkplace(workplace_ID);

    viewCon->showView(ViewType::DOCUMENTATION_VIEW, &prevViews);
    selectWorkProcess(1, AVType::BASIC);
    initilizeWorkProcesses();
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


//WorkplaceView
void Controller::initializeWorkplaces(){
    emit clearWorkplaces();
    QList<QHash<QString, QVariant>> rows = dbHandler->select(DBConstants::TBL_WORKPLACE, QString(""));
    for(int i = 0; i < rows.count(); ++i)
        emit createWorkplace(rows.at(i));
}

void Controller::createWorkplace(QHash<QString, QVariant> values){
    int wp_ID = dbHandler->insert(DBConstants::TBL_WORKPLACE, DBConstants::HASH_WORKPLACE_TYPES, values, DBConstants::COL_WORKPLACE_ID);
    values.insert(DBConstants::COL_WORKPLACE_ID, wp_ID);
    emit createdWorkplace(values);
    saveRecordingObservesWorkplace(wp_ID);
}

void Controller::createWorkplace(QHash<QString, QVariant> values, QList<QHash<QString, QVariant>> activityValues){
    int workplace_ID = dbHandler->insert(DBConstants::TBL_WORKPLACE, DBConstants::HASH_WORKPLACE_TYPES, values,DBConstants::COL_WORKPLACE_ID);
    values.insert(DBConstants::COL_WORKPLACE_ID, workplace_ID);
    emit createdWorkplace(values);
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

void Controller::deleteWorkplace(int id){
    QString tbl = DBConstants::TBL_WORKPLACE;
    dbHandler->deleteAll(tbl, QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_ID).arg(QString::number(id)));

    deleteRecordingOberservesWorkplace(id);

    QList<QHash<QString, QVariant>> values = dbHandler->select(DBConstants::TBL_ACTIVITY, QString("%1 = %2").arg(DBConstants::COL_ACTIVITY_WORKPLACE_ID).arg(id));
    for(int i = 0; i < values.count(); ++i)
        deleteActivity(values.at(i).value(DBConstants::COL_ACTIVITY_ID).toInt(), false);

    dbHandler->deleteAll(DBConstants::TBL_COMMENT, QString("%1 = %2").arg(DBConstants::COL_COMMENT_WORKPLACE_ID).arg(id));

    viewCon->showMessage(tr("Deleted workplace"), NotificationMessage::ACCEPT);

    emit removedWorkplace(id);
}

void Controller::selectWorkplace(int id){
    QHash<QString, QVariant> values = dbHandler->selectFirst(DBConstants::TBL_WORKPLACE, QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_ID).arg(id));
    workplace_ID = id;
    emit selectedWorkplace(values);
    selectedEmployee_ID = values.value(DBConstants::COL_WORKPLACE_EMPLOYEE_ID).toInt();
    emit employeeSelected(selectedEmployee_ID);
    values = dbHandler->selectFirst(DBConstants::TBL_LINE, QString("%1 = %2").arg(DBConstants::COL_LINE_ID).arg(values.value(DBConstants::COL_WORKPLACE_LINE_ID).toInt()));
    emit selectedLine(values);
    values = dbHandler->selectFirst(DBConstants::TBL_COMMENT, QString("%1 = %2").arg(DBConstants::COL_COMMENT_WORKPLACE_ID).arg(workplace_ID));
    emit selectedComment(values);
    initializeActivities(id);
}

void Controller::saveWorkplace(QHash<QString, QVariant> values){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_ID).arg(workplace_ID);
    values.insert(DBConstants::COL_WORKPLACE_ID, workplace_ID);
    values.insert(DBConstants::COL_WORKPLACE_EMPLOYEE_ID, selectedEmployee_ID);
    dbHandler->update(DBConstants::TBL_WORKPLACE, DBConstants::HASH_WORKPLACE_TYPES, values, filter);
    emit updatedWorkplace(values);
}

//Comment
void Controller::saveComment(QHash<QString, QVariant> values){
    values.insert(DBConstants::COL_COMMENT_WORKPLACE_ID, workplace_ID);
    QString filter = QString("%1 = %2").arg(DBConstants::COL_COMMENT_WORKPLACE_ID).arg(workplace_ID);
    dbHandler->save(DBConstants::TBL_COMMENT, DBConstants::HASH_COMMENT_TYPES, values, filter, DBConstants::COL_COMMENT_ID);
    emit updatedComment(values);
}

//Line
void Controller::initializeLines(){
    emit clearLines();
    QList<QHash<QString, QVariant>> rows = dbHandler->select(DBConstants::TBL_LINE, QString(""));
    for(int i = 0; i < rows.count(); ++i)
        emit createdLine(rows.at(i));
}


void Controller::createLine(QHash<QString, QVariant> values){
    values.insert(DBConstants::COL_LINE_FACTORY_ID, factory_ID);
    int line_ID = dbHandler->insert(DBConstants::TBL_LINE, DBConstants::HASH_LINE_TYPES, values, DBConstants::COL_LINE_ID);
    values.insert(DBConstants::COL_LINE_ID, line_ID);
    saveRecordingObservesLine(line_ID);
    emit createdLine(values);
}

void Controller::editLine(int id){
    QHash<QString, QVariant> values = dbHandler->selectFirst(DBConstants::TBL_LINE, QString("%1 = %2").arg(DBConstants::COL_LINE_ID).arg(id));
    emit editLine(values);
}

void Controller::saveLine(QHash<QString, QVariant> values){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_LINE_ID).arg(values.value(DBConstants::COL_LINE_ID).toInt());
    dbHandler->update(DBConstants::TBL_LINE, DBConstants::HASH_LINE_TYPES, values, filter);
    emit updatedLine(values);
}

void Controller::deleteLine(int id){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_LINE_ID).arg(id);
    dbHandler->deleteAll(DBConstants::TBL_LINE, filter);
    deleteRecordingObservesLine(id);
    emit removedLine(id);
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_WORKPLACE_LINE_ID, 0);
    filter = QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_LINE_ID).arg(id);
    dbHandler->update(DBConstants::TBL_WORKPLACE, DBConstants::HASH_WORKPLACE_TYPES, values, filter);
}

void Controller::selectLine(int id){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_LINE_ID).arg(id);
    QHash<QString, QVariant> lineValues = dbHandler->selectFirst(DBConstants::TBL_LINE, filter);
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_WORKPLACE_LINE_ID, id);
    filter = QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_ID).arg(workplace_ID);
    dbHandler->update(DBConstants::TBL_WORKPLACE, DBConstants::HASH_WORKPLACE_TYPES, values, filter);
    selectedLine(lineValues);
}

//Product
void Controller::initializeProducts(){
    emit clearProducts();
    QList<QHash<QString, QVariant>> rows = dbHandler->select(DBConstants::TBL_PRODUCT, QString(""));
    for(int i = 0; i < rows.count(); ++i)
        emit createdProduct(rows.at(i));
}

void Controller::createProduct(QHash<QString, QVariant> values){
    int prod_ID = dbHandler->insert(DBConstants::TBL_PRODUCT, DBConstants::HASH_PRODUCT_TYPES, values, DBConstants::COL_PRODUCT_ID);
    values.insert(DBConstants::COL_PRODUCT_ID, prod_ID);
    emit createdProduct(values);
}

void Controller::saveProduct(QHash<QString, QVariant> values){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_PRODUCT_ID).arg(values.value(DBConstants::COL_PRODUCT_ID).toInt());
    dbHandler->update(DBConstants::TBL_PRODUCT, DBConstants::HASH_PRODUCT_TYPES, values, filter);
    emit updatedProduct(values);
}


void Controller::deleteProduct(int id){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_PRODUCT_ID).arg(id);
    dbHandler->deleteAll(DBConstants::TBL_PRODUCT, filter);
    emit removedProduct(id);
    filter = QString("%1 = %2").arg(DBConstants::COL_ACTIVITY_PRODUCT_ID).arg(id);
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_ACTIVITY_PRODUCT_ID, 0);
    dbHandler->update(DBConstants::TBL_ACTIVITY, DBConstants::HASH_ACTIVITY_TYPES, values, filter);
}

//Equipment
void Controller::initializeEquipments(){
    emit clearEquipments();
    QList<QHash<QString, QVariant>> rows = dbHandler->select(DBConstants::TBL_EQUIPMENT, QString(""));
    for(int i = 0; i < rows.count(); ++i)
        emit createdEquipment(rows.at(i));
}

void Controller::createEquipment(QHash<QString, QVariant> values){
    int eq_ID = dbHandler->insert(DBConstants::TBL_EQUIPMENT, DBConstants::HASH_EQUIPMENT_TYPES, values, DBConstants::COL_EQUIPMENT_ID);
    values.insert(DBConstants::COL_EQUIPMENT_ID, eq_ID);
    emit createdEquipment(values);
}

void Controller::saveEquipment(QHash<QString, QVariant> values){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_EQUIPMENT_ID).arg(values.value(DBConstants::COL_EQUIPMENT_ID).toString());
    dbHandler->update(DBConstants::TBL_EQUIPMENT, DBConstants::HASH_EQUIPMENT_TYPES, values, filter);
    emit updatedEquipment(values);
}

void Controller::deleteEquipment(int id){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_EQUIPMENT_ID).arg(id);
    dbHandler->deleteAll(DBConstants::TBL_EQUIPMENT, filter);
    emit removedEquipment(id);
}

//Activity
void Controller::initializeActivities(int workplace_ID){
    emit clearActivities();
    QString filter = QString("%1 = %2").arg(DBConstants::COL_ACTIVITY_WORKPLACE_ID).arg(workplace_ID);
    QList<QHash<QString, QVariant>> rows = dbHandler->select(DBConstants::TBL_ACTIVITY, filter);
    for(int i = 0; i < rows.count(); ++i)
        emit createActivity(rows.at(i));
}

void Controller::createActivity(QHash<QString, QVariant> values){
   values.insert(DBConstants::COL_ACTIVITY_WORKPLACE_ID, workplace_ID);
   int ac_ID = dbHandler->insert(DBConstants::TBL_ACTIVITY, DBConstants::HASH_ACTIVITY_TYPES, values, DBConstants::COL_ACTIVITY_ID);
   values.insert(DBConstants::COL_ACTIVITY_ID, ac_ID);
   emit createdActivity(values);
}

void Controller::saveActivity(QHash<QString, QVariant> values){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_ACTIVITY_ID).arg(values.value(DBConstants::COL_ACTIVITY_ID).toInt());
    values.insert(DBConstants::COL_ACTIVITY_WORKPLACE_ID, workplace_ID);
    dbHandler->update(DBConstants::TBL_ACTIVITY, DBConstants::HASH_ACTIVITY_TYPES, values, filter);
    emit updatedActivity(values);
}

void Controller::deleteActivity(int id, bool showMessage){
    dbHandler->deleteAll(DBConstants::TBL_ACTIVITY, QString("%1 = %2").arg(DBConstants::COL_ACTIVITY_ID).arg(id));
    deleteWorkProcesses(id);
    emit removedActivity(id);
    if(showMessage)
        viewCon->showMessage(tr("Deleted activity"), NotificationMessage::ACCEPT);
}

void Controller::selectACtivity(int id){
    activity_ID = id;
    initilizeWorkProcesses();
}

void Controller::editActivity(int id){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_ACTIVITY_ID).arg(id);
    QHash<QString, QVariant> values = dbHandler->selectFirst(DBConstants::TBL_ACTIVITY, filter);
    emit editActivity(values);
}


//Transportation
void Controller::initializeTansportations(){
    emit clearTransportations();
    QList<QHash<QString, QVariant>> rows = dbHandler->select(DBConstants::TBL_TRANSPORTATION, QString(""));
    for(int i = 0; i < rows.count(); ++i)
        emit createdTransportation(rows.at(i));
}

void Controller::createTransportation(QHash<QString, QVariant> values){
    int trans_ID = dbHandler->insert(DBConstants::TBL_TRANSPORTATION, DBConstants::HASH_TRANSPORTATION_TYPES, values, DBConstants::COL_TRANSPORTATION_ID);
    values.insert(DBConstants::COL_TRANSPORTATION_ID, trans_ID);
    emit createdTransportation(values);
}

void Controller::saveTransportation(QHash<QString, QVariant> values){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_TRANSPORTATION_ID).arg(values.value(DBConstants::COL_TRANSPORTATION_ID).toString());
    dbHandler->update(DBConstants::TBL_TRANSPORTATION, DBConstants::HASH_TRANSPORTATION_TYPES, values, filter);
    emit updatedTransportation(values);
}

void Controller::deleteTransportation(int id){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_TRANSPORTATION_ID).arg(id);
    dbHandler->deleteAll(DBConstants::TBL_TRANSPORTATION, filter);
    emit removedTransportation(id);
}

//LoadHandling
void Controller::saveLoadHandling(QHash<QString, QVariant> values){
    QString filter = QString("%1 = '%2'").arg(DBConstants::COL_LOAD_HANDLING_TYPE_NAME).arg(values.value(DBConstants::COL_LOAD_HANDLING_TYPE_NAME).toString());
    QHash<QString, QVariant> loadType = dbHandler->selectFirst(DBConstants::TBL_LOAD_HANDLING_TYPE, filter);
    if(loadType.isEmpty()){
        loadType.insert(DBConstants::COL_LOAD_HANDLING_TYPE_NAME, values.value(DBConstants::COL_LOAD_HANDLING_TYPE_NAME).toString());
        int lt_ID = dbHandler->insert(DBConstants::TBL_LOAD_HANDLING_TYPE, DBConstants::HASH_LOAD_HANDLING_TYPE_TYPES, loadType, DBConstants::COL_LOAD_HANDLING_TYPE_ID);
        loadType.insert(DBConstants::COL_LOAD_HANDLING_TYPE_ID, lt_ID);
    }
    values.insert(DBConstants::COL_LOAD_HANDLING_LOAD_HANDLING_TYPE_ID, loadType.value(DBConstants::COL_LOAD_HANDLING_TYPE_ID));
    values.remove(DBConstants::COL_LOAD_HANDLING_TYPE_NAME);

    filter = QString("%1 = '%2'").arg(DBConstants::COL_TYPE_OF_GRASPING_NAME).arg(values.value(DBConstants::COL_TYPE_OF_GRASPING_NAME).toString());
    QHash<QString, QVariant> graspType = dbHandler->selectFirst(DBConstants::TBL_TYPE_OF_GRASPING, filter);
    if(graspType.isEmpty()){
        graspType.insert(DBConstants::COL_TYPE_OF_GRASPING_NAME, values.value(DBConstants::COL_TYPE_OF_GRASPING_NAME).toString());
        int gt_ID = dbHandler->insert(DBConstants::TBL_TYPE_OF_GRASPING, DBConstants::HASH_TYPE_OF_GRASPING_TYPES, graspType, DBConstants::COL_TYPE_OF_GRASPING_ID);
        graspType.insert(DBConstants::COL_TYPE_OF_GRASPING_ID, gt_ID);
    }
    values.insert(DBConstants::COL_LOAD_HANDLING_TYPE_OF_GRASPING, graspType.value(DBConstants::COL_TYPE_OF_GRASPING_ID));
    values.remove(DBConstants::COL_TYPE_OF_GRASPING_NAME);

    filter = QString("%1 = %2").arg(DBConstants::COL_LOAD_HANDLING_ID).arg(loadhandling_ID);
    int l_ID = dbHandler->save(DBConstants::TBL_LOAD_HANDLING, DBConstants::HASH_LOAD_HANDLING_TYPES, values, filter, DBConstants::COL_LOAD_HANDLING_ID);
    if(l_ID > 0)
        loadhandling_ID = l_ID;
    values.insert(DBConstants::COL_LOAD_HANDLING_ID, loadhandling_ID);
    emit setLoadHandling(values);
    saveWorkProcess(QHash<QString, QVariant>());
}

//BodyPosture
void Controller::saveBodyPosture(QHash<QString, QVariant> values){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_BODY_POSTURE_ID).arg(bodyPosture_ID);
    int bp_ID = dbHandler->save(DBConstants::TBL_BODY_POSTURE, DBConstants::HASH_BODY_POSTURE_TYPES, values, filter, DBConstants::COL_BODY_POSTURE_ID);
    if(bp_ID > 0)
        bodyPosture_ID = bp_ID;
    values.insert(DBConstants::COL_BODY_POSTURE_ID, bodyPosture_ID);
    emit setBodyPosture(values);
    saveWorkProcess(QHash<QString, QVariant>());
}

//AppliedForce
void Controller::saveAppliedForce(QHash<QString, QVariant> values){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_APPLIED_FORCE_ID).arg(appliedforce_ID);
    int af_ID = dbHandler->save(DBConstants::TBL_APPLIED_FORCE, DBConstants::HASH_APPLIED_FORCE_TYPES, values, filter, DBConstants::COL_APPLIED_FORCE_ID);
    if(af_ID > 0)
        appliedforce_ID = af_ID;
    values.insert(DBConstants::COL_APPLIED_FORCE_ID, appliedforce_ID);
    emit setAppliedForce(values);
    saveWorkProcess(QHash<QString, QVariant>());
}

//WorkProcess
void Controller::saveWorkProcess(QHash<QString, QVariant> values){
    QString filter = QString("%1 = %2 AND %3 = %4 AND %5 = %6").arg(DBConstants::COL_WORK_PROCESS_ACTIVITY_ID).arg(activity_ID).arg(DBConstants::COL_WORK_PROCESS_ID).arg(workprocess_ID).arg(DBConstants::COL_WORK_PROCESS_TYPE).arg(workprocess_Type);
    values.insert(DBConstants::COL_WORK_PROCESS_ID, workprocess_ID);
    values.insert(DBConstants::COL_WORK_PROCESS_ACTIVITY_ID, activity_ID);
    values.insert(DBConstants::COL_WORK_PROCESS_TYPE, workprocess_Type);
    values.insert(DBConstants::COL_WORK_PROCESS_APPLIED_FORCE_ID, appliedforce_ID);
    values.insert(DBConstants::COL_WORK_PROCESS_CONDITION_ID, workcondition_ID);
    values.insert(DBConstants::COL_WORK_PROCESS_LOAD_HANDLING_ID, loadhandling_ID);
    values.insert(DBConstants::COL_WORK_PROCESS_POSTURE_ID, bodyPosture_ID);
    dbHandler->update(DBConstants::TBL_WORK_PROCESS, DBConstants::HASH_WORK_PROCESS_TYPES, values, filter);
    emit setWorkProcess(values);
}

//ExecutionCondition
void Controller::saveExecutionCondition(QHash<QString, QVariant> values){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_WORK_CONDITION_ID).arg(workcondition_ID);
    int wc_ID = dbHandler->save(DBConstants::TBL_WORK_CONDITION, DBConstants::HASH_WORK_CONDITION_TYPES, values, filter, DBConstants::COL_WORK_CONDITION_ID);
    if(wc_ID > 0)
        workcondition_ID = wc_ID;
    values.insert(DBConstants::COL_WORK_CONDITION_ID, workcondition_ID);
    emit setExecutionCondition(values);
    saveWorkProcess(QHash<QString, QVariant>());
}

//Employee
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

void Controller::setSelectedEmployee(int id){
    selectedEmployee_ID = id;
}

void Controller::resetEmployeeSelection(){
    emit employeeSelected(selectedEmployee_ID);
}

//BodyMeasurement
void Controller::saveBodyMeasurement(QHash<QString, QVariant> values){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_BODY_MEASUREMENT_ID).arg(bodyMeasurement_ID);
    dbHandler->save(DBConstants::TBL_BODY_MEASUREMENT, DBConstants::HASH_BODY_MEASUREMENT_TYPES, values, filter, DBConstants::COL_BODY_MEASUREMENT_ID);
}


//WorkProcessControll
void Controller::initilizeWorkProcesses(bool selectFirst){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_WORK_PROCESS_ACTIVITY_ID).arg(activity_ID);
    QList<QHash<QString, QVariant>> values = dbHandler->select(DBConstants::TBL_WORK_PROCESS, filter);
    emit initiliazedWorkProcesses(values);
    if(selectFirst)
        selectWorkProcess(1, AVType::BASIC);
}

void Controller::createWorkprocess(QHash<QString, QVariant> values){
    AVType type = (AVType) values.value(DBConstants::COL_WORK_PROCESS_TYPE).toInt();
    QString filter = QString("%1 = %2 AND %3 = %4").arg(DBConstants::COL_WORK_PROCESS_ACTIVITY_ID).arg(activity_ID).arg(DBConstants::COL_WORK_PROCESS_TYPE).arg(type);

    int id = dbHandler->getNextID(DBConstants::TBL_WORK_PROCESS, DBConstants::COL_WORK_PROCESS_ID, filter);
    values.insert(DBConstants::COL_WORK_PROCESS_ID, id);
    values.insert(DBConstants::COL_WORK_PROCESS_ACTIVITY_ID, activity_ID);
    values.insert(DBConstants::COL_WORK_PROCESS_TYPE, type);
    dbHandler->insert(DBConstants::TBL_WORK_PROCESS, DBConstants::HASH_WORK_PROCESS_TYPES, values, DBConstants::COL_WORK_PROCESS_ID);
    if(type == workprocess_Type && id == workprocess_ID + 1 )
        emit setHasNextWorkProcess(true);
    emit createdWorkProcess(values);
    if(type == workprocess_Type && id == 1){
        selectWorkProcess(1, type);
    }
}

void Controller::selectNextWorkProcess(){
    selectWorkProcess(workprocess_ID + 1, workprocess_Type);

}

void Controller::selectPreviousWorkProcess(){
    selectWorkProcess(workprocess_ID - 1, workprocess_Type);
}

void Controller::workProcessTypeChanged(AVType type){
    selectWorkProcess(1, type);

}

void Controller::resetWorkProcesses(){
    deleteWorkProcesses(activity_ID);
    initilizeWorkProcesses();
}

void Controller::workProcessDurationChanged(QTime time){
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
            initilizeWorkProcesses(false);
        }
}


void Controller::selectWorkProcess(int id , AVType type){
    QString absFilter = QString("%1 = %2 AND %3 = %4 AND %5 = %6").arg(DBConstants::COL_WORK_PROCESS_ACTIVITY_ID).arg(activity_ID).arg(DBConstants::COL_WORK_PROCESS_TYPE).arg(type).arg(DBConstants::COL_WORK_PROCESS_ID);
    QString filter = absFilter.arg(id);

    QString tbl = DBConstants::TBL_WORK_PROCESS;
    QHash<QString, QVariant> row = dbHandler->selectFirst(tbl, filter);
    bodyPosture_ID = row.value(DBConstants::COL_WORK_PROCESS_POSTURE_ID).toInt();
    emit setBodyPosture(dbHandler->selectFirst(DBConstants::TBL_BODY_POSTURE, QString("%1 = %2").arg(DBConstants::COL_BODY_POSTURE_ID).arg(bodyPosture_ID)));
    appliedforce_ID = row.value(DBConstants::COL_WORK_PROCESS_APPLIED_FORCE_ID).toInt();
    emit setAppliedForce(dbHandler->selectFirst(DBConstants::TBL_APPLIED_FORCE, QString("%1 = %2").arg(DBConstants::COL_APPLIED_FORCE_ID).arg(appliedforce_ID)));
    loadhandling_ID = row.value(DBConstants::COL_WORK_PROCESS_LOAD_HANDLING_ID).toInt();
    QHash<QString, QVariant> lhValues = dbHandler->selectFirst(DBConstants::TBL_LOAD_HANDLING, QString("%1 = %2").arg(DBConstants::COL_LOAD_HANDLING_ID).arg(loadhandling_ID));
    QHash<QString, QVariant> lhtValues = dbHandler->selectFirst(DBConstants::TBL_LOAD_HANDLING_TYPE, QString("%1 = %2").arg(DBConstants::COL_LOAD_HANDLING_TYPE_ID).arg(lhValues.value(DBConstants::COL_LOAD_HANDLING_LOAD_HANDLING_TYPE_ID).toString()));
    lhValues.insert(DBConstants::COL_LOAD_HANDLING_TYPE_NAME, lhtValues.value(DBConstants::COL_LOAD_HANDLING_TYPE_NAME));
    QHash<QString, QVariant> togValues = dbHandler->selectFirst(DBConstants::TBL_TYPE_OF_GRASPING, QString("%1 = %2").arg(DBConstants::COL_TYPE_OF_GRASPING_ID).arg(lhValues.value(DBConstants::COL_LOAD_HANDLING_TYPE_OF_GRASPING).toString()));
    lhValues.insert(DBConstants::COL_TYPE_OF_GRASPING_NAME, togValues.value(DBConstants::COL_TYPE_OF_GRASPING_NAME));
    emit setLoadHandling(lhValues);
    workcondition_ID = row.value(DBConstants::COL_WORK_PROCESS_CONDITION_ID).toInt();
    emit setExecutionCondition(dbHandler->selectFirst(DBConstants::TBL_WORK_CONDITION, QString("%1 = %2").arg(DBConstants::COL_WORK_CONDITION_ID).arg(workcondition_ID)));
    emit setWorkProcess(row);

    workprocess_ID = id;
    workprocess_Type = type;
    emit setSelectedWorkProcessType(type);
    emit setSelectedWorkProcess(row);
    bool hasPrevious = !dbHandler->isSelectEmpty(tbl, absFilter.arg(id - 1));
    bool hasNext = !dbHandler->isSelectEmpty(tbl, absFilter.arg(id + 1));
    emit setHasPreviousWorkProcess(hasPrevious);
    emit setHasNextWorkProcess(hasNext);
}

//Gantt
void Controller::saveWorkProcessFrequence(int frequence){
    QString filter = QString("%1 = %2 AND %3 = %4 AND %5 = %6").arg(DBConstants::COL_WORK_PROCESS_ACTIVITY_ID).arg(activity_ID).arg(DBConstants::COL_WORK_PROCESS_TYPE).arg(workprocess_Type).arg(DBConstants::COL_WORK_PROCESS_ID).arg(workprocess_ID);
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_WORK_PROCESS_FREQUENCY, frequence);
    dbHandler->update(DBConstants::TBL_WORK_PROCESS, DBConstants::HASH_WORK_PROCESS_TYPES, values, filter);

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
         out<<"german"<<','<<settings.at(1)<<','<<settings.at(2)<<','<<settings.at(3);
         file.close();
         settingsView->setCurrentLanguageIcon("germanIcon");
         viewCon->showMessage(tr("Language changed"), NotificationMessage::ACCEPT);
         viewCon->showMessage(("Neustart erforderlich um die Änderungen umzusetzen"), NotificationMessage::INFORMATION, NotificationMessage::PERSISTENT);
         break;
    case(1):
         out<<"english"<<','<<settings.at(1)<<','<<settings.at(2)<<','<<settings.at(3);
         file.close();
         settingsView->setCurrentLanguageIcon("englishIcon");
         viewCon->showMessage(tr("Language changed"), NotificationMessage::ACCEPT);
         viewCon->showMessage(("Restart App to apply changes"), NotificationMessage::INFORMATION, NotificationMessage::PERSISTENT);
         break;
    default:
         out<<"english"<<','<<settings.at(1)<<','<<settings.at(2)<<','<<settings.at(3);
         file.close();
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
            out<<settings.at(0)<<','<<"blue"<<','<<settings.at(2)<<','<<settings.at(3);
            break;
        case(1):
            settingsView->setCurrentThemeIcon("greenIcon");
            application->setStyleSheet(stringFromResource(":/assets/stylesheetGreen.qss"));
            out<<settings.at(0)<<','<<"green"<<','<<settings.at(2)<<','<<settings.at(3);
            break;
        default:
            settingsView->setCurrentThemeIcon("blueIcon");
            application->setStyleSheet(stringFromResource(":/assets/stylesheet.qss"));
            out<<settings.at(0)<<','<<"blue"<<','<<settings.at(2)<<','<<settings.at(3);
            break;
        }
    file.close();
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
        emit clearWorkplaces();
    }
    if(resetPopUp->equipmentSelected()){
        dbHandler->deleteAll(DBConstants::TBL_EQUIPMENT, emptyFilter);
        emit clearEquipments();
    }
    if(resetPopUp->productsSelected()){
        dbHandler->deleteAll(DBConstants::TBL_PRODUCT, emptyFilter);
        emit clearProducts();
    }
    if(resetPopUp->transportationSelected()){
        dbHandler->deleteAll(DBConstants::TBL_TRANSPORTATION, emptyFilter);
        emit clearTransportations();
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
