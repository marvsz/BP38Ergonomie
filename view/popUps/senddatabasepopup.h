#ifndef SENDDATABASEPOPUP_H
#define SENDDATABASEPOPUP_H

<<<<<<< HEAD
#include "../view/navigation/abstractpopupwidget.h"
#include "iftpconnections.h"
#include "ftpconnectionswidget.h"
=======
#include "../navigation/abstractpopupwidget.h"
#include "../numberlineedit.h"
#include <QComboBox>
#include <QCheckBox>
>>>>>>> origin/Unstable

class SendDatabasePopUp : public AbstractPopUpWidget, public IFTPConnections
{
    Q_OBJECT
    Q_INTERFACES(IFTPConnections)

public:
    explicit SendDatabasePopUp(QWidget *parent = 0);
    ~SendDatabasePopUp();

    QString getName() const;
    void setName(const QString &name);
    QString getUserName() const;
    void setUserName(const QString &username);
    QString getPassword() const;
    void setPassword(const QString &password);
    QString getAddress() const;
    void setAddress(const QString &address);
    int getPort() const;
    void setPort(int port);
    bool getSetAsDefault() const;
    void setSetAsDefault(bool setAsDefault);

signals:
    void create(IFTPConnections *widget);
    void edit(IFTPConnections *widget, int id);
    void selected(IFTPConnections *widget, int id);

public slots:
    void add(const QString &name, int id);
    void select(int id);
    void clear();
    void onConfirm();

private slots:
    void selectedConnectionChanged(int id);

    void startedUpload();
    void finishedUpload(const QString filename);
    void errorDurringUpload(const QString &error);

private:
    FTPConnectionsWidget *ftpConnectionWidget;

};

#endif // SENDDATABASEPOPUP_H
