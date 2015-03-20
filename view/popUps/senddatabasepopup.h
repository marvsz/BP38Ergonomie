#ifndef SENDDATABASEPOPUP_H
#define SENDDATABASEPOPUP_H

#include "../view/navigation/abstractpopupwidget.h"
#include "../ftpconnectionswidget.h"
#include "../interfaces/isenddata.h"
#include "../../databaseHandler/dbconstants.h"

class SendDatabasePopUp : public AbstractPopUpWidget, public ISendData
{
    Q_OBJECT
    Q_INTERFACES(ISendData)

public:
    explicit SendDatabasePopUp(QWidget *parent = 0);
    ~SendDatabasePopUp();

    QHash<QString, QVariant> getFTPConnection() const;
    void setFTPConnection(QHash<QString, QVariant> values);

signals:
    void initializeFTPConnections(IFTPConnections *widget);
    void createFTPConnection(IFTPConnections *widget);
    void editFTPConnection(IFTPConnections *widget, int id);
    void selectFTPConnection(IFTPConnections *widget, int id);
    void sendData(ISendData *widget);

public slots:
    void addFTPConnection(QHash<QString, QVariant> values);
    void selectedFTPConnection(int id);
    void clearFTPConnections();

    void onEnter();

private slots:
    void selectedConnectionChanged(int id);
    void onConfirm();

private:
    FTPConnectionsWidget *ftpConnectionWidget;

};

#endif // SENDDATABASEPOPUP_H
