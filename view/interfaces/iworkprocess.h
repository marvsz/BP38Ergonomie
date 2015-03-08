#ifndef IWORKPROCESS
#define IWORKPROCESS

#include <QtPlugin>

class IWorkProcess{

signals:
    virtual void saveWorkProcess(QHash<QString, QVariant> values) = 0;

public slots:
    virtual void setWorkProcess(QHash<QString, QVariant> values) = 0;

};

#define IWorkProcess_iid "IWorkProcess"
Q_DECLARE_INTERFACE(IWorkProcess, IWorkProcess_iid)

#endif // IWORKPROCESS

