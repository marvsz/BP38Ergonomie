#ifndef EMPLOYEEPOPUP_H
#define EMPLOYEEPOPUP_H

#include "../navigation/abstractpopupwidget.h"
#include <QGridLayout>
#include <QScrollArea>
#include "../interfaces/iemployeelist.h"
#include "../interfaces/iemployeeselect.h"
#include "../databaseHandler/dbconstants.h"
#include "../detailedlistitem.h"

class EmployeePopUp : public AbstractPopUpWidget, IEmployeeList, IEmployeeSelect
{
    Q_OBJECT
    Q_INTERFACES(IEmployeeList)
    Q_INTERFACES(IEmployeeSelect)
public:
    EmployeePopUp(QWidget *parent = 0);

signals:
    void createEmployee(QHash<QString, QVariant> values);
    void deleteEmployee(int id);
    void selectEmployee(int id);

    void saveEmployeeSelected(int id);
    void resetEmployeeSelection();

    void selectedEmployee(int id);

public slots:
    void addEmployee(QHash<QString, QVariant> values);
    void updateEmployee(QHash<QString, QVariant> values);
    void removeEmployee(int id);
    void clearEmployees();

    void setEmployeeSelected(int id);


private slots:
    void onConfirm();
    void onCancel();
    void selectedEmployeeChanged(int id);
    void deselectedEmployee(int id);

private:
    const QList<QStringList> employeeCaptions = QList<QStringList>() <<(QStringList() << tr("Staff number"));
    QGridLayout *mainLayout;
    QScrollArea *scEmployees;
    int selectedEmployeeID;

};

#endif // EMPLOYEEPOPUP_H
