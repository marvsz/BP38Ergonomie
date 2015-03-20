#ifndef IROTATIONGROUPTASKENTRYLIST_H
#define IROTATIONGROUPTASKENTRYLIST_H

#include <QtPlugin>

class IRotationGroupTaskEntryList{

public slots:
    virtual void addRotationGroupTaskEntry(QHash<QString, QVariant> values) = 0;
    virtual void removeRotationGroupTaskEntry(int id) = 0;
    virtual void clearRotationGroupTaskEntries() = 0;

signals:
    virtual void createRotationGroupTaskEntry(QHash<QString, QVariant> values) = 0;
    virtual void deleteRotationGroupTaskEntry(int id) = 0;
};

#define IRotationGroupTaskEntryList_iid "IRotationGroupTaskEntryList"

Q_DECLARE_INTERFACE(IRotationGroupTaskEntryList, IRotationGroupTaskEntryList_iid)
#endif // IROTATIONGROUPTASKENTRYLIST_H
