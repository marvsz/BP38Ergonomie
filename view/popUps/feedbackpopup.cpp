#include "feedbackpopup.h"
#include <QGridLayout>

FeedbackPopUp::FeedbackPopUp(QWidget *parent) : AbstractPopUpWidget(ConfirmMode::SEND, tr("Feedback"), parent),
    lblViewName(new QLabel(tr("View name:"))),
    txtBxViewName(new TextLineEdit()),
    chbxScreenshot(new QCheckBox()),
    lblDescription(new QLabel(tr("Description:"))),
    txtBxDescription(new TextEdit()),
    lblPriority(new QLabel(tr("Priority:"))),
    cmbBxPriority(new QComboBox()),
    lblCategory(new QLabel("Category:")),
    cmbBxCategory(new QComboBox())
{
    txtBxViewName->setEnabled(false);

    chbxScreenshot->setText(tr("attach screenshot"));

    cmbBxPriority->addItem("1", QVariant(1));
    cmbBxPriority->addItem("2", QVariant(2));
    cmbBxPriority->addItem("3", QVariant(3));
    cmbBxPriority->addItem("4", QVariant(4));
    cmbBxPriority->addItem("5", QVariant(5));

    cmbBxCategory->addItem(tr("Bug"), QVariant("Bug"));
    cmbBxCategory->addItem(tr("Wish"), QVariant("Wish"));
    cmbBxCategory->addItem(tr("Missing function"), QVariant("Missing function"));
    cmbBxCategory->addItem(tr("Wrong implementation"), QVariant("Wrong implementation"));
    cmbBxCategory->addItem(tr("Usability comment"), QVariant("Usability comment"));


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(lblPriority, 0, 0, 1, 1, 0);
    mainLayout->addWidget(cmbBxPriority, 0, 1, 1, 1, 0);
    mainLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 0, 2, 1, 1, 0);
    mainLayout->addWidget(lblCategory, 0, 3, 1, 1, 0);
    mainLayout->addWidget(cmbBxCategory, 0, 4, 1, 1, 0);
    mainLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 0, 5, 1, 1, 0);
    mainLayout->addWidget(chbxScreenshot, 0, 6, 1, 1, 0);
    mainLayout->addWidget(lblDescription, 1, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxDescription, 1, 1, 1, 6, 0);

    connect(this, SIGNAL(confirm()), this, SLOT(sendData()));

    setLayout(mainLayout);
}

FeedbackPopUp::~FeedbackPopUp()
{

}


void FeedbackPopUp::onEnter(){
    cmbBxCategory->setCurrentIndex(0);
    cmbBxPriority->setCurrentIndex(0);
    chbxScreenshot->setChecked(true);
    txtBxDescription->setText("");
}

void FeedbackPopUp::sendData(){

    emit closePopUp();
}
