#include "employeepopup.h"
#include <QGridLayout>

EmployeePopUp::EmployeePopUp(QWidget *parent):
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Select employee"), parent)
{
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(new QLabel("test"), 0, 0, 1, 1, 0);

    setLayout(mainLayout);
}

EmployeePopUp::~EmployeePopUp()
{

}

