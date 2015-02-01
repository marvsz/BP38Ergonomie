#include "viewcontroller.h"
#include "separator.h"
#include "iconconstants.h"
#include <QVBoxLayout>

ViewController::ViewController(QWidget *parent) : QWidget(parent),
    content(new QStackedWidget()),
    previousViews(new QStack<ViewType>()),
    viewTypeToIndex(new QHash<ViewType, int>()),
    viewTypeToWidget(new QHash<ViewType, NavigateableWidget*>()),
    btnBack(new QPushButton),
    btnForward(new QPushButton),
    btnFeedback(new QPushButton),
    lblBackTitle(new QLabel),
    lblForwardTitle(new QLabel),
    lblTitle(new QLabel),
    internalNavigation(0),
    additionalNavigation(0),
    middleNavigationLayout(new QHBoxLayout),
    additionalNavigationLayout(new QHBoxLayout)
{
    btnBack->setObjectName("leftIcon");
    btnBack->setFixedSize(45, 45);
    connect(btnBack, SIGNAL(clicked()), this, SLOT(btnBackClicked()));

    btnForward->setObjectName("rightIcon");
    btnForward->setFixedSize(45, 45);
    connect(btnForward, SIGNAL(clicked()), this, SLOT(btnForwardClicked()));

    btnFeedback->setObjectName("btnIcon");
    btnFeedback->setIcon(QIcon(IconConstants::ICON_COMMENT));
    btnFeedback->setIconSize(QSize(45, 45));
    btnFeedback->setFixedSize(45, 45);

    middleNavigationLayout->addWidget(lblTitle);

    QHBoxLayout *navigationBarLayout = new QHBoxLayout;
    navigationBarLayout->addWidget(btnBack, 0, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblBackTitle, 0, Qt::AlignLeft);
    navigationBarLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    navigationBarLayout->addLayout(middleNavigationLayout);
    navigationBarLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    navigationBarLayout->addLayout(additionalNavigationLayout);
    navigationBarLayout->addWidget(btnFeedback, 0, Qt::AlignRight);
    navigationBarLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
    navigationBarLayout->addWidget(lblForwardTitle, 0, Qt::AlignRight);
    navigationBarLayout->addWidget(btnForward, 0, Qt::AlignRight);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3));
    mainLayout->addWidget(content);
    setLayout(mainLayout);
}

ViewController::~ViewController()
{

}

//PUBLIC METHODS
void ViewController::showStartView(ViewType type){
    if(viewTypeToIndex->contains(type)){
        previousViews->push(type);
        content->setCurrentIndex(viewTypeToIndex->value(type));
        adaptNavigationBar(type);
        emit update(type);
        this->show();
    }
}

void ViewController::registerView(NavigateableWidget *widget, ViewType type){
    if(!viewTypeToIndex->contains(type) && widget != 0){
        viewTypeToIndex->insert(type, content->addWidget(widget));
        viewTypeToWidget->insert(type, widget);
        connect(widget, SIGNAL(show(ViewType)), this, SLOT(goToView(ViewType)));
    }
}

//PRIVATE SLOTS
void ViewController::btnBackClicked(){
    ViewType currentType = previousViews->top();
    NavigateableWidget *currentView = viewTypeToWidget->value(currentType);
    backToView(currentView->getBackViewType());
}

void ViewController::btnForwardClicked(){
    ViewType currentType = previousViews->top();
    NavigateableWidget *currentView = viewTypeToWidget->value(currentType);
    goToView(currentView->getForwardViewType());
}

void ViewController::goToView(ViewType type){
    if(viewTypeToIndex->contains(type)){
        emit save(previousViews->top());
        emit update(type);
        content->setCurrentIndex(viewTypeToIndex->value(type));
        previousViews->push(type);
        adaptNavigationBar(type);
    }
}

void ViewController::backToView(ViewType type){
    if((viewTypeToIndex->contains(type) && previousViews->contains(type)) || type == ViewType::UNKNOWN){
        emit save(previousViews->top());
        if(type == ViewType::UNKNOWN){
            previousViews->pop();
        }
        else {
            while(previousViews->top() != type)
                previousViews->pop();
        }
        ViewType nextType = previousViews->top();
        emit update(nextType);
        content->setCurrentIndex(viewTypeToIndex->value(nextType));
        adaptNavigationBar(nextType);
    }
}

//PRIVATE METHODS
void ViewController::adaptNavigationBar(ViewType type){
    NavigateableWidget *currentWidget = viewTypeToWidget->value(type);

    if(currentWidget->canGoBack()){
        btnBack->show();
        ViewType backType = currentWidget->getBackViewType();
        if(backType == UNKNOWN){
            backType = previousViews->at(previousViews->count() - 2);
        }
        lblBackTitle->show();
        lblBackTitle->setText(viewTypeToWidget->value(backType)->getTitle());
    }
    else {
        btnBack->hide();
        lblBackTitle->hide();
    }

    if(currentWidget->canGoForward() && viewTypeToWidget->contains(currentWidget->getForwardViewType())){
        btnForward->show();
        lblForwardTitle->show();
        lblForwardTitle->setText(viewTypeToWidget->value(currentWidget->getForwardViewType())->getTitle());
    }
    else{
        btnForward->hide();
        lblForwardTitle->hide();
    }

    if(additionalNavigation != 0){
        for(int i = 0; i < additionalNavigation->count(); ++i)
            additionalNavigation->at(i)->hide();
    }
    if(currentWidget->hasAdditionalNavigation()){
        additionalNavigation = currentWidget->getAdditionalNavigation();
        for(int i = 0; i < additionalNavigation->count(); ++i){
            QAbstractButton *btnAdditional = additionalNavigation->at(i);
            btnAdditional->show();
            additionalNavigationLayout->addWidget(btnAdditional, 0, Qt::AlignRight);
        }
    }
    else{
        additionalNavigation = 0;
    }

    if(internalNavigation != 0)
        internalNavigation->hide();
    if(currentWidget->hasInteralNavigation()){
        lblTitle->hide();
        internalNavigation = currentWidget->getInternalNavigation();
        internalNavigation->show();
        middleNavigationLayout->addWidget(internalNavigation);
    }
    else{
        lblTitle->setText(currentWidget->getTitle());
        lblTitle->show();
        internalNavigation = 0;
    }
}


