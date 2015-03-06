#ifndef IWORKPLACELIST_H
#define IWORKPLACELIST_H

#include <QtPlugin>

class IWorkplaceList{

public slots:
    virtual void addWorkplace(QHash<QString, QVariant> values) = 0;
    virtual void updateWorkplace(QHash<QString, QVariant> values) = 0;
    virtual void removeWorkplace(int id) = 0;
    virtual void clearWorkplaces() = 0;

signals:
    virtual void createWorkplace(QHash<QString, QVariant> values) = 0;
    virtual void deleteWorkplace(int id) = 0;
    virtual void selectWorkplace(int id) = 0;

};

#define IWorkplaceList_iid "IWorkplaceList"

Q_DECLARE_INTERFACE(IWorkplaceList, IWorkplaceList_iid)

#endif // IWORKPLACELIST_H
