#ifndef IACTIVITYLIST_H
#define IACTIVITYLIST_H

#include <QtPlugin>

class IActivityList{

signals:
    virtual void createActivity(QHash<QString, QVariant> values) = 0;
    virtual void deleteActivity(int id) = 0;
    virtual void editActivity(int id) = 0;
    virtual void selectActivity(int id) = 0;

public slots:
    virtual void addActivity(QHash<QString, QVariant> values) = 0;
    virtual void updateActivity(QHash<QString, QVariant> values) = 0;
    virtual void removeActivity(int id) = 0;
    virtual void clearActivities() = 0;
};

#define IActivityList_iid "IActivityList"

Q_DECLARE_INTERFACE(IActivityList, IActivityList_iid)

#endif // IACTIVITYLIST_H
