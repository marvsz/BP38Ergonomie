#ifndef IFTPCONNECTIONS_H
#define IFTPCONNECTIONS_H

#include <QtPlugin>

class IFTPConnections
{

public:
    virtual QString getName() const = 0;
    virtual void setName(const QString &name) = 0;
    virtual QString getUserName() const = 0;
    virtual void setUserName(const QString &username) = 0;
    virtual QString getPassword() const = 0;
    virtual void setPassword(const QString &password) = 0;
    virtual QString getAddress() const = 0;
    virtual void setAddress(const QString &address) = 0;
    virtual int getPort() const = 0;
    virtual void setPort(int port) = 0;
    virtual bool getSetAsDefault() const = 0;
    virtual void setSetAsDefault(bool setAsDefault) = 0;

signals:
  virtual void create(IFTPConnections *widget) = 0;
  virtual void edit(IFTPConnections *widget, int id) = 0;
  virtual void selected(IFTPConnections *widget, int id) = 0;

public slots:
  virtual void add(const QString &name, int id) = 0;
  virtual void select(int id) = 0;
  virtual void clear() = 0;
};

#define IFTPConnections_iid "IFTPConnections"

Q_DECLARE_INTERFACE(IFTPConnections, IFTPConnections_iid)

#endif // IFTPCONNECTIONS_H
