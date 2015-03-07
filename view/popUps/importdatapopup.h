#ifndef IMPORTDATAPOPUP_H
#define IMPORTDATAPOPUP_H

#include "../view/navigation/abstractpopupwidget.h"
#include "../view/interfaces/iftpconnections.h"
#include "ftpconnectionswidget.h"

class ImportDataPopUp : public AbstractPopUpWidget, public IFTPConnections
{
    Q_OBJECT
    Q_INTERFACES(IFTPConnections)
public:
    explicit ImportDataPopUp(QWidget *parent = 0);
    ~ImportDataPopUp();

    QString getImportMode() const;
    bool importTransportations() const;
    bool importEquipments() const;
    bool importProducts() const;
    bool importEmployees() const;
    bool importWorkplaces() const;

    //Inherited from IFTPConnections
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

private:
    int countFinDownload;
    FTPConnectionsWidget *ftpConnectionWidget;
    QComboBox *cmbxImportMethod;
    QCheckBox *chBxTransportation;
    QCheckBox *chBxEquipment;
    QCheckBox *chBxProduct;
    QCheckBox *chBxEmployee;
    QCheckBox *chBxWorkplace;
};

#endif // IMPORTDATAPOPUP_H
