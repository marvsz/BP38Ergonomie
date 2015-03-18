#include "importdatapopup.h"
#include <QDir>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "standardpaths.h"
#include "separator.h"

ImportDataPopUp::ImportDataPopUp(QWidget *parent) :
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Import data"), parent),
    ftpConnectionWidget(new FTPConnectionsWidget(this)),
    cmbxImportMethod(new QComboBox()),
    chBxTransportation(new QCheckBox()),
    chBxEquipment(new QCheckBox()),
    chBxProduct(new QCheckBox()),
    chBxEmployee(new QCheckBox()),
    chBxWorkplace(new QCheckBox())
{
    cmbxImportMethod->addItem(tr("XML"));

    chBxTransportation->setText(tr("Transportations"));
    chBxEquipment->setText(tr("Equipments"));
    chBxProduct->setText(tr("Products"));
    chBxEmployee->setText(tr("Employees"));
    chBxWorkplace->setText(tr("Workplaces"));

    connect(ftpConnectionWidget, SIGNAL(selectedConnectionChanged(int)), this, SLOT(selectedConnectionChanged(int)));

    connect(this, SIGNAL(confirm()), this, SLOT(onConfirm()));

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addWidget(cmbxImportMethod);
    configLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    configLayout->addWidget(chBxTransportation);
    configLayout->addWidget(chBxEquipment);
    configLayout->addWidget(chBxProduct);
    configLayout->addWidget(chBxEmployee);
    configLayout->addWidget(chBxWorkplace);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(ftpConnectionWidget);
    mainLayout->addSpacerItem(new QSpacerItem(10, 0));
    mainLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    mainLayout->addSpacerItem(new QSpacerItem(10, 0));
    mainLayout->addLayout(configLayout);
    mainLayout->addSpacerItem(new QSpacerItem(10, 0));

    setLayout(mainLayout);
}

ImportDataPopUp::~ImportDataPopUp()
{

}

//PUBLIC SLOTS
void ImportDataPopUp::addFTPConnection(QHash<QString, QVariant> values){
    ftpConnectionWidget->add(values.value(DBConstants::COL_CONNECTION_NAME).toString(), values.value(DBConstants::COL_CONNECTION_ID).toInt());
}

void ImportDataPopUp::selectedFTPConnection(int id){
    ftpConnectionWidget->select(id);
}

void ImportDataPopUp::clearFTPConnections(){
    ftpConnectionWidget->clear();
}

void ImportDataPopUp::onEnter(){
    emit initializeFTPConnections(this);
}

//PRIVATE SLOTS
void ImportDataPopUp::selectedConnectionChanged(int id){
    emit selectFTPConnection(this, id);
}

void ImportDataPopUp::onConfirm(){
    if(ftpConnectionWidget->getSaved() && ftpConnectionWidget->getSelectedIndex() == 0)
        emit createFTPConnection(this);
    else if(ftpConnectionWidget->getSaved())
        emit editFTPConnection(this, ftpConnectionWidget->getSelectedID());
    emit importData(this);
}


// Getter / Setter
QString ImportDataPopUp::getImportMode() const
{
    return cmbxImportMethod->currentText();
}
bool ImportDataPopUp::importTransportations() const
{
    return chBxTransportation->isChecked();
}
bool ImportDataPopUp::importEquipments() const
{
    return chBxEquipment->isChecked();
}
bool ImportDataPopUp::importProducts() const
{
    return chBxProduct->isChecked();
}
bool ImportDataPopUp::importEmployees() const
{
    return chBxEmployee->isChecked();
}
bool ImportDataPopUp::importWorkplaces() const
{
    return chBxWorkplace->isChecked();
}

//GETTER / SETTER
QHash<QString, QVariant> ImportDataPopUp::getFTPConnection() const{
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_CONNECTION_NAME, ftpConnectionWidget->getName());
    values.insert(DBConstants::COL_CONNECTION_USERNAME, ftpConnectionWidget->getUserName());
    values.insert(DBConstants::COL_CONNECTION_PASSWORD, ftpConnectionWidget->getPassword());
    values.insert(DBConstants::COL_CONNECTION_PORT, ftpConnectionWidget->getPort());
    values.insert(DBConstants::COL_CONNECTION_SERVER_ADDRESS, ftpConnectionWidget->getAddress());
    values.insert(DBConstants::COL_CONNECTION_DEFAULT, ftpConnectionWidget->getSetAsDefault());
    return values;
}
void ImportDataPopUp::setFTPConnection(QHash<QString, QVariant> values){
    ftpConnectionWidget->setName(values.value(DBConstants::COL_CONNECTION_NAME).toString());
    ftpConnectionWidget->setUserName(values.value(DBConstants::COL_CONNECTION_USERNAME).toString());
    ftpConnectionWidget->setPassword(values.value(DBConstants::COL_CONNECTION_PASSWORD).toString());
    ftpConnectionWidget->setPort(values.value(DBConstants::COL_CONNECTION_PORT).toInt());
    ftpConnectionWidget->setAddress(values.value(DBConstants::COL_CONNECTION_SERVER_ADDRESS).toString());
    ftpConnectionWidget->setSetAsDefault(values.value(DBConstants::COL_CONNECTION_DEFAULT).toBool());
}


