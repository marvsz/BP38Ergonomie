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
    rotationGroupTaskView(new RotationGroupTaskView()),
    rotationGroupTaskListView(new RotationGroupTaskListView()),
    settingsView(new SettingsView()),
    documentationView(new DocumentationView()),
    workProcessMetaDataView(new WorkProcessMetaDataView()),
    appliedForceView(new AppliedForceView()),
    bodyPostureView(new BodyPostureView()),
    loadHandlingView(new LoadHandlingView()),
    executionConditionView(new ExecutionConditionView()),
    gantTimerView(new GantTimerView()),
    timerViewController(new TimerViewController()),
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

    connect(mainMenuView, SIGNAL(createBlankRecording()), this, SLOT(createBlankRecording()));

    //AnalystSelectionView signals/slots
    connect(this, SIGNAL(clearAll()), analystSelectionView, SLOT(clearAnalysts()));
    connect(this, SIGNAL(clearAnalysts()), analystSelectionView, SLOT(clearAnalysts()));
    connect(this, SIGNAL(createdAnalyst(QHash<QString,QVariant>)), analystSelectionView, SLOT(addAnalyst(QHash<QString,QVariant>)));
    connect(this, SIGNAL(removedAnalyst(int)), analystSelectionView, SLOT(removeAnalyst(int)));
    connect(analystSelectionView, SIGNAL(deleteAnalyst(int)), this, SLOT(deleteAnalyst(int)));
    connect(analystSelectionView, SIGNAL(selectAnalyst(int)), this, SLOT(selectAnalyst(int)));
    connect(this, SIGNAL(updatedAnalyst(QHash<QString,QVariant>)), analystSelectionView, SLOT(updateAnalyst(QHash<QString,QVariant>)));

    //AnalystPopUp signals/slots
    connect(analystPopUp, SIGNAL(saveAnalyst(QHash<QString,QVariant>)), this, SLOT(createAnalyst(QHash<QString,QVariant>)));

    //MetaDataView signals/slots
    connect(metaDataView, SIGNAL(saveBranchOfIndustry(QHash<QString,QVariant>)), this, SLOT(saveBranchOfIndustry(QHash<QString,QVariant>)));
    connect(this, SIGNAL(settedBranchOfIndustry(QHash<QString,QVariant>)), metaDataView, SLOT(setBranchOfIndustry(QHash<QString,QVariant>)));
    connect(metaDataView, SIGNAL(saveCorperation(QHash<QString,QVariant>)), this, SLOT(saveCorperation(QHash<QString,QVariant>)));
    connect(this, SIGNAL(settedCorperation(QHash<QString,QVariant>)), metaDataView, SLOT(setCorperation(QHash<QString,QVariant>)));
    connect(metaDataView, SIGNAL(saveFactory(QHash<QString,QVariant>)), this, SLOT(saveFactory(QHash<QString,QVariant>)));
    connect(this, SIGNAL(settedFactory(QHash<QString,QVariant>)), metaDataView, SLOT(setFactory(QHash<QString,QVariant>)));
    connect(metaDataView, SIGNAL(saveRecording(QHash<QString,QVariant>)), this, SLOT(saveRecording(QHash<QString,QVariant>)));
    connect(this, SIGNAL(settedRecording(QHash<QString,QVariant>)), metaDataView, SLOT(setRecording(QHash<QString,QVariant>)));

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

    //SendDatabasePopUp signals/slots
    connect(sendDatabasePopUp, SIGNAL(initializeFTPConnections(IFTPConnections*)), this, SLOT(initializeFTPConnections(IFTPConnections*)));
    connect(sendDatabasePopUp, SIGNAL(createFTPConnection(IFTPConnections*)), this, SLOT(createFTPConnection(IFTPConnections*)));
    connect(sendDatabasePopUp, SIGNAL(editFTPConnection(IFTPConnections*,int)), this, SLOT(editFTPConnection(IFTPConnections*,int)));
    connect(sendDatabasePopUp, SIGNAL(selectFTPConnection(IFTPConnections*,int)), this, SLOT(selectFTPConnection(IFTPConnections*,int)));
    connect(sendDatabasePopUp, SIGNAL(sendData(ISendData*)), this, SLOT(sendData(ISendData*)));

    //ImportDatabasePopUp signals/slots
    connect(importDataPopUp, SIGNAL(initializeFTPConnections(IFTPConnections*)), this, SLOT(initializeFTPConnections(IFTPConnections*)));
    connect(importDataPopUp, SIGNAL(createFTPConnection(IFTPConnections*)), this, SLOT(createFTPConnection(IFTPConnections*)));
    connect(importDataPopUp, SIGNAL(editFTPConnection(IFTPConnections*,int)), this, SLOT(editFTPConnection(IFTPConnections*,int)));
    connect(importDataPopUp, SIGNAL(selectFTPConnection(IFTPConnections*,int)), this, SLOT(selectFTPConnection(IFTPConnections*,int)));
    connect(importDataPopUp, SIGNAL(importData(IImportData*)), this, SLOT(importData(IImportData*)));

    //ShiftView signals/slots
    connect(shiftView, SIGNAL(saveShift(QHash<QString,QVariant>)), this, SLOT(saveShift(QHash<QString,QVariant>)));
    connect(this, SIGNAL(selectedShift(QHash<QString,QVariant>)), shiftView, SLOT(setShift(QHash<QString,QVariant>)));

    //rotationGroupTaskListView signals/slots
    connect(this, SIGNAL(clearAll()), rotationGroupTaskListView, SLOT(clearRotationGroupTasks()));
    connect(this, SIGNAL(clearRotationGroupTasks()), rotationGroupTaskListView, SLOT(clearRotationGroupTasks()));
    connect(this, SIGNAL(createdRotationGroupTask(QHash<QString,QVariant>)), rotationGroupTaskListView, SLOT(addRotationGroupTask(QHash<QString,QVariant>)));
    connect(rotationGroupTaskListView, SIGNAL(createRotationGroupTask(QHash<QString,QVariant>)), this, SLOT(createRotationGroupTask(QHash<QString,QVariant>)));
    connect(this, SIGNAL(removedRotationGroupTask(int)), rotationGroupTaskListView, SLOT(removeRotationGroupTask(int)));
    connect(rotationGroupTaskListView, SIGNAL(deleteRotationGroupTask(int)), this, SLOT(deleteRotationGroupTask(int)));
    connect(rotationGroupTaskListView, SIGNAL(selectRotationGroupTask(int)), this, SLOT(selectRotationGroupTask(int)));
    connect(this, SIGNAL(updatedRotationGroupTask(QHash<QString,QVariant>)), rotationGroupTaskListView, SLOT(updateRotationGroupTask(QHash<QString,QVariant>)));

    //rotationGroupTaskView signals/slots
    connect(this, SIGNAL(clearAll()), rotationGroupTaskView, SLOT(clearRotationGroupTaskEntries()));
    connect(this, SIGNAL(clearAll()), rotationGroupTaskView, SLOT(clearWorkplaces()));
    connect(this, SIGNAL(clearWorkplaces()), rotationGroupTaskView, SLOT(clearWorkplaces()));
    connect(this, SIGNAL(clearRotationGroupTaskEntries()), rotationGroupTaskView, SLOT(clearRotationGroupTaskEntries()));
    connect(this, SIGNAL(createdWorkplace(QHash<QString,QVariant>)), rotationGroupTaskView, SLOT(addWorkplace(QHash<QString,QVariant>)));
    connect(this, SIGNAL(updatedWorkplace(QHash<QString,QVariant>)), rotationGroupTaskView, SLOT(updateWorkplace(QHash<QString,QVariant>)));
    connect(this, SIGNAL(removedWorkplace(int)), rotationGroupTaskView, SLOT(removeWorkplace(int)));
    connect(rotationGroupTaskView, SIGNAL(createRotationGroupTaskEntry(QHash<QString,QVariant>)), this, SLOT(createRotationGroupTaskEntry(QHash<QString,QVariant>)));
    connect(this, SIGNAL(createdRotationGroupTaskEntry(QHash<QString,QVariant>)), rotationGroupTaskView, SLOT(addRotationGroupTaskEntry(QHash<QString,QVariant>)));
    connect(rotationGroupTaskView, SIGNAL(deleteRotationGroupTaskEntry(int)), this, SLOT(deleteRotationGroupTaskEntry(int)));
    connect(this, SIGNAL(removedRotationGroupTaskEntry(int)), rotationGroupTaskView, SLOT(removeRotationGroupTaskEntry(int)));
    connect(rotationGroupTaskView, SIGNAL(saveRotationGroupTask(QHash<QString,QVariant>)), this, SLOT(saveRotationGroupTask(QHash<QString,QVariant>)));
    connect(this, SIGNAL(selectedRotationGroupTask(QHash<QString,QVariant>)), rotationGroupTaskView, SLOT(setRotationGroupTask(QHash<QString,QVariant>)));
    connect(this, SIGNAL(updatedRotationGroupTaskDuration(int)), rotationGroupTaskView, SLOT(setRotationGroupTaskDuration(int)));

    //shiftCalendarView signals/slots
    connect(this, SIGNAL(clearAll()), shiftCalendarView, SLOT(clearRotationGroup()));
    connect(this, SIGNAL(clearAll()), shiftCalendarView, SLOT(clearRotationGroupTasks()));
    connect(this, SIGNAL(clearRotationGroupTasks()), shiftCalendarView, SLOT(clearRotationGroupTasks()));
    connect(this, SIGNAL(clearRotationGroup()), shiftCalendarView, SLOT(clearRotationGroup()));
    connect(this, SIGNAL(createdRotationGroupTask(QHash<QString,QVariant>)), shiftCalendarView, SLOT(addRotationGroupTask(QHash<QString,QVariant>)));
    connect(this, SIGNAL(updatedRotationGroupTask(QHash<QString,QVariant>)), shiftCalendarView, SLOT(updateRotationGroupTask(QHash<QString,QVariant>)));
    connect(this, SIGNAL(removedRotationGroupTask(int)), shiftCalendarView, SLOT(removeRotationGroupTask(int)));
    connect(this, SIGNAL(addRotationGroupBreakEntry(QHash<QString,QVariant>)), shiftCalendarView, SLOT(addRotationGroupBreakEntry(QHash<QString,QVariant>)));
    connect(this, SIGNAL(addRotationGroupEntry(QHash<QString,QVariant>)), shiftCalendarView, SLOT(addRotationGroupEntry(QHash<QString,QVariant>)));
    connect(shiftCalendarView, SIGNAL(createRotationGroupBreakEntry(QHash<QString,QVariant>)), this, SLOT(createRotationGroupBreakEntry(QHash<QString,QVariant>)));
    connect(shiftCalendarView, SIGNAL(createRotationGroupEntry(QHash<QString,QVariant>)), this, SLOT(createRotationGroupEntry(QHash<QString,QVariant>)));
    connect(shiftCalendarView, SIGNAL(requestMoveEntryDown(int)), this, SLOT(moveRotationGroupEntryDown(int)));
    connect(shiftCalendarView, SIGNAL(requestMoveEntryUp(int)), this, SLOT(moveRotationGroupEntryUp(int)));
    connect(shiftCalendarView, SIGNAL(requestRemoveEntry(int)), this, SLOT(removeRotationGroupEntry(int)));


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
    viewCon->registerView(rotationGroupTaskView, ViewType::ROTATION_GROUP_TASK_VIEW);
    viewCon->registerView(rotationGroupTaskListView, ViewType::ROTATION_GROUP_TASK_LIST_VIEW);
    viewCon->registerView(employeeView, ViewType::EMPLOYEE_VIEW);
    viewCon->registerView(employeeListView, ViewType::EMPLOYEE_LIST_VIEW);
    viewCon->registerView(bodyMeasurementView, ViewType::BODY_MEASUREMENT_VIEW);
    viewCon->registerView(documentationView, ViewType::DOCUMENTATION_VIEW);

    // Register PopUps on ViewController
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
    viewCon->registerPopUp(employeePopUp,PopUpType::EMPLOYEE_POPUP);
    viewCon->registerPopUp(factorySettingsPopUp, PopUpType::FACTORYSETTINGS_POPUP);
    viewCon->registerPopUp(linePopUp, PopUpType::LINE_POPUP);

    //Set the start Views
    documentationView->showStartView(ViewType::BODY_POSTURE_VIEW);
    viewCon->showStartView(ViewType::ANALYST_SELECTION_VIEW);

    initializeAnalysts();
    initializeProducts();
    initializeTansportations();
    initializeEquipments();
    initializeEmployees();
    initializeLines();
    initializeWorkplaces();
    initializeRotationGroupTasks();
}

