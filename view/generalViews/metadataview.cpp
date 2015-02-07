#include "metadataview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSpacerItem>
#include "separator.h"

MetaDataView::MetaDataView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Meta data"), parent),
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
    mainLayout->setAlignment(Qt::AlignTop);
    QGridLayout *upperLayout = new QGridLayout;
    upperLayout->setAlignment(Qt::AlignTop);
    QHBoxLayout *recordingLayout = new QHBoxLayout;
    recordingLayout->setAlignment(Qt::AlignTop);
    QVBoxLayout *beginLayout = new QVBoxLayout;
    QVBoxLayout *endLayout = new QVBoxLayout;

    lblCorporation->setObjectName("lblHeader");
    lblBranchOfIndustry->setObjectName("lblHeader");
    lblFactory->setObjectName("lblHeader");
    lblRecordingDateTime->setObjectName("lblHeader");

    txtBxBoIDescription->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    upperLayout->addWidget(lblCorporation, 0, 0, 1, 3, 0);
    upperLayout->addWidget(lblCorpName, 1, 0, 1, 1, 0);
    upperLayout->addWidget(txtBxCorpName, 1, 1, 1, 1, 0);
    upperLayout->addWidget(new Separator(Qt::Horizontal, 3, 0), 2, 0, 1, 5, 0);
    upperLayout->addItem(new QSpacerItem(0, 20, QSizePolicy::Fixed, QSizePolicy::Fixed), 3, 0, 1, 5, 0);
    upperLayout->addWidget(lblBranchOfIndustry, 4, 0, 1, 3, 0);
    upperLayout->addWidget(lblBoIName, 5, 0, 1, 1, 0);
    upperLayout->addWidget(txtBxBoIName, 5, 1, 1, 1, 0);
    upperLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 5, 2, 1, 1, 0);
    upperLayout->addWidget(lblBoIDescription, 5, 3, 1, 1, 0);
    upperLayout->addWidget(txtBxBoIDescription, 5, 4, 1, 1, 0);
    upperLayout->addWidget(new Separator(Qt::Horizontal, 3, 0), 6, 0, 1, 5, 0);
    upperLayout->addItem(new QSpacerItem(0, 20, QSizePolicy::Fixed, QSizePolicy::Fixed), 7, 0, 1, 5, 0);
    upperLayout->addWidget(lblFactory, 8, 0, 1, 3, 0);
    upperLayout->addWidget(lblFactoryName, 9, 0, 1, 1, 0);
    upperLayout->addWidget(txtBxFactoryName, 9, 1, 1, 1, 0);
    upperLayout->addWidget(lblFactoryStreet, 10, 0, 1, 1, 0);
    upperLayout->addWidget(txtBxFactoryStreet, 10, 1, 1, 1, 0);
    upperLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 10, 2, 1, 1, 0);
    upperLayout->addWidget(lblFactoryCity, 10, 3, 1, 1, 0);
    upperLayout->addWidget(txtBxFactoryCity, 10, 4, 1, 1, 0);
    upperLayout->addWidget(lblFactoryZip, 11, 0, 1, 1, 0);
    upperLayout->addWidget(txtBxFactoryZip, 11, 1, 1, 1, 0);
    upperLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 11, 2, 1, 1, 0);
    upperLayout->addWidget(lblFactoryCountry, 11, 3, 1, 1, 0);
    upperLayout->addWidget(txtBxFactoryCountry, 11, 4, 1, 1, 0);
    upperLayout->addWidget(lblFactoryContact, 12, 0, 1, 1, 0);
    upperLayout->addWidget(txtBxFactoryContact, 12, 1, 1, 1, 0);
    upperLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 12, 2, 1, 1, 0);
    upperLayout->addWidget(lblFactoryEmployeeCount, 12, 3, 1, 1, 0);
    upperLayout->addWidget(txtBxFactoryEmployeeCount, 12, 4, 1, 1, 0);

    beginLayout->addWidget(lblRecordingDateTimeBegin, 0, Qt::AlignCenter);
    beginLayout->addWidget(dteRecordingTimeBegin, 0, Qt::AlignCenter);

    endLayout->addWidget(lblRecordingDateTimeEnd, 0, Qt::AlignCenter);
    endLayout->addWidget(dteRecordingTimeEnd, 0, Qt::AlignCenter);

    recordingLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    recordingLayout->addLayout(beginLayout);
    recordingLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    recordingLayout->addLayout(endLayout);
    recordingLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

    mainLayout->addLayout(upperLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addSpacerItem(new QSpacerItem(0, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));
    mainLayout->addWidget(lblRecordingDateTime);
    mainLayout->addLayout(recordingLayout);

    setLayout(mainLayout);
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

// SETTER

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
