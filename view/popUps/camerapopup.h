#if defined(Q_OS_IOS) || defined(Q_OS_ANDROID)
#ifndef CAMERAPOPUP_H
#define CAMERAPOPUP_H

#include "../navigation/abstractpopupwidget.h"
#include "../imageviewer.h"
#include "../capture.h"
#include "../converter.h"
#include <QThread>
#include <QPushButton>

class CameraPopUp : public AbstractPopUpWidget
{
    Q_OBJECT
public:
    explicit CameraPopUp(QWidget *parent = 0);
    ~CameraPopUp();

signals:

public slots:
    void onEnter();
    void onLeaving();

private slots:
    void btnCaptureClicked();
    void btnSwitchCameraClicked();
    void btnStartRecordingClicked();

private:
    bool isRecording;
    int currentCamera;
    QThread captureThread;
    QThread converterThread;
    ImageViewer viewer;
    Capture capture;
    Converter converter;

    QPushButton *btnCapture;
    QPushButton *btnStartRecording;
    QPushButton *btnSwitchCamera;
};

#endif // CAMERAPOPUP_H
#endif
