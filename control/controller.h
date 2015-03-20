#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "../databaseHandler/dbhandler.h"
#include "../view/navigation/viewcontroller.h"
#include "../xmlHandler/xmlparser.h"
#include "standardpaths.h"
#include "../view/generalViews/mainmenu.h"
#include "../view/generalViews/metadataview.h"
#include "../view/workplaceView/activityview.h"
#include "../view/workplaceView/commentview.h"
#include "../view/workplaceView/lineview.h"
#include "../view/workplaceView/workplacelistview.h"
#include "../view/workplaceView/workplaceview.h"
#include "../view/documentationView/documentationview.h"
#include "../view/generalViews/analystselectionview.h"
#include "../view/timerView/ganttimerview.h"
#include "../view/rotationGroupView/shiftview.h"
#include "../view/rotationGroupView/shiftcalendar.h"
#include "../view/rotationGroupView/rotationgrouptaskview.h"
#include "../view/rotationGroupView/rotationgrouptasklistview.h"
#include "../view/ressourceManagementView/equipmentview.h"
#include "../view/ressourceManagementView/transportationview.h"
#include "../view/ressourceManagementView/productview.h"
#include "../view/ressourceManagementView/ressourcemanagementview.h"
#include "../view/ressourceManagementView/bodymeasurementview.h"
#include "../view/ressourceManagementView/employeeview.h"
#include "../view/ressourceManagementView/employeelistview.h"
#include "../view/generalViews/settingsview.h"
#include "../view/popUps/equipmentpopup.h"
#include "../view/popUps/transporationpopup.h"
#include "../view/popUps/senddatabasepopup.h"
#include "../view/popUps/analystpopup.h"
#include "../view/popUps/createproductpopup.h"
#include "../view/popUps/activitypopup.h"
#include "../view/popUps/languagepopup.h"
#include "../view/popUps/themepopup.h"
#include "../view/popUps/workplacepopup.h"
#include "../view/popUps/importdatapopup.h"
#include "../view/interfaces/iftpconnections.h"
#include "../view/popUps/resetpopup.h"
#include "../view/popUps/employeepopup.h"
#include "../view/popUps/factorysettingspopup.h"
#include "../view/popUps/linepopup.h"
#include "../view/documentationView/appliedforceview.h"
#include "../view/documentationView/loadhandlingview.h"
#include "../view/documentationView/executionconditionview.h"
#include "../view/documentationView/workprocessmetadataview.h"
#include "../view/documentationView/bodyPostureView/bodypostureview.h"
#include <QSqlField>
#include <QCryptographicHash>
#include <QHash>
#include <QApplication>


class Controller : QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0, QApplication *app = 0);

signals:
    void clearAll();

    //Analyst
    void clearAnalysts();
    void createdAnalyst(QHash<QString, QVariant> values);
    void selectedAnalyst(QHash<QString, QVariant> values);
    void updatedAnalyst(QHash<QString, QVariant> values);
    void removedAnalyst(int id);

    //Branch of Industry
    void settedBranchOfIndustry(QHash<QString, QVariant> values);

    //Corperation
    void settedCorperation(QHash<QString, QVariant> values);

    //Factory
    void settedFactory(QHash<QString, QVariant> values);

    //Recording
    void settedRecording(QHash<QString, QVariant> values);

    //Workplace
    void clearWorkplaces();
    void createdWorkplace(QHash<QString, QVariant> values);
    void selectedWorkplace(QHash<QString, QVariant> values);
    void updatedWorkplace(QHash<QString, QVariant> values);
    void removedWorkplace(int id);

    //Workplace comment
    void selectedComment(QHash<QString, QVariant> values);
    void updatedComment(QHash<QString, QVariant> values);

    //Line
    void createdLine(QHash<QString, QVariant> values);
    void updatedLine(QHash<QString, QVariant> values);
    void editLine(QHash<QString, QVariant> values);
    void removedLine(int id);
    void selectedLine(QHash<QString, QVariant> values);
    void clearLines();

    //Employee
    void clearEmployees();
    void createdEmployee(QHash<QString, QVariant> values);
    void selectedEmployee(QHash<QString, QVariant> values);
    void updatedEmployee(QHash<QString, QVariant> values);
    void removedEmployee(int id);

    //EmployeeSelectList
    void employeeSelected(int id);

    //BodyMeasurement
    void selectedBodyMeasurement(QHash<QString, QVariant> values);

    //Product
    void clearProducts();
    void createdProduct(QHash<QString, QVariant> values);
    void updatedProduct(QHash<QString, QVariant> values);
    void removedProduct(int id);

    //Activity
    void clearActivities();
    void createdActivity(QHash<QString, QVariant> values);
    void updatedActivity(QHash<QString, QVariant> values);
    void removedActivity(int id);
    void editActivity(QHash<QString, QVariant> values);

    //Equipment
    void clearEquipments();
    void createdEquipment(QHash<QString, QVariant> values);
    void updatedEquipment(QHash<QString, QVariant> values);
    void removedEquipment(int id);

    //Transportation
    void clearTransportations();
    void createdTransportation(QHash<QString, QVariant> values);
    void updatedTransportation(QHash<QString, QVariant> values);
    void removedTransportation(int id);

    //LoadHandling
    void setLoadHandling(QHash<QString, QVariant> values);

    //BodyPosture
    void setBodyPosture(QHash<QString, QVariant> values);

    //AppliedForce
    void setAppliedForce(QHash<QString, QVariant> values);

    //WorkProcess
    void setWorkProcess(QHash<QString, QVariant> values);

    //ExecutionCondition
    void setExecutionCondition(QHash<QString, QVariant> values);

    //WorkProcessControll
    void createdWorkProcess(QHash<QString, QVariant> values);
    void setSelectedWorkProcess(QHash<QString, QVariant> values);
    void setHasPreviousWorkProcess(bool hasPrevious);
    void setHasNextWorkProcess(bool hasNext);
    void setSelectedWorkProcessType(AVType type);
    void initiliazedWorkProcesses(QList<QHash<QString, QVariant>> values);
    void resettedWorkProcesses();


