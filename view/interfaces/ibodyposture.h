#ifndef IBODYPOSTURE
#define IBODYPOSTURE

#include <QtPlugin>

class IBodyPosture{

public slots:
    virtual void setBodyPosture(QHash<QString, QVariant> values) = 0;

signals:
    virtual void saveBodyPosture(QHash<QString, QVariant> values) = 0;
};

#define IBodyPosture_iid "IBodyPosture"
Q_DECLARE_INTERFACE(IBodyPosture, IBodyPosture_iid)

#endif // IBODYPOSTURE

