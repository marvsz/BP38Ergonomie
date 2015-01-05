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
    int recording_ID;

    void updateAnalyst(int id);
    int saveAnalyst();

    void updateEmployer(int id);
    int saveEmployer();

    void updateCorporation(int id);
    int saveCorporation();

    void updateFactory(int id);
    int saveFactory();

    void updateRecording(int id);
    int saveRecording();


};

#endif // CONTROLLER_H
