#ifndef NOTIFICATIONWIDGET_H
#define NOTIFICATIONWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include "notificationmessage.h"
#include "abstractpopupwidget.h"

class NotificationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NotificationWidget(QWidget *parent = 0);
    ~NotificationWidget();

    void setMainWidget(QWidget *widget);

    QSize sizeHint() const;

public slots:
    void closePopUp();
    void showMessage(const QString &message, NotificationMessage::MessageType msgType = NotificationMessage::INFORMATION, NotificationMessage::MessageDisplayType msgDisplayType = NotificationMessage::MIDDLE);
    void closeMessage();

protected slots:
    void openPopUp(AbstractPopUpWidget *popUp);

private:
    QGridLayout *popUpLayout;

    QWidget *mainWidget;
    QWidget *popUpWidget;
    QWidget *notificationMessageWidget;

    AbstractPopUpWidget *currentPopUp;
    NotificationMessage *notifiMessage;

    void resizeEvent(QResizeEvent *event);

};

#endif // NOTIFICATIONWIDGET_H
