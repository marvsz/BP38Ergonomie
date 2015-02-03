#ifndef DOCUMENTATIONVIEWNAVIGATEABLEWIDGET_H
#define DOCUMENTATIONVIEWNAVIGATEABLEWIDGET_H

#include "navigateablewidget.h"

class DocumentationViewNavigateableWidget : public NavigateableWidget
{
public:
    DocumentationViewNavigateableWidget(const QString &title, QWidget *parent = 0) :
        NavigateableWidget(title, parent){

    }

    ~DocumentationViewNavigateableWidget(){

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
        return false;
    }
    bool canGoForward() const{
        return false;
    }
};

#endif // DOCUMENTATIONVIEWNAVIGATEABLEWIDGET_H
