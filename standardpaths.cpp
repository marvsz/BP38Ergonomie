#include "standardpaths.h"
#include <QStandardPaths>



#if defined(Q_OS_ANDROID)
    const QString StandardPaths::ORIGIN_DATABASE_PATH = QString(":/assets/ergoAppDB.sqlite");
    const QString StandardPaths::WRITEABLE_LOCATION = QString("%1/").arg(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
#elif defined(Q_OS_IOS)
    const QString StandardPaths::ORIGIN_DATABASE_PATH = QString("%1/%2/%3").arg(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)).arg("Documents").arg("ergoAppDB.sqlite");
    const QString StandardPaths::WRITEABLE_LOCATION = QString("%1/").arg(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
#else
    const QString StandardPaths::ORIGIN_DATABASE_PATH = QString(":/assets/ergoAppDB.sqlite");
    const QString StandardPaths::WRITEABLE_LOCATION = QString("%1/").arg(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
#endif

const QString StandardPaths::DATABASE_PATH = QString("%1%2").arg(StandardPaths::WRITEABLE_LOCATION).arg("ergoAppDB.sqlite");

const QString StandardPaths::SCREENSHOT_PATH = QString("%1%2/").arg(StandardPaths::WRITEABLE_LOCATION).arg("screenshots");
const QString StandardPaths::LOGGING_PATH = QString("%1%2/").arg(StandardPaths::WRITEABLE_LOCATION).arg("log");




StandardPaths::StandardPaths(QObject *parent) : QObject(parent)
{

}

StandardPaths::~StandardPaths()
{

}

