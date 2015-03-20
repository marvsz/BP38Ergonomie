#ifndef IROTATIONGROUPTASKLIST_H
#define IROTATIONGROUPTASKLIST_H

#include <QtPlugin>

class IRotationGroupTaskList
{
public slots:
    virtual void addRotationGroupTask(QHash<QString, QVariant> values) = 0;
    virtual void updateRotationGroupTask(QHash<QString, QVariant> values) = 0;
    virtual void removeRotationGroupTask(int id) = 0;
    virtual void clearRotationGroupTasks() = 0;

signals:
    virtual void createRotationGroupTask(QHash<QString, QVariant> values) = 0;
    virtual void deleteRotationGroupTask(int id) = 0;
    virtual void selectRotationGroupTask(int id) = 0;
};

#define IRotationGroupTaskList_iid "IRotationGroupTaskList"

Q_DECLARE_INTERFACE(IRotationGroupTaskList, IRotationGroupTaskList_iid)

#endif // IROTATIONGROUPTASKLIST_H
