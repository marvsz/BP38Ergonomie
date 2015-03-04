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
void SendDatabasePopUp::add(const QString &name, int id){
    ftpConnectionWidget->add(name, id);
}

void SendDatabasePopUp::select(int id){
    ftpConnectionWidget->select(id);
}

void SendDatabasePopUp::clear(){
    ftpConnectionWidget->clear();
}

void SendDatabasePopUp::onConfirm(){
    if(ftpConnectionWidget->getSaved() && ftpConnectionWidget->getSelectedIndex() == 0)
        emit create(this);
    else if(ftpConnectionWidget->getSaved())
        emit edit(this, ftpConnectionWidget->getSelectedID());

    FtpHandler *ftpHandler = new FtpHandler();
    connect(ftpHandler, SIGNAL(started()), this, SLOT(startedUpload()));
    connect(ftpHandler, SIGNAL(finished(QString)), this, SLOT(finishedUpload(QString)));
    connect(ftpHandler, SIGNAL(error(QString)), this, SLOT(errorDurringUpload(QString)));
    ftpHandler->setUser(ftpConnectionWidget->getUserName(), ftpConnectionWidget->getPassword());
    ftpHandler->setPort(ftpConnectionWidget->getPort());
    ftpHandler->setServer(ftpConnectionWidget->getAddress());
    ftpHandler->uploadFile(StandardPaths::databasePath());
}


//PRIVATE SLOTS
void SendDatabasePopUp::selectedConnectionChanged(int id){
    emit selected(this, id);
}

void SendDatabasePopUp::startedUpload(){
    emit showMessage(tr("Started Upload"), NotificationMessage::INFORMATION, NotificationMessage::MIDDLE);
}

void SendDatabasePopUp::finishedUpload(const QString filename){
    emit showMessage(QString(tr("Finished Upload: ")).append(filename), NotificationMessage::INFORMATION, NotificationMessage::MIDDLE);
    emit closePopUp();
}

void SendDatabasePopUp::errorDurringUpload(const QString &error){
    emit showMessage(error, NotificationMessage::ERROR, NotificationMessage::PERSISTENT);
}

//GETTER / SETTER
QString SendDatabasePopUp::getName() const{
    return ftpConnectionWidget->getName();
}
void SendDatabasePopUp::setName(const QString &name){
    ftpConnectionWidget->setName(name);
}

QString SendDatabasePopUp::getUserName() const{
    return ftpConnectionWidget->getUserName();
}
void SendDatabasePopUp::setUserName(const QString &username){
    ftpConnectionWidget->setUserName(username);
}

QString SendDatabasePopUp::getPassword() const{
    return ftpConnectionWidget->getPassword();
}
void SendDatabasePopUp::setPassword(const QString &password){
    ftpConnectionWidget->setPassword(password);
}

QString SendDatabasePopUp::getAddress() const{
    return ftpConnectionWidget->getAddress();
}
void SendDatabasePopUp::setAddress(const QString &address){
    ftpConnectionWidget->setAddress(address);
}

int SendDatabasePopUp::getPort() const{
    return ftpConnectionWidget->getPort();
}
void SendDatabasePopUp::setPort(int port){
    ftpConnectionWidget->setPort(port);
}

bool SendDatabasePopUp::getSetAsDefault() const{
    return ftpConnectionWidget->getSetAsDefault();
}
void SendDatabasePopUp::setSetAsDefault(bool setAsDefault){
    ftpConnectionWidget->setSetAsDefault(setAsDefault);
}
