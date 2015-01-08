#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#if defined(Q_OS_IOS)
    #include "dbhandler.h"
    #include "viewcontroller.h"
#else
    #include "databaseHandler/dbhandler.h"
    #include "view/viewcontroller.h"
#endif
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
    void updateWorkplaceView();
    int createWorkplace();
    void saveWorkplaceView();
    void deleteWorkplace(int id);

    void updateLineView();
    int saveSelectedLine(int id);
    int saveLine();
    void deleteLine(int id);

    void updateProductView();
    int saveSelectedProducts();
    int saveProduct();
    void deleteProduct(int id);

    void updateComment();
    int saveComment();


private:
    DBHandler *dbHandler;
    ViewController *viewCon;

    int recording_ID;
    int factory_ID;
    int selectedWorkplaceID;

    int save(DB_TABLES tbl, const QString &filter, const QString &colID, const QStringList &colNames, const QList<QVariant::Type> &colTypes, QHash<QString, QVariant> &colMapNameValue);

    int save(DB_TABLES tbl, const QString &filter, const QString &colID, const QHash<QString, QVariant::Type> &colMapNameType, QHash<QString, QVariant> &colMapNameValue);

    void updateAnalyst(int id);
    int saveAnalyst();

    int saveEmployer();
    void updateEmployer(int id);


    void updateCorporation(int id);
    int saveCorporation();

    void updateFactory(int id);
    int saveFactory();

    void updateRecording(int id);
    int saveRecording();

    int saveWorkplace(int id);


    void saveRecordingObservesLine(int recID, int lineID);
    void deleteRecordingObservesLine(int lineID);

    void saveRecordingObservesWorkplace(int recID, int workplaceID);
    void deleteRecordingOberservesWorkplace(int wpID);


};

#endif // CONTROLLER_H
