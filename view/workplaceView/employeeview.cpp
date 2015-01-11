#include "employeeview.h"
#include "QGridLayout"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include <QSpacerItem>
#include "separator.h"

EmployeeView::EmployeeView(QWidget *parent) : QWidget(parent),
    lblViewName(new QLabel(tr("Coworker data"))),
    lblGender(new QLabel(tr("gender:"))),
    lblStaffNumber(new QLabel(tr("PersonalID:"))),
    lblNote(new QLabel(tr("Remarks:"))),
    oscGender(new OptionSelectionControl()),
    vcAge(new ValueControl(VariantControl::VALUE_CONTROL)),
    vcHeight(new ValueControl(VariantControl::VALUE_CONTROL)),
    txtBxStaffNumber(new TextLineEdit()),
    txtBxNote(new TextEdit()),
    btnBack(new QPushButton(tr("back")))
{
    btnBack->setObjectName("btnNavigation");

    connect(btnBack, SIGNAL(clicked()), this, SLOT(btnBackClicked()));

    vcAge->setText(tr("age"));
    vcAge->setValues(16, 70, ageValues,new QString(""));
    vcAge->setValue(35);

    vcHeight->setText(tr("height"));
    vcHeight->setValues(100, 220, heightValues, new QString(""));
    vcHeight->setValue(175);

    oscGender->setValues(genderTextValues);

    QGridLayout *navigationBarLayout = new QGridLayout();
    navigationBarLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewName, 0, 1, 1, 1, Qt::AlignCenter);
    navigationBarLayout->addWidget(new QLabel(), 0, 2, 1, 1, 0);

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
    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
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


//PRIVATE SLOTS
void EmployeeView::btnBackClicked(){
    emit save();
    emit back();
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
