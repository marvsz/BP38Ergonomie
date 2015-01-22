#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <QStackedWidget>
#include <QStack>
#include "analystselectionview.h"
#include "mainmenu.h"
#include "metadataview.h"
#include "workplaceView/workplacelistview.h"
#include "workplaceView/workplaceview.h"
#include "workplaceView/lineview.h"
#include "workplaceView/commentview.h"
#include "workplaceView/activityview.h"
#include "documentationview.h"
#include "ressourceManagementView/ressourcemanagementview.h"
#include "ressourceManagementView/equipmentview.h"
#include "ressourceManagementView/productview.h"
#include "ressourceManagementView/transportationview.h"
#include "settingsview.h"

class ViewController : public QStackedWidget
{
    Q_OBJECT
public:
    explicit ViewController(QWidget *parent = 0);

    static const int ANALYST_SELECTION_VIEW = 0;
    static const int MAIN_MENU_VIEW = 1;
    static const int METADATA_VIEW = 2;
    static const int WORKPLACELIST_VIEW = 3;
    static const int WORKPLACE_VIEW = 4;
    static const int LINE_VIEW = 5;
    static const int ACTIVITY_VIEW = 6;
    static const int COMMENT_VIEW = 7;
    static const int DOCUMENTATION_VIEW = 8;
    static const int RESSOURCE_MANAGEMENT_VIEW = 9;
    static const int PRODUCT_VIEW = 10;
    static const int EQUIPMENT_VIEW = 11;
    static const int TRANSPORTATION_VIEW = 12;
    static const int SETTINGS_VIEW = 13;

    void setAnalystSelectionView(AnalystSelectionView *analystSelectionView);
    void setMainMenuView(MainMenu *mainMenuView);
    void setMetaDataView(MetaDataView *metaDataView);
    void setWorkplaceListView(WorkplaceListView *workplaceListView);
    void setWorkplaceView(WorkplaceView *workplaceView);
    void setLineView(LineView *lineView);
    void setActivityView(ActivityView *activityView);
    void setCommentView(CommentView *commentView);
    void setDocumentationView(DocumentationView *documentationView);
    void setRessourceManagementView(RessourceManagementView *ressourceManagementView);
    void setProductView(ProductView *productView);
    void setEquipmentView(EquipmentView *equipmentView);
    void setTransportationView(TransportationView *transportationView);
    void setSettingsView(SettingsView *settingsView);

    void registerViews();

signals:
    // Analyst Selection View
    void updateAnalystSelectionView();

    // METADATA VIEW
    void saveMetaData();
    void updateMetaData();

    // WORKPLACELIST VIEW
    void updateWorkplaceList();
    void updateWorkplace(int id);
    void updateWorkplace();
    void createWorkplace();
    void setSelectedWorkplace(int id);

    // WORKPLACE VIEW
    void saveWorkplace();

    // LINE VIEW
    void updateLineView();

    // COMMENT VIEW
    void updateCommentView();

    // ACTIVITY VIEW
    void updateActivityView();
    void saveActivity();
    void deleteActivity(int id);

    //DOCUMENTATION VIEW
    void updateDocumentationView();
    void updateDocumentationViewRessources();

    //WORKPROCESS
    void createWorkprocess(AVType type, const QTime &start, const QTime &end);
    void saveCurrentWorkProcess();

    // RESSOURCE MANAGEMENT VIEW

    // EQUIPMENT VIEW
    void updateEquipmentView();

    // PRODUCT VIEW
    void updateProductView();

    // TRANSPORTATION VIEW
    void updateTransportationView();
    void saveTransportation();
    void deleteTransportation(int id);


public slots:

private slots:

    void backToView();

    void goToAnalystSelectionView();
    void goToMainMenuView();
    void goToMetaDataView();
    void goToWorkplaceListView();
    void goToWorkplaceView();
    void goToWorkplaceView(int id);
    void goToLineView();
    void goToActivityView();
    void goToCommentView();
    void goToDocumentationView();
    void goToRessourceManagementView();
    void goToSettingsView();
    void goToEquipmentView();
    void goToProductView();
    void goToTransportationView();

private:
    QStack<int> *previousViews;
    AnalystSelectionView *analystSelectionView;
    MainMenu *mainMenuView;
    MetaDataView *metaDataView;
    WorkplaceListView *workplaceListView;
    WorkplaceView *workplaceView;
    LineView *lineView;
    ActivityView *activityView;
    CommentView *commentView;
    DocumentationView *documentationView;
    RessourceManagementView *ressourceManagementView;
    ProductView *productView;
    EquipmentView *equipmentView;
    TransportationView *transportationView;
    SettingsView *settingsView;

    void goToView(int index);
};

#endif // VIEWCONTROLLER_H
