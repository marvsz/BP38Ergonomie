#include "notificationwidget.h"
#include <QDebug>

NotificationWidget::NotificationWidget(QWidget *parent) : QWidget(parent),
    popUpLayout(new QGridLayout),
    mainWidget(0),
    popUpWidget(new QWidget()),
    notificationMessageWidget(new QWidget()),
    currentPopUp(0)
{
    popUpLayout->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 0, 1, 3, 0);
    popUpLayout->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding), 1, 0, 1, 1, 0);
    popUpLayout->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding), 1, 2, 1, 1, 0);
    popUpLayout->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding), 2, 0, 1, 3, 0);
    popUpWidget->setLayout(popUpLayout);
    popUpWidget->setObjectName("popUpBackground");
}

NotificationWidget::~NotificationWidget()
{

}

//PUBLIC METHODS
void NotificationWidget::setMainWidget(QWidget *widget){
    mainWidget = widget;
    mainWidget->setParent(this);
    mainWidget->show();
    popUpWidget->setParent(this);
    popUpWidget->hide();
    notifiMessage = new NotificationMessage(this);
}

QSize NotificationWidget::sizeHint() const{
    if(mainWidget != 0)
        return mainWidget->sizeHint();
    else
        return QWidget::sizeHint();
}

//PUBLIC SLOTS
void NotificationWidget::closePopUp(){
    currentPopUp->hide();
    popUpWidget->hide();
    currentPopUp->onLeaving();
}

void NotificationWidget::showMessage(const QString &message, NotificationMessage::MessageType msgType, NotificationMessage::MessageDisplayType msgDisplayType){
    notifiMessage->showMessage(message, msgType, msgDisplayType);
}

void NotificationWidget::closeMessage(){
    notifiMessage->closeMessage();
}

//PROTECTED SLOTS
void NotificationWidget::openPopUp(AbstractPopUpWidget *popUp){
    popUpLayout->addWidget(popUp, 1, 1, 1, 1, Qt::AlignCenter);
    popUp->show();
    currentPopUp = popUp;
    popUpWidget->show();
}

//PRIVATE METHODS
void NotificationWidget::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);
    mainWidget->resize(this->width(), this->height());
    popUpWidget->resize(this->width(), this->height());
    QSize size(notifiMessage->width(), notifiMessage->height());
    int xPos = (this->width() - size.width()) / 2;
    int yPos = this->height() - size.height() - 40;
    notifiMessage->setGeometry(xPos, yPos, size.width(), size.height());
}

