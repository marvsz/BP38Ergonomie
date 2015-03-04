#ifndef CAPTURE_H
#define CAPTURE_H

#include <QObject>
#include <QBasicTimer>
#include <QScopedPointer>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class Capture : public QObject
{
    Q_OBJECT
public:
    explicit Capture(QObject *parent = 0);

    static int cameraCount();
    int currentCam();

signals:
    void started();
    void matReady(const cv::Mat &, int cam);

public slots:
    void start(int cam = 0);
    void stop();
    void switchCam();

private:
    int currentCamera;
    QBasicTimer timer;
    QScopedPointer<cv::VideoCapture> videoCapture;

    void timerEvent(QTimerEvent * ev);
};

#endif // CAPTURE_H
