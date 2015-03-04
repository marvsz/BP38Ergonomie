#ifndef EMPLOYEEPOPUP_H
#define EMPLOYEEPOPUP_H

#include "navigation/abstractpopupwidget.h"

class EmployeePopUp : public AbstractPopUpWidget
{
    Q_OBJECT
public:
    explicit EmployeePopUp(QWidget *parent = 0);
    ~EmployeePopUp();
};

#endif // EMPLOYEEPOPUP_H
