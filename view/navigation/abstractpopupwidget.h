#ifndef ABSTRACTPOPUPWIDGET_H
#define ABSTRACTPOPUPWIDGET_H

#include "titledwidget.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

class AbstractPopUpWidget : public TitledWidget
{
    Q_OBJECT
public:
    enum ConfirmMode{ACCEPT, SEND};

    explicit AbstractPopUpWidget(ConfirmMode mode, const QString &title, QWidget *parent = 0);
    ~AbstractPopUpWidget();

    void setLayout(QLayout *layout);

signals:
    void closePopUp();
    void cancel();
    void confirm();

private:
    QGridLayout *mainContentLayout;

    QPushButton *btnClose;
    QPushButton *btnConfirm;
    QLabel *lblTitle;

    void paintEvent(QPaintEvent *);
};

#endif // ABSTRACTPOPUPWIDGET_H
