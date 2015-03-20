#ifndef IRECORDING
#define IRECORDING

#include <QtPlugin>

class IRecording {

signals:
    virtual void saveRecording(QHash<QString, QVariant> values) = 0;

public slots:
    virtual void setRecording(QHash<QString, QVariant> values) = 0;
};


#define IRecording_iid "IRecording"
Q_DECLARE_INTERFACE(IRecording, IRecording_iid)

#endif // IRECORDING

