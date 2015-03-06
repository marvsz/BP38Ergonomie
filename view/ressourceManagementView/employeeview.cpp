#include "employeeview.h"
#include "QGridLayout"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include <QSpacerItem>
#include "../separator.h"

EmployeeView::EmployeeView(QWidget *parent) : SimpleNavigateableWidget(tr("Worker Data"), parent),
    lblGender(new QLabel(tr("Gender:"))),
    lblStaffNumber(new QLabel(tr("Personal ID:"))),
    lblNote(new QLabel(tr("Remarks:"))),
    oscGender(new OptionSelectionControl()),
    vcAge(new ValueControl(VALUE)),
    vcHeight(new ValueControl(VALUE)),
    txtBxStaffNumber(new TextLineEdit()),
    txtBxNote(new TextEdit()),
    btnBodyMeasurements(new QPushButton())

{
    btnBodyMeasurements->setFixedSize(45, 45);
    btnBodyMeasurements->setObjectName("bodyMeasurementIcon");

    connect(btnBodyMeasurements, SIGNAL(clicked()), this, SLOT(btnBodyMeasurementsClicked()));

    vcAge->setText(tr("age"));
    vcAge->setValues(16, 70, ageValues, QString(""));
    vcAge->setValue(35);

    vcHeight->setText(tr("height"));
    vcHeight->setValues(100, 220, heightValues, QString(""));
    vcHeight->setValue(175);

    oscGender->setValues(genderTextValues);

    QGridLayout *employeeDataLayout = new QGridLayout;
    employeeDataLayout->setAlignment(Qt::AlignTop);
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
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addLayout(employeeDataLayout);

    setLayout(mainLayout);
}

EmployeeView::~EmployeeView()
{

}

//PUBLIC METHODS
QList<QAbstractButton*> * EmployeeView::getAdditionalNavigation() const{
    QList<QAbstractButton*> *additions = new QList<QAbstractButton*>();
    additions->append(btnBodyMeasurements);
    return additions;
}

//PUBLIC SLOTS
void EmployeeView::setEmployee(QHash<QString, QVariant> values){
    oscGender->setSelectedValue(values.value(DBConstants::COL_EMPLOYEE_GENDER).toInt());
    vcAge->setValue(values.value(DBConstants::COL_EMPLOYEE_AGE).toInt());
    vcHeight->setValue(values.value(DBConstants::COL_EMPLOYEE_HEIGHT).toInt());
    txtBxStaffNumber->setText(values.value(DBConstants::COL_EMPLOYEE_STAFF_NUMBER).toString());
    txtBxNote->setText(values.value(DBConstants::COL_EMPLOYEE_NOTE).toString());
}

void EmployeeView::onLeaving(){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_EMPLOYEE_GENDER, oscGender->getSelectedID());
    values.insert(DBConstants::COL_EMPLOYEE_AGE, vcAge->getValue());
    values.insert(DBConstants::COL_EMPLOYEE_HEIGHT, vcHeight->getValue());
    values.insert(DBConstants::COL_EMPLOYEE_STAFF_NUMBER, txtBxStaffNumber->text());
    values.insert(DBConstants::COL_EMPLOYEE_NOTE, txtBxNote->toPlainText());
    emit saveEmployee(values);
}

//PRIVATE SLOTS
void EmployeeView::btnBodyMeasurementsClicked(){
    emit showView(ViewType::BODY_MEASUREMENT_VIEW);
}

