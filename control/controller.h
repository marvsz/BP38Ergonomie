#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "../databaseHandler/dbhandler.h"
#include "../view/navigation/viewcontroller.h"
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
#include "../view/ressourceManagementView/equipmentview.h"
#include "../view/ressourceManagementView/transportationview.h"
#include "../view/ressourceManagementView/productview.h"
#include "../view/ressourceManagementView/ressourcemanagementview.h"
#include "../view/ressourceManagementView/bodymeasurementview.h"
#include "../view/ressourceManagementView/employeeview.h"
#include "../view/generalViews/settingsview.h"
#include "../view/generalViews/feedbackview.h"
#include "../view/documentationView/appliedforceview.h"
#include "../view/documentationView/loadhandlingview.h"
#include "../view/documentationView/executionconditionview.h"
#include "../view/documentationView/workprocessmetadataview.h"
#include "../view/documentationView/bodyPostureView/bodypostureview.h"
#include <QSqlField>
#include <QHash>

class Controller : QObject
{
Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

signals:

public slots:

private slots:
    void update(ViewType type);
    void save(ViewType type);

    void updateAnalystSelectionView();
    void createAnalyst();
    void removeAnalyst(int id);
    void selectAnalyst(int id);

    void updateMetaDataView();
    void saveMetaDataView();

    void updateWorkplacesView();

    void updateWorkplaceView(int id);
    void updateWorkplaceView();
    int createWorkplace();
    void saveWorkplaceView();
    void deleteWorkplace(int id);

    void updateLineView();
    int saveSelectedLine(int id);
    int saveLine();
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

    void updateGantView();

    void updateProductView();
    void createProduct();
    void deleteProduct(int id);

    void updateEquipmentView();
    void createEquipment();
    void deleteEquipment(int id);

    void updateTransportationView();
    void createTransportation();
    void deleteTransportation(int id);

    void updateActivityView();
    void createActivity();
    void deleteActivity(int id);
    void selectActivity(int id);

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

    void resetDatabase();

private:
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
    BodyMeasurementView *bodyMeasurementView;
    ShiftView *shiftView;
    ShiftCalendar *shiftCalendarView;
    RotationGroupView *rotationGroupView;
    SettingsView *settingsView;

    DocumentationView *documentationView;
    WorkProcessMetaDataView *workProcessMetaDataView;
    AppliedForceView *appliedForceView;
    BodyPostureView *bodyPostureView;
    LoadHandlingView *loadHandlingView;
    ExecutionConditionView *executionConditionView;
    GantTimerView *gantTimerView;

    TimerViewController *timerViewController;

    FeedbackView *feedbackView;

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

    int insert(DB_TABLES tbl, const QString &colID, const QHash<QString, QVariant::Type> &colMapNameType, QHash<QString, QVariant> &colMapNameValue);

    int save(DB_TABLES tbl, const QString &filter, const QString &colID, const QHash<QString, QVariant::Type> &colMapNameType, QHash<QString, QVariant> &colMapNameValue);

    void save(DB_TABLES tbl, const QString &filter, const QHash<QString, QVariant::Type> &colMapNameType, const QHash<QString, QVariant> &colMapNameValue);

    int saveWorkplace(int id);
    int qTimeToSeconds(const QTime &time);

    void saveRecordingObservesLine(int lineID);
    void deleteRecordingObservesLine(int lineID);

    void saveRecordingObservesWorkplace(int workplaceID);
    void deleteRecordingOberservesWorkplace(int wpID);

    void updateActivityViewActivities();

    void deleteWorkProcesses(int activity_ID);
    void saveWorkProcessEvaluationID(const QString &colName, const int id);
};

#endif // CONTROLLER_H
