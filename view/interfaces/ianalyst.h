#ifndef IANALYST
#define IANALYST

#include <QtPlugin>

class IAnalyst {

public slots:
    virtual void setAnalyst(QHash<QString, QVariant> values) = 0;

signals:
    virtual void saveAnalyst(QHash<QString, QVariant> values) = 0;
};

#define IAnalyst_iid "IAnalyst"
Q_DECLARE_INTERFACE(IAnalyst, IAnalyst_iid)

#endif // IANALYST

