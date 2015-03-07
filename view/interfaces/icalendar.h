#ifndef ICALENDAR_H
#define ICALENDAR_H

#include <QtPlugin>

class ICalendar {

public slots:
    virtual void setTimes(QHash<QString, QVariant> values) = 0;
};

#define ICalendar_iid "ICalendar"
Q_DECLARE_INTERFACE(ICalendar, ICalendar_iid)

#endif // ICALENDAR_H
