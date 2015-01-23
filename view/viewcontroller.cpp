#include "viewcontroller.h"

ViewController::ViewController(QWidget *parent) :
    QStackedWidget(parent)
{
    previousViews = new QStack<int>();
}

// PUBLIC
void ViewController::goToView(int index){
    previousViews->push(currentIndex());
    setCurrentIndex(index);
}

void ViewController::setAnalystSelectionView(AnalystSelectionView *analystSelectionView){
    this->analystSelectionView = analystSelectionView;
    connect(analystSelectionView, SIGNAL(forward()), this, SLOT(goToMainMenuView()));
}

void ViewController::setMainMenuView(MainMenu *mainMenuView){
    this->mainMenuView = mainMenuView;
    connect(mainMenuView, SIGNAL(showMetaDataView()), this, SLOT(goToMetaDataView()));
    connect(mainMenuView, SIGNAL(showWorkplaceListView()), this, SLOT(goToWorkplaceListView()));
    connect(mainMenuView, SIGNAL(showRessourceManagementView()), this, SLOT(goToRessourceManagementView()));
    connect(mainMenuView, SIGNAL(showNewRecordingView()), this, SLOT(goToDocumentationView()));
    connect(mainMenuView, SIGNAL(showSettingsView()), this, SLOT(goToSettingsView()));
}

void ViewController::setMetaDataView(MetaDataView *metaDataView){
    this->metaDataView = metaDataView;
    connect(metaDataView, SIGNAL(back()), this, SLOT(backToView()));
    connect(metaDataView, SIGNAL(forward()), this, SLOT(goToWorkplaceListView()));
    connect(metaDataView, SIGNAL(save()), this, SIGNAL(saveMetaData()));
}

void ViewController::setWorkplaceListView(WorkplaceListView *workplaceListView){
    this->workplaceListView = workplaceListView;
    connect(workplaceListView, SIGNAL(back()), this, SLOT(backToView()));
    connect(workplaceListView, SIGNAL(forward()), this, SLOT(goToWorkplaceView()));
    connect(workplaceListView, SIGNAL(showWorkplace(int)), this, SLOT(goToWorkplaceView(int)));
}

void ViewController::setWorkplaceView(WorkplaceView *workplaceView){
    this->workplaceView = workplaceView;
    connect(workplaceView, SIGNAL(back()), this, SLOT(backToView()));
    connect(workplaceView, SIGNAL(showLineView()), this, SLOT(goToLineView()));
    connect(workplaceView, SIGNAL(showActivityView()), this, SLOT(goToActivityView()));
    connect(workplaceView, SIGNAL(showCommentView()), this, SLOT(goToCommentView()));
}

void ViewController::setLineView(LineView *lineView){
    this->lineView = lineView;
    connect(lineView, SIGNAL(back()), this, SLOT(backToView()));
}

void ViewController::setActivityView(ActivityView *activityView){
    this->activityView = activityView;
    connect(activityView, SIGNAL(back()), this, SLOT(backToView()));
    connect(activityView, SIGNAL(showProductView()), this, SLOT(goToProductView()));
    connect(activityView, SIGNAL(showWorkProcessView()), this, SLOT(goToDocumentationView()));
}

void ViewController::setCommentView(CommentView *commentView){
    this->commentView = commentView;
    connect(commentView, SIGNAL(back()), this, SLOT(backToView()));
}

void ViewController::setDocumentationView(DocumentationView *documentationView){
    this->documentationView = documentationView;
    connect(documentationView, SIGNAL(showPreviousView()), this, SLOT(backToView()));
    connect(documentationView, SIGNAL(showTransportationView()), this, SLOT(goToTransportationView()));
    connect(documentationView, SIGNAL(showEquipmentView()), this, SLOT(goToEquipmentView()));
}

void ViewController::setRessourceManagementView(RessourceManagementView *ressourceManagementView){
    this->ressourceManagementView = ressourceManagementView;
    connect(ressourceManagementView, SIGNAL(back()), this, SLOT(backToView()));
    connect(ressourceManagementView, SIGNAL(showEquipmentView()), this, SLOT(goToEquipmentView()));
    connect(ressourceManagementView, SIGNAL(showProductView()), this, SLOT(goToProductView()));
    connect(ressourceManagementView, SIGNAL(showTransportationView()), this, SLOT(goToTransportationView()));
}

void ViewController::setProductView(ProductView *productView){
    this->productView = productView;
    connect(productView, SIGNAL(back()), this, SLOT(backToView()));
}

void ViewController::setEquipmentView(EquipmentView *equipmentView){
    this->equipmentView = equipmentView;
    connect(equipmentView, SIGNAL(back()), this, SLOT(backToView()));
}

