#include "employeeview.h"
#include "QGridLayout"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include <QSpacerItem>
#include "separator.h"

EmployeeView::EmployeeView(QWidget *parent) : SimpleNavigateableWidget(tr("Worker Data"),parent),
    lblGender(new QLabel(tr("Gender:"))),
    lblStaffNumber(new QLabel(tr("Personal ID:"))),
    lblNote(new QLabel(tr("Remarks:"))),
    oscGender(new OptionSelectionControl()),
    vcAge(new ValueControl(VALUE)),
    vcHeight(new ValueControl(VALUE)),
    txtBxStaffNumber(new TextLineEdit()),
    txtBxNote(new TextEdit())
{
    vcAge->setText(tr("age"));
    vcAge->setValues(16, 70, ageValues, QString(""));
    vcAge->setValue(35);

    vcHeight->setText(tr("height"));
    vcHeight->setValues(100, 220, heightValues, QString(""));
    vcHeight->setValue(175);

    oscGender->setValues(genderTextValues);

    QGridLayout *employeeDataLayout = new QGridLayout();
    employeeDataLayout->addWidget(lblGender, 0, 0, 1, 1, 0);
    employeeDataLayout->addWidget(oscGender, 0, 1, 1, 1, 0);
    employeeDataLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 1, 0, 1, 2, 0);
    employeeDataLayout->addWidget(vcAge, 2, 0, 1, 2, 0);
    employeeDataLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 3, 0, 1, 2, 0);
    employeeDataLayout->addWidget(vcHeight, 4, 0, 1, 2, 0);
    employeeDataLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 5, 0, 1, 2, 0);
    employeeDataLayout->addWidget(lblStaffNumber, 6, 0, 1, 1, 0);
    employeeDataLayout->addWidget(txtBxStaffNumber, 6, 1, 1, 1, 0);
    employeeDataLayout->addWidget(lblNote, 7, 0, 1, 1, 0);
    employeeDataLayout->addWidget(txtBxNote, 7, 1, 1, 1, 0);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(employeeDataLayout);
    mainLayout->addSpacerItem(new QSpacerItem(0, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

    setLayout(mainLayout);
}

EmployeeView::~EmployeeView()
{

}

//PUBLIC SLOTS
void EmployeeView::setEmployee(int gender, int age, int height, const QString &staffNumber, const QString &note){
    oscGender->setSelectedValue(gender);
    vcAge->setValue(age);
    vcHeight->setValue(height);
    txtBxStaffNumber->setText(staffNumber);
    txtBxNote->setText(note);
}


//GETTER
int EmployeeView::getGender() const{
    return oscGender->getSelectedID();
}
int EmployeeView::getAge() const{
    return vcAge->getValue();
}
int EmployeeView::getHeight() const{
    return vcHeight->getValue();
}
QString EmployeeView::getStaffNumber() const{
    return txtBxStaffNumber->text();
}
QString EmployeeView::getNote() const{
    return txtBxNote->toPlainText();
}
