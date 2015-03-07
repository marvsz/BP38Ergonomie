#ifndef IEMPLOYEESELECT_H
#define IEMPLOYEESELECT_H

#include <QtPlugin>

class IEmployeeSelect {

public slots:
    virtual void setEmployeeSelected(int id) = 0;

signals:
    virtual void saveEmployeeSelected(int id) = 0;
};

#define IEmployeeSelect_iid "IEmployeeSelect"
Q_DECLARE_INTERFACE(IEmployeeSelect, IEmployeeSelect_iid)

#endif // IEMPLOYEESELECT_H
