#ifndef IWORKPLACE
#define IWORKPLACE
#include <QtPlugin>

class IWorkplace {

signals:
    virtual void saveWorkplace(QHash<QString, QVariant> values) = 0;

public slots:
    virtual void setWorkplace(QHash<QString, QVariant> values) = 0;
    virtual void setSavedLine(QHash<QString, QVariant> values) = 0;
    virtual void setSavedComment(QHash<QString, QVariant> values) = 0;
};

#define IWorkplace_iid "IWorkplace"
Q_DECLARE_INTERFACE(IWorkplace, IWorkplace_iid)

#endif // IWORKPLACE

