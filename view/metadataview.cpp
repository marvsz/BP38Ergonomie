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
    dteRecordingBeginTime(new QDateTimeEdit(this)),
    dteRecordingEndTime(new QDateTimeEdit(this))
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

    recordingLayout->addWidget(dteRecordingBeginTime);
    recordingLayout->addWidget(dteRecordingEndTime);

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
    emit showMainMenu();
}
