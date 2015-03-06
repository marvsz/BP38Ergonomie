#include "converter.h"
#include <QDebug>
#include <QPixmap>
#include <QPainter>

Converter::Converter(QObject *parent) :
    QObject(parent),
    processAll(true)
{
}

void Converter::matDeleter(void* mat){
    delete static_cast<cv::Mat*>(mat);
}

void Converter::queue(const cv::Mat &frame, int cam){
    this->frame = frame;
    this->cam = cam;
    if(!this->timer.isActive())
        this->timer.start(0, this);
}

void Converter::process(cv::Mat frame, int cam){
    //cv::resize(frame, frame, cv::Size(), 1.3, 1.3, cv::INTER_AREA);
    if(frame.rows > frame.cols){
        cv::transpose(frame, frame);
        cv::flip(frame, frame, 0);
        if (cam == 1){
            cv::Point2f center(frame.cols/2.0F, frame.rows/2.0F);
            cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, 180, 1.0);
            cv::warpAffine(frame, frame, rotationMatrix, frame.size());
        }
    }
    cv::cvtColor(frame, frame, CV_BGR2RGB);
    const QImage image(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888, &matDeleter, new cv::Mat(frame));
    emit imageReady(image);
}

void Converter::timerEvent(QTimerEvent *ev){
    if(ev->timerId() != this->timer.timerId())
        return;
    process(this->frame, this->cam);
    this->frame.release();
    this->timer.stop();
}

void Converter::setProcessAll(bool all){
    processAll = all;
}

void Converter::processFrame(const cv::Mat &frame, int cam){
    if(this->processAll)
        process(frame, cam);
    else
        queue(frame, cam);
}
