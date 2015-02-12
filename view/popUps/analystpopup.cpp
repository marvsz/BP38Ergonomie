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
    mainLayout->addWidget(new QLabel(tr("Experience")), 3, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxAnalystExperience, 3, 1, 1, 1, 0);

    setLayout(mainLayout);
}

AnalystPopUp::~AnalystPopUp()
{

}

//PUBLIC SLOTS
void AnalystPopUp::onEnter(){
    txtBxAnalystLastName->setText("");
    txtBxAnalystFirstName->setText("");
    txtBxAnalystEmployer->setText("");
    txtBxAnalystExperience->setText("");
}

//GETTER
QString AnalystPopUp::getAnalystLastName() const {
    return txtBxAnalystLastName->text();
}

QString AnalystPopUp::getAnalystFirstName() const {
    return txtBxAnalystFirstName->text();
}

QString AnalystPopUp::getAnalystEmployer() const {
    return txtBxAnalystEmployer->text();
}

QString AnalystPopUp::getAnalystExperience() const {
    return txtBxAnalystExperience->text();
}
