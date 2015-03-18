#ifndef IMPORTDATAPOPUP_H
#define IMPORTDATAPOPUP_H

#include "../view/navigation/abstractpopupwidget.h"
#include "../view/interfaces/iimportdata.h"
#include "../ftpconnectionswidget.h"
#include "../../databaseHandler/dbconstants.h"

class ImportDataPopUp : public AbstractPopUpWidget, public IImportData
{
    Q_OBJECT
    Q_INTERFACES(IImportData)
public:
    explicit ImportDataPopUp(QWidget *parent = 0);
    ~ImportDataPopUp();

    QHash<QString, QVariant> getFTPConnection() const;
    void setFTPConnection(QHash<QString, QVariant> values);

    QString getImportMode() const;
    bool importTransportations() const;
    bool importEquipments() const;
    bool importProducts() const;
    bool importEmployees() const;
    bool importWorkplaces() const;

signals:
    void initializeFTPConnections(IFTPConnections *widget);
    void createFTPConnection(IFTPConnections *widget);
    void editFTPConnection(IFTPConnections *widget, int id);
    void selectFTPConnection(IFTPConnections *widget, int id);
    void importData(IImportData *widget);

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
    QComboBox *cmbxImportMethod;
    QCheckBox *chBxTransportation;
    QCheckBox *chBxEquipment;
    QCheckBox *chBxProduct;
    QCheckBox *chBxEmployee;
    QCheckBox *chBxWorkplace;
};

#endif // IMPORTDATAPOPUP_H
