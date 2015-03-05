#ifndef IEMPLOYEELIST
#define IEMPLOYEELIST

#include <QtPlugin>

class IEmployeeList{

public slots:
    virtual void addEmployee(QHash<QString, QVariant> values) = 0;
    virtual void removeEmployee(int id) = 0;
    virtual void clear() = 0;

signals:
    virtual void createEmployee(QHash<QString, QVariant> values) = 0;
    virtual void deleteEmployee(int id) = 0;
    virtual void selectEmployee(int id) = 0;

};

#define IEmployee_iid "IEmployeeList"

Q_DECLARE_INTERFACE(IEmployeeList, IEmployee_iid)

#endif // IEMPLOYEELIST

