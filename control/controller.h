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
#include "../view/rotationGroupView/rotationgroupview.h"
#include "../view/rotationGroupView/rotationgrouplistview.h"
#include "../view/ressourceManagementView/equipmentview.h"
#include "../view/ressourceManagementView/transportationview.h"
#include "../view/ressourceManagementView/productview.h"
#include "../view/ressourceManagementView/ressourcemanagementview.h"
#include "../view/ressourceManagementView/bodymeasurementview.h"
#include "../view/ressourceManagementView/employeeview.h"
#include "../view/ressourceManagementView/employeelistview.h"
#include "../view/generalViews/settingsview.h"
#include "../view/popUps//feedbackpopup.h"
#include "../view/popUps/equipmentpopup.h"
#include "../view/popUps/transporationpopup.h"
#include "../view/popUps/senddatabasepopup.h"
#include "../view/popUps/analystpopup.h"
#include "../view/popUps/productpopup.h"
#include "../view/popUps/activitypopup.h"
#include "../view/popUps/languagepopup.h"
#include "../view/popUps/themepopup.h"
#include "../view/popUps/workplacepopup.h"
#include "../view/popUps/importdatapopup.h"
#include "../view/interfaces/iftpconnections.h"
#include "../view/popUps/resetpopup.h"
#include "../view/popUps/employeepopup.h"
#include "../view/documentationView/appliedforceview.h"
#include "../view/documentationView/loadhandlingview.h"
#include "../view/documentationView/executionconditionview.h"
#include "../view/documentationView/workprocessmetadataview.h"
#include "../view/documentationView/bodyPostureView/bodypostureview.h"
#include "translator.h"
#include <QSqlField>
#include <QCryptographicHash>
#include <QHash>
#include <QApplication>


class Controller : QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0, QApplication *app = 0, Translator *trans = 0);

signals:
    void createdEmployee(QHash<QString, QVariant> values);
    void selectedEmployee(QHash<QString, QVariant> values);
    void updatedEmployee(QHash<QString, QVariant> values);
    void removedEmployee(int id);

private slots:
    void databaseError(QString error);

    void update(ViewType type);
    void update(PopUpType type);
    void save(ViewType type);

    void updateAnalystSelectionView();
    void createAnalyst();
    void removeAnalyst(int id);
    void selectAnalyst(int id);

    void createBlankRecording();

    void updateMetaDataView();
    void saveMetaDataView();

    void updateWorkplacesView();

    void updateWorkplaceView(int id);
    void updateWorkplaceView();
    int createWorkplace();
    void saveWorkplaceView();
    void deleteWorkplace(int id);
    void createWorkplacePopup();
    void createWorkplace(QHash<QString, QVariant> values, QList<QHash<QString, QVariant>> activityValues);

    void updateLineView();
    int saveSelectedLine(int id);
    int createLine();
    void deleteLine(int id);

    void updateComment();
    int saveComment();


    int createWorkprocess(AVType type, const QTime &start, const QTime &end);
    void setSelectedWorkProcess(int, AVType);
    void selectNextWorkProcess();
    void selectPreviousWorkProcess();
    void workProcessTypeChanged(AVType type);
    void resetWorkProcesses();
    void saveCurrentWorkProcess();
    void workProcessDurationChanged(QTime time);

    void initializeRecording();

    void updateProductView();
    void createProduct();
    void createProductPopUp();
    void createProduct(QHash<QString, QVariant> values);
    void deleteProduct(int id);

    void updateEquipmentView();
    void createEquipment();
    void createEquipmentPopUp();
    void createEquipment(QHash<QString, QVariant> values);
    void deleteEquipment(int id);

    void updateTransportationView();
    void createTransportation();
    void createTransportationPopUp();
    void createTransportation(QHash<QString, QVariant> values);
    void deleteTransportation(int id);

    void initializeEmployees();
    void createEmployee(QHash<QString, QVariant> values);
    void createEmployee(QHash<QString, QVariant> values, QHash<QString, QVariant> bodyMeasurementValues);
    void deleteEmployee(int id);
    void selectEmployee(int id);
    void saveEmployee(QHash<QString, QVariant> values);

    void updateBodyMeasurementView();
    void saveBodyMeasurementView();

    void updateActivityView();
    void createActivity();
    void deleteActivity(int id);
    void selectActivity(int id);
    void updateActivityPopUp(int id);
    void updateActivity();

    void saveBodyPostureView();
    void updateBodyPostureView();

    void updateExecutionConditionView();
    void saveExecutionConditionView();

    void updateAppliedForceView();
    void saveAppliedForceView();

    void updateLoadHandlingView();
    void saveLoadHandlingView();
    void updateLoadHandlingTransportations();

    void updateWorkProcessMetaDataView();
    void updateWorkProcessMetaDataEquipment();

    void updateDocumentationViewRessources();

    void updateFTPConnectionPopUp(IFTPConnections *widget);
    void selectedConnectionChanged(IFTPConnections *widget, int id);
    void createConnection(IFTPConnections *widget);
    void editConnection(IFTPConnections *widget, int id);

    void parseImportData();
    void importDataDownloadFinished(const QString filename);
    void importDataDownloadError(const QString &error);

    void resetDatabaseRecording();
    void resetDatabaseFactory();
    void resetSelectedEntries();

    void languageChanged();
    void themeChanged();

private:
    QApplication *application;
    Translator *translator;
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
    RotationGroupView *rotationGroupView;
    RotationGroupListView *rotationGroupListView;
    SettingsView *settingsView;

    DocumentationView *documentationView;
    WorkProcessMetaDataView *workProcessMetaDataView;
    AppliedForceView *appliedForceView;
    BodyPostureView *bodyPostureView;
    LoadHandlingView *loadHandlingView;
    ExecutionConditionView *executionConditionView;
    GantTimerView *gantTimerView;

    TimerViewController *timerViewController;

    FeedbackPopUp *feedbackPopUp;
    EquipmentPopUp *equipmentPopUp;
    TransporationPopUp *transportationPopUp;
    SendDatabasePopUp *sendDatabasePopUp;
    AnalystPopUp *analystPopUp;
    ProductPopUp *productPopUp;
    ActivityPopUp *activityPopUp;
    LanguagePopUp *languagePopUp;
    ThemePopUp *themePopUp;
    WorkplacePopUp *workplacePopUp;
    ImportDataPopUp *importDataPopUp;
    ResetPopUp *resetPopUp;
    EmployeePopUp *employeePopUp;

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

    IImportDataParser *parser;
    QString downloadDir;


    int saveWorkplace(int id);
    int qTimeToSeconds(const QTime &time);

    void saveRecordingObservesLine(int lineID);
    void deleteRecordingObservesLine(int lineID);

    void saveRecordingObservesWorkplace(int workplaceID);
    void deleteRecordingOberservesWorkplace(int wpID);

    void updateActivityViewActivities();

    void deleteWorkProcesses(int activity_ID);
    void saveWorkProcessEvaluationID(const QString &colName, const int id);

    QString stringFromResource(const QString &resName);
};

#endif // CONTROLLER_H
