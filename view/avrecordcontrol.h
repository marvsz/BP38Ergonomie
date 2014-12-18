#ifndef AVRECORDCONTROL_H
#define AVRECORDCONTROL_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>
#include <graphtimelineview.h>

class AVRecordControl : public QMainWindow
{
    Q_OBJECT
public:
    explicit AVRecordControl(QWidget *parent = 0);

        QLineEdit *avTime;
        QPushButton *btnSelAV;
        QPushButton *btnAV;
        QPushButton *btnAVLeft;
        QPushButton *btnAVRight;
        QPushButton *btnPlus;
        QPushButton *btnMinus;
        QPushButton *btnNextAV;
        QPushButton *btnPrevAV;
        QPushButton *btnSetAv;
        QPushButton *btnSetLeft;
        QPushButton *btnSetRight;
        QPushButton *btnSetLeftRight;

        QList<bool> *lstAV;
        QList<bool> *lstLeftAVs;
        QList<bool> *lstRightAVs;
        QList<int> *lstAVTime;
        QList<int> *lstLeftAVTime;
        QList<int> *lstRightAVTime;

        bool leftPressed;
        bool rightPressed;
        bool avPressed;
        bool leftSelected;
        bool rightSelected;
        bool avSelected;
        bool stopped;
        bool windowMinimized;

        int totalAV;
        int totalLeftAV;
        int totalRightAV;
        int currentAV;
        int currentLeftAV;
        int currentRightAV;

public slots:
    int getTime(int currentAV);
    int getLeftRightTime(int currentAV, QString leftright);
    void updateAVs();
    void updateGraph();

private slots:
    void btnSetAVClicked();
    void btnSetLeftClicked();
    void btnSetRightClicked();
    void btnSetLeftRightClicked();
    void btnSelAVClicked();
    void btnAVClicked();
    void btnAVLeftClicked();
    void btnAVRightClicked();
    void btnPlusClicked();
    void btnMinusClicked();
    void btnNextAVClicked();
    void btnPrevAVClicked();

private:


    GraphTimelineView *graphView;

    static const QString qssSelected;
    static const QString qssNotSelected;
};

#endif // AVRECORDCONTROL_H
