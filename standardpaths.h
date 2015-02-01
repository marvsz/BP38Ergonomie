#ifndef STANDARDPATHS_H
#define STANDARDPATHS_H

#include <QObject>

class StandardPaths : public QObject
{
    Q_OBJECT
public:
    explicit StandardPaths(QObject *parent = 0);
    ~StandardPaths();

    static const QString WRITEABLE_LOCATION;

    static const QString ORIGIN_DATABASE_PATH;
    static const QString DATABASE_PATH;

    static const QString SCREENSHOT_PATH;
    static const QString LOGGING_PATH;

};

#endif // STANDARDPATHS_H