private slots:
    //Analyst
    void initializeAnalysts();
    void createAnalyst(QHash<QString, QVariant> values);
    void deleteAnalyst(int id);
    void selectAnalyst(int id);

    //MainMenuView
    void createBlankRecording();

    //BranchOfIndustry
    void setBranchOfIndustry(int id);
    void saveBranchOfIndustry(QHash<QString, QVariant> values);

    //Corperation
    void setCorperation(int id);
    void saveCorperation(QHash<QString, QVariant> values);

    //Factory
    void setFactory(int id);
    void saveFactory(QHash<QString, QVariant> values);

    //Recording
    void setRecording(int id);
    void saveRecording(QHash<QString, QVariant> values);

    //Workplace
    void initializeWorkplaces();
    void createWorkplace(QHash<QString, QVariant> values);
    void createWorkplace(QHash<QString, QVariant> values, QList<QHash<QString, QVariant>> activityValues);
    void deleteWorkplace(int id);
    void selectWorkplace(int id);
    void saveWorkplace(QHash<QString, QVariant> values);

    //Comment
    void saveComment(QHash<QString, QVariant> values);

    //Line
    void initializeLines();
    void createLine(QHash<QString, QVariant> values);
    void editLine(int id);
    void saveLine(QHash<QString, QVariant> values);
    void deleteLine(int id);
    void selectLine(int id);

    //Product
    void initializeProducts();
    void createProduct(QHash<QString, QVariant> values);
    void saveProduct(QHash<QString, QVariant> values);
    void deleteProduct(int id);

    //Activity
    void initializeActivities(int workplace_ID);
    void createActivity(QHash<QString, QVariant> values);
    void saveActivity(QHash<QString, QVariant> values);
    void deleteActivity(int id, bool showMessage = true);
    void selectACtivity(int id);
    void editActivity(int id);

    //Equipment
    void initializeEquipments();
    void createEquipment(QHash<QString, QVariant> values);
    void saveEquipment(QHash<QString, QVariant> values);
    void deleteEquipment(int id);

    //Transportation
    void initializeTansportations();
    void createTransportation(QHash<QString, QVariant> values);
    void saveTransportation(QHash<QString, QVariant> values);
    void deleteTransportation(int id);

    //LoadHandling
    void saveLoadHandling(QHash<QString, QVariant> values);

    //BodyPosture
    void saveBodyPosture(QHash<QString, QVariant> values);

    //AppliedForce
    void saveAppliedForce(QHash<QString, QVariant> values);

    //WorkProcess
    void saveWorkProcess(QHash<QString, QVariant> values);

    //ExecutionCondition
    void saveExecutionCondition(QHash<QString, QVariant> values);

    //WorkProcessControll
    void initilizeWorkProcesses(bool selectFirst = true);
    void createWorkprocess(QHash<QString, QVariant> values);
    void selectNextWorkProcess();
    void selectPreviousWorkProcess();
    void workProcessTypeChanged(AVType type);
    void resetWorkProcesses();
    void workProcessDurationChanged(QTime time);
    void selectWorkProcess(int id, AVType type);

    //Gantt
    void saveWorkProcessFrequence(int frequence);

    //Employee
    void initializeEmployees();
    void createEmployee(QHash<QString, QVariant> values);
    void createEmployee(QHash<QString, QVariant> values, QHash<QString, QVariant> bodyMeasurementValues);
    void deleteEmployee(int id);
    void selectEmployee(int id);
    void saveEmployee(QHash<QString, QVariant> values);
    void setSelectedEmployee(int id);
    void resetEmployeeSelection();

    //BodyMeasurement
    void saveBodyMeasurement(QHash<QString, QVariant> values);

    //Connection
    void initializeFTPConnections(IFTPConnections *widget);
    void createFTPConnection(IFTPConnections *widget);
    void editFTPConnection(IFTPConnections *widget, int id);
    void selectFTPConnection(IFTPConnections *widget, int id);

    //ImportData
    void importData(IImportData *widget);
    void importDataDownloadFinished(const QString filename);
    void importDataDownloadError(const QString &error);

    //SendData
    void sendData(ISendData *widget);
    void sendDataUploadStarted();
    void sendDataUploadFinished(const QString filename);
    void sendDataUploadError(const QString &error);

    void resetDatabaseFactory();
    void resetSelectedEntries();

    void languageChanged();
    void themeChanged();

