#ifndef IEXECUTIONCONDITION
#define IEXECUTIONCONDITION

#include <QtPlugin>

class IExecutionCondition{

signals:
    virtual void saveExecutionCondition(QHash<QString, QVariant> values) = 0;

public slots:
    virtual void setExecutionCondition(QHash<QString, QVariant> values) = 0;

};

#define IExecutionCondition_iid "IExecutionCondition"
Q_DECLARE_INTERFACE(IExecutionCondition, IExecutionCondition_iid)

#endif // IEXECUTIONCONDITION

