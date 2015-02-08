#ifndef STANDARDPATHS_H
#define STANDARDPATHS_H

#include <QObject>
#include <QStandardPaths>

class StandardPaths : public QObject
{
    Q_OBJECT
public:
    explicit StandardPaths(QObject *parent = 0) : QObject(parent){

    }

    ~StandardPaths(){

    }

    static QString writeableLocation(){
        #if defined(Q_OS_ANDROID)
            return QString("%1").arg(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
        #elif defined(Q_OS_IOS)
            return QString("%1").arg(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
        #else
            return QString("%1").arg(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
        #endif
    }

    static QString originDatabasePath(){
        #if defined(Q_OS_IOS)
            return QString("%1/%2/%3").arg(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)).arg("Documents").arg("ergoAppDB.sqlite");
        #else
            return QString(":/assets/ergoAppDB.sqlite");
        #endif
    }

    static QString databasePath(){
        return QString("%1/%2").arg(StandardPaths::writeableLocation()).arg("ergoAppDB.sqlite");
    }

    static QString screenshotPath(){
        return QString("%1/%2/%3").arg(StandardPaths::writeableLocation()).arg("screenshots").arg("screenshot.png");
    }

};

#endif // STANDARDPATHS_H

