#ifndef IBODYPOSTUREVIEW
#define IBODYPOSTUREVIEW

#include <QTPlugin>

class IBodyPostureView{

public slots:
    virtual void setBodyPosture(QHash<QString, QVariant> values) = 0;

signals:
    virtual void saveBodyPostureView(QHash<QString, QVariant> values) = 0;
};

#define IBodyPostureView_iid "IBodyPostureView"
Q_DECLARE_INTERFACE(IBodyPostureView, IBodyPostureView_iid)

#endif // IBODYPOSTUREVIEW

