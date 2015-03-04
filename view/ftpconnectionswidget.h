#ifndef FTPCONNECTIONSWIDGET_H
#define FTPCONNECTIONSWIDGET_H

#include "numberlineedit.h"
#include <QComboBox>
#include <QCheckBox>

class FTPConnectionsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FTPConnectionsWidget(QWidget *parent = 0);
    ~FTPConnectionsWidget();

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

    bool getSaved() const;
    int getSelectedIndex() const;
    int getSelectedID() const;

signals:
    void selectedConnectionChanged(int id);

public slots:
    void add(const QString &name, int id);
    void select(int id);
    void clear();

private slots:
    void cmBxFTPConnectionsIndexChanged(int index);

private:
    QComboBox *cmBxFTPConnections;
    TextLineEdit *txtBxName;
    TextLineEdit *txtBxUserName;
    TextLineEdit *txtBxPassword;
    TextLineEdit *txtBxAddress;
    NumberLineEdit *numBxPort;
    QCheckBox *chBxSave;
    QCheckBox *chBxSetDefault;
};

#endif // FTPCONNECTIONSWIDGET_H