void ViewController::setTransportationView(TransportationView *transportationView){
    this->transportationView = transportationView;
    connect(transportationView, SIGNAL(back()), this, SLOT(backToView()));
}

void ViewController::setSettingsView(SettingsView *settingsView){
    this->settingsView = settingsView;
    connect(settingsView, SIGNAL(back()), this, SLOT(backToView()));
    connect(settingsView, SIGNAL(showAnalystSelectionView()), this, SLOT(goToAnalystSelectionView()));
}

void ViewController::registerViews(){
    this->addWidget(analystSelectionView);
    this->addWidget(mainMenuView);
    this->addWidget(metaDataView);
    this->addWidget(workplaceListView);
    this->addWidget(workplaceView);
    this->addWidget(lineView);
    this->addWidget(activityView);
    this->addWidget(commentView);
    this->addWidget(documentationView);
    this->addWidget(ressourceManagementView);
    this->addWidget(productView);
    this->addWidget(equipmentView);
    this->addWidget(transportationView);
    this->addWidget(settingsView);
    setCurrentIndex(ViewController::ANALYST_SELECTION_VIEW);
    goToAnalystSelectionView();
}

// PRIVATE SLOTS
void ViewController::goToAnalystSelectionView(){
    emit updateAnalystSelectionView();
    goToView(ViewController::ANALYST_SELECTION_VIEW);
}

void ViewController::goToMainMenuView(){
    goToView(ViewController::MAIN_MENU_VIEW);
}

void ViewController::goToMetaDataView(){
    emit updateMetaData();
    goToView(ViewController::METADATA_VIEW);
}

void ViewController::goToWorkplaceListView(){
    emit updateWorkplaceList();
    goToView(ViewController::WORKPLACELIST_VIEW);
}

void ViewController::goToWorkplaceView(){
    emit createWorkplace();
    goToView(ViewController::WORKPLACE_VIEW);
}

void ViewController::goToWorkplaceView(int id){
    emit updateWorkplace(id);
    goToView(ViewController::WORKPLACE_VIEW);
}

void ViewController::goToLineView(){
    emit updateLineView();
    goToView(ViewController::LINE_VIEW);
}

void ViewController::goToActivityView(){
    emit updateActivityView();
    goToView(ViewController::ACTIVITY_VIEW);
}

void ViewController::goToCommentView(){
    emit updateCommentView();
    goToView(ViewController::COMMENT_VIEW);
}


void ViewController::goToDocumentationView(){
    emit updateDocumentationView();
    goToView(ViewController::DOCUMENTATION_VIEW);
}

void ViewController::goToRessourceManagementView(){
    goToView(ViewController::RESSOURCE_MANAGEMENT_VIEW);
}
void ViewController::goToSettingsView(){
    goToView(ViewController::SETTINGS_VIEW);
}

void ViewController::goToEquipmentView(){
    emit updateEquipmentView();
    goToView(ViewController::EQUIPMENT_VIEW);
}

void ViewController::goToProductView(){
    emit updateProductView();
    goToView(ViewController::PRODUCT_VIEW);
}

void ViewController::goToTransportationView(){
    emit updateTransportationView();
    goToView(ViewController::TRANSPORTATION_VIEW);
}

// SET VIEWS AND PUSH/POP
void ViewController::backToView(){
    int nextView = previousViews->pop();
    switch(nextView){
        case ViewController::MAIN_MENU_VIEW:
            break;
        case ViewController::METADATA_VIEW:
            break;
        case ViewController::WORKPLACELIST_VIEW:
            emit updateWorkplaceList();
            break;
        case ViewController::WORKPLACE_VIEW:
            emit updateWorkplace();
            break;
        case ViewController::LINE_VIEW:
            emit updateLineView();
            break;
        case ViewController::ACTIVITY_VIEW:
            emit saveCurrentWorkProcess();
            emit updateActivityView();
            break;
        case ViewController::COMMENT_VIEW:
            emit updateCommentView();
            break;
        case ViewController::DOCUMENTATION_VIEW:
            emit updateDocumentationViewRessources();
            break;
        case ViewController::RESSOURCE_MANAGEMENT_VIEW:
            break;
        case ViewController::PRODUCT_VIEW:
            emit updateProductView();
            break;
        case ViewController::EQUIPMENT_VIEW:
            emit updateEquipmentView();
            break;
        case ViewController::TRANSPORTATION_VIEW:
            emit updateTransportationView();
            break;
        case ViewController::SETTINGS_VIEW:
            break;
        default:
            break;
    }
    ViewController::setCurrentIndex(nextView);
}


