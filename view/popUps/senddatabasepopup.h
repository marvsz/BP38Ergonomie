#ifndef SENDDATABASEPOPUP_H
#define SENDDATABASEPOPUP_H

#include "../navigation/abstractpopupwidget.h"
#include "../numberlineedit.h"
#include <QComboBox>
#include <QCheckBox>

class SendDatabasePopUp : public AbstractPopUpWidget
{
    Q_OBJECT
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
    void create();
    void edit(int id);
    void selected(int id);

public slots:
    void add(const QString &name, int id);
    void select(int id);
    void clear();

private slots:
    void cmBxFTPConnectionsIndexChanged(int index);
    void onConfirm();
    void startedUpload();
    void finishedUpload();
    void progressUpload(int progress);
    void errorDurringUpload(const QString &error);

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

#endif // SENDDATABASEPOPUP_H