//PRIVATE SLOTS

//Analyst
void Controller::initializeAnalysts(){
    emit clearAnalysts();
    QList<QHash<QString, QVariant>> rows = dbHandler->select(DBConstants::TBL_ANALYST, QString(""));
    for(int i = 0; i < rows.size(); ++i)
        emit createdAnalyst(rows.at(i));
}

void Controller::createAnalyst(QHash<QString, QVariant> values){
    QString empName = values.value(DBConstants::COL_EMPLOYER_NAME).toString();
    QString filter = QString("%1 = '%2'").arg(DBConstants::COL_EMPLOYER_NAME).arg(empName);
    QHash<QString, QVariant> valuesEmployer = QHash<QString, QVariant>();
    valuesEmployer.insert(DBConstants::COL_EMPLOYER_NAME, empName);
    int emp_ID = dbHandler->save(DBConstants::TBL_EMPLOYER, DBConstants::HASH_EMPLOYER_TYPES, valuesEmployer, filter, DBConstants::COL_EMPLOYER_ID);

    values.remove(DBConstants::COL_EMPLOYER_NAME);
    values.insert(DBConstants::COL_ANALYST_EMPLOYER_ID, emp_ID);
    dbHandler->insert(DBConstants::TBL_ANALYST, DBConstants::HASH_ANALYST_TYPES, values, DBConstants::COL_ANALYST_ID);
    viewCon->showMessage(tr("Created analyst"), NotificationMessage::ACCEPT);
    emit createdAnalyst(values);
}

