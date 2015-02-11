#include "senddatabasepopup.h"
#include "ftpHandler/ftphandler.h"
#include "standardpaths.h"
#include <QGridLayout>

SendDatabasePopUp::SendDatabasePopUp(QWidget *parent) : AbstractPopUpWidget(ConfirmMode::SEND, tr("Send database"), parent),
    cmBxFTPConnections(new QComboBox()),
    txtBxName( new TextLineEdit()),
    txtBxUserName(new TextLineEdit()),
    txtBxPassword(new TextLineEdit()),
    txtBxAddress( new TextLineEdit()),
    numBxPort(new NumberLineEdit()),
    chBxSave(new QCheckBox()),
    chBxSetDefault(new QCheckBox())
{
    connect(cmBxFTPConnections, SIGNAL(currentIndexChanged(int)), this, SLOT(cmBxFTPConnectionsIndexChanged(int)));

    txtBxPassword->setEchoMode(QLineEdit::Password);
    txtBxPassword->setInputMethodHints(Qt::ImhHiddenText | Qt::ImhNoAutoUppercase | Qt::ImhNoPredictiveText);

    txtBxName->setPlaceholderText(tr("Connection name"));
    txtBxUserName->setPlaceholderText(tr("Username"));
    txtBxPassword->setPlaceholderText(tr("Password"));
    txtBxAddress->setPlaceholderText(tr("Server address"));
    numBxPort->setPlaceholderText(tr("Port"));
    chBxSave->setText(tr("Save"));
    chBxSetDefault->setText(tr("Set as default"));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(new QLabel(tr("Select connection:")), 0, 0, 1, 1, 0);
    mainLayout->addWidget(cmBxFTPConnections, 0, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Name:")), 1, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxName, 1, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Username:")), 2, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxUserName, 2, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Password:")), 3, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxPassword, 3, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Server address:")), 4, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxAddress, 4, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Port:")), 5, 0, 1, 1, 0);
    mainLayout->addWidget(numBxPort, 5, 1, 1, 1, 0);
    mainLayout->addWidget(chBxSave, 6, 0, 1, 1, 0);
    mainLayout->addWidget(chBxSetDefault, 6, 1, 1, 1, 0);

    setLayout(mainLayout);

    connect(this, SIGNAL(confirm()), this, SLOT(onConfirm()));

    clear();
}

SendDatabasePopUp::~SendDatabasePopUp()
{

}

// PUBLIC SLOTS
void SendDatabasePopUp::add(const QString &name, int id){
    cmBxFTPConnections->addItem(name, id);
}

void SendDatabasePopUp::select(int id){
    for(int i = 0; i < cmBxFTPConnections->count(); ++i){
        if(cmBxFTPConnections->itemData(i).toInt() == id){
            cmBxFTPConnections->setCurrentIndex(i);
            break;
        }
    }
}

void SendDatabasePopUp::clear(){
    cmBxFTPConnections->clear();
    cmBxFTPConnections->addItem(tr("New Connection"), QVariant(0));
}

//PRIVATE SLOTS
void SendDatabasePopUp::cmBxFTPConnectionsIndexChanged(int index){
    if(index != 0)
        emit selected(cmBxFTPConnections->itemData(index).toInt());
    else{
        txtBxName->setText("");
        txtBxUserName->setText("");
        txtBxPassword->setText("");
        txtBxAddress->setText("");
        numBxPort->setValue(21);
        chBxSave->setChecked(true);
        chBxSetDefault->setChecked(false);
    }
}

void SendDatabasePopUp::onConfirm(){
    if(chBxSave && cmBxFTPConnections->currentIndex() == 0)
        emit create();
    else if(chBxSave)
        emit edit(cmBxFTPConnections->currentData().toInt());

    FtpHandler *ftpHandler = new FtpHandler();
    connect(ftpHandler, SIGNAL(started()), this, SLOT(startedUpload()));
    connect(ftpHandler, SIGNAL(finished()), this, SLOT(finishedUpload()));
    connect(ftpHandler, SIGNAL(progress(int)), this, SLOT(progressUpload(int)));
    connect(ftpHandler, SIGNAL(error(QString)), this, SLOT(errorDurringUpload(QString)));
    ftpHandler->setUser(getUserName(), getPassword());
    ftpHandler->setPort(getPort());
    ftpHandler->setServer(getAddress());
    ftpHandler->uploadFile(StandardPaths::databasePath());
}

void SendDatabasePopUp::startedUpload(){
    emit showMessage(tr("Started Upload"), NotificationMessage::INFORMATION, NotificationMessage::SHORT);
}

void SendDatabasePopUp::finishedUpload(){
    emit showMessage(tr("Finished Upload"), NotificationMessage::INFORMATION, NotificationMessage::SHORT);
}

void SendDatabasePopUp::progressUpload(int progress){

}

void SendDatabasePopUp::errorDurringUpload(const QString &error){
    emit showMessage(error, NotificationMessage::ERROR, NotificationMessage::PERSISTENT);
}

// GETTER / SETTER
QString SendDatabasePopUp::getName() const{
    return txtBxName->text();
}
void SendDatabasePopUp::setName(const QString &name){
    txtBxName->setText(name);
}
QString SendDatabasePopUp::getUserName() const{
    return txtBxUserName->text();
}
void SendDatabasePopUp::setUserName(const QString &username){
    txtBxUserName->setText(username);
}
QString SendDatabasePopUp::getPassword() const{
    return txtBxPassword->text();
}
void SendDatabasePopUp::setPassword(const QString &password){
    txtBxPassword->setText(password);
}
QString SendDatabasePopUp::getAddress() const{
    return txtBxAddress->text();
}
void SendDatabasePopUp::setAddress(const QString &address){
    txtBxAddress->setText(address);
}

int SendDatabasePopUp::getPort() const{
    return numBxPort->getValue();
}
void SendDatabasePopUp::setPort(int port){
    numBxPort->setValue(port);
}

bool SendDatabasePopUp::getSetAsDefault() const{
    return chBxSetDefault->isChecked();
}
void SendDatabasePopUp::setSetAsDefault(bool setAsDefault){
    chBxSetDefault->setChecked(setAsDefault);
}

