#ifndef IACTIVITY_H
#define IACTIVITY_H

#include <QtPlugin>

class IActivity {

signals:
    virtual void saveActivity(QHash<QString, QVariant> values) = 0;

public slots:
    virtual void setActivity(QHash<QString, QVariant> values) = 0;
};

#define IActivity_iid "IActivity"
Q_DECLARE_INTERFACE(IActivity, IActivity_iid)

#endif // IACTIVITY_H
