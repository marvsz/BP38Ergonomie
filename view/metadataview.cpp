#include "metadataview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSpacerItem>
#include "separator.h"

MetaDataView::MetaDataView(QWidget *parent) :
    QWidget(parent),
    btnBack(new QPushButton()),
    lblViewDescription(new QLabel(tr("head data"), this)),
    btnForward(new QPushButton(tr("work places"),this)),
    lblCorporation(new QLabel(tr("coproration"), this)),
    lblCorpName(new QLabel(tr("name:"), this)),
    txtBxCorpName(new TextLineEdit(this)),
    lblBranchOfIndustry(new QLabel(tr("Branch of Industry"),this)),
    lblBoIName(new QLabel(tr("name:"),this)),
    txtBxBoIName(new TextLineEdit(this)),
    lblBoIDescription(new QLabel(tr("description:"),this)),
    txtBxBoIDescription(new TextLineEdit(this)),
    lblFactory(new QLabel(tr("factory"), this)),
    lblFactoryName(new QLabel(tr("name:"), this)),
    lblFactoryStreet(new QLabel(tr("street:"), this)),
    lblFactoryZip(new QLabel(tr("zip:"), this)),
    lblFactoryCity(new QLabel(tr("city:"), this)),
    lblFactoryCountry(new QLabel(tr("country:"), this)),
    lblFactoryContact(new QLabel(tr("contact:"), this)),
    lblFactoryEmployeeCount(new QLabel(tr("employee:"), this)),
    txtBxFactoryName(new TextLineEdit(this)),
    txtBxFactoryStreet(new TextLineEdit(this)),
    txtBxFactoryCity(new TextLineEdit(this)),
    txtBxFactoryZip(new NumberLineEdit(this)),
    txtBxFactoryCountry(new TextLineEdit(this)),
    txtBxFactoryContact(new TextLineEdit(this)),
    txtBxFactoryEmployeeCount(new NumberLineEdit(this)),
    lblRecordingDateTime(new QLabel(tr("recording"), this)),
    lblRecordingDateTimeBegin(new QLabel(tr("begin:"), this)),
    lblRecordingDateTimeEnd(new QLabel(tr("end:"), this)),
    dteRecordingTimeBegin(new DateTimeSpinner(this)),
    dteRecordingTimeEnd(new DateTimeSpinner(this))

{
    txtBxCorpName->setPlaceholderText(tr("name"));
    txtBxBoIName->setPlaceholderText(tr("name"));
    txtBxBoIDescription->setPlaceholderText(tr("description"));
    txtBxFactoryName->setPlaceholderText(tr("name"));
    txtBxFactoryStreet->setPlaceholderText(tr("street"));
    txtBxFactoryCity->setPlaceholderText(tr("city"));
    txtBxFactoryZip->setPlaceholderText(tr("zip"));
    txtBxFactoryCountry->setPlaceholderText(tr("country"));
    txtBxFactoryContact->setPlaceholderText(tr("contact"));
    txtBxFactoryEmployeeCount->setPlaceholderText(tr("count"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QGridLayout *navigationBarLayout = new QGridLayout;
    QHBoxLayout *corporationLayout = new QHBoxLayout;
    QHBoxLayout *branchOfIndustryLayout = new QHBoxLayout;
    QGridLayout *factoryLayout = new QGridLayout;
    QHBoxLayout *recordingLayout = new QHBoxLayout;
    QVBoxLayout *beginLayout = new QVBoxLayout;
    QVBoxLayout *endLayout = new QVBoxLayout;

    lblCorporation->setObjectName("lblHeader");
    lblBranchOfIndustry->setObjectName("lblHeader");
    lblFactory->setObjectName("lblHeader");
    lblRecordingDateTime->setObjectName("lblHeader");

    txtBxBoIDescription->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    btnBack->setObjectName("leftIcon");
    btnBack->setFixedSize(45, 45);
    connect(btnBack, SIGNAL(clicked()), this, SLOT(backButtonClicked()));
    btnForward->setObjectName("btnNavigation");
    connect(btnForward, SIGNAL(clicked()), this, SLOT(forwardButtonClicked()));
    txtBxCorpName->setMaximumWidth(317);

    navigationBarLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewDescription, 0, 1, 1, 1, Qt::AlignCenter);
    navigationBarLayout->addWidget(btnForward, 0, 2, 1, 1, Qt::AlignRight);


    corporationLayout->addWidget(lblCorpName);
    corporationLayout->addWidget(txtBxCorpName);
    corporationLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

    branchOfIndustryLayout->addWidget(lblBoIName);
    branchOfIndustryLayout->addWidget(txtBxBoIName);
    branchOfIndustryLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
    branchOfIndustryLayout->addWidget(lblBoIDescription);
    branchOfIndustryLayout->addWidget(txtBxBoIDescription);

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

    beginLayout->addWidget(lblRecordingDateTimeBegin, 0, Qt::AlignCenter);
    beginLayout->addWidget(dteRecordingTimeBegin, 0, Qt::AlignCenter);

    endLayout->addWidget(lblRecordingDateTimeEnd, 0, Qt::AlignCenter);
    endLayout->addWidget(dteRecordingTimeEnd, 0, Qt::AlignCenter);

    recordingLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    recordingLayout->addLayout(beginLayout);
    recordingLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    recordingLayout->addLayout(endLayout);
    recordingLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));

    mainLayout->addWidget(lblCorporation);
    mainLayout->addLayout(corporationLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));

    mainLayout->addWidget(lblBranchOfIndustry);
    mainLayout->addLayout(branchOfIndustryLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));

    mainLayout->addWidget(lblFactory);
    mainLayout->addLayout(factoryLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));

    mainLayout->addWidget(lblRecordingDateTime);
    mainLayout->addLayout(recordingLayout);

    setLayout(mainLayout);
}

void MetaDataView::backButtonClicked(){
    emit save();
    emit back();
}

void MetaDataView::forwardButtonClicked(){
    emit save();
    emit forward();
}

// GETTER

QString MetaDataView::getCorporationName() const {
    return txtBxCorpName->text();
}

QString MetaDataView::getBranchOfIndustryName() const {
    return txtBxBoIName->text();
}

QString MetaDataView::getBranchOfIndustryDescription() const {
    return txtBxBoIDescription->text();
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
    return dteRecordingTimeBegin->getDateTime();
}

QDateTime MetaDataView::getRecordTimeEnd() const {
    return dteRecordingTimeEnd->getDateTime();
}


void MetaDataView::setEmployer(const QString &employer){
    txtBxAnalystEmployer->setText(employer);
}

void MetaDataView::setCorporation(const QString &name){
    txtBxCorpName->setText(name);


}

void MetaDataView::setBranchOfIndustry(const QString &name, const QString &description){
    txtBxBoIName->setText(name);
    txtBxBoIDescription->setText(description);
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
