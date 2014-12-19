#ifndef AVRECORDCONTROL_H
#define AVRECORDCONTROL_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>
#include <graphtimelineview.h>
#include <selectablevaluebutton.h>

class AVRecordControl : public QMainWindow
{
    Q_OBJECT
public:
    explicit AVRecordControl(QWidget *parent = 0);

    void btnAVClickedWithID(int id);
    void btnLeftClickedWithID(int id);
    void btnRightClickedWithID(int id);

        QLineEdit *avTime;
        SelectableValueButton *btnSelAV;
        SelectableValueButton *btnAV;
        SelectableValueButton *btnAVLeft;
        SelectableValueButton *btnAVRight;
        QPushButton *btnPlus;
        QPushButton *btnMinus;
        QPushButton *btnNextAV;
        QPushButton *btnPrevAV;
        SelectableValueButton *btnSetAv;
        SelectableValueButton *btnSetLeft;
        SelectableValueButton *btnSetRight;
        SelectableValueButton *btnSetLeftRight;

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

        QVBoxLayout *avSetLayout;
        GraphTimelineView *graphView;

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
};

#endif // AVRECORDCONTROL_H
