#ifndef IFACTORY
#define IFACTORY

#include <QtPlugin>

class IFactory {

signals:
    virtual void saveFactory(QHash<QString, QVariant> values) = 0;

public slots:
    virtual void setFactory(QHash<QString, QVariant> values) = 0;
};


#define IFactory_iid "IFactory"
Q_DECLARE_INTERFACE(IFactory, IFactory_iid)

#endif // IFACTORY