void Controller::deleteAnalyst(int id){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_ANALYST_ID).arg(id);
    dbHandler->deleteAll(DBConstants::TBL_ANALYST, filter);
    viewCon->showMessage(tr("Deleted analyst"), NotificationMessage::ACCEPT);
    emit removedAnalyst(id);
}

void Controller::selectAnalyst(int id){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_ANALYST_ID).arg(id);
    QHash<QString, QVariant> values = dbHandler->selectFirst(DBConstants::TBL_ANALYST, filter);
    analyst_ID = id;
    viewCon->showMessage(tr("Hello  ") + dbHandler->select(DBConstants::TBL_ANALYST, QString("")).
                         at(id -1).value(DBConstants::COL_ANALYST_FIRSTNAME).toString() + "! ",
                         NotificationMessage::WELCOME, NotificationMessage::LONG);
    emit selectedAnalyst(values);
    filter = QString("%1 = %2").arg(DBConstants::COL_RECORDING_ANALYST_ID).arg(analyst_ID);
    QHash<QString, QVariant> recValues = dbHandler->selectFirst(DBConstants::TBL_RECORDING, filter);
    int recID = 0;
    if(recValues.isEmpty()){
        recValues.insert(DBConstants::COL_RECORDING_ANALYST_ID, analyst_ID);
        recID = dbHandler->insert(DBConstants::TBL_RECORDING, DBConstants::HASH_RECORDING_TYPES, recValues, DBConstants::COL_RECORDING_ID);
    }
    else
        recID = recValues.value(DBConstants::COL_RECORDING_ID).toInt();
    setRecording(recID);
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


//BranchOfIndustry
void Controller::setBranchOfIndustry(int id){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_BRANCH_OF_INDUSTRY_ID).arg(id);
    QHash<QString, QVariant> boiValues = dbHandler->selectFirst(DBConstants::TBL_BRANCH_OF_INDUSTRY, filter);
    if(!boiValues.isEmpty())
        emit settedBranchOfIndustry(boiValues);
}

void Controller::saveBranchOfIndustry(QHash<QString, QVariant> values){
    QString filter = QString("%1 = '%2'").arg(DBConstants::COL_BRANCH_OF_INDUSTRY_NAME).arg(values.value(DBConstants::COL_BRANCH_OF_INDUSTRY_NAME).toString());
    dbHandler->save(DBConstants::TBL_BRANCH_OF_INDUSTRY, DBConstants::HASH_BRANCH_OF_INDUSTRY_TYPES, values, filter, DBConstants::COL_BRANCH_OF_INDUSTRY_ID);
}

//Corperation
void Controller::setCorperation(int id){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_CORPORATION_ID).arg(id);
    QHash<QString, QVariant> corpValues = dbHandler->selectFirst(DBConstants::TBL_CORPORATION, filter);
    if(!corpValues.isEmpty()){
        emit settedCorperation(corpValues);
        int boiID = corpValues.value(DBConstants::COL_CORPORATION_BRANCH_OF_INDUSTRY_ID).toInt();
        if(boiID > 0)
            setBranchOfIndustry(boiID);
    }
}

void Controller::saveCorperation(QHash<QString, QVariant> values){
    QString filter = QString("%1 = '%2'").arg(DBConstants::COL_BRANCH_OF_INDUSTRY_NAME).arg(values.value(DBConstants::COL_BRANCH_OF_INDUSTRY_NAME).toString());
    QHash<QString, QVariant> boiValues = dbHandler->selectFirst(DBConstants::TBL_BRANCH_OF_INDUSTRY, filter);
    values.insert(DBConstants::COL_CORPORATION_BRANCH_OF_INDUSTRY_ID, boiValues.value(DBConstants::COL_BRANCH_OF_INDUSTRY_ID));
    values.remove(DBConstants::COL_BRANCH_OF_INDUSTRY_NAME);
    filter = QString("%1 = '%2'").arg(DBConstants::COL_CORPORATION_NAME).arg(values.value(DBConstants::COL_CORPORATION_NAME).toString());
    dbHandler->save(DBConstants::TBL_CORPORATION, DBConstants::HASH_CORPORATION_TYPES, values, filter, DBConstants::COL_CORPORATION_ID);
}

