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

private:
    int currentCamera;
    QThread captureThread;
    QThread converterThread;
    ImageViewer viewer;
    Capture capture;
    Converter converter;

    QPushButton *btnCapture;
    QPushButton *btnSwitchCamera;
};

#endif // CAMERAPOPUP_H
