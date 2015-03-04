#include "camerapopup.h"
#include <QGridLayout>
#include <QDebug>

CameraPopUp::CameraPopUp(QWidget *parent) :
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Camera"), parent),
    btnCapture(new QPushButton(this)),
    btnSwitchCamera(new QPushButton(this))
{
    btnCapture->setFixedSize(60, 60);
    btnCapture->setObjectName("cameraIcon");
    connect(btnCapture, SIGNAL(clicked()), this, SLOT(btnCaptureClicked()));

    btnSwitchCamera->setFixedSize(60, 60);
    btnSwitchCamera->setObjectName("rotationIcon");
    connect(btnSwitchCamera, SIGNAL(clicked()), this, SLOT(btnSwitchCameraClicked()));
    btnSwitchCamera->setEnabled(false);//capture.cameraCount() > 1);
    converter.setProcessAll(false);

    connect(&capture, SIGNAL(matReady(cv::Mat, int)), &converter, SLOT(processFrame(cv::Mat, int)));
    connect(&converter, SIGNAL(imageReady(QImage)), &viewer, SLOT(setImage(QImage)));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(&viewer, 0, 0, 2, 1, Qt::AlignCenter);
    mainLayout->addWidget(btnCapture, 0, 1, 1, 1, Qt::AlignCenter);
    mainLayout->addWidget(btnSwitchCamera, 1, 1, 1, 1, Qt::AlignCenter);
    this->setLayout(mainLayout);
}

CameraPopUp::~CameraPopUp(){

}

void CameraPopUp::onEnter(){
    QMetaObject::invokeMethod(&capture, "start", Q_ARG(int, 0));
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
    QString path = viewer.saveImage();
    if(path != NULL){
        showMessage(tr("Photo Saved"), NotificationMessage::ACCEPT);
        qDebug() << path;
    }
    else
        showMessage(tr("Saving Photo Failed!"), NotificationMessage::ERROR);
}

void CameraPopUp::btnSwitchCameraClicked(){
    capture.switchCam();
    QMetaObject::invokeMethod(&capture, "start", Q_ARG(int, capture.currentCam()));
}
