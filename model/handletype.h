#ifndef HANDLETYPE_H
#define HANDLETYPE_H

#include "QString"

class HandleType
{
public:
    HandleType(QString* handleType);
    ~HandleType();

    void setHandleType(QString* h);
    QString getHandleType();

private:
    QString* handleType;
};

#endif // HANDLETYPE_H
