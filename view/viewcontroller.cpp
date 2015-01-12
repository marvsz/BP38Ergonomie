#include "viewcontroller.h"

ViewController::ViewController(QWidget *parent) :
    QStackedWidget(parent)
{
    previousViews = new QStack<int>();
    mainMenuView = new MainMenu;
    metaDataView = new MetaDataView;
    workplaceListView = new WorkplaceListView;
    workplaceView = new WorkplaceView;
    lineView = new LineView;
    activityView = new ActivityView;
    commentView = new CommentView;
    employeeView = new EmployeeView;
    documentationView = new DocumentationView;
    ressourceManagementView = new RessourceManagementView;
    productView = new ProductView;
    equipmentView = new EquipmentView;
    transportationView = new TransportationView;
    settingsView = new SettingsView;

    // MAIN MENU
    connect(mainMenuView, SIGNAL(showMetaDataView()), this, SLOT(goToMetaDataView()));
    connect(mainMenuView, SIGNAL(showWorkplaceListView()), this, SLOT(goToWorkplaceListView()));
    connect(mainMenuView, SIGNAL(showRessourceManagementView()), this, SLOT(goToRessourceManagementView()));
    connect(mainMenuView, SIGNAL(showNewRecordingView()), this, SLOT(goToDocumentationView()));
    connect(mainMenuView, SIGNAL(showSettingsView()), this, SLOT(goToSettingsView()));

    // METADATA VIEW
    connect(metaDataView, SIGNAL(showMainMenu()), this, SLOT(backToView()));
    connect(metaDataView, SIGNAL(showWorkplaceListView()), this, SLOT(goToWorkplaceListView()));
    connect(metaDataView, SIGNAL(saveMetaData()), this, SIGNAL(saveMetaData()));

    // WORKPLACE LIST VIEW
    connect(workplaceListView, SIGNAL(back()), this, SLOT(backToView()));
    connect(workplaceListView, SIGNAL(forward()), this, SLOT(goToWorkplaceView()));
    connect(workplaceListView, SIGNAL(showWorkplace(int)), this, SLOT(goToWorkplaceView(int)));
    connect(workplaceListView, SIGNAL(deleteWorkplace(int)), this, SIGNAL(deleteWorkplace(int)));

    // WORKPLACE VIEW
    connect(workplaceView, SIGNAL(back()), this, SLOT(backToView()));
    connect(workplaceView, SIGNAL(save()), this, SIGNAL(saveWorkplace()));
    connect(workplaceView, SIGNAL(cancel(int)), this, SIGNAL(deleteWorkplace(int)));

    connect(workplaceView, SIGNAL(showLineView()), this, SLOT(goToLineView()));
    connect(workplaceView, SIGNAL(showActivityView()), this, SLOT(goToActivityView()));
    connect(workplaceView, SIGNAL(showCommentView()), this, SLOT(goToCommentView()));

    // LINE VIEW
    connect(lineView, SIGNAL(back()), this, SLOT(backToView()));
    connect(lineView, SIGNAL(deleteLine(int)), this, SIGNAL(deleteLine(int)));
    connect(lineView, SIGNAL(saveLine()), this, SIGNAL(saveLine()));
    connect(lineView, SIGNAL(saveSelectedLine(int)), this, SIGNAL(saveSelectedLine(int)));

    // EMPLOYEE VIEW
    connect(employeeView, SIGNAL(back()), this, SLOT(backToView()));

    // ACTIVITY VIEW
    connect(activityView, SIGNAL(back()), this, SLOT(backToView()));
    connect(activityView, SIGNAL(showProductView()), this, SLOT(goToProductView()));
    connect(activityView, SIGNAL(deleteActivity(int)), this, SIGNAL(deleteActivity(int)));
    connect(activityView, SIGNAL(showWorkProcessView(int)), this, SLOT(goToDocumentationView(int)));

    // COMMENT VIEW
    connect(commentView, SIGNAL(back()), this, SLOT(backToView()));
    connect(commentView, SIGNAL(save()), this, SIGNAL(saveComment()));

    // DOCUMENTATION VIEW
    connect(documentationView, SIGNAL(showPreviousView()), this, SLOT(backToView()));
    connect(documentationView, SIGNAL(createWorkProcess(int,QTime,QTime)), this, SIGNAL(createWorkprocess(int,QTime,QTime)));

    // RESSOURCE MANAGEMENT VIEW
    connect(ressourceManagementView, SIGNAL(back()), this, SLOT(backToView()));
    connect(ressourceManagementView, SIGNAL(showEquipmentView()), this, SLOT(goToEquipmentView()));
    connect(ressourceManagementView, SIGNAL(showProductView()), this, SLOT(goToProductView()));
    connect(ressourceManagementView, SIGNAL(showTransportationView()), this, SLOT(goToTransportationView()));

    // EQUIPMENT VIEW

    // PRODUCT VIEW
    connect(productView, SIGNAL(back()), this, SLOT(backToView()));
    connect(productView, SIGNAL(deleteProduct(int)), this, SIGNAL(deleteProduct(int)));
    connect(productView, SIGNAL(saveProduct()), this, SIGNAL(saveProduct()));

    // TRANSPORTATION VIEW

    // SETTINGS VIEW


    // ADD ALL VIEWS
    this->addWidget(mainMenuView);
    this->addWidget(metaDataView);
    this->addWidget(workplaceListView);
    this->addWidget(workplaceView);
    this->addWidget(lineView);
    this->addWidget(employeeView);
    this->addWidget(activityView);
    this->addWidget(commentView);
    this->addWidget(documentationView);
    this->addWidget(ressourceManagementView);
    this->addWidget(productView);
    this->addWidget(equipmentView);
    this->addWidget(transportationView);
    this->addWidget(settingsView);

    setCurrentIndex(ViewController::MAIN_MENU_VIEW);
}

