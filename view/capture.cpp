#include "capture.h"
#include <QVector>
#include <QTimerEvent>
#include <QDebug>
#include <QDateTime>
#include "../standardpaths.h"
#include <string>

Capture::Capture(QObject *parent) :
    QObject(parent)
{
}

void Capture::start(int cam){
    if(!this->videoCapture){
        this->videoCapture.reset(new cv::VideoCapture(cam));
        currentCamera = cam;
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

QString Capture::startRecording(){
    /*cv::Size s = cv::Size((int) videoCapture->get(CV_CAP_PROP_FRAME_WIDTH),
                  (int) videoCapture->get(CV_CAP_PROP_FRAME_HEIGHT));

    videoWriter.reset(new cv::VideoWriter());
    QString timestamp = QDateTime::currentDateTime().toString("dd-MM-yy-hh-mm-ss");
    QString filePath = QString("%1%2%3%4").arg(StandardPaths::writeableLocation()).arg("/video-").arg(timestamp).arg(".avi");
    int codec = videoCapture->get(cv::CAP_PROP_FOURCC);
    videoWriter->open(cv::String(filePath.toLocal8Bit().data()), codec, videoCapture->get(cv::CAP_PROP_FPS), s, true);
    if(!videoWriter->isOpened())
            qDebug() << "failed";

    cv::Mat frame;
    this->recording = true;
    while(this->recording){
        videoCapture->read(frame);
        qDebug() << "Read Frame";
        videoWriter->write(frame);
        qDebug() << "Wrote Frame";
    }
    return filePath;*/
    return "";
}

void Capture::stopRecording(){
    /*this->recording = false;
    this->videoWriter->release();*/
}

void Capture::switchCam(){
    currentCamera = (currentCamera + 1) % 2;
    this->videoCapture.reset(new cv::VideoCapture(currentCamera));
    videoCapture->open(currentCamera);
}
