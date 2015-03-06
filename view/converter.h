#ifndef CONVERTER_H
#define CONVERTER_H

#include <QObject>
#include <QBasicTimer>
#include <QTimerEvent>
#include <QImage>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>


class Converter : public QObject
{
    Q_OBJECT
public:
    explicit Converter(QObject *parent = 0);
    void setProcessAll(bool all);

signals:
    void imageReady(const QImage &);

public slots:
    void processFrame(const cv::Mat &frame, int cam);

private:
    QBasicTimer timer;
    cv::Mat frame;
    int cam;
    bool processAll;

    static void matDeleter(void* mat);
    void queue(const cv::Mat &frame, int cam);
    void process(cv::Mat frame, int cam);
    void timerEvent(QTimerEvent *ev);
};

#endif // CONVERTER_H
