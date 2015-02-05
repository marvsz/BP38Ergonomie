#include "documentationview.h"
#include <QVBoxLayout>
#include "separator.h"

/**
 * @brief Constructs a DocumentationView widget which is a child of parent.
 * @param parent If parent is 0, the new widget becomes a window.
 * If parent is another widget, this widget becomes a child window inside parent.
 * The new widget is deleted when its parent is deleted.
 */
DocumentationView::DocumentationView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Documentation"), parent),
    indexBeforeTimeLineView(0),
    registeredTimerViewController(false),
    views(new QComboBox()),
    mainContent(new QStackedWidget),
    mainLayout(new QVBoxLayout),
    viewTypeToWidget(new QHash<ViewType, TitledWidget*>()),
    viewTypeToIndex(new QHash<ViewType, int>())
{
    views->setMinimumSize(280, 40);
    connect(views, SIGNAL(currentIndexChanged(int)), this, SLOT(changeView(int)));

    mainLayout->addWidget(mainContent);

    setLayout(mainLayout);
}

// PUBLIC
void DocumentationView::showStartView(ViewType type){
    if(viewTypeToIndex->contains(type)){
        currentView = type;
        views->setCurrentIndex(viewTypeToIndex->value(type));
    }
}

void DocumentationView::registerView(TitledWidget *widget, ViewType type){
    if(!viewTypeToIndex->contains(type) && widget != 0){
        viewTypeToIndex->insert(type, mainContent->addWidget(widget));
        views->addItem(widget->getTitle(), type);
        viewTypeToWidget->insert(type, widget);
        connect(widget, SIGNAL(showView(ViewType)), this, SIGNAL(showView(ViewType)));
    }
}

void DocumentationView::setTimerViewController(TimerViewController *timerViewController){
    if(!registeredTimerViewController && timerViewController != 0){
        this->timerViewController = timerViewController;

        connect(timerViewController, SIGNAL(showGantView()), this, SLOT(showGant()));
        connect(timerViewController, SIGNAL(hideGantView()), this, SLOT(hideGant()));

        mainLayout->addWidget(new Separator(Qt::Horizontal, 14, this));
        mainLayout->addWidget(timerViewController);

        registeredTimerViewController = true;
    }
}

// PUBLIC SLOTS
void DocumentationView::onLeaving(){
    timerViewController->closeTimerView();
}

// PRIVATE SLOTS
void DocumentationView::showGant(){
    indexBeforeTimeLineView = mainContent->currentIndex();
    views->setCurrentIndex(viewTypeToIndex->value(ViewType::GANT_VIEW));
}

void DocumentationView::hideGant(){
    changeView(indexBeforeTimeLineView);
}

void DocumentationView::changeView(int index){
    emit save(currentView);
    ViewType nextView = (ViewType) views->currentData().toInt();
    emit update(nextView);
    mainContent->setCurrentIndex(index);
    currentView = nextView;
}

//GETTER / SETTER
ViewType DocumentationView::getCurrentView() const{
    return currentView;
}
