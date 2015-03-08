#ifndef IAPPLIEDFORCE
#define IAPPLIEDFORCE

#include <QtPlugin>

class IAppliedForce{

signals:
    virtual void saveAppliedForce(QHash<QString, QVariant> values) = 0;

public slots:
    virtual void setAppliedForce(QHash<QString, QVariant> values) = 0;

};

#define IAppliedForce_iid "IAppliedForce"
Q_DECLARE_INTERFACE(IAppliedForce, IAppliedForce_iid)

#endif // IAPPLIEDFORCE

