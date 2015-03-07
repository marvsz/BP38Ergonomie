#ifndef ICALENDARLIST_H
#define ICALENDARLIST_H
#include "irotationgrouplist.h"
#include "IWorkplaceList.h"
#include <QtPlugin>

class ICalendarList : public IRotationGroupList {

public slots:
    virtual void addCalendarRotationGroup(QHash<QString, QVariant> values) = 0;
    virtual void updateCalendarRotationGroup(QHash<QString, QVariant> values) = 0;
    virtual void removeCalendarRotationGroup(int id) = 0;
    virtual void addCalendarBreak(QHash<QString, QVariant> values) = 0;
    virtual void updateCalendarBreak(QHash<QString, QVariant> values) = 0;
    virtual void removeCalendarBreak(int id) = 0;
    virtual void clearCalendar() = 0;

signals:
    virtual void createCalendarRotationGroup(QHash<QString, QVariant> values) = 0;
    virtual void deleteCalendarRotationGroup(int id) = 0;
    virtual void selectCalendarRotationGroup(int id) = 0;
    virtual void createCalendarBreak(QHash<QString, QVariant> values) = 0;
    virtual void deleteCalendarBreak(int id) = 0;
    virtual void selectCalendarBreak(int id) = 0;
};

#define ICalendarList_iid "ICalendarList"

Q_DECLARE_INTERFACE(ICalendarList, ICalendarList_iid)
#endif // ICALENDARLIST_H
