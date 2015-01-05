#include "metadataview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSpacerItem>
#include "separator.h"

MetaDataView::MetaDataView(QWidget *parent) :
    QWidget(parent),
    btnBack(new QPushButton("Zurück", this)),
    lblViewDescription(new QLabel("Kopfdaten", this)),
    btnForward(new QPushButton("Arbeitsplätze",this)),
    lblAnalyst(new QLabel("Analyst", this)),
    lblAnalystLastName(new QLabel("Nachname:", this)),
    lblAnalystFirstName(new QLabel("Vorname:", this)),
    lblAnalystEmployer(new QLabel("Arbeitgeber:", this)),
    lblAnalystExperience(new QLabel("Erfahrung:", this)),
    txtBxAnalystLastName(new TextLineEdit(this)),
    txtBxAnalystFirstName(new TextLineEdit(this)),
    txtBxAnalystEmployer(new TextLineEdit(this)),
    txtBxAnalystExperience(new TextLineEdit(this)),
    lblCorporation(new QLabel("Unternehmen", this)),
    lblCorpName(new QLabel("Name:", this)),
    txtBxCorpName(new TextLineEdit(this)),
    lblFactory(new QLabel("Werk", this)),
    lblFactoryName(new QLabel("Name:", this)),
    lblFactoryStreet(new QLabel("Straße:", this)),
    lblFactoryCity(new QLabel("Stadt:", this)),
    lblFactoryZip(new QLabel("PLZ:", this)),
    lblFactoryCountry(new QLabel("Land:", this)),
    lblFactoryContact(new QLabel("Kontakt:", this)),
    lblFactoryEmployeeCount(new QLabel("Mitarbeiter:", this)),
    txtBxFactoryName(new TextLineEdit(this)),
    txtBxFactoryStreet(new TextLineEdit(this)),
    txtBxFactoryCity(new TextLineEdit(this)),
    txtBxFactoryZip(new NumberLineEdit(this)),
    txtBxFactoryCountry(new TextLineEdit(this)),
    txtBxFactoryContact(new TextLineEdit(this)),
    txtBxFactoryEmployeeCount(new NumberLineEdit(this)),
    lblRecordingDateTime(new QLabel("Aufnahme", this)),
    dteRecordingTimeBegin(new QDateTimeEdit(this)),
    dteRecordingTimeEnd(new QDateTimeEdit(this))
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QGridLayout *navigationBarLayout = new QGridLayout;
    QGridLayout *analystLayout = new QGridLayout;
    QHBoxLayout *corporationLayout = new QHBoxLayout;
    QGridLayout *factoryLayout = new QGridLayout;
    QHBoxLayout *recordingLayout = new QHBoxLayout;

    btnBack->setObjectName("btnNavigation");
    connect(btnBack, SIGNAL(clicked()), this, SLOT(backButtonClicked()));
    btnForward->setObjectName("btnNavigation");
    txtBxCorpName->setMaximumWidth(350);


    navigationBarLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewDescription, 0, 1, 1, 1, Qt::AlignCenter);
    navigationBarLayout->addWidget(btnForward, 0, 2, 1, 1, Qt::AlignRight);

    analystLayout->addWidget(lblAnalystLastName, 0, 0, 1, 1, 0);
    analystLayout->addWidget(txtBxAnalystLastName, 0, 1, 1, 1, 0);
    analystLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 0, 2, 1, 1, 0);
    analystLayout->addWidget(lblAnalystFirstName, 0, 3, 1, 1, 0);
    analystLayout->addWidget(txtBxAnalystFirstName, 0, 4, 1, 1, 0);
    analystLayout->addWidget(lblAnalystEmployer, 1, 0, 1, 1, 0);
    analystLayout->addWidget(txtBxAnalystEmployer, 1, 1, 1, 1, 0);
    analystLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 1, 2, 1, 1, 0);
    analystLayout->addWidget(lblAnalystExperience, 1, 3, 1, 1, 0);
    analystLayout->addWidget(txtBxAnalystExperience, 1, 4, 1, 1, 0);

    corporationLayout->addWidget(lblCorpName);
    corporationLayout->addWidget(txtBxCorpName);
    corporationLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

    factoryLayout->addWidget(lblFactoryName, 0, 0, 1, 1, 0);
    factoryLayout->addWidget(txtBxFactoryName, 0, 1, 1, 3, 0);
    factoryLayout->addWidget(lblFactoryStreet, 1, 0, 1, 1, 0);
    factoryLayout->addWidget(txtBxFactoryStreet, 1, 1, 1, 1, 0);
    factoryLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 1, 2, 1, 1, 0);
    factoryLayout->addWidget(lblFactoryZip, 1, 3, 1, 1, 0);
    factoryLayout->addWidget(txtBxFactoryZip, 1, 4, 1, 1, 0);
    factoryLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 1, 5, 1, 1, 0);
    factoryLayout->addWidget(lblFactoryCity, 1, 6, 1, 1, 0);
    factoryLayout->addWidget(txtBxFactoryCity, 1, 7, 1, 1, 0);
    factoryLayout->addWidget(lblFactoryCountry, 2, 0, 1, 1, 0);
    factoryLayout->addWidget(txtBxFactoryCountry, 2, 1, 1, 1, 0);
    factoryLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 2, 2, 1, 1, 0);
    factoryLayout->addWidget(lblFactoryContact, 2, 3, 1, 1, 0);
    factoryLayout->addWidget(txtBxFactoryContact, 2, 4, 1, 1, 0);
    factoryLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 2, 5, 1, 1, 0);
    factoryLayout->addWidget(lblFactoryEmployeeCount, 2, 6, 1, 1, 0);
    factoryLayout->addWidget(txtBxFactoryEmployeeCount, 2, 7, 1, 1, 0);

    recordingLayout->addWidget(dteRecordingTimeBegin);
    recordingLayout->addWidget(dteRecordingTimeEnd);

    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));

    mainLayout->addWidget(lblAnalyst);
    mainLayout->addLayout(analystLayout);
    mainLayout->addLayout(analystLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));

    mainLayout->addWidget(lblCorporation);
    mainLayout->addLayout(corporationLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));

    mainLayout->addWidget(lblFactory);
    mainLayout->addLayout(factoryLayout);
    mainLayout->addLayout(factoryLayout);
    mainLayout->addLayout(factoryLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));

    mainLayout->addWidget(lblRecordingDateTime);
    mainLayout->addLayout(recordingLayout);

    setLayout(mainLayout);
}

