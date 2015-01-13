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
}

void DocumentationView::setAppliedForceView(AppliedForceView *appliedForceView){
    this->appliedForceView = appliedForceView;
}

void DocumentationView::setExecutionConditionView(ExecutionConditionView *executionConditionView){
    this->executionConditionView = executionConditionView;
}

void DocumentationView::setWorkprocessMetaDataView(WorkProcessMetaDataView *workprocessMetaDataView){
    this->workprocessMetaDataView = workprocessMetaDataView;
}

void DocumentationView::setTimerViewController(TimerViewController *timerViewController){
    this->timerViewController = timerViewController;

    connect(timerViewController, SIGNAL(showGantView()), this, SLOT(showGant()));
    connect(timerViewController, SIGNAL(hideGantView()), this, SLOT(hideGant()));
    connect(timerViewController, SIGNAL(createWorkProcess(int,QTime,QTime)), this, SIGNAL(createWorkProcess(int,QTime,QTime)));
}

void DocumentationView::setGantTimerView(GantTimerView *gantTimerView){
    this->gantView = gantTimerView;

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
    connect(views, SIGNAL(currentIndexChanged(int)), mainContent, SLOT(setCurrentIndex(int)));
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
    indexBeforeTimeLineView = mainContent->currentIndex();
    mainContent->setCurrentIndex(5);
}

void DocumentationView::hideGant(){
    mainContent->setCurrentIndex(indexBeforeTimeLineView);
}

void DocumentationView::backButtonClicked(){
    emit showPreviousView();
}