//Factory
void Controller::setFactory(int id){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_FACTORY_ID).arg(id);
    QHash<QString, QVariant> factoryValues = dbHandler->selectFirst(DBConstants::TBL_FACTORY, filter);
    if(!factoryValues.isEmpty()){
        factory_ID = id;
        emit settedFactory(factoryValues);
        int corpID = factoryValues.value(DBConstants::COL_FACTORY_CORPORATION_ID).toInt();
        if(corpID > 0)
            setCorperation(corpID);
    }

}

void Controller::saveFactory(QHash<QString, QVariant> values){
    QString filter = QString("%3 = '%4'").arg(DBConstants::COL_CORPORATION_NAME).arg(values.value(DBConstants::COL_CORPORATION_NAME).toString());
    QHash<QString, QVariant> corpValues = dbHandler->selectFirst(DBConstants::TBL_CORPORATION, filter);
    if(!corpValues.isEmpty())
        values.insert(DBConstants::COL_FACTORY_CORPORATION_ID, corpValues.value(DBConstants::COL_CORPORATION_ID));
    values.remove(DBConstants::COL_CORPORATION_NAME);
    filter = QString("%1 = '%2' AND %3 = '%4'").arg(DBConstants::COL_FACTORY_NAME).arg(values.value(DBConstants::COL_FACTORY_NAME).toString()).arg(DBConstants::COL_FACTORY_STREET).arg(values.value(DBConstants::COL_FACTORY_STREET).toString());
    dbHandler->save(DBConstants::TBL_FACTORY, DBConstants::HASH_FACTORY_TYPES, values, filter, DBConstants::COL_FACTORY_ID);
}

//Recording
void Controller::setRecording(int id){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_RECORDING_ID).arg(id);
    QHash<QString, QVariant> recordValues = dbHandler->selectFirst(DBConstants::TBL_RECORDING, filter);
    if(!recordValues.isEmpty()){
        recording_ID = id;
        emit settedRecording(recordValues);
        int factoryID = recordValues.value(DBConstants::COL_RECORDING_FACTORY_ID).toInt();
        if(factoryID > 0)
            setFactory(factoryID);
        filter = QString("%1 = %2").arg(DBConstants::COL_SHIFT_RECORDING_ID).arg(recording_ID);
        QHash<QString, QVariant> shiftValues = dbHandler->selectFirst(DBConstants::TBL_SHIFT, filter);
        int shift_ID = shiftValues.value(DBConstants::COL_SHIFT_ID).toInt();
        initializeShift(shift_ID);
    }
}

void Controller::saveRecording(QHash<QString, QVariant> values){
    QString filter = QString("%1 = '%2' AND %3 = '%4'").arg(DBConstants::COL_FACTORY_NAME).arg(values.value(DBConstants::COL_FACTORY_NAME).toString()).arg(DBConstants::COL_FACTORY_STREET).arg(values.value(DBConstants::COL_FACTORY_STREET).toString());
    QHash<QString, QVariant> factoryValues = dbHandler->selectFirst(DBConstants::TBL_FACTORY, filter);
    if(!factoryValues.isEmpty())
        values.insert(DBConstants::COL_RECORDING_FACTORY_ID, factoryValues.value(DBConstants::COL_FACTORY_ID));
    values.remove(DBConstants::COL_FACTORY_NAME);
    values.remove(DBConstants::COL_FACTORY_STREET);
    values.insert(DBConstants::COL_RECORDING_ID, recording_ID);
    values.insert(DBConstants::COL_RECORDING_ANALYST_ID, analyst_ID);
    filter = QString("%1 = %2").arg(DBConstants::COL_RECORDING_ID).arg(recording_ID);
    dbHandler->save(DBConstants::TBL_RECORDING, DBConstants::HASH_RECORDING_TYPES, values, filter, DBConstants::COL_RECORDING_ID);
    viewCon->showMessage(tr("Saved meta data"), NotificationMessage::ACCEPT);
}

//WorkplaceView
void Controller::initializeWorkplaces(){
    emit clearWorkplaces();
    QList<QHash<QString, QVariant>> rows = dbHandler->select(DBConstants::TBL_WORKPLACE, QString(""));
    for(int i = 0; i < rows.count(); ++i)
        emit createdWorkplace(rows.at(i));
}

void Controller::createWorkplace(QHash<QString, QVariant> values){
    int wp_ID = dbHandler->insert(DBConstants::TBL_WORKPLACE, DBConstants::HASH_WORKPLACE_TYPES, values, DBConstants::COL_WORKPLACE_ID);
    values.insert(DBConstants::COL_WORKPLACE_ID, wp_ID);
    emit createdWorkplace(values);
    saveRecordingObservesWorkplace(wp_ID);
    viewCon->showMessage(tr("Created new workplace"), NotificationMessage::ACCEPT);
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
    viewCon->showMessage(tr("Created new line"), NotificationMessage::ACCEPT);
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
    viewCon->showMessage(tr("Deleted line"), NotificationMessage::ACCEPT);
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
    viewCon->showMessage(tr("Created new product"), NotificationMessage::ACCEPT);
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
    viewCon->showMessage(tr("Deleted product"), NotificationMessage::ACCEPT);
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
    viewCon->showMessage(tr("Created new equipment"), NotificationMessage::ACCEPT);
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
    viewCon->showMessage(tr("Deleted equipment"), NotificationMessage::ACCEPT);
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
   viewCon->showMessage(tr("Created new activity"), NotificationMessage::ACCEPT);
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
    viewCon->showMessage(tr("Created new transportation"), NotificationMessage::ACCEPT);
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
    viewCon->showMessage(tr("Deleted transportation"), NotificationMessage::ACCEPT);
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
    viewCon->showMessage(tr("Created new employee"), NotificationMessage::ACCEPT);
}

