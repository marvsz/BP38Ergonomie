#if defined(Q_OS_IOS)
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
    void btnSaveClicked();
    void btnDiscardClicked();

private:
    bool isRecording;
    int currentCamera;
    QThread captureThread;
    QThread converterThread;
    ImageViewer viewer;
    Capture capture;
    Converter converter;

    QPushButton *btnCapture;
    //QPushButton *btnStartRecording;
    QPushButton *btnSwitchCamera;
    QPushButton *btnSave;
    QPushButton *btnDiscard;
};

#endif // CAMERAPOPUP_H
#endif
