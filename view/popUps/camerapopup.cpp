#include "camerapopup.h"
#include <QGridLayout>
#include <QDebug>

CameraPopUp::CameraPopUp(QWidget *parent) :
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Camera"), parent),
    btnCapture(new QPushButton(this)),
    btnSwitchCamera(new QPushButton(this))
{
    btnCapture->setFixedSize(45 ,45);
    btnCapture->setObjectName("cameraIcon");
    connect(btnCapture, SIGNAL(clicked()), this, SLOT(btnCaptureClicked()));

    btnSwitchCamera->setFixedSize(45, 45);
    btnSwitchCamera->setObjectName("rotationIcon");
    connect(btnSwitchCamera, SIGNAL(clicked()), this, SLOT(btnSwitchCameraClicked()));

    converter.setProcessAll(false);

    connect(&capture, SIGNAL(matReady(cv::Mat, int)), &converter, SLOT(processFrame(cv::Mat, int)));
    connect(&converter, SIGNAL(imageReady(QImage)), &viewer, SLOT(setImage(QImage)));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(&viewer, 0, 0, 1, 2, Qt::AlignCenter);
    mainLayout->addWidget(btnCapture, 1, 0, 1, 1, Qt::AlignCenter);
    mainLayout->addWidget(btnSwitchCamera, 1, 1, 1, 1, Qt::AlignCenter);
    this->setLayout(mainLayout);
}

CameraPopUp::~CameraPopUp(){

}

void CameraPopUp::onEnter(){
    QMetaObject::invokeMethod(&capture, "start");
    captureThread.start();
    converterThread.start();
    capture.moveToThread(&captureThread);
    converter.moveToThread(&converterThread);
}

void CameraPopUp::onLeaving(){
    QMetaObject::invokeMethod(&capture, "stop");
    captureThread.quit();
    converterThread.quit();
}

void CameraPopUp::btnCaptureClicked(){
    bool success = viewer.saveImage();
    if(success)
        showMessage(tr("Photo Saved"), NotificationMessage::ACCEPT);
    else
        showMessage(tr("Saving Photo Failed!"), NotificationMessage::ERROR);
}

void CameraPopUp::btnSwitchCameraClicked(){
    QMetaObject::invokeMethod(&capture, "stop");
    capture.switchCam();
    QMetaObject::invokeMethod(&capture, "start", Q_ARG(int, capture.currentCam()));
}
