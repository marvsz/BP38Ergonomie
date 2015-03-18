#include "analystpopup.h"
#include <QGridLayout>
#include <QLabel>

AnalystPopUp::AnalystPopUp(QWidget *parent):
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Create Analyst"), parent),
    txtBxAnalystLastName(new TextLineEdit()),
    txtBxAnalystFirstName(new TextLineEdit()),
    txtBxAnalystEmployer(new TextLineEdit()),
    txtBxAnalystExperience(new TextLineEdit())
{
    txtBxAnalystLastName->setPlaceholderText(tr("last name"));
    txtBxAnalystFirstName->setPlaceholderText(tr("prename"));
    txtBxAnalystEmployer->setPlaceholderText(tr("employer"));
    txtBxAnalystExperience->setPlaceholderText(tr("experience"));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(new QLabel(tr("Last Name:")), 0, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxAnalystLastName, 0, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("First Name:")), 1, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxAnalystFirstName, 1, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Employer:")), 2, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxAnalystEmployer, 2, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Experience:")), 3, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxAnalystExperience, 3, 1, 1, 1, 0);

    connect(this, SIGNAL(confirm()), this, SLOT(onConfirm()));

    setLayout(mainLayout);
}

AnalystPopUp::~AnalystPopUp()
{

}

//PUBLIC SLOTS
void AnalystPopUp::onEnter(){
    txtBxAnalystLastName->clear();
    txtBxAnalystFirstName->clear();
    txtBxAnalystEmployer->clear();
    txtBxAnalystExperience->clear();
}

//PRIVATE SLOTS
void AnalystPopUp::onConfirm(){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_ANALYST_LASTNAME, txtBxAnalystLastName->text());
    values.insert(DBConstants::COL_ANALYST_FIRSTNAME, txtBxAnalystFirstName->text());
    values.insert(DBConstants::COL_ANALYST_EXPERIENCE, txtBxAnalystExperience->text());
    values.insert(DBConstants::COL_EMPLOYER_NAME, txtBxAnalystEmployer->text());
    emit saveAnalyst(values);
    emit closePopUp();
}

