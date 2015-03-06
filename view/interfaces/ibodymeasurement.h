#ifndef IBODYMEASUREMENT
#define IBODYMEASUREMENT

#include <QtPlugin>

class IBodyMeasurement {
signals:
    virtual void saveBodyMeasurement(QHash<QString, QVariant> values) = 0;

public slots:
    virtual void setBodyMeasurement(QHash<QString, QVariant> values) = 0;
};

#define IBodyMeasurement_iid "IBodyMeasurement"
Q_DECLARE_INTERFACE(IBodyMeasurement, IBodyMeasurement_iid)

#endif // IBODYMEASUREMENT