void Controller::createEmployee(QHash<QString, QVariant> values, QHash<QString, QVariant> bodyMeasurementValues){
    int bmID = dbHandler->insert(DBConstants::TBL_BODY_MEASUREMENT, DBConstants::HASH_BODY_MEASUREMENT_TYPES, bodyMeasurementValues, DBConstants::COL_BODY_MEASUREMENT_ID);
    values.insert(DBConstants::COL_EMPLOYEE_BODY_MEASUREMENT_ID, bmID);
    int empID = dbHandler->insert(DBConstants::TBL_EMPLOYEE, DBConstants::HASH_EMPLOYEE_TYPES, values, DBConstants::COL_EMPLOYEE_ID);
    values.insert(DBConstants::COL_EMPLOYEE_ID, empID);
    emit createdEmployee(values);
}

void Controller::deleteEmployee(int id){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_EMPLOYEE_ID).arg(id);
    QHash<QString, QVariant> values = dbHandler->selectFirst(DBConstants::TBL_EMPLOYEE, filter);
    dbHandler->deleteAll(DBConstants::TBL_EMPLOYEE, filter);
    emit removedEmployee(id);
    filter = QString("%1 = %2").arg(DBConstants::COL_EMPLOYEE_BODY_MEASUREMENT_ID).arg(values.value(DBConstants::COL_EMPLOYEE_BODY_MEASUREMENT_ID).toInt());
    dbHandler->deleteAll(DBConstants::TBL_BODY_MEASUREMENT, filter);
    viewCon->showMessage(tr("Deleted employee"), NotificationMessage::ACCEPT);
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

//Connection
void Controller::initializeFTPConnections(IFTPConnections *widget){
    widget->clearFTPConnections();
    int defaultConnection_ID = 0;
    QList<QHash<QString, QVariant>> values = dbHandler->select(DBConstants::TBL_CONNECTION, QString("%1 = %2").arg(DBConstants::COL_CONNECTION_ANALYST_ID).arg(analyst_ID));
    for(int i = 0; i < values.count(); ++i){
        QHash<QString, QVariant> row = values.at(i);
        widget->addFTPConnection(row);
        if(row.value(DBConstants::COL_CONNECTION_DEFAULT).toBool())
            defaultConnection_ID = row.value(DBConstants::COL_CONNECTION_ID).toInt();
    }
    widget->selectedFTPConnection(defaultConnection_ID);
}

void Controller::selectFTPConnection(IFTPConnections *widget, int id){
    QHash<QString, QVariant> row = dbHandler->selectFirst(DBConstants::TBL_CONNECTION, QString("%1 = %2").arg(DBConstants::COL_CONNECTION_ID).arg(id));
    if(!row.isEmpty()){
        widget->setFTPConnection(row);
    }
}

void Controller::createFTPConnection(IFTPConnections *widget)
{
    QHash<QString, QVariant> values = widget->getFTPConnection();
    values.insert(DBConstants::COL_CONNECTION_ANALYST_ID, analyst_ID);
    dbHandler->insert(DBConstants::TBL_CONNECTION, DBConstants::HASH_CONNECTION_TYPES, values, DBConstants::COL_CONNECTION_ID);
}

void Controller::editFTPConnection(IFTPConnections *widget, int id)
{
    QHash<QString, QVariant> values = widget->getFTPConnection();
    values.insert(DBConstants::COL_CONNECTION_ANALYST_ID, analyst_ID);
    dbHandler->update(DBConstants::TBL_CONNECTION, DBConstants::HASH_CONNECTION_TYPES, values, QString("%1 = %2").arg(DBConstants::COL_CONNECTION_ID).arg(id));
}

//ImportData
void Controller::importData(IImportData *widget){
    viewCon->showMessage(tr("Start parsing"));
    viewCon->closePopUp();
    importDataWidget = widget;
    if(widget->getImportMode().compare("XML") == 0){
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
        QHash<QString, QVariant> conValues = widget->getFTPConnection();
        ftpHandler->setUser(conValues.value(DBConstants::COL_CONNECTION_USERNAME).toString(), conValues.value(DBConstants::COL_CONNECTION_PASSWORD).toString());
        ftpHandler->setPort(conValues.value(DBConstants::COL_CONNECTION_PORT).toInt());
        ftpHandler->setServer(conValues.value(DBConstants::COL_CONNECTION_SERVER_ADDRESS).toString());

        if(parser->getFileMode() == IImportDataParser::FileMode::MultiFile){
            if(widget->importTransportations())
                ftpHandler->downloadFile(parser->getTransportationFilename(), downloadDir);
            if(widget->importEquipments())
                ftpHandler->downloadFile(parser->getEquipmentFilename(), downloadDir);
            if(widget->importProducts())
                ftpHandler->downloadFile(parser->getProductFilename(), downloadDir);
            if(widget->importEmployees())
                ftpHandler->downloadFile(parser->getEmployeeFilename(), downloadDir);
            if(widget->importWorkplaces())
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
            if(importDataWidget->importTransportations())
                parser->parseTransportations(path.arg(filename));
            if(importDataWidget->importEquipments())
                parser->parseEquipments(path.arg(filename));
            if(importDataWidget->importProducts())
                parser->parseProducts(path.arg(filename));
            if(importDataWidget->importEmployees())
                parser->parseEmployees(path.arg(filename));
            if(importDataWidget->importWorkplaces())
                parser->parseWorkplaces(path.arg(filename));
        }
    }
}

void Controller::importDataDownloadError(const QString &error){
    viewCon->showMessage(error, NotificationMessage::ERROR, NotificationMessage::PERSISTENT);
}

//SendData
void Controller::sendData(ISendData *widget){
    FtpHandler *ftpHandler = new FtpHandler();
    connect(ftpHandler, SIGNAL(started()), this, SLOT(sendDataUploadStarted()));
    connect(ftpHandler, SIGNAL(finished(QString)), this, SLOT(sendDataUploadFinished(QString)));
    connect(ftpHandler, SIGNAL(error(QString)), this, SLOT(sendDataUploadError(QString)));
    QHash<QString, QVariant> conValues = widget->getFTPConnection();
    ftpHandler->setUser(conValues.value(DBConstants::COL_CONNECTION_USERNAME).toString(), conValues.value(DBConstants::COL_CONNECTION_PASSWORD).toString());
    ftpHandler->setPort(conValues.value(DBConstants::COL_CONNECTION_PORT).toInt());
    ftpHandler->setServer(conValues.value(DBConstants::COL_CONNECTION_SERVER_ADDRESS).toString());
    ftpHandler->uploadFile(StandardPaths::databasePath());
}

