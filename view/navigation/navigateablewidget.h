#ifndef NAVIGATABELWIDGET_H
#define NAVIGATABELWIDGET_H

#include <QWidget>
#include <QAbstractButton>
#include <QList>
#include "viewtype.h"

class NavigateableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NavigateableWidget(const QString &title, QWidget *parent = 0) : QWidget(parent),
        title(title){

    }

    ~NavigateableWidget(){

    }

    const QString getTitle() const{
        return title;
    }

    virtual ViewType getBackViewType() const = 0;
    virtual ViewType getForwardViewType() const = 0;
    virtual QList<QAbstractButton*> * getAdditionalNavigation() const = 0;
    virtual QWidget* getInternalNavigation() const = 0;

    virtual bool canGoForward() const = 0;
    virtual bool canGoBack() const = 0;
    virtual bool hasInteralNavigation() const = 0;
    virtual bool hasAdditionalNavigation() const = 0;

signals:
    void back(ViewType type);
    void forward(ViewType type);
    void show(ViewType type);

public slots:

private:
    const QString title;


};

#endif // NAVIGATABELWIDGET_H
