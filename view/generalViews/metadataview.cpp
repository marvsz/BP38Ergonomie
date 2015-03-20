#include "metadataview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSpacerItem>
#include "../separator.h"

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
    connect(dteRecordingTimeEnd, SIGNAL(dateTimechanged()), this, SLOT(validateEndTime()));

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

// PUBLIC SLOTS
void MetaDataView::setRecording(QHash<QString, QVariant> values){
    QDateTime time = QDateTime();
    dteRecordingTimeBegin->setDateTime(time.fromString(values.value(DBConstants::COL_RECORDING_START).toString()));
    dteRecordingTimeEnd->setDateTime(time.fromString(values.value(DBConstants::COL_RECORDING_END).toString()));
}

void MetaDataView::setFactory(QHash<QString, QVariant> values){
    txtBxFactoryName->setText(values.value(DBConstants::COL_FACTORY_NAME).toString());
    txtBxFactoryStreet->setText(values.value(DBConstants::COL_FACTORY_STREET).toString());
    txtBxFactoryCity->setText(values.value(DBConstants::COL_FACTORY_CITY).toString());
    txtBxFactoryZip->setValue(values.value(DBConstants::COL_FACTORY_ZIP).toInt());
    txtBxFactoryCountry->setText(values.value(DBConstants::COL_FACTORY_COUNTRY).toString());
    txtBxFactoryEmployeeCount->setValue(values.value(DBConstants::COL_FACTORY_HEADCOUNT).toInt());
    txtBxFactoryContact->setText(values.value(DBConstants::COL_FACTORY_CONTACT_PERSON).toString());
}

void MetaDataView::setCorperation(QHash<QString, QVariant> values){
    txtBxCorpName->setText(values.value(DBConstants::COL_CORPORATION_NAME).toString());
}

void MetaDataView::setBranchOfIndustry(QHash<QString, QVariant> values){
    txtBxBoIName->setText(values.value(DBConstants::COL_BRANCH_OF_INDUSTRY_NAME).toString());
    txtBxBoIDescription->setText(values.value(DBConstants::COL_BRANCH_OF_INDUSTRY_DESCRIPTION).toString());
}


void MetaDataView::onLeaving(){
    QHash<QString, QVariant> boiValues = QHash<QString, QVariant>();
    boiValues.insert(DBConstants::COL_BRANCH_OF_INDUSTRY_NAME, txtBxBoIName->text());
    boiValues.insert(DBConstants::COL_BRANCH_OF_INDUSTRY_DESCRIPTION, txtBxBoIDescription->text());
    emit saveBranchOfIndustry(boiValues);

    QHash<QString, QVariant> corpValues = QHash<QString, QVariant>();
    corpValues.insert(DBConstants::COL_CORPORATION_NAME, txtBxCorpName->text());
    corpValues.insert(DBConstants::COL_BRANCH_OF_INDUSTRY_NAME, txtBxBoIName->text());
    emit saveCorperation(corpValues);

    QHash<QString, QVariant> factoryValues = QHash<QString, QVariant>();
    factoryValues.insert(DBConstants::COL_FACTORY_NAME, txtBxFactoryName->text());
    factoryValues.insert(DBConstants::COL_FACTORY_STREET, txtBxFactoryStreet->text());
    factoryValues.insert(DBConstants::COL_FACTORY_CITY, txtBxFactoryCity->text());
    factoryValues.insert(DBConstants::COL_FACTORY_ZIP, txtBxFactoryZip->getValue());
    factoryValues.insert(DBConstants::COL_FACTORY_COUNTRY, txtBxFactoryCountry->text());
    factoryValues.insert(DBConstants::COL_FACTORY_HEADCOUNT, txtBxFactoryEmployeeCount->getValue());
    factoryValues.insert(DBConstants::COL_FACTORY_CONTACT_PERSON, txtBxFactoryContact->text());
    factoryValues.insert(DBConstants::COL_CORPORATION_NAME, txtBxCorpName->text());
    emit saveFactory(factoryValues);

    QHash<QString, QVariant> recordValues = QHash<QString, QVariant>();
    recordValues.insert(DBConstants::COL_RECORDING_START, dteRecordingTimeBegin->getDateTime().toString());
    recordValues.insert(DBConstants::COL_RECORDING_END, dteRecordingTimeEnd->getDateTime().toString());
    recordValues.insert(DBConstants::COL_FACTORY_NAME, txtBxFactoryName->text());
    recordValues.insert(DBConstants::COL_FACTORY_STREET, txtBxFactoryStreet->text());
    emit saveRecording(recordValues);
}

//PRIVATE SLOTS
void MetaDataView::validateEndTime(){
    if(dteRecordingTimeEnd->getDateTime() < dteRecordingTimeBegin->getDateTime()){
        dteRecordingTimeBegin->setDateTime(dteRecordingTimeEnd->getDateTime());
    }
}