void Controller::sendDataUploadStarted(){
    viewCon->showMessage(tr("Started Upload"), NotificationMessage::INFORMATION, NotificationMessage::MIDDLE);
}

void Controller::sendDataUploadFinished(const QString filename){
    viewCon->showMessage(QString(tr("Finished Upload: ")).append(filename));
    viewCon->closePopUp();
}

void Controller::sendDataUploadError(const QString &error){
    viewCon->showMessage(error, NotificationMessage::ERROR, NotificationMessage::PERSISTENT);
}

//Shift
void Controller::initializeShift(int id){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_SHIFT_ID).arg(id);
    QHash<QString, QVariant> values = dbHandler->selectFirst(DBConstants::TBL_SHIFT, filter);
    if(!values.isEmpty()){
        shift_ID = values.value(DBConstants::COL_SHIFT_ID).toInt();
        filter = QString ("%1 = %2").arg(DBConstants::COL_EMPLOYEE_WORKS_SHIFT_SHIFT_ID).arg(shift_ID);
        selectedEmployee_ID = dbHandler->selectFirst(DBConstants::TBL_EMPLOYEE_WORKS_SHIFT, filter).value(DBConstants::COL_EMPLOYEE_WORKS_SHIFT_EMPLOYEE_ID).toInt();
        emit employeeSelected(selectedEmployee_ID);
        emit selectedShift(values);
        initializeRotationGroup(values.value(DBConstants::COL_SHIFT_ROTATION_GROUP_ID).toInt());
    }
}

void Controller::saveShift(QHash<QString, QVariant> values){
    QHash<QString, QVariant> ewsValues = QHash<QString, QVariant>();
    ewsValues.insert(DBConstants::COL_EMPLOYEE_WORKS_SHIFT_EMPLOYEE_ID, selectedEmployee_ID);
    QString filter = QString("%1 = %2").arg(DBConstants::COL_EMPLOYEE_WORKS_SHIFT_SHIFT_ID).arg(shift_ID);
    dbHandler->update(DBConstants::TBL_EMPLOYEE_WORKS_SHIFT, DBConstants::HASH_EMPLOYEE_WORKS_SHIFT_TYPES, ewsValues, filter, DBConstants::COL_EMPLOYEE_WORKS_SHIFT_EMPLOYEE_ID);
    filter = QString("%1 = %2").arg(DBConstants::COL_SHIFT_ID).arg(shift_ID);
    values.insert(DBConstants::COL_SHIFT_RECORDING_ID, recording_ID);
    values.insert(DBConstants::COL_SHIFT_ROTATION_GROUP_ID, rotationGroup_ID);
    values.insert(DBConstants::COL_SHIFT_ID, shift_ID);
    dbHandler->save(DBConstants::TBL_SHIFT, DBConstants::HASH_SHIFT_TYPES, values, filter, DBConstants::COL_SHIFT_ID);

}

//RotationGroup
void Controller::initializeRotationGroup(int id){
    rotationGroup_ID = id;
    emit clearRotationGroup();
    QString filter = QString("%1 = %2").arg(DBConstants::COL_ROTATION_GROUP_ID).arg(id);
    QList<QHash<QString, QVariant>> rgesValues = dbHandler->select(DBConstants::TBL_ROTATION_GROUP, filter);
    for(int i = 0; i < rgesValues.size(); ++i){
        QHash<QString, QVariant> rgeValues = rgesValues.at(i);
        int entry_ID = rgeValues.value(DBConstants::COL_ROTATION_GROUP_ENTRY_ID).toInt();
        bool isTask = rgeValues.value(DBConstants::COL_ROTATION_GROUP_IS_TASK).toBool();
        QHash<QString, QVariant> additionalValues;
        QString tblName = isTask ? DBConstants::TBL_ROTATION_GROUP_TASK : DBConstants::TBL_BREAK;
        QString colIDName = isTask ? DBConstants::COL_ROTATION_GROUP_TASK_ID : DBConstants::COL_BREAK_ID;
        filter = QString("%1 = %2").arg(colIDName).arg(entry_ID);
        additionalValues = dbHandler->selectFirst(tblName, filter);
        foreach(QString key , additionalValues.keys())
            rgeValues.insert(key, additionalValues.value(key));
        if(isTask)
            emit addRotationGroupEntry(rgeValues);
        else
            emit addRotationGroupBreakEntry(rgeValues);
    }

}

void Controller::createRotationGroupEntry(QHash<QString, QVariant> values){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_ROTATION_GROUP_ID).arg(rotationGroup_ID);
    int order = dbHandler->getNextID(DBConstants::TBL_ROTATION_GROUP, DBConstants::COL_ROTATION_GROUP_ORDER_NUMBER, filter);
    values.insert(DBConstants::COL_ROTATION_GROUP_ORDER_NUMBER, order);
    values.insert(DBConstants::COL_ROTATION_GROUP_IS_TASK, true);
    values.insert(DBConstants::COL_ROTATION_GROUP_ID, rotationGroup_ID);
    int success = dbHandler->insert(DBConstants::TBL_ROTATION_GROUP, DBConstants::HASH_ROTATION_GROUP_TYPES, values, DBConstants::COL_ROTATION_GROUP_ORDER_NUMBER);
    if(success > 0) {
        emit addRotationGroupEntry(values);
        viewCon->showMessage(tr("Added rotation group task to calendar"), NotificationMessage::ACCEPT);
    }
}

