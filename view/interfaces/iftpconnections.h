#ifndef IFTPCONNECTIONS_H
#define IFTPCONNECTIONS_H

#include <QtPlugin>

class IFTPConnections{

public:
    virtual QHash<QString, QVariant> getFTPConnection() const = 0;
    virtual void setFTPConnection(QHash<QString, QVariant> values) = 0;

signals:
    virtual void initializeFTPConnections(IFTPConnections *widget) = 0;
    virtual void createFTPConnection(IFTPConnections *widget) = 0;
    virtual void editFTPConnection(IFTPConnections *widget, int id) = 0;
    virtual void selectFTPConnection(IFTPConnections *widget, int id) = 0;

public slots:
    virtual void addFTPConnection(QHash<QString, QVariant> values) = 0;
    virtual void selectedFTPConnection(int id) = 0;
    virtual void clearFTPConnections() = 0;
};

#define IFTPConnections_iid "IFTPConnections"

Q_DECLARE_INTERFACE(IFTPConnections, IFTPConnections_iid)

#endif // IFTPCONNECTIONS_H
