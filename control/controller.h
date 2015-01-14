#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#if defined(Q_OS_IOS)
    #include "dbhandler.h"
    #include "viewcontroller.h"
    #include "mainmenu.h"
    #include "metadataview.h"
    #include "workplaceView/activityview.h"
#else
    #include "../databaseHandler/dbhandler.h"
    #include "../view/viewcontroller.h"
    #include "../view/mainmenu.h"
    #include "../view/metadataview.h"
    #include "../view/workplaceView/activityview.h"
    #include "../view/workplaceView/commentview.h"
    #include "../view/workplaceView/lineview.h"
    #include "../view/workplaceView/workplacelistview.h"
    #include "../view/workplaceView/workplaceview.h"
    #include "../view/documentationview.h"
    #include "../view/analystselectionview.h"
    #include "../view/timerView/ganttimerview.h"
#endif
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

    void updateWorkprocessViews();
    int createWorkprocess(int type, const QTime &start, const QTime &end); 

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

    void updateExecutionConditionView();
    int saveExecutionConditionView();

    void updateAppliedForceView();
    int saveAppliedForceView();

    void updateLoadHandlingView();
    int saveLoadHandlingView();

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
    SettingsView *settingsView;

    DocumentationView *documentationView;
    WorkProcessMetaDataView *workProcessMetaDataView;
    AppliedForceView *appliedForceView;
    BodyPostureView *bodyPostureView;
    LoadHandlingView *loadHandlingView;
    ExecutionConditionView *executionConditionView;
    GantTimerView *gantTimerView;

    TimerViewController *timerViewController;

    int analyst_ID;
    int recording_ID;
    int factory_ID;
    int workplace_ID;
    int workcondition_ID;
    int selectedWorkprocessID;
    int activity_ID;
    int appliedforce_ID;
    int loadhandling_ID;

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
};

#endif // CONTROLLER_H