void Controller::createRotationGroupBreakEntry(QHash<QString, QVariant> values){
    int duration = values.value(DBConstants::COL_BREAK_DURATION).toInt();
    QString filter = QString("%1 = %2").arg(DBConstants::COL_BREAK_DURATION).arg(duration);
    QHash<QString, QVariant> breakValues = QHash<QString, QVariant>();
    breakValues.insert(DBConstants::COL_BREAK_DURATION, duration);
    values.remove(DBConstants::COL_BREAK_DURATION);
    int break_ID = dbHandler->save(DBConstants::TBL_BREAK, DBConstants::HASH_BREAK_TYPES, breakValues, filter, DBConstants::COL_BREAK_ID);
    if(break_ID > 0) {
        values.insert(DBConstants::COL_ROTATION_GROUP_ENTRY_ID, break_ID);
        filter = QString("%1 = %2").arg(DBConstants::COL_ROTATION_GROUP_ID).arg(rotationGroup_ID);
        int order = dbHandler->getNextID(DBConstants::TBL_ROTATION_GROUP, DBConstants::COL_ROTATION_GROUP_ORDER_NUMBER, filter);
        values.insert(DBConstants::COL_ROTATION_GROUP_ORDER_NUMBER, order);
        values.insert(DBConstants::COL_ROTATION_GROUP_IS_TASK, false);
        values.insert(DBConstants::COL_ROTATION_GROUP_ID, rotationGroup_ID);
        int success = dbHandler->insert(DBConstants::TBL_ROTATION_GROUP, DBConstants::HASH_ROTATION_GROUP_TYPES, values, DBConstants::COL_ROTATION_GROUP_ORDER_NUMBER);
        if(success > 0) {
            emit addRotationGroupBreakEntry(values);
            viewCon->showMessage(tr("Added break to calendar"), NotificationMessage::ACCEPT);
        }
    }
}

void Controller::removeRotationGroupEntry(int order){
    QString filter = QString("%1 = %2 AND %3 = %4").arg(DBConstants::COL_ROTATION_GROUP_ID).arg(rotationGroup_ID).arg(DBConstants::COL_ROTATION_GROUP_ORDER_NUMBER).arg(order);
    if(dbHandler->deleteAll(DBConstants::TBL_ROTATION_GROUP, filter)){
        viewCon->showMessage(tr("Removed entry form calendar"), NotificationMessage::ACCEPT);
        filter = QString("%1 = %2 AND %3 > %4").arg(DBConstants::COL_ROTATION_GROUP_ID).arg(rotationGroup_ID).arg(DBConstants::COL_ROTATION_GROUP_ORDER_NUMBER).arg(order);
        QList<QHash<QString, QVariant>> rgesValues = dbHandler->select(DBConstants::TBL_ROTATION_GROUP, filter);
        QString absFilter = QString("%1 = %2 AND %3 = %4").arg(DBConstants::COL_ROTATION_GROUP_ID).arg(rotationGroup_ID).arg(DBConstants::COL_ROTATION_GROUP_ORDER_NUMBER);
        for(int i = 0; i < rgesValues.size(); ++i){
            QHash<QString, QVariant> rgeValues = rgesValues.at(i);
            int order = rgeValues.value(DBConstants::COL_ROTATION_GROUP_ORDER_NUMBER).toInt();
            rgeValues.insert(DBConstants::COL_ROTATION_GROUP_ORDER_NUMBER, order - 1);
            dbHandler->update(DBConstants::TBL_ROTATION_GROUP, DBConstants::HASH_ROTATION_GROUP_TYPES, rgeValues, absFilter.arg(order), DBConstants::COL_ROTATION_GROUP_ORDER_NUMBER);
        }
        initializeRotationGroup(rotationGroup_ID);
    }
}

void Controller::moveRotationGroupEntryUp(int order){
    swapRotationGroupEntries(order, order+1);
    initializeRotationGroup(rotationGroup_ID);
}

void Controller::moveRotationGroupEntryDown(int order){
    swapRotationGroupEntries(order, order-1);
    initializeRotationGroup(rotationGroup_ID);
}


//RotationGroupTask
void Controller::initializeRotationGroupTasks(){
    emit clearRotationGroupTasks();
    QList<QHash<QString, QVariant>> rows = dbHandler->select(DBConstants::TBL_ROTATION_GROUP_TASK, QString(""));
    for(int i = 0; i < rows.size(); ++i)
        emit createdRotationGroupTask(rows.value(i));
}

void Controller::createRotationGroupTask(QHash<QString, QVariant> values){
    dbHandler->insert(DBConstants::TBL_ROTATION_GROUP_TASK, DBConstants::HASH_ROTATION_GROUP_TASK_TYPES, values, DBConstants::COL_ROTATION_GROUP_TASK_ID);
    viewCon->showMessage(tr("Created rotation group task"), NotificationMessage::ACCEPT);
    emit createdRotationGroupTask(values);
}

void Controller::deleteRotationGroupTask(int id){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_ROTATION_GROUP_TASK_ID).arg(id);
    dbHandler->deleteAll(DBConstants::TBL_ROTATION_GROUP_TASK, filter);
    QList<QHash<QString, QVariant>> rgteRows = dbHandler->select(DBConstants::TBL_ROTATION_GROUP_TASK_ENTRY, QString("%1 = %2").arg(DBConstants::COL_ROTATION_GROUP_TASK_ENTRY_TASK_ID).arg(id));
    rotationGroupTask_ID = id;
    for(int i = 0; i < rgteRows.size(); ++i){
        deleteRotationGroupTaskEntry(rgteRows.at(i).value(DBConstants::COL_ROTATION_GROUP_TASK_ENTRY_ID).toInt(), false);
    }
    viewCon->showMessage(tr("Deleted rotation group task"), NotificationMessage::ACCEPT);
    emit removedRotationGroupTask(id);
}

void Controller::selectRotationGroupTask(int id){
    rotationGroupTask_ID = id;
    QString filter = QString("%1 = %2").arg(DBConstants::COL_ROTATION_GROUP_TASK_ID).arg(id);
    QHash<QString, QVariant> values = dbHandler->selectFirst(DBConstants::TBL_ROTATION_GROUP_TASK, filter);
    emit selectedRotationGroupTask(values);
    initializeRotationGroupTaskEntries(id);
}

void Controller::saveRotationGroupTask(QHash<QString, QVariant> values){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_ROTATION_GROUP_TASK_ID).arg(rotationGroupTask_ID);
    values.insert(DBConstants::COL_ROTATION_GROUP_TASK_ID, rotationGroupTask_ID);
    dbHandler->save(DBConstants::TBL_ROTATION_GROUP_TASK, DBConstants::HASH_ROTATION_GROUP_TASK_TYPES, values, filter, DBConstants::COL_ROTATION_GROUP_TASK_ID);
    viewCon->showMessage(tr("Saved rotation group task"), NotificationMessage::ACCEPT);
    emit updatedRotationGroupTask(values);
}


