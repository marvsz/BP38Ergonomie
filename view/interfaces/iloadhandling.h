#ifndef ILOADHANDLING
#define ILOADHANDLING

#include <QtPlugin>

class ILoadHandling{

signals:
    virtual void saveLoadHandling(QHash<QString, QVariant> values) = 0;

public slots:
    virtual void setLoadHandling(QHash<QString, QVariant> values) = 0;

};

#define ILoadHandling_iid "ILoadHandling"
Q_DECLARE_INTERFACE(ILoadHandling, ILoadHandling_iid)

#endif // ILOADHANDLING

