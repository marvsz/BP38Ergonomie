#ifndef TITLEDWIDGET_H
#define TITLEDWIDGET_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QPaintEvent>
#include "viewtype.h"
#include "notificationmessage.h"

class TitledWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TitledWidget(const QString &title, QWidget *parent = 0):
    QWidget(parent),
    title(title){

    }

    ~TitledWidget(){

    }

    const QString getTitle() const{
        return title;
    }

signals:
    void showView(ViewType type);
    void showPopUp(PopUpType type);
    void showMessage(const QString &message, NotificationMessage::MessageType msgType = NotificationMessage::ACCEPT, NotificationMessage::MessageDisplayType msgDisplayType = NotificationMessage::MIDDLE);

public slots:
    virtual void onLeaving(){
    }

    virtual void onEnter(){

    }


private:
    const QString title;

    void paintEvent(QPaintEvent *){
        QStyleOption opt;
        opt.init(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    }


};

#endif // TITLEDWIDGET_H
