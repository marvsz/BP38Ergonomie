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
    shiftPauseView = new ShiftPauseView;
    productView = new ProductView;
    commentView = new CommentView;
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
    connect(workplaceView, SIGNAL(showLineView()), this, SLOT(goToLineView()));
    connect(workplaceView, SIGNAL(showShiftAndPauseView()), this, SLOT(goToShiftAndPauseView()));
    connect(workplaceView, SIGNAL(showEmployeeView()), this, SLOT(goToEmployeeView()));
    connect(workplaceView, SIGNAL(showProductView()), this, SLOT(goToProductView()));
    connect(workplaceView, SIGNAL(showCommentView()), this, SLOT(goToCommentView()));

    // LINE VIEW
    connect(lineView, SIGNAL(back()), this, SLOT(backToView()));
    connect(shiftPauseView, SIGNAL(back()), this, SLOT(backToView()));
    connect(employeeView, SIGNAL(back()), this, SLOT(backToView()));
    connect(productView, SIGNAL(back()), this, SLOT(backToView()));
    connect(commentView, SIGNAL(back()), this, SLOT(backToView()));

    // DOCUMENTATION VIEW
    connect(documentationView, SIGNAL(showPreviousView()), this, SLOT(backToView()));

    // ADD ALL VIEWS
    this->addWidget(mainMenuView);
    this->addWidget(metaDataView);
    this->addWidget(workplaceListView);
    this->addWidget(workplaceView);
    this->addWidget(lineView);
    this->addWidget(shiftPauseView);
    this->addWidget(employeeView);
    this->addWidget(productView);
    this->addWidget(commentView);
    this->addWidget(documentationView);

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

// WORKPLACE LIST VIEW SETTER

void ViewController::addWorkplace(int id, const QString &name, const QString &description, const QString &code){
    workplaceListView->addWorkplace(id, name, description, code);
}

void ViewController::clearWorkplaceList(){
    workplaceListView->clear();
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
            break;
        case ViewController::WORKPLACE_VIEW:
            emit updateWorkplaceList();
            break;
        case ViewController::LINE_VIEW:
            break;
        case ViewController::SHIFTPAUSE_VIEW:
            break;
        case ViewController::EMPLOYEE_VIEW:
            break;
        case ViewController::PRODUCT_VIEW:
            break;
        case ViewController::COMMENT_VIEW:
            break;
        case ViewController::DOCUMENTATION_VIEW:
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