//RotationGroupTaskEntry
void Controller::initializeRotationGroupTaskEntries(int id){
    emit clearRotationGroupTaskEntries();
    QString filter = QString("%1 = %2").arg(DBConstants::COL_ROTATION_GROUP_TASK_ENTRY_TASK_ID).arg(id);
    QList<QHash<QString, QVariant>> rgtesValues = dbHandler->select(DBConstants::TBL_ROTATION_GROUP_TASK_ENTRY, filter);
    for(int i = 0; i < rgtesValues.size(); ++i){
        QHash<QString, QVariant> rgteValues = rgtesValues.at(i);
        rgteValues.insert(DBConstants::COL_WORKPLACE_NAME, getWorkplaceNameByID(rgteValues.value(DBConstants::COL_ROTATION_GROUP_TASK_ENTRY_WORKPLACE_ID).toInt()));
        emit createdRotationGroupTaskEntry(rgteValues);
    }
    updateRotationGroupTaskDuration();

}

void Controller::createRotationGroupTaskEntry(QHash<QString, QVariant> values){
    values.insert(DBConstants::COL_ROTATION_GROUP_TASK_ENTRY_TASK_ID, rotationGroupTask_ID);
    QString filter = QString("%1 = %2").arg(DBConstants::COL_ROTATION_GROUP_TASK_ENTRY_TASK_ID).arg(rotationGroupTask_ID);
    int rgte_ID = dbHandler->getNextID(DBConstants::TBL_ROTATION_GROUP_TASK_ENTRY, DBConstants::COL_ROTATION_GROUP_TASK_ENTRY_ID, filter);
    values.insert(DBConstants::COL_ROTATION_GROUP_TASK_ENTRY_ID, rgte_ID);
    dbHandler->insert(DBConstants::TBL_ROTATION_GROUP_TASK_ENTRY, DBConstants::HASH_ROTATION_GROUP_TASK_ENTRY_TYPES, values, DBConstants::COL_ROTATION_GROUP_TASK_ENTRY_ID);
    values.insert(DBConstants::COL_WORKPLACE_NAME, getWorkplaceNameByID(values.value(DBConstants::COL_ROTATION_GROUP_TASK_ENTRY_WORKPLACE_ID).toInt()));
    emit createdRotationGroupTaskEntry(values);
    viewCon->showMessage(tr("Created rotation group task entry"), NotificationMessage::ACCEPT);
    updateRotationGroupTaskDuration();
}

void Controller::deleteRotationGroupTaskEntry(int id, bool showMessage){
    QString filter = QString("%1 = %2 AND %3 = %4").arg(DBConstants::COL_ROTATION_GROUP_TASK_ENTRY_ID).arg(id).arg(DBConstants::COL_ROTATION_GROUP_TASK_ENTRY_TASK_ID).arg(rotationGroupTask_ID);
    dbHandler->deleteAll(DBConstants::TBL_ROTATION_GROUP_TASK_ENTRY, filter);
    emit removedRotationGroupTaskEntry(id);
    if(showMessage)
        viewCon->showMessage(tr("Deleted rotation group task entry"), NotificationMessage::ACCEPT);
    updateRotationGroupTaskDuration();
}

//Database Factory Reset
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
    QList<QString> tblNames = DBConstants::LIST_TABLE_NAMES;
    for(int i = 0; i < tblNames.size(); ++i)
        dbHandler->deleteAll(tblNames.at(i), emptyFilter);
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
         viewCon->showMessage(("Neustart erforderlich um die Änderungen zu übernehmen"), NotificationMessage::INFORMATION, NotificationMessage::PERSISTENT);
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
void Controller::updateRotationGroupTaskDuration(){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_ROTATION_GROUP_TASK_ENTRY_TASK_ID).arg(rotationGroupTask_ID);
    QList<QHash<QString, QVariant>> rgtesValues = dbHandler->select(DBConstants::TBL_ROTATION_GROUP_TASK_ENTRY, filter);
    int duration = 0;
    for(int i = 0; i < rgtesValues.size(); ++i){
        duration += rgtesValues.at(i).value(DBConstants::COL_ROTATION_GROUP_TASK_ENTRY_DURATION).toInt();
    }
    emit updatedRotationGroupTaskDuration(duration);
}

QString Controller::getWorkplaceNameByID(int id){
    QString filter = QString("%1 = %2").arg(DBConstants::COL_WORKPLACE_ID).arg(id);
    return dbHandler->selectFirst(DBConstants::TBL_WORKPLACE, filter).value(DBConstants::COL_WORKPLACE_NAME).toString();
}

void Controller::swapRotationGroupEntries(int order1, int order2){
    QString absFilter = QString("%1 = %2 AND %3 = %4").arg(DBConstants::COL_ROTATION_GROUP_ID).arg(rotationGroup_ID).arg(DBConstants::COL_ROTATION_GROUP_ORDER_NUMBER);
    QHash<QString, QVariant> values1 = dbHandler->selectFirst(DBConstants::TBL_ROTATION_GROUP, absFilter.arg(order1));
    dbHandler->deleteAll(DBConstants::TBL_ROTATION_GROUP, absFilter.arg(order1));
    QHash<QString, QVariant> values2 = dbHandler->selectFirst(DBConstants::TBL_ROTATION_GROUP, absFilter.arg(order2));
    values2.insert(DBConstants::COL_ROTATION_GROUP_ORDER_NUMBER, order1);
    dbHandler->update(DBConstants::TBL_ROTATION_GROUP, DBConstants::HASH_ROTATION_GROUP_TYPES, values2, absFilter.arg(order2), DBConstants::COL_ROTATION_GROUP_ORDER_NUMBER);
    values1.insert(DBConstants::COL_ROTATION_GROUP_ORDER_NUMBER, order2);
    dbHandler->insert(DBConstants::TBL_ROTATION_GROUP, DBConstants::HASH_ROTATION_GROUP_TYPES, values1, DBConstants::COL_ROTATION_GROUP_ORDER_NUMBER);
}


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