void ViewController::goToMetaDataView(){
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

void ViewController::goToEmployeeView(){
    emit updateEmployeeView();
    goToView(ViewController::EMPLOYEE_VIEW);
}

void ViewController::goToActivityView(){
    emit updateActivityView();
    goToView(ViewController::ACTIVITY_VIEW);
}

void ViewController::goToCommentView(){
    emit updateCommentView();
    goToView(ViewController::COMMENT_VIEW);
}

void ViewController::goToDocumentationView(int id){
    emit updateDocumentationView(id);
    goToView(ViewController::DOCUMENTATION_VIEW);
}

void ViewController::goToDocumentationView(){
    goToView(ViewController::DOCUMENTATION_VIEW);
}

void ViewController::goToRessourceManagementView(){
    goToView(ViewController::RESSOURCE_MANAGEMENT_VIEW);
}
void ViewController::goToSettingsView(){
    goToView(ViewController::SETTINGS_VIEW);
}

void ViewController::goToEquipmentView(){

    goToView(ViewController::EQUIPMENT_VIEW);
}

void ViewController::goToProductView(){
    goToView(ViewController::PRODUCT_VIEW);
}

void ViewController::goToTransportationView(){
    goToView(ViewController::TRANSPORTATION_VIEW);
}

// METADATAVIEW GETTER/SETTER
// GETTER

QString ViewController::getAnalystLastName() const{
    return metaDataView->getAnalystLastName();
}

QString ViewController::getAnalystFirstName() const {
    return metaDataView->getAnalystFirstName();
}

QString ViewController::getAnalystEmployer() const {
    return metaDataView->getAnalystEmployer();
}

QString ViewController::getAnalystExperience() const {
    return metaDataView->getAnalystExperience();
}

QString ViewController::getCorporationName() const {
    return metaDataView->getCorporationName();
}

QString ViewController::getFactoryName() const {
    return metaDataView->getFactoryName();
}

QString ViewController::getFactoryStreet() const {
    return metaDataView->getFactoryStreet();
}

int ViewController::getFactoryZip() const {
    return metaDataView->getFactoryZip();
}

QString ViewController::getFactoryCity() const {
    return metaDataView->getFactoryCity();
}

QString ViewController::getFactoryCountry() const {
    return metaDataView->getFactoryCountry();
}

QString ViewController::getFactoryContact() const {
    return metaDataView->getFactoryContact();
}

int ViewController::getFactoryEmployeeCount() const {
    return metaDataView->getFactoryEmployeeCount();
}

QDateTime ViewController::getRecordTimeBegin() const {
    return metaDataView->getRecordTimeBegin();
}

QDateTime ViewController::getRecordTimeEnd() const {
    return metaDataView->getRecordTimeEnd();
}

// SETTER

void ViewController::setAnalyst(const QString &lastName, const QString &firstName, const QString &experience){
    metaDataView->setAnalyst(lastName, firstName, experience);
}

void ViewController::setEmployer(const QString &employer){
    metaDataView->setEmployer(employer);
}

void ViewController::setCorporation(const QString &name){
    metaDataView->setCorporation(name);
}

void ViewController::setFactory(const QString &name, const QString &street, int zip, const QString &city, const QString &country, const QString &contact, int employeeCount){
    metaDataView->setFactory(name, street, zip, city, country, contact, employeeCount);
}

void ViewController::setRecordTime(const QDateTime &begin, const QDateTime &end){
    metaDataView->setRecordTime(begin, end);
}

// WORKPLACE LIST VIEW SETTER

void ViewController::addWorkplace(int id, const QString &name, const QString &description, const QString &code){
    workplaceListView->addWorkplace(id, name, description, code);
}

void ViewController::clearWorkplaceList(){
    workplaceListView->clear();
}

// WORKPLACE VIEW GETTER/SETTER

// SLOTS

void ViewController::setWorkplaceLine(const QString &name, const QString &description){
    workplaceView->setLine(name, description);
}

void ViewController::setWorkplaceComment(const QString &problemName, const QString &measureName){
    workplaceView->setComment(problemName, measureName);
}


// SETTER
void ViewController::setWorkplaceMetaData(const QString &name, const QString &description, const QString &code, int percentageWoman){
    workplaceView->setWorkplaceMetaData(name, description, code, percentageWoman);
}

void ViewController::setShiftWorkplaceTimes(const QTime &basicTime, const QTime &setupTime, const QTime &restTime, const QTime &allowanceTime, const QTime &cycleTime){
    workplaceView->setWorkplaceTimes(basicTime, setupTime, restTime, allowanceTime, cycleTime);
}

// GETTER
QString ViewController::getWorkplaceName() const {
    return workplaceView->getName();
}

QString ViewController::getWorkplaceDescription() const {
    return workplaceView->getDescription();
}

QString ViewController::getWorkplaceCode() const{
    return workplaceView->getCode();
}

int ViewController::getWorkplaceWomanPercentage() const{
    return workplaceView->getWomanPercentage();
}

QTime ViewController::getWorkplaceCycleTime() const{
    return workplaceView->getCycleTime();
}

QTime ViewController::getWorkplaceSetupTime() const{
    return workplaceView->getSetupTime();
}

QTime ViewController::getWorkplaceBasicTime() const{
    return workplaceView->getBasicTime();
}

QTime ViewController::getWorkplaceRestTime() const{
    return workplaceView->getRestTime();
}

QTime ViewController::getWorkplaceAllowanceTime() const{
    return workplaceView->getAllowanceTime();
}


// LINE VIEW GETTER/SETTER
// SETTER

void ViewController::setLine(const QString &name, const QString &description, int workplaceCount){
    lineView->setLine(name, description, workplaceCount);
}

void ViewController::addLine(int id, const QString &name){
    lineView->addLine(id, name);
}

void ViewController::clearLines(){
    lineView->clearLines();
}

void ViewController::setSelectedLine(int id){
    lineView->setSelectedLine(id);
}


// GETTER
QString ViewController::getLineName() const{
    return lineView->getName();
}

QString ViewController::getLineDescription() const{
    return lineView->getDescription();
}

int ViewController::getLineWorkplaceCount() const{
    return lineView->getWorkplaceCount();
}

// EMPLOYEE VIEW GETTER/SETTER
// SETTER
void ViewController::setEmployee(int gender, int age, int height, const QString &staffNumber, const QString &note){
    employeeView->setEmployee(gender, age, height, staffNumber, note);
}

// GETTER
int ViewController::getEmployeeGender() const{
    return employeeView->getGender();
}

int ViewController::getEmployeeAge() const{
    return employeeView->getAge();
}

int ViewController::getEmployeeHeight() const{
    return employeeView->getHeight();
}

QString ViewController::getEmployeeStaffNumber() const{
    return employeeView->getStaffNumber();
}

QString ViewController::getEmployeeNote() const{
    return employeeView->getNote();
}

// ACTIVITY VIEW GETTER/SETTER
// SETTER
void ViewController::addActivityProduct(int id, const QString &name){
    activityView->addProduct(id, name);
}

void ViewController::clearActivityProducts(){
    activityView->clearProducts();
}

void ViewController::setActivityProductSelected(int id){
    activityView->setSelectedProduct(id);
}

void ViewController::setActivity(const QString &description, int repetitions, int selectedProductID){
    activityView->setActivity(description, repetitions, selectedProductID);
}

void ViewController::addActivity(int id, const QString &description){
    activityView->addActivity(id, description);
}

void ViewController::clearActivities(){
    activityView->clearActivities();
}

// GETTER
QString ViewController::getActivityDescription() const{
    return activityView->getDescription();
}

int ViewController::getActivityRepetitions() const {
    return activityView->getRepetitions();
}



// GETTER

// EQUIPMENT VIEW GETTER/SETTER
//SETTER

void ViewController::setEquipment(const QString &name, int recoilIntensity, int recoilCount, int vibrationIntensity, int vibrationCount){

}

void ViewController::addEquipment(int id, const QString &name, int recoilIntensity, int recoilCount, int vibrationIntensity, int vibrationCount){

}

void ViewController::clearEquipment(){

}

// GETTER
QString ViewController::getEquipmentName() const{

}

int ViewController::getEquipmentRecoilIntensity() const{

}

int ViewController::getEquipmentRecoilCount() const{

}

int ViewController::getEquipmentVibrationIntensity() const{

}

int ViewController::getEquipmentVibrationCount() const{

}
// PRODUCT VIEW GETTER/SETTER
// SETTER
void ViewController::setProduct(const QString &name, const QString &number, int totalPercentage){
    productView->setProduct(name, number, totalPercentage);
}

void ViewController::addProduct(int id, const QString &name){
    productView->addProduct(id, name);
}

void ViewController::clearProducts(){
    productView->clearProducts();
}

// GETTER
QString ViewController::getProductName() const{
    return productView->getName();
}

QString ViewController::getProductNumber() const{
    return productView->getNumber();
}

int ViewController::getProductTotalPercentage() const{
    return productView->getTotalPercentage();
}

// TRANSPORTATION VIEW GETTER/SETTER
//SETTER
void ViewController::setTransportation(const QString &name, int hasFixedRoller, int hasBrakes, int emptyWeight, int maxLoad){

}

void ViewController::addTransportation(int id, const QString &name, int hasFixedRoller, int hasBrakes, int emptyWeight, int maxLoad){

}

void ViewController::clearTransportations(){

}

// GETTER
QString ViewController::getTransportationName() const{

}

int ViewController::hasTransportationFixedRoller() const{

}

int ViewController::hasTransportationBrakes() const{

}

int ViewController::getTransportationEmptyWeight() const{

}

int ViewController::getTransportationMaxLoad() const{

}


// COMMENT VIEW GETTER/SETTER
//SETTER
void ViewController::setComment(const QString &problemName, const QString &problemDesc, const QString &measureName, const QString &measureDesc, const QString &workerPerception){
    commentView->setComment(problemName, problemDesc, measureName, measureDesc, workerPerception);
}

// GETTER
QString ViewController::getCommentProblemName() const{
    return commentView->getProblemName();
}

QString ViewController::getCommentProblemDescription() const{
    return commentView->getProblemDescription();
}

QString ViewController::getCommentMeasureName() const{
    return commentView->getMeasureName();
}

QString ViewController::getCommentMeasureDescription() const{
    return commentView->getMeasureDescription();
}

QString ViewController::getCommentWorkerPerception() const{
    return commentView->getWorkerPerception();
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
        case ViewController::EMPLOYEE_VIEW:
            emit updateEmployeeView();
            break;
        case ViewController::ACTIVITY_VIEW:
            emit updateActivityView();
            break;
        case ViewController::COMMENT_VIEW:
            emit updateCommentView();
            break;
        case ViewController::DOCUMENTATION_VIEW:
            break;
        case ViewController::RESSOURCE_MANAGEMENT_VIEW:
            break;
        case ViewController::PRODUCT_VIEW:
            break;
        case ViewController::EQUIPMENT_VIEW:
            break;
        case ViewController::TRANSPORTATION_VIEW:
            break;
        case ViewController::SETTINGS_VIEW:
            break;
        default:
            break;
    }
    ViewController::setCurrentIndex(nextView);
}

void ViewController::goToView(int index){
    previousViews->push(currentIndex());
    setCurrentIndex(index);
}

