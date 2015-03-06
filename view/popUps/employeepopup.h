#ifndef EMPLOYEEPOPUP_H
#define EMPLOYEEPOPUP_H

#include "../navigation/abstractpopupwidget.h"
#include <QGridLayout>
#include "../interfaces/iemployeelist.h"
#include "../../databaseHandler/dbconstants.h"
#include "../detailedlistitem.h"

class EmployeePopUp : public AbstractPopUpWidget, IEmployeeList
{
    Q_OBJECT
    Q_INTERFACES(IEmployeeList)
public:
    EmployeePopUp(QWidget *parent = 0);

signals:
    void createEmployee(QHash<QString, QVariant> values);
    void deleteEmployee(int id);
    void selectEmployee(int id);

    void selectedEmployee(int id);

public slots:
    void onEnter();
    void addEmployee(QHash<QString, QVariant> values);
    void updateEmployee(QHash<QString, QVariant> values);
    void removeEmployee(int id);
    void clear();

    void setSelectedEmployee(int id);

private slots:
    void selectedEmployeeChanged(int id);

private:
    const QList<QStringList> employeeCaptions = QList<QStringList>() <<(QStringList() << tr("Staff number"));
    QGridLayout *mainLayout;
    int selectedEmployeeID;

};

#endif // EMPLOYEEPOPUP_H
