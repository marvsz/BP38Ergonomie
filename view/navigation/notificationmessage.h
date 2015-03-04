#ifndef NOTIFICATIONMESSAGE_H
#define NOTIFICATIONMESSAGE_H

#include <QPushButton>
#include <QList>

class NotificationMessage : public QPushButton
{
    Q_OBJECT
public:
    NotificationMessage(QWidget *parent = 0);
    ~NotificationMessage();

    enum MessageType{ACCEPT, ERROR, WARNING, INFORMATION, RESTART};
    enum MessageDisplayType{PERSISTENT, SHORT, MIDDLE, LONG};

public slots:
    void showMessage(const QString &message, MessageType msgType = INFORMATION, MessageDisplayType msgDisplayType = MIDDLE);
    void closeMessage();

private:
    struct Message {
        QString text;
        MessageType type;
        MessageDisplayType displayType;
    };

    int timerID;
    bool idle;
    QList<Message> msgQueue;

    void processMessageQueue();

    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *);
};

#endif // NOTIFICATIONMESSAGE_H
