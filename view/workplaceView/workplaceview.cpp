#include "workplaceview.h"
#include "separator.h"
#include "QGridLayout"
#include "QVBoxLayout"
#include "QHBoxLayout"

WorkplaceView::WorkplaceView(QWidget *parent) :
    QWidget(parent),
    id(-1),
    lblViewDescription(new QLabel("Arbeitsplatz:")),
    lblName(new QLabel("Bezeichnung:")),
    lblDescription(new QLabel("Beschreibung:")),
    lblCode(new QLabel("Arbeitsplatz Code:")),
    lblPercentageWoman(new QLabel("Nutzerpopulation:")),
    txtBxName(new TextLineEdit()),
    txtBxDescription(new TextLineEdit()),
    txtBxCode(new TextLineEdit()),
    numBxWomanPercentage(new NumberLineEdit()),
    btnCancel(new QPushButton("Abbruch")),
    btnSave(new QPushButton("Speichern")),
    btnGoOnWithWorkProcesses(new QPushButton("Weiter zu den Arbeitsvorgängen"))
{
    QHBoxLayout *navigationBarLayout = new QHBoxLayout;
    navigationBarLayout->addWidget(btnCancel, 0, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewDescription, 0, Qt::AlignHCenter);

    QGridLayout *workplaceMetaDataLayout = new QGridLayout;
    workplaceMetaDataLayout->addWidget(lblName, 0, 0, 1, 1, 0);
    workplaceMetaDataLayout->addWidget(txtBxName, 0, 1, 1, 1, 0);
    workplaceMetaDataLayout->addWidget(lblDescription, 0, 2, 1, 1, 0);
    workplaceMetaDataLayout->addWidget(txtBxDescription, 0, 3, 1, 1, 0);
    workplaceMetaDataLayout->addWidget(lblCode, 1, 0, 1, 1, 0);
    workplaceMetaDataLayout->addWidget(txtBxCode, 1, 1, 1, 1, 0);
    workplaceMetaDataLayout->addWidget(lblPercentageWoman, 1, 2, 1, 1, 0);
    workplaceMetaDataLayout->addWidget(numBxWomanPercentage, 1, 3, 1, 1, 0);

    QVBoxLayout *additionsLayout = new QVBoxLayout;

    QHBoxLayout *bottomLineLayout = new QHBoxLayout;
    bottomLineLayout->addWidget(btnSave, 0, Qt::AlignCenter);
    bottomLineLayout->addWidget(btnGoOnWithWorkProcesses, 0, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addLayout(workplaceMetaDataLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addLayout(additionsLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addLayout(bottomLineLayout);

    setLayout(mainLayout);
}

WorkplaceView::WorkplaceView(int id, QWidget *parent) : WorkplaceView(parent){
    this->id = id;
}

//public slots
void WorkplaceView::setWorkplaceMetaData(const QString &name, const QString &description, const QString &code, int percentageWoman){
    txtBxName->setText(name);
    txtBxDescription->setText(description);
    txtBxCode->setText(code);
    numBxWomanPercentage->setValue(percentageWoman);
}


//private slots
void WorkplaceView::WorkplaceView::btnSaveClicked(){
    if(id == -1)
        emit save();
    else
        emit save(id);
}

void WorkplaceView::WorkplaceView::btnCancelClicked(){
    emit cancle();
}

void WorkplaceView::WorkplaceView::btnGoOnWithWorkProcessesClicked(){
    emit goOnToWorkProcesses();
}
