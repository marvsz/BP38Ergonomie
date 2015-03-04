#include "capture.h"
#include <QTimerEvent>
#include <QDebug>

Capture::Capture(QObject *parent) :
    QObject(parent)
{
}

void Capture::start(int cam){
    if(!this->videoCapture){
        this->videoCapture.reset(new cv::VideoCapture(cam));
        currentCamera = cam;
        qDebug() << "camera started " << currentCamera;
    }
    if (this->videoCapture->isOpened()) {
        this->timer.start(0, this);
        emit started();
    }
}


void Capture::stop(){
    this->timer.stop();
}

void Capture::timerEvent(QTimerEvent * ev) {
    if (ev->timerId() != timer.timerId()) return;
    cv::Mat frame;
    if (!this->videoCapture->read(frame)) { // Blocks until a new frame is ready
        this->timer.stop();
        return;
    }
    emit matReady(frame, currentCamera);
}


int Capture::cameraCount(){
    cv::VideoCapture tempCam(1);
    bool res = (tempCam.isOpened());
    qDebug() << res;
    tempCam.release();
    return res ? 2 : 1;
}

int Capture::currentCam(){
    return this->currentCamera;
}

void Capture::switchCam(){
    currentCamera = (currentCamera + 1) % 2;
    videoCapture->open(currentCamera);
}
