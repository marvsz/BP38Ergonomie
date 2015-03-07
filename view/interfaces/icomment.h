#ifndef ICOMMENT
#define ICOMMENT

#include <QtPlugin>

class IComment {
signals:
    virtual void saveComment(QHash<QString, QVariant> values) = 0;

public slots:
    virtual void setComment(QHash<QString, QVariant> values) = 0;
};

#define IComment_iid "IComment"
Q_DECLARE_INTERFACE(IComment, IComment_iid)

#endif // ICOMMENT

