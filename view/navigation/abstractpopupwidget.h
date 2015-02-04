#ifndef ABSTRACTPOPUPWIDGET_H
#define ABSTRACTPOPUPWIDGET_H

#include "titledwidget.h"

class AbstractPopUpWidget : public TitledWidget
{
    Q_OBJECT
public:
    explicit AbstractPopUpWidget(const QString &title, QWidget *parent = 0);
    ~AbstractPopUpWidget();

    void setLayout(QLayout *layout);

signals:
    void close();

};

#endif // ABSTRACTPOPUPWIDGET_H
