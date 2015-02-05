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

    explicit AbstractPopUpWidget(const QString &title, QWidget *parent = 0);
    ~AbstractPopUpWidget();

    void setLayout(QLayout *layout);

protected:
    virtual ConfirmMode getConfirmMode() const{
        return ConfirmMode::ACCEPT;
    }

signals:
    void close();
    void confirm();

private:
    QGridLayout *mainLayout;

    QPushButton *btnClose;
    QPushButton *btnConfirm;
    QLabel *lblTitle;

};

#endif // ABSTRACTPOPUPWIDGET_H