void MetaDataView::backButtonClicked(){
    emit saveMetaData();
    emit showMainMenu();
}


// GETTER

QString MetaDataView::getAnalystLastName() const {
    return txtBxAnalystLastName->text();
}

QString MetaDataView::getAnalystFirstName() const {
    return txtBxAnalystFirstName->text();
}

QString MetaDataView::getAnalystEmployer() const {
    return txtBxAnalystEmployer->text();
}

QString MetaDataView::getAnalystExperience() const {
    return txtBxAnalystExperience->text();
}

QString MetaDataView::getCorporationName() const {
    return txtBxCorpName->text();
}

QString MetaDataView::getFactoryName() const {
    return txtBxFactoryName->text();
}

QString MetaDataView::getFactoryStreet() const {
    return txtBxFactoryStreet->text();
}

int MetaDataView::getFactoryZip() const {
    return txtBxFactoryZip->getValue();
}

QString MetaDataView::getFactoryCity() const {
    return txtBxFactoryCity->text();
}

QString MetaDataView::getFactoryCountry() const {
    return txtBxFactoryCountry->text();
}

QString MetaDataView::getFactoryContact() const {
    return txtBxFactoryContact->text();
}

int MetaDataView::getFactoryEmployeeCount() const {
    return txtBxFactoryEmployeeCount->getValue();
}

QDateTime MetaDataView::getRecordTimeBegin() const {
    return dteRecordingTimeBegin->dateTime();
}

QDateTime MetaDataView::getRecordTimeEnd() const {
    return dteRecordingTimeEnd->dateTime();
}

// SETTER SLOTS

void MetaDataView::setAnalyst(const QString &lastName, const QString &firstName, const QString &employer, const QString &experience){
    txtBxAnalystLastName->setText(lastName);
    txtBxAnalystFirstName->setText(firstName);
    txtBxAnalystEmployer->setText(employer);
    txtBxAnalystExperience->setText(experience);
}

void MetaDataView::setCorporation(const QString &name){
    txtBxCorpName->setText(name);
}

void MetaDataView::setFactory(const QString &name, const QString &street, int zip, const QString &city, const QString &country, const QString &contact, int employeeCount){
    txtBxFactoryName->setText(name);
    txtBxFactoryStreet->setText(street);
    txtBxFactoryZip->setValue(zip);
    txtBxFactoryCity->setText(city);
    txtBxFactoryCountry->setText(country);
    txtBxFactoryContact->setText(contact);
    txtBxFactoryEmployeeCount->setValue(employeeCount);
}

void MetaDataView::setRecordTime(const QDateTime &begin, const QDateTime &end){
    dteRecordingTimeBegin->setDateTime(begin);
    dteRecordingTimeEnd->setDateTime(end);
}