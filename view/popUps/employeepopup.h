#ifndef EMPLOYEEPOPUP_H
#define EMPLOYEEPOPUP_H

#include "../navigation/abstractpopupwidget.h"
#include <QGridLayout>

class EmployeePopUp : public AbstractPopUpWidget
{
    Q_OBJECT
public:
    explicit EmployeePopUp(QWidget *parent = 0);
    ~EmployeePopUp();

public slots:
    void onEnter();
    void addEmployees(int id, const QString &name);
    //void setSelectedEmployee(int id);

private slots:
    void selectedEmployeeChanged(int id);

private:
    QGridLayout *mainLayout;
    int selectedEmployeeID;

};

#endif // EMPLOYEEPOPUP_H
