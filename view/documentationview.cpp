#include "documentationview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QIcon>
#include <QUrl>
#include <QList>
#include <QStringList>
#include "transportview.h"
#include "actionforceview.h"
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
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // CAMERA BUTTON INITIALIZATION
    cameraButton = new QPushButton;
    cameraButton->setObjectName("btnCamera");

    // NO FUNCTION YET
    backButton = new QPushButton(tr("< back"));
    backButton->setMaximumSize(100, 40);
    backButton->setObjectName("btnNavigation");
    connect(backButton, SIGNAL(clicked()), this, SLOT(backButtonClicked()));

    // INIT COMBOBOX
    QList<QString> viewNames = QList<QString>();
    viewNames.append(tr("body posture"));
    viewNames.append(tr("weight handling"));
    viewNames.append(tr("acting force"));
    viewNames.append(tr("conditions"));
    this->views = new QComboBox();
    this->views->setMinimumSize(280, 40);
    this->views->addItems(QStringList(viewNames));

    // ADD DIFFERENT VIEWS TO STACKEDWIDGET
    mainContent = new QStackedWidget;
    angleView = new AngleView;
    btnTimeLineView = new ButtonTimelineView;
    mainContent->addWidget(angleView);
    mainContent->addWidget(new TransportView);
    mainContent->addWidget(new ActionForceView);
    mainContent->addWidget(new ExecutionConditionView);
    mainContent->addWidget(btnTimeLineView);

    // CONNECT THE COMBOBOX TO THE STACKEDWIDGET
    connect(views, SIGNAL(currentIndexChanged(int)), mainContent, SLOT(setCurrentIndex(int)));

    // INCLUDE QML-CAMERA
    connect(cameraButton, SIGNAL(clicked()), this, SLOT(showCamera()));

    // ADD TIMER
    this->timer = new StopWatch(btnTimeLineView);
    connect(timer, SIGNAL(leftAvPressed()), this, SLOT(leftAvPressed()));
    connect(timer, SIGNAL(rightAvPressed()), this, SLOT(rightAvPressed()));
    connect(timer, SIGNAL(avPressed()), this, SLOT(avPressed()));
    connect(timer, SIGNAL(maximizePressed()), this, SLOT(maximizeBtnTimeLineView()));
    connect(timer, SIGNAL(minimizePressed()), this, SLOT(minimizeBtnTimeLineView()));
    indexBeforeTimeLineView = 0;

    QGridLayout *topLayout = new QGridLayout;
    topLayout->addWidget(backButton, 0, 0, 1, 1, Qt::AlignLeft);
    topLayout->addWidget(views, 0, 1, 1, 1, Qt::AlignHCenter);
    topLayout->addWidget(cameraButton, 0, 2, 1, 1, Qt::AlignRight);

    QVBoxLayout *centerLayout = new QVBoxLayout;
    centerLayout->addWidget(new Separator(Qt::Horizontal, 3, mainContent));
    centerLayout->addWidget(mainContent);

    QVBoxLayout *bottomLayout = new QVBoxLayout;
    bottomLayout->addWidget(new Separator(Qt::Horizontal, 3, timer));
    bottomLayout->addWidget(timer);

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(centerLayout);
    mainLayout->addLayout(bottomLayout);

    this->setLayout(mainLayout);

}

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
    angleView->selectLeftAV();
}

void DocumentationView::rightAvPressed(){
    mainContent->setCurrentIndex(0);
    angleView->selectRightAV();
}

void DocumentationView::avPressed(){
    mainContent->setCurrentIndex(0);
    angleView->selectAV();
}

void DocumentationView::maximizeBtnTimeLineView(){
    indexBeforeTimeLineView = mainContent->currentIndex();
    mainContent->setCurrentIndex(4);
}

void DocumentationView::minimizeBtnTimeLineView(){
    mainContent->setCurrentIndex(indexBeforeTimeLineView);
}

void DocumentationView::backButtonClicked(){
    emit showPreviousView();
}
