#ifndef AVRECORDCONTROL_H
#define AVRECORDCONTROL_H

#include <QMainWindow>
#include <QPushButton>

class AVRecordControl : public QMainWindow
{
    Q_OBJECT
public:
    explicit AVRecordControl(QWidget *parent = 0);

        QPushButton *btnSetAv;
        QPushButton *btnSetLeft;
        QPushButton *btnSetRight;
        QPushButton *btnSetLeftRight;

        QStringList *lstAV;
        QStringList *lstLeftAVs;
        QStringList *lstRightAVs;
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

private slots:
    void btnSetAVClicked();
    void btnSetLeftClicked();
    void btnSetRightClicked();
    void btnSetLeftRightClicked();

private:
    static const QString qssSelected;
    static const QString qssNotSelected;
};

#endif // AVRECORDCONTROL_H
