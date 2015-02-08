#include "notificationmessage.h"
#include <QStyleOption>
#include <QPainter>

NotificationMessage::NotificationMessage(QWidget *parent) : QPushButton(parent),
    timerID(-1),
    idle(true),
    msgQueue(QList<Message>())
{
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    this->setIconSize(QSize(30, 30));
    this->setGeometry(0, 0, 100, 42);
    connect(this, SIGNAL(clicked()), this, SLOT(closeMessage()));
    this->hide();
}

NotificationMessage::~NotificationMessage()
{

}

//PUBLIC SLOTS
void NotificationMessage::showMessage(const QString &message, MessageType msgType, MessageDisplayType msgDisplayType){
    Message m;
    m.text = message;
    m.type = msgType;
    m.displayType = msgDisplayType;
    msgQueue.append(m);
    processMessageQueue();
}

void NotificationMessage::closeMessage(){
    idle = true;
    msgQueue.removeFirst();
    this->hide();
    processMessageQueue();
}

//PRIVATE METHODS
void NotificationMessage::processMessageQueue(){
    if(!msgQueue.isEmpty() && idle){
        Message msg = msgQueue.at(0);
        idle = false;
        int duration;
        switch(msg.displayType){
            case SHORT: duration = 500; break;
            case MIDDLE: duration = 1000; break;
            case LONG: duration = 2000; break;
            default: duration = 1000; break;
        }
        if(msg.displayType != PERSISTENT){
            timerID = startTimer(duration);
        }
        switch(msg.type){
            case ACCEPT: this->setObjectName("saveIcon"); break;
            case ERROR: this->setObjectName("cancelIcon"); break;
            case WARNING: this->setObjectName("btnWarning"); break;
            case INFORMATION: this->setIcon(QIcon(":/button/icons/Buttons/check.png")); break;
            default: this->setObjectName("saveIcon"); break;
        }
        this->setText(msg.text);
        int width = 35 + msg.text.length() * 12;
        int xPos = this->x() + (this->width() - width) / 2;
        this->setGeometry(xPos, this->y(), width, this->height());
        this->show();
        update();
    }
}

void NotificationMessage::paintEvent(QPaintEvent *event){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QPushButton::paintEvent(event);
}

void NotificationMessage::timerEvent(QTimerEvent *){
    if(!idle){
        killTimer(timerID);
        closeMessage();
    }
}