private:
    QApplication *application;
    DBHandler *dbHandler;
    ViewController *viewCon;

    AnalystSelectionView *analystSelectionView;
    MainMenu *mainMenuView;
    MetaDataView *metaDataView;
    WorkplaceListView *workplaceListView;
    WorkplaceView *workplaceView;
    LineView *lineView;
    ActivityView *activityView;
    CommentView *commentView;
    RessourceManagementView *ressourceManagementView;
    ProductView *productView;
    EquipmentView *equipmentView;
    TransportationView *transportationView;
    EmployeeView *employeeView;
    EmployeeListView *employeeListView;
    BodyMeasurementView *bodyMeasurementView;
    ShiftView *shiftView;
    ShiftCalendar *shiftCalendarView;
    RotationGroupTaskView *rotationGroupTaskView;
    RotationGroupTaskListView *rotationGroupTaskListView;
    SettingsView *settingsView;

    DocumentationView *documentationView;
    WorkProcessMetaDataView *workProcessMetaDataView;
    AppliedForceView *appliedForceView;
    BodyPostureView *bodyPostureView;
    LoadHandlingView *loadHandlingView;
    ExecutionConditionView *executionConditionView;
    GantTimerView *gantTimerView;

    TimerViewController *timerViewController;

    EquipmentPopUp *equipmentPopUp;
    TransporationPopUp *transportationPopUp;
    SendDatabasePopUp *sendDatabasePopUp;
    AnalystPopUp *analystPopUp;
    CreateProductPopUp *createProductPopUp;
    ActivityPopUp *activityPopUp;
    LanguagePopUp *languagePopUp;
    ThemePopUp *themePopUp;
    WorkplacePopUp *workplacePopUp;
    ImportDataPopUp *importDataPopUp;
    ResetPopUp *resetPopUp;
    EmployeePopUp *employeePopUp;
    FactorySettingsPopUp *factorySettingsPopUp;
    LinePopUp *linePopUp;

    int analyst_ID;
    int recording_ID;
    int factory_ID;
    int workplace_ID;
    int workcondition_ID;
    int workprocess_ID;
    AVType workprocess_Type;
    int activity_ID;
    int appliedforce_ID;
    int loadhandling_ID;
    int bodyPosture_ID;
    int employee_ID;
    int bodyMeasurement_ID;
    int selectedEmployee_ID;

    IImportData *importDataWidget;
    IImportDataParser *parser;
    QString downloadDir;

    void saveRecordingObservesLine(int line_ID);
    void deleteRecordingObservesLine(int line_ID);

    void saveRecordingObservesWorkplace(int workplace_ID);
    void deleteRecordingOberservesWorkplace(int workplace_ID);

    void deleteWorkProcesses(int activity_ID);

    QString stringFromResource(const QString &resName);
};

#endif // CONTROLLER_H
