#ifndef ISHIFT_H
#define ISHIFT_H

#include <QtPlugin>

class IShift {

signals:
    virtual void saveShift(QHash<QString, QVariant> values) = 0;

public slots:
    virtual void setShift(QHash<QString, QVariant> values) = 0;
};

#define IShift_iid "IShift"
Q_DECLARE_INTERFACE(IShift, IShift_iid)
#endif // ISHIFT_H
