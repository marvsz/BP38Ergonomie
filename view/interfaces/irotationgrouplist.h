#ifndef IROTATIONGROUPLIST_H
#define IROTATIONGROUPLIST_H

#include <QtPlugin>

class IRotationGroupList
{
public slots:
    virtual void addRotationGroup(QHash<QString, QVariant> values) = 0;
    virtual void updateRotationGroup(QHash<QString, QVariant> values) = 0;
    virtual void removeRotationGroup(int id) = 0;
    virtual void clearRotationGroups() = 0;

signals:
    virtual void createRotationGroup(QHash<QString, QVariant> values) = 0;
    virtual void deleteRotationGroup(int id) = 0;
    virtual void selectRotationGroup(int id) = 0;
};

#define IRotationGroupList_iid "IRotationGroupList"

Q_DECLARE_INTERFACE(IRotationGroupList, IRotationGroupList_iid)

#endif // IROTATIONGROUPLIST_H
