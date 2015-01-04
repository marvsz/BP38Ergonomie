#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <databaseHandler/dbhandler.h>
#include <view/viewcontroller.h>
#include <QSqlField>

class Controller : QObject
{
Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

signals:

public slots:

private slots:
    void updateMetaData();
    void saveMetaData();

private:
    DBHandler *dbHandler;
    ViewController *viewCon;
    int analyst_ID;

    int getAnalystID();

};

#endif // CONTROLLER_H
