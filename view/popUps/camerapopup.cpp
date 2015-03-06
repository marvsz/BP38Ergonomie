#include "camerapopup.h"
#include <QGridLayout>
#include <QDebug>

CameraPopUp::CameraPopUp(QWidget *parent) :
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Camera"), parent),
    isRecording(false),
    btnCapture(new QPushButton(this)),
    //btnStartRecording(new QPushButton(this)),
    btnSwitchCamera(new QPushButton(this)),
    btnSave(new QPushButton(this)),
    btnDiscard(new QPushButton(this))
{
    btnCapture->setFixedSize(70, 70);
    btnCapture->setObjectName("captureIcon");
    connect(btnCapture, SIGNAL(clicked()), this, SLOT(btnCaptureClicked()));

    //btnStartRecording->setFixedSize(60, 60);
    //btnStartRecording->setObjectName("recordIcon");
    //connect(btnStartRecording, SIGNAL(clicked()), this, SLOT(btnStartRecordingClicked()));

    btnSwitchCamera->setFixedSize(70, 70);
    btnSwitchCamera->setObjectName("switchCameraIcon");
    connect(btnSwitchCamera, SIGNAL(clicked()), this, SLOT(btnSwitchCameraClicked()));
    btnSwitchCamera->setEnabled(capture.cameraCount() > 1); // setEnabled(false);//

    btnSave->setFixedSize(70, 70);
    btnSave->setObjectName("savePhotoIcon");
    connect(btnSave, SIGNAL(clicked()), this, SLOT(btnSaveClicked()));

    btnDiscard->setFixedSize(70, 70);
    btnDiscard->setObjectName("errorIcon");
    connect(btnDiscard, SIGNAL(clicked()), this, SLOT(btnDiscardClicked()));

    converter.setProcessAll(false);

    connect(&capture, SIGNAL(matReady(cv::Mat, int)), &converter, SLOT(processFrame(cv::Mat, int)));
    connect(&converter, SIGNAL(imageReady(QImage)), &viewer, SLOT(setImage(QImage)));

    btnSave->setVisible(false);
    btnDiscard->setVisible(false);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(&viewer, 0, 0, 3, 1, Qt::AlignCenter);
    mainLayout->addWidget(btnCapture, 0, 1, 1, 1, Qt::AlignCenter);
    mainLayout->addWidget(btnSave, 0, 1, 1, 1, Qt::AlignCenter);
    //mainLayout->addWidget(btnStartRecording, 1, 1, 1, 1, Qt::AlignCenter);
    mainLayout->addWidget(btnSwitchCamera, 2, 1, 1, 1, Qt::AlignCenter);
    mainLayout->addWidget(btnDiscard, 2, 1, 1, 1, Qt::AlignCenter);
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

void CameraPopUp::btnSwitchCameraClicked(){
    QMetaObject::invokeMethod(&capture, "stop");
    capture.switchCam();
    QMetaObject::invokeMethod(&capture, "start", Q_ARG(int, capture.currentCam()));
}

void CameraPopUp::btnCaptureClicked(){
    capture.blockSignals(true);
    btnCapture->setVisible(false);
    btnSwitchCamera->setVisible(false);
    btnSave->setVisible(true);
    btnDiscard->setVisible(true);
}

void CameraPopUp::btnSaveClicked(){
    QString path = viewer.saveImage();
    if(path != NULL)
        showMessage(tr("Photo Saved"), NotificationMessage::ACCEPT);
    else
        showMessage(tr("Saving Photo Failed!"), NotificationMessage::ERROR);

    btnCapture->setVisible(true);
    btnSwitchCamera->setVisible(true);
    btnSave->setVisible(false);
    btnDiscard->setVisible(false);
    capture.blockSignals(false);
}

void CameraPopUp::btnDiscardClicked(){
    showMessage(tr("Photo Discarded"), NotificationMessage::ACCEPT);
    btnCapture->setVisible(true);
    btnSwitchCamera->setVisible(true);
    btnSave->setVisible(false);
    btnDiscard->setVisible(false);
    capture.blockSignals(false);
}

void CameraPopUp::btnStartRecordingClicked() {
   /* QString path;
    if(!isRecording)
        path = capture.startRecording();
    else
        capture.stopRecording();
        if(path != NULL){
            showMessage(tr("Video Saved"), NotificationMessage::ACCEPT);
            qDebug() << path;
        }
        else
            showMessage(tr("Saving Video Failed!"), NotificationMessage::ERROR);*/
}


