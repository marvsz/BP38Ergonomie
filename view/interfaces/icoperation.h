#ifndef ICOPERATION
#define ICOPERATION

#include <QtPlugin>

class ICorperation {

signals:
    virtual void saveCorperation(QHash<QString, QVariant> values) = 0;

public slots:
    virtual void setCorperation(QHash<QString, QVariant> values) = 0;
};


#define ICorperation_iid "ICorperation"
Q_DECLARE_INTERFACE(ICorperation, ICorperation_iid)

#endif // ICOPERATION

