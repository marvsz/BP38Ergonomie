#ifndef ICALENDARLIST_H
#define ICALENDARLIST_H

#include <QtPlugin>

class IRotationGroup {

public slots:
    virtual void addRotationGroupEntry(QHash<QString, QVariant> values) = 0;
    virtual void updateRotationGroupEntry(QHash<QString, QVariant> values) = 0;
    //virtual void removeRotationGroupEntry(int id) = 0;
    virtual void addBreakEntry(QHash<QString, QVariant> values) = 0;
    //virtual void removeBreakEntry(int id) = 0;

    virtual void removeEntry(int id) = 0;
    virtual void moveEntryUp(int id) = 0;
    virtual void moveEntryDown(int id) = 0;
    virtual void clearCalendar() = 0;

signals:
    virtual void createRotationGroupTask(QHash<QString, QVariant> values) = 0;
    virtual void deleteRotationGroupTask(int id) = 0;
    virtual void createBreak(QHash<QString, QVariant> values) = 0;
    virtual void deleteBreak(int id) = 0;

    virtual void requestRemoveEntry(int id) = 0;
    virtual void requestMoveEntryUp(int id) = 0;
    virtual void requestMoveEntryDown(int id) = 0;
};

#define IRotationGroup_iid "IRotationGroup"

Q_DECLARE_INTERFACE(IRotationGroup, IRotationGroup_iid)
#endif // ICALENDARLIST_H
