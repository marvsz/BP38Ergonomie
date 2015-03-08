#ifndef IWORKPROCESSCONTROLLER
#define IWORKPROCESSCONTROLLER

#include <QtPlugin>
#include "../../enum.h"

class IWorkProcessController {

signals:
    virtual void selectNextWorkProcess() = 0;
    virtual void selectPreviousWorkProcess() = 0;
    virtual void workProcessTypeChanged(AVType type) = 0;
    virtual void workProcessDurationChanged(QTime duration) = 0;
    virtual void createWorkProcess(QHash<QString, QVariant> values) = 0;
    virtual void resetWorkProcesses() = 0;

public slots:
    virtual void setSelectedWorkProcess(QHash<QString, QVariant> values) = 0;
    virtual void setHasPreviousWorkProcess(bool hasPrevious) = 0;
    virtual void setHasNextWorkProcess(bool hasNext) = 0;
    virtual void setSelectedWorkProcessType(AVType type) = 0;
    virtual void initiliazedWorkProcesses(QList<QHash<QString, QVariant>> values) = 0;

};

#define IWorkProcessController_iid "IWorkProcessController"
Q_DECLARE_INTERFACE(IWorkProcessController, IWorkProcessController_iid)

#endif // IWORKPROCESSCONTROLLER

