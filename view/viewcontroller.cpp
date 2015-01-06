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
    employeeView = new EmployeeView;
    documentationView = new DocumentationView;

    // MAIN MENU
    connect(mainMenuView, SIGNAL(metaDataViewSelected()), this, SLOT(goToMetaDataView()));
    connect(mainMenuView, SIGNAL(workplaceListViewSelected()), this, SLOT(goToWorkplaceListView()));
    connect(mainMenuView, SIGNAL(newRecordingViewSelected()), this, SLOT(goToDocumentationView()));

    // METADATA VIEW
    connect(metaDataView, SIGNAL(showMainMenu()), this, SLOT(backToView()));
    connect(metaDataView, SIGNAL(showWorkplaceListView()), this, SLOT(goToWorkplaceListView()));
    connect(metaDataView, SIGNAL(saveMetaData()), this, SLOT(saveMetaDataRequested()));

    // WORKPLACE LIST VIEW
    connect(workplaceListView, SIGNAL(showPreviousView()), this, SLOT(backToView()));
    connect(workplaceListView, SIGNAL(showNewWorkplaceView()), this, SLOT(goToWorkplaceView()));

    // WORKPLACE VIEW
    connect(workplaceView, SIGNAL(showPreviousView()), this, SLOT(backToView()));
    connect(workplaceView, SIGNAL(showWorkprocessView()), this, SLOT(goToDocumentationView()));

    // DOCUMENTATION VIEW
    connect(documentationView, SIGNAL(showPreviousView()), this, SLOT(backToView()));

    // ADD ALL VIEWS
    this->addWidget(mainMenuView);
    this->addWidget(metaDataView);
    this->addWidget(workplaceListView);
    this->addWidget(workplaceView);
    this->addWidget(lineView);
    this->addWidget(employeeView);
    this->addWidget(documentationView);

    setCurrentIndex(ViewController::MAIN_MENU_VIEW);
}

void ViewController::goToMetaDataView(){
    goToView(ViewController::METADATA_VIEW);
}

void ViewController::goToWorkplaceListView(){
    goToView(ViewController::WORKPLACELIST_VIEW);
}

void ViewController::goToWorkplaceView(){
    goToView(ViewController::WORKPLACE_VIEW);
}

void ViewController::goToLineView(){
    goToView(ViewController::LINE_VIEW);
}

void ViewController::goToShiftAndPauseView(){
    goToView(ViewController::SHIFTPAUSE_VIEW);
}

void ViewController::goToEmployeeView(){
    goToView(ViewController::EMPLOYEE_VIEW);
}

void ViewController::goToProductView(){
    goToView(ViewController::PRODUCT_VIEW);
}

void ViewController::goToCommentView(){
    goToView(ViewController::COMMENT_VIEW);
}

void ViewController::goToDocumentationView(){
    goToView(ViewController::DOCUMENTATION_VIEW);
}


// METADATAVIEW GETTER/SETTER

void ViewController::saveMetaDataRequested(){
    emit saveMetaData();
}

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

// SETTER SLOTS

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

// SET VIEWS AND PUSH/POP
void ViewController::backToView(){
    ViewController::setCurrentIndex(previousViews->pop());
}

void ViewController::goToView(int index){
    previousViews->push(currentIndex());
    setCurrentIndex(index);
}
