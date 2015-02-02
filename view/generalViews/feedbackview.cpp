#include "feedbackview.h"
#include <QGridLayout>

FeedbackView::FeedbackView(QWidget *parent) : SimpleNavigateableWidget(tr("Feedback"), parent),
    btnSend(new QPushButton()),
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
    btnSend->setText(tr("Send"));

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
    mainLayout->addWidget(btnSend, 2, 0, 1, 7, Qt::AlignCenter);
    setLayout(mainLayout);
}

FeedbackView::~FeedbackView()
{

}
//PUBLIC METHODS
void FeedbackView::reset(){
    screenshotPath = "";
    loggingPath = "";
    viewName = "";
    cmbBxCategory->setCurrentIndex(0);
    cmbBxPriority->setCurrentIndex(0);
    txtBxDescription->setText("");
    txtBxViewName->setText("");
    chbxScreenshot->setChecked(true);
}


//SETTER
void FeedbackView::setScreenshotPath(const QString &path){
    screenshotPath = path;
}

void FeedbackView::setLoggingPath(const QString &path){
    loggingPath = path;
}

void FeedbackView::setViewName(const QString &name){
    viewName = name;
    txtBxViewName->setText(name);
}
