#ifndef ICALENDARLIST_H
#define ICALENDARLIST_H

#include <QtPlugin>

class IRotationGroup {

public slots:
    virtual void addRotationGroup(QHash<QString, QVariant> values) = 0;
    virtual void updateRotationGroup(QHash<QString, QVariant> values) = 0;
    virtual void removeRotationGroup(int id) = 0;
    virtual void addBreak(QHash<QString, QVariant> values) = 0;
    virtual void updateBreak(QHash<QString, QVariant> values) = 0;
    virtual void removeBreak(int id) = 0;
    virtual void moveEntryUp(int id) = 0;
    virtual void moveEntryDown(int id) = 0;
    virtual void clearCalendar() = 0;

signals:
    virtual void createRotationGroup(QHash<QString, QVariant> values) = 0;
    virtual void deleteRotationGroup(int id) = 0;
    virtual void createBreak(QHash<QString, QVariant> values) = 0;
    virtual void deleteBreak(int id) = 0;
    virtual void requestMoveEntryUp(int id) = 0;
    virtual void requestMoveEntryDown(int id) = 0;
};

#define IRotationGroup_iid "IRotationGroup"

Q_DECLARE_INTERFACE(IRotationGroup, IRotationGroup_iid)
#endif // ICALENDARLIST_H
