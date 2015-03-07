#ifndef ILINE_H
#define ILINE_H

#include <QtPlugin>

class ILine {

signals:
    virtual void saveLine(QHash<QString, QVariant> values) = 0;

public slots:
    virtual void setLine(QHash<QString, QVariant> values) = 0;
};

#define ILine_iid "ILine"
Q_DECLARE_INTERFACE(ILine, ILine_iid)

#endif // ILINE_H
