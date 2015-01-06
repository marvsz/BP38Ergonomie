#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "databaseHandler/dbhandler.h"
#include "view/viewcontroller.h"
#include <QSqlField>
#include <QHash>

class Controller : QObject
{
Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

signals:

public slots:

private slots:
    void updateMetaDataView();
    void saveMetaDataView();

    void updateWorkplacesView();

    void updateWorkplaceView(int id);
    void saveWorkplaceView();

    void updateLine(int id);
    int saveLine();


private:
    DBHandler *dbHandler;
    ViewController *viewCon;
    int recording_ID;

    int save(DB_TABLES tbl, const QString &filter, const QString &colID, const QStringList &colNames, const QList<QVariant::Type> &colTypes, QHash<QString, QVariant> &colMapNameValue);

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

    void updateWorkplace(int id);
    int saveWorkingplace();

    void saveRecordingObservesLine(int recID, int lineID);
    void saveRecordingObservesWorkplace(int recID, int workplaceID);


};

#endif // CONTROLLER_H
