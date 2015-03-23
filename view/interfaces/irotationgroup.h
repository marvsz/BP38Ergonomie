#ifndef IROTATIONGROUP_H
#define IROTATIONGROUP_H

#include <QtPlugin>

class IRotationGroup {

public slots:
    virtual void addRotationGroupEntry(QHash<QString, QVariant> values) = 0;
    virtual void updateRotationGroupEntry(QHash<QString, QVariant> values) = 0;
    virtual void addRotationGroupBreakEntry(QHash<QString, QVariant> values) = 0;

    virtual void clearRotationGroup() = 0;

signals:
    virtual void createRotationGroupEntry(QHash<QString, QVariant> values) = 0;
    virtual void createRotationGroupBreakEntry(QHash<QString, QVariant> values) = 0;

    virtual void requestRemoveEntry(int order) = 0;
    virtual void requestMoveEntryUp(int order) = 0;
    virtual void requestMoveEntryDown(int order) = 0;
};

#define IRotationGroup_iid "IRotationGroup"

Q_DECLARE_INTERFACE(IRotationGroup, IRotationGroup_iid)
#endif // IROTATIONGROUP_H
