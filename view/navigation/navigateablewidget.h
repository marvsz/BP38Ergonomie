#ifndef NAVIGATABELWIDGET_H
#define NAVIGATABELWIDGET_H

#include "titledwidget.h"
#include <QAbstractButton>
#include <QList>

class NavigateableWidget : public TitledWidget
{
    Q_OBJECT
public:
    explicit NavigateableWidget(const QString &title, QWidget *parent = 0) : TitledWidget(title, parent){

    }

    ~NavigateableWidget(){

    }

    virtual ViewType getBackViewType() const = 0;
    virtual ViewType getForwardViewType() const = 0;
    virtual QList<QAbstractButton*> * getAdditionalNavigation() const = 0;
    virtual QWidget* getInternalNavigation() const = 0;

    virtual bool canGoForward() const = 0;
    virtual bool canGoBack() const = 0;
    virtual bool hasInteralNavigation() const = 0;
    virtual bool hasAdditionalNavigation() const = 0;



};

#endif // NAVIGATABELWIDGET_H
