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

    void updateProductView();
    int saveSelectedProducts();
    int saveProduct();
    void deleteProduct(int id);

    void updateComment();
    int saveComment();

    void updateWorkprocessViews();
    int createWorkprocess(int type, const QTime &start, const QTime &end);

private:
    DBHandler *dbHandler;
    ViewController *viewCon;

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

    TimerViewController *timerViewController;


    int recording_ID;
    int factory_ID;
    int selectedWorkplaceID;
    int selectedWorkprocessID;
    int activity_ID;

    int save(DB_TABLES tbl, const QString &filter, const QString &colID, const QStringList &colNames, const QList<QVariant::Type> &colTypes, QHash<QString, QVariant> &colMapNameValue);

    int save(DB_TABLES tbl, const QString &filter, const QString &colID, const QHash<QString, QVariant::Type> &colMapNameType, QHash<QString, QVariant> &colMapNameValue);

    void save(DB_TABLES tbl, const QString &filter, const QHash<QString, QVariant::Type> &colMapNameType, const QHash<QString, QVariant> &colMapNameValue);

    void updateAnalyst(int id);
    int saveAnalyst();

    int saveEmployer();
    void updateEmployer(int id);


    void updateCorporation(int id);
    int saveCorporation();

    void updateFactory(int id);
    int saveFactory();

    void updateRecording(int id);
    int saveRecording();

    int saveWorkplace(int id);
    int qTimeToSeconds(const QTime &time);

    void saveRecordingObservesLine(int lineID);
    void deleteRecordingObservesLine(int lineID);

    void saveRecordingObservesWorkplace(int workplaceID);
    void deleteRecordingOberservesWorkplace(int wpID);


};

#endif // CONTROLLER_H
