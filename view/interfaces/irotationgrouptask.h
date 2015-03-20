#ifndef IROTATIONGROUPTASK_H
#define IROTATIONGROUPTASK_H

#include <QtPlugin>

class IRotationGroupTask {

public slots:
    virtual void setRotationGroupTask(QHash<QString, QVariant> values) = 0;

signals:
    virtual void saveRotationGroupTask(QHash<QString, QVariant> values) = 0;
};

#define IRotationGroupTask_iid "IRotationGroupTask"

Q_DECLARE_INTERFACE(IRotationGroupTask, IRotationGroupTask_iid)

#endif // IROTATIONGROUPTASK_H
