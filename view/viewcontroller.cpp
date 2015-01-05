#include "viewcontroller.h"

ViewController::ViewController(QWidget *parent) :
    QStackedWidget(parent)
{
    mainMenuView = new MainMenu;
    metaDataView = new MetaDataView;
    documentationView = new DocumentationView;

    connect(mainMenuView, SIGNAL(metaDataViewSelected()), this, SLOT(setMetaDataView()));
    connect(mainMenuView, SIGNAL(newRecordingViewSelected()), this, SLOT(setDocumentationView()));

    connect(metaDataView, SIGNAL(showMainMenu()), this, SLOT(setMainMenuView()));
    connect(metaDataView, SIGNAL(saveMetaData()), this, SLOT(saveMetaDataRequested()));
    connect(documentationView, SIGNAL(showMainMenu()), this, SLOT(setMainMenuView()));

    this->addWidget(mainMenuView);
    this->addWidget(metaDataView);
    this->addWidget(documentationView);

    setCurrentIndex(ViewController::MAIN_MENU_VIEW);
}

void ViewController::setMainMenuView(){
    setCurrentIndex(ViewController::MAIN_MENU_VIEW);
}

void ViewController::setMetaDataView(){
    setCurrentIndex(ViewController::METADATA_VIEW);
    emit updateMetaData();
}

void ViewController::setDocumentationView(){
    setCurrentIndex(ViewController::DOCUMENTATION_VIEW);
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
