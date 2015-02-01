#ifndef SIMPLENAVIGATABLEWIDGET_H
#define SIMPLENAVIGATABLEWIDGET_H

#include "navigateablewidget.h"

class SimpleNavigateableWidget : public NavigateableWidget
{
public:
    SimpleNavigateableWidget(const QString &title, QWidget *parent = 0) :
        NavigateableWidget(title, parent){

    }

    ~SimpleNavigateableWidget(){

    }

    QWidget* getInternalNavigation() const {
        return 0;
    }

    QList<QAbstractButton*> * getAdditionalNavigation() const{
        return 0;
    }

    bool hasInteralNavigation() const{
        return false;
    }

    bool hasAdditionalNavigation() const{
        return false;
    }

    ViewType getForwardViewType() const{
        return ViewType::UNKNOWN;
    }
    ViewType getBackViewType() const{
        return ViewType::UNKNOWN;
    }

    bool canGoBack() const{
        return true;
    }
    bool canGoForward() const{
        return false;
    }

};

#endif // SIMPLENAVIGATABLEWIDGET_H
