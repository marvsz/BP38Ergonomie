#include "importdatapopup.h"
#include <QDir>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "standardpaths.h"
#include "separator.h"

ImportDataPopUp::ImportDataPopUp(QWidget *parent) :
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Import data"), parent),
    countFinDownload(0),
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
void ImportDataPopUp::add(const QString &name, int id)
{
    ftpConnectionWidget->add(name, id);
}

void ImportDataPopUp::select(int id)
{
    ftpConnectionWidget->select(id);
}

void ImportDataPopUp::clear()
{
    ftpConnectionWidget->clear();
}

void ImportDataPopUp::onConfirm()
{
    if(ftpConnectionWidget->getSaved() && ftpConnectionWidget->getSelectedIndex() == 0)
        emit create(this);
    else if(ftpConnectionWidget->getSaved())
        emit edit(this, ftpConnectionWidget->getSelectedID());
}

//PRIVATE SLOTS
void ImportDataPopUp::selectedConnectionChanged(int id)
{
    emit selected(this, id);
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

QString ImportDataPopUp::getName() const
{
    return ftpConnectionWidget->getName();
}
void ImportDataPopUp::setName(const QString &name)
{
    ftpConnectionWidget->setName(name);
}

QString ImportDataPopUp::getUserName() const
{
    return ftpConnectionWidget->getUserName();
}
void ImportDataPopUp::setUserName(const QString &username)
{
    ftpConnectionWidget->setUserName(username);
}

QString ImportDataPopUp::getPassword() const
{
    return ftpConnectionWidget->getPassword();
}
void ImportDataPopUp::setPassword(const QString &password)
{
    ftpConnectionWidget->setPassword(password);
}

QString ImportDataPopUp::getAddress() const
{
    return ftpConnectionWidget->getAddress();
}
void ImportDataPopUp::setAddress(const QString &address)
{
    ftpConnectionWidget->setAddress(address);
}

int ImportDataPopUp::getPort() const
{
    return ftpConnectionWidget->getPort();
}
void ImportDataPopUp::setPort(int port)
{
    ftpConnectionWidget->setPort(port);
}

bool ImportDataPopUp::getSetAsDefault() const
{
    return ftpConnectionWidget->getSetAsDefault();
}
void ImportDataPopUp::setSetAsDefault(bool setAsDefault)
{
    ftpConnectionWidget->setSetAsDefault(setAsDefault);
}

