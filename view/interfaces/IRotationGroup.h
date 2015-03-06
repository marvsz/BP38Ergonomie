#ifndef IROTATIONGROUP_H
#define IROTATIONGROUP_H

#include <QtPlugin>

class IRotationGroup {

public slots:
    virtual void setRotationGroup(QHash<QString, QVariant> values) = 0;

signals:
    virtual void saveRotationGroup(QHash<QString, QVariant> values) = 0;
};

#define IRotationGroup_iid "IRotationGroup"

Q_DECLARE_INTERFACE(IRotationGroup, IRotationGroup_iid)

#endif // IROTATIONGROUP_H
