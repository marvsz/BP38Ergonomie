#include "FTPConnectionsWidget.h"
#include <QGridLayout>
#include <QLabel>

FTPConnectionsWidget::FTPConnectionsWidget(QWidget *parent) :
  QWidget(parent),
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

  clear();
}

FTPConnectionsWidget::~FTPConnectionsWidget()
{

}

// PUBLIC SLOTS
void FTPConnectionsWidget::add(const QString &name, int id){
    cmBxFTPConnections->addItem(name, id);
}

void FTPConnectionsWidget::select(int id){
    for(int i = 0; i < cmBxFTPConnections->count(); ++i){
        if(cmBxFTPConnections->itemData(i).toInt() == id){
            cmBxFTPConnections->setCurrentIndex(i);
            break;
        }
    }
}

void FTPConnectionsWidget::clear(){
    cmBxFTPConnections->clear();
    cmBxFTPConnections->addItem(tr("New Connection"), QVariant(0));
}

//PRIVATE SLOTS
void FTPConnectionsWidget::cmBxFTPConnectionsIndexChanged(int index){
    if(index != 0)
        emit selectedConnectionChanged(cmBxFTPConnections->itemData(index).toInt());
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

// GETTER / SETTER
QString FTPConnectionsWidget::getName() const{
    return txtBxName->text();
}
void FTPConnectionsWidget::setName(const QString &name){
    txtBxName->setText(name);
}
QString FTPConnectionsWidget::getUserName() const{
    return txtBxUserName->text();
}
void FTPConnectionsWidget::setUserName(const QString &username){
    txtBxUserName->setText(username);
}
QString FTPConnectionsWidget::getPassword() const{
    return txtBxPassword->text();
}
void FTPConnectionsWidget::setPassword(const QString &password){
    txtBxPassword->setText(password);
}
QString FTPConnectionsWidget::getAddress() const{
    return txtBxAddress->text();
}
void FTPConnectionsWidget::setAddress(const QString &address){
    txtBxAddress->setText(address);
}

int FTPConnectionsWidget::getPort() const{
    return numBxPort->getValue();
}
void FTPConnectionsWidget::setPort(int port){
    numBxPort->setValue(port);
}

bool FTPConnectionsWidget::getSetAsDefault() const{
    return chBxSetDefault->isChecked();
}
void FTPConnectionsWidget::setSetAsDefault(bool setAsDefault){
    chBxSetDefault->setChecked(setAsDefault);
}

bool FTPConnectionsWidget::getSaved() const{
  return chBxSave->isChecked();
}

int FTPConnectionsWidget::getSelectedIndex() const{
  return cmBxFTPConnections->currentIndex();
}

int FTPConnectionsWidget::getSelectedID() const{
  return cmBxFTPConnections->currentData().toInt();
}

