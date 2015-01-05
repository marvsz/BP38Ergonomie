#include "viewcontroller.h"

ViewController::ViewController(QWidget *parent) :
    QStackedWidget(parent)
{
    previousView = ViewController::MAIN_MENU_VIEW;
    mainMenuView = new MainMenu;
    metaDataView = new MetaDataView;
    workplaceListView = new WorkplaceListView;
    documentationView = new DocumentationView;

    connect(mainMenuView, SIGNAL(metaDataViewSelected()), this, SLOT(setMetaDataView()));
    connect(mainMenuView, SIGNAL(workplaceListViewSelected()), this, SLOT(setWorkplaceListView()));
    connect(mainMenuView, SIGNAL(newRecordingViewSelected()), this, SLOT(setDocumentationView()));

    connect(metaDataView, SIGNAL(showMainMenu()), this, SLOT(setMainMenuView()));
    connect(metaDataView, SIGNAL(showWorkplaceListView()), this, SLOT(setWorkplaceListView()));
    connect(metaDataView, SIGNAL(saveMetaData()), this, SLOT(saveMetaDataRequested()));

    connect(workplaceListView, SIGNAL(showPreviousView()), this, SLOT(setWorkplaceListPreviousView()));
    connect(documentationView, SIGNAL(showMainMenu()), this, SLOT(setMainMenuView()));

    this->addWidget(mainMenuView);
    this->addWidget(metaDataView);
    this->addWidget(workplaceListView);
    this->addWidget(documentationView);

    setCurrentIndex(ViewController::MAIN_MENU_VIEW);
}

void ViewController::setMainMenuView(){
    previousView = currentIndex();
    setCurrentIndex(ViewController::MAIN_MENU_VIEW);
}

void ViewController::setMetaDataView(){
    previousView = currentIndex();
    setCurrentIndex(ViewController::METADATA_VIEW);
    emit updateMetaData();
}

void ViewController::setWorkplaceListView(){
    previousView = currentIndex();
    setCurrentIndex(ViewController::WORKPLACELIST_VIEW);
    if(previousView == ViewController::METADATA_VIEW)
        emit updateMetaData();
}

void ViewController::setDocumentationView(){
    previousView = currentIndex();
    setCurrentIndex(ViewController::DOCUMENTATION_VIEW);
}

void ViewController::setWorkplaceListPreviousView(){
    if(previousView == ViewController::MAIN_MENU_VIEW){
        setMainMenuView();
    }
    else if (previousView == ViewController::METADATA_VIEW){
        setMetaDataView();
    }
}

// WORKPLACELISTVIEW GETTER/SETTER
void ViewController::saveWorkplaceListRequested(){

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
