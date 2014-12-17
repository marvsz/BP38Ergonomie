#include "documentationview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QIcon>
#include <QUrl>
#include <QList>
#include <QStringList>
#include "angleview.h"
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
    //QGridLayout *mainLayout = new QGridLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // CAMERA BUTTON INITIALIZATION
    cameraButton = new QPushButton;
    cameraButton->setObjectName("cameraButton");

    // NO FUNCTION YET
    backButton = new QPushButton("< Zurück");
    backButton->setMaximumSize(100, 40);
    backButton->setObjectName("backButton");

    // INIT COMBOBOX
    QList<QString> viewNames = QList<QString>();
    viewNames.append("Körperhaltung");
    viewNames.append("Lastenhandhabung");
    viewNames.append("Aktionskraft");
    viewNames.append("Ausführungbedingungen");
    this->views = new QComboBox();
    this->views->setMinimumSize(280, 40);
    this->views->addItems(QStringList(viewNames));

    // ADD DIFFERENT VIEWS TO STACKEDWIDGET
    mainContent = new QStackedWidget;
    mainContent->addWidget(new AngleView);
    mainContent->addWidget(new TransportView);
    mainContent->addWidget(new ActionForceView);
    mainContent->addWidget(new ExecutionConditionView);

    // CONNECT THE COMBOBOX TO THE STACKEDWIDGET
    connect(views, SIGNAL(currentIndexChanged(int)), mainContent, SLOT(setCurrentIndex(int)));

    // INCLUDE QML-CAMERA
    connect(cameraButton, SIGNAL(clicked()), this, SLOT(showCamera()));

    // ADD TIMER
    this->timer = new StopWatch;

    // GRID LAYOUT
    /*mainLayout->addWidget(backButton, 0, 0, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(views, 0, 1, 1, 1, Qt::AlignHCenter);
    mainLayout->addWidget(cameraButton, 0, 2, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 1, 0, 1, 3, 0);
    mainLayout->addWidget(mainContent, 2, 0, 1, 3, Qt::AlignTop);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 3, 0, 1, 3, 0);
    mainLayout->addWidget(timer, 4, 0, 1, 3,Qt::AlignBottom);
    setLayout(mainLayout);*/

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
