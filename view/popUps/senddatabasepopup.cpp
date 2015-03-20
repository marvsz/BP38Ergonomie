#include "senddatabasepopup.h"
#include "../ftpHandler/ftphandler.h"
#include "standardpaths.h"
#include <QVBoxLayout>


SendDatabasePopUp::SendDatabasePopUp(QWidget *parent) :
  AbstractPopUpWidget(ConfirmMode::SEND, tr("Send Database"), parent),
  ftpConnectionWidget(new FTPConnectionsWidget(this))
{
    connect(ftpConnectionWidget, SIGNAL(selectedConnectionChanged(int)), this, SLOT(selectedConnectionChanged(int)));

    connect(this, SIGNAL(confirm()), this, SLOT(onConfirm()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(ftpConnectionWidget);

    setLayout(mainLayout);
}

SendDatabasePopUp::~SendDatabasePopUp()
{

}

//PUBLIC SLOTS
void SendDatabasePopUp::addFTPConnection(QHash<QString, QVariant> values){
    ftpConnectionWidget->add(values.value(DBConstants::COL_CONNECTION_NAME).toString(), values.value(DBConstants::COL_CONNECTION_ID).toInt());
}

void SendDatabasePopUp::selectedFTPConnection(int id){
    ftpConnectionWidget->select(id);
}

void SendDatabasePopUp::clearFTPConnections(){
    ftpConnectionWidget->clear();
}

void SendDatabasePopUp::onEnter(){
    emit initializeFTPConnections(this);
}

//PRIVATE SLOTS
void SendDatabasePopUp::selectedConnectionChanged(int id){
    emit selectFTPConnection(this, id);
}

void SendDatabasePopUp::onConfirm(){
    if(ftpConnectionWidget->getSaved() && ftpConnectionWidget->getSelectedIndex() == 0)
        emit createFTPConnection(this);
    else if(ftpConnectionWidget->getSaved())
        emit editFTPConnection(this, ftpConnectionWidget->getSelectedID());

    emit sendData(this);

}

//GETTER / SETTER
QHash<QString, QVariant> SendDatabasePopUp::getFTPConnection() const{
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_CONNECTION_NAME, ftpConnectionWidget->getName());
    values.insert(DBConstants::COL_CONNECTION_USERNAME, ftpConnectionWidget->getUserName());
    values.insert(DBConstants::COL_CONNECTION_PASSWORD, ftpConnectionWidget->getPassword());
    values.insert(DBConstants::COL_CONNECTION_PORT, ftpConnectionWidget->getPort());
    values.insert(DBConstants::COL_CONNECTION_SERVER_ADDRESS, ftpConnectionWidget->getAddress());
    values.insert(DBConstants::COL_CONNECTION_DEFAULT, ftpConnectionWidget->getSetAsDefault());
    return values;
}
void SendDatabasePopUp::setFTPConnection(QHash<QString, QVariant> values){
    ftpConnectionWidget->setName(values.value(DBConstants::COL_CONNECTION_NAME).toString());
    ftpConnectionWidget->setUserName(values.value(DBConstants::COL_CONNECTION_USERNAME).toString());
    ftpConnectionWidget->setPassword(values.value(DBConstants::COL_CONNECTION_PASSWORD).toString());
    ftpConnectionWidget->setPort(values.value(DBConstants::COL_CONNECTION_PORT).toInt());
    ftpConnectionWidget->setAddress(values.value(DBConstants::COL_CONNECTION_SERVER_ADDRESS).toString());
    ftpConnectionWidget->setSetAsDefault(values.value(DBConstants::COL_CONNECTION_DEFAULT).toBool());
}
