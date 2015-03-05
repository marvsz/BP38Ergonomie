#ifndef IEMPLOYEE
#define IEMPLOYEE

#include <QtPlugin>

class IEmployee {

public slots:
    virtual void setEmployee(QHash<QString, QVariant> values) = 0;

signals:
    virtual void saveEmployee(QHash<QString, QVariant> values) = 0;
};

#define IEmployee_iid "IEmployee"
Q_DECLARE_INTERFACE(IEmployee, IEmployee_iid)

#endif // IEMPLOYEE

