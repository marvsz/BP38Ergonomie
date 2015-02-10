#include "senddatabasepopup.h"
#include <QGridLayout>

SendDatabasePopUp::SendDatabasePopUp(QWidget *parent) : AbstractPopUpWidget(ConfirmMode::SEND, tr("Send database"), parent),
    cmBxFTPConnections(new QComboBox()),
    txtBxName( new TextLineEdit()),
    txtBxAddress( new TextLineEdit()),
    numBxPort(new NumberLineEdit()),
    chBxSave(new QCheckBox()),
    chBxSetDefault(new QCheckBox())
{
    connect(cmBxFTPConnections, SIGNAL(currentIndexChanged(int)), this, SLOT(cmBxFTPConnectionsIndexChanged(int)));

    txtBxName->setPlaceholderText(tr("Connection name"));
    txtBxAddress->setPlaceholderText(tr("Server address"));
    numBxPort->setPlaceholderText(tr("Port"));
    chBxSave->setText(tr("Save"));
    chBxSetDefault->setText(tr("Set as default"));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(new QLabel(tr("Select connection:")), 0, 0, 1, 1, 0);
    mainLayout->addWidget(cmBxFTPConnections, 0, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Name:")), 1, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxName, 1, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Server address:")), 2, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxAddress, 2, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Port:")), 3, 0, 1, 1, 0);
    mainLayout->addWidget(numBxPort, 3, 1, 1, 1, 0);
    mainLayout->addWidget(chBxSave, 4, 0, 1, 1, 0);
    mainLayout->addWidget(chBxSetDefault, 4, 1, 1, 1, 0);

    setLayout(mainLayout);
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
    emit selected(cmBxFTPConnections->itemData(index).toInt());
}

void SendDatabasePopUp::onConfirm(){
    if(chBxSave && cmBxFTPConnections->currentIndex() == 0)
        emit create();
    else if(chBxSave)
        emit edit(cmBxFTPConnections->currentData().toInt());
}

// GETTER / SETTER
QString SendDatabasePopUp::getName() const{
    return txtBxName->text();
}
void SendDatabasePopUp::setName(const QString &name){
    txtBxName->setText(name);
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

