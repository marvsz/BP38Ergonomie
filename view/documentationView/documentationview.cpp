#include "documentationview.h"
#include <QVBoxLayout>
#include "../separator.h"

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
    btnCamera(new QPushButton(this)),
    views(new QComboBox(this)),
    mainContent(new QStackedWidget(this)),
    mainLayout(new QVBoxLayout),
    viewTypeToWidget(new QHash<ViewType, TitledWidget*>()),
    viewTypeToIndex(new QHash<ViewType, int>())
{
    btnCamera->setObjectName("cameraIcon");
    btnCamera->setFixedSize(45, 45);
    connect(btnCamera, SIGNAL(clicked()), this, SLOT(btnCameraClicked()));

    views->setMinimumSize(280, 40);
    connect(views, SIGNAL(currentIndexChanged(int)), this, SLOT(changeView(int)));

    mainLayout->addWidget(mainContent);

    setLayout(mainLayout);
}

// PUBLIC
QList<QAbstractButton*> * DocumentationView::getAdditionalNavigation() const {
    QList<QAbstractButton*> *additions = new QList<QAbstractButton*>();
    additions->append(btnCamera);
    return additions;
}

void DocumentationView::showStartView(ViewType type){
    if(viewTypeToIndex->contains(type)){
        currentView = type;
        views->setCurrentIndex(viewTypeToIndex->value(type));
    }
}

void DocumentationView::registerView(TitledWidget *widget, ViewType type){
    if(!viewTypeToIndex->contains(type) && widget != 0){
        viewTypeToWidget->insert(type, widget);
        viewTypeToIndex->insert(type, mainContent->addWidget(widget));
        views->addItem(widget->getTitle(), type);
        connect(widget, SIGNAL(showView(ViewType)), this, SIGNAL(showView(ViewType)));
        connect(widget, SIGNAL(showPopUp(PopUpType)), this, SIGNAL(showPopUp(PopUpType)));
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
    emit save((ViewType) views->currentData().toInt());
    timerViewController->closeTimerView();
}


// PRIVATE SLOTS
void DocumentationView::btnCameraClicked(){
    emit showPopUp(PopUpType::CAMERA_POPUP);
}

void DocumentationView::showGant(){
    indexBeforeTimeLineView = mainContent->currentIndex();
    views->setCurrentIndex(viewTypeToIndex->value(ViewType::GANT_VIEW));
}

void DocumentationView::hideGant(){
    if(currentView == ViewType::GANT_VIEW)
        views->setCurrentIndex(indexBeforeTimeLineView);
}

void DocumentationView::changeView(int index){
    if(viewTypeToIndex->contains(currentView)){
        viewTypeToWidget->value(currentView)->onLeaving();
        if(currentView == GANT_VIEW)
            timerViewController->gantViewHidden();
        emit save(currentView);
    }
    ViewType nextView = (ViewType) views->currentData().toInt();
    if(viewTypeToIndex->contains(nextView)){
        emit update(nextView);
        mainContent->setCurrentIndex(index);
        currentView = nextView;
        viewTypeToWidget->value(nextView)->onEnter();
    }
}

//GETTER / SETTER
ViewType DocumentationView::getCurrentView() const{
    return currentView;
}
