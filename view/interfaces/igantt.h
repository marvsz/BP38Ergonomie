#ifndef IGANTT
#define IGANTT

#include <QtPlugin>
#include "../../enum.h"

class IGantt{

signals:
    virtual void saveWorkProcessFrequence(int frequence) = 0;
    virtual void selectWorkProcess(int id, AVType type) = 0;

public slots:
    virtual void initiliazeWorkProcesses(QList<QHash<QString, QVariant>> values) = 0;
    virtual void setSelectedWorkProcess(QHash<QString, QVariant> values) = 0;
    virtual void addWorkProcess(QHash<QString, QVariant> values) = 0;
    virtual void resetWorkProcesses() = 0;
};

#define IGantt_iid "IGantt"
Q_DECLARE_INTERFACE(IGantt, IGantt_iid)

#endif // IGANTT

