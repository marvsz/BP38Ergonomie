#include "documentationview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QIcon>
#include <QUrl>
#include <QList>
#include <QStringList>
#include "loadhandlingview.h"
#include "appliedforceview.h"
#include "executionconditionview.h"
#include "separator.h"

/**
 * @brief Constructs a DocumentationView widget which is a child of parent.
 * @param parent If parent is 0, the new widget becomes a window.
 * If parent is another widget, this widget becomes a child window inside parent.
 * The new widget is deleted when its parent is deleted.
 */
DocumentationView::DocumentationView(QWidget *parent) :
    QWidget(parent)
{
    // CAMERA BUTTON INITIALIZATION
    cameraButton = new QPushButton;
    cameraButton->setObjectName("cameraIcon");
    // !!!!!!!COMMENT TO ACTIVATE CAMERA!!!!!!!
    cameraButton->hide();
    connect(cameraButton, SIGNAL(clicked()), this, SLOT(showCamera()));

    // BACK BUTTON
    backButton = new QPushButton();
    backButton->setFixedSize(45, 45);
    backButton->setObjectName("leftIcon");
    connect(backButton, SIGNAL(clicked()), this, SLOT(backButtonClicked()));

    // INIT COMBOBOX
    QList<QString> viewNames = QList<QString>();
    viewNames.append(tr("body posture"));
    viewNames.append(tr("weight handling"));
    viewNames.append(tr("acting force"));
    viewNames.append(tr("conditions"));
    viewNames.append(tr("metadata"));
    this->views = new QComboBox();
    this->views->setMinimumSize(280, 40);
    this->views->addItems(QStringList(viewNames));


    indexBeforeTimeLineView = 0;

}

// PUBLIC

void DocumentationView::setBodyPostureView(BodyPostureView *bodyPostureView){
    this->bodyPostureView = bodyPostureView;
}

void DocumentationView::setLoadHandlingView(LoadHandlingView *loadHandlingView){
    this->loadHandlingView = loadHandlingView;
    connect(loadHandlingView, SIGNAL(showTransportationView()), this, SIGNAL(showTransportationView()));
}

void DocumentationView::setAppliedForceView(AppliedForceView *appliedForceView){
    this->appliedForceView = appliedForceView;
}

void DocumentationView::setExecutionConditionView(ExecutionConditionView *executionConditionView){
    this->executionConditionView = executionConditionView;
}

void DocumentationView::setWorkprocessMetaDataView(WorkProcessMetaDataView *workprocessMetaDataView){
    this->workprocessMetaDataView = workprocessMetaDataView;
    connect(workprocessMetaDataView, SIGNAL(showEquipmentView()), this, SIGNAL(showEquipmentView()));
}

void DocumentationView::setTimerViewController(TimerViewController *timerViewController){
    this->timerViewController = timerViewController;

    connect(timerViewController, SIGNAL(showGantView()), this, SLOT(showGant()));
    connect(timerViewController, SIGNAL(hideGantView()), this, SLOT(hideGant()));
}

void DocumentationView::setGantTimerView(GantTimerView *gantTimerView){
    this->gantView = gantTimerView;
    connect(gantTimerView, SIGNAL(workProcessSelected(int,AVType)), this, SLOT(workProcessSelectionChanged(int, AVType)));
}

void DocumentationView::setupViews(){
    mainContent = new QStackedWidget;

    mainContent->addWidget(bodyPostureView);
    mainContent->addWidget(loadHandlingView);
    mainContent->addWidget(appliedForceView);
    mainContent->addWidget(executionConditionView);
    mainContent->addWidget(workprocessMetaDataView);
    mainContent->addWidget(gantView);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QGridLayout *topLayout = new QGridLayout;
    topLayout->addWidget(backButton, 0, 0, 1, 1, Qt::AlignLeft);
    topLayout->addWidget(views, 0, 1, 1, 1, Qt::AlignHCenter);
    topLayout->addWidget(cameraButton, 0, 2, 1, 1, Qt::AlignRight);
    //Placeholder
    topLayout->addItem(new QSpacerItem(300, 45, QSizePolicy::Fixed, QSizePolicy::Fixed), 0, 2, 1, 1, 0);

    QVBoxLayout *centerLayout = new QVBoxLayout;
    centerLayout->addWidget(new Separator(Qt::Horizontal, 3, mainContent));
    centerLayout->addWidget(mainContent);

    QVBoxLayout *bottomLayout = new QVBoxLayout;
    bottomLayout->setContentsMargins(0, 0, 0, 0);
    bottomLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    bottomLayout->addWidget(timerViewController);

    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(centerLayout);
    mainLayout->addLayout(bottomLayout);

    this->setLayout(mainLayout);
    connect(views, SIGNAL(currentIndexChanged(int)), this, SLOT(changeView(int)));
}

// PRIVATE SLOTS
/**
 * @brief Opens a view for the the QML-Camera
 */
void DocumentationView::showCamera(){

    this->cameraView = new QQuickView();
    this->cameraView->setSource(QUrl("qrc:///declarative-camera.qml"));
    this->cameraView->setResizeMode(QQuickView::SizeRootObjectToView);
    this->cameraView->setFlags(Qt::FramelessWindowHint);
    connect(cameraView->engine(), SIGNAL(quit()), this, SLOT(hideCamera()));
    this->cameraView->show();
}

/**
 * @brief Closes the view for the the QML-Camera
 */
void DocumentationView::hideCamera(){
    this->cameraView->destroy();
}

void DocumentationView::leftAvPressed(){
    mainContent->setCurrentIndex(0);
}

void DocumentationView::rightAvPressed(){
    mainContent->setCurrentIndex(0);
}

void DocumentationView::avPressed(){
    mainContent->setCurrentIndex(0);
}

void DocumentationView::showGant(){
    emit updateGantView();
    indexBeforeTimeLineView = mainContent->currentIndex();
    changeView(5);
}

void DocumentationView::hideGant(){
    mainContent->setCurrentIndex(indexBeforeTimeLineView);
}

void DocumentationView::backButtonClicked(){
    emit showPreviousView();
}

void DocumentationView::workProcessSelectionChanged(int id, AVType type){
    changeView(0);
    bodyPostureView->setSelectedType(type);
}


void DocumentationView::changeView(int index){
    switch(lastIndex){
    case 0: emit saveBodyPostureView(); break;
    case 1: emit saveLoadHandlingView(); break;
    case 2: emit saveAppliedForceView(); break;
    case 3: emit saveExecutionConditionView(); break;
    case 4: emit saveWorkProcessMetaDataView(); break;
    case 5: emit saveFrequenz(); break;
    }
    switch(index){
    case 0: emit updateBodyPostureView(); break;
    case 1: emit updateLoadHandlingView(); break;
    case 2: emit updateAppliedForceView(); break;
    case 3: emit updateExecutionConditionView(); break;
    case 4: emit updateWorkProcessMetaDataView(); break;
    case 5: emit updateGantView(); break;
    }
    lastIndex = index;
    mainContent->setCurrentIndex(index);
    views->setCurrentIndex(index);
}
