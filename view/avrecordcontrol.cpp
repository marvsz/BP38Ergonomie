#include "avrecordcontrol.h"

#include <QBoxLayout>

AVRecordControl::AVRecordControl(QWidget *parent) : QMainWindow(parent)
  , btnSetAv(new QPushButton("AV"))
  , btnSetLeft(new QPushButton("L"))
  , btnSetRight(new QPushButton("R"))
  , btnSetLeftRight(new QPushButton("L/R"))
  , lstAV(new QStringList)
  , lstLeftAVs(new QStringList)
  , lstRightAVs(new QStringList)
  , lstAVTime(new QList<int>)
  , lstLeftAVTime(new QList<int>)
  , lstRightAVTime(new QList<int>)
  , leftPressed(false)
  , rightPressed(false)
  , avPressed(false)
  , avSelected(true)
  , leftSelected(false)
  , rightSelected(false)
  , stopped(false)
  , totalAV(0)
  , totalLeftAV(0)
  , totalRightAV(0)
  , currentAV(0)
  , currentLeftAV(0)
  , currentRightAV(0)
{
    QWidget *main = new QWidget();

    QVBoxLayout *avSetLayout = new QVBoxLayout();

    avSetLayout->addWidget(btnSetLeft);
    avSetLayout->addWidget(btnSetRight);
    avSetLayout->addWidget(btnSetAv);

    main->setLayout(avSetLayout);
    this->setCentralWidget(main);

    btnSetAv->setFixedSize(45,45);
    btnSetLeft->setFixedSize(45,45);
    btnSetRight->setFixedSize(45,45);
    btnSetLeftRight->setFixedSize(45, 100);

    btnSetAv->setEnabled(false);

    connect(btnSetAv, SIGNAL(clicked()), SLOT(btnSetAVClicked()));
    connect(btnSetLeft, SIGNAL(clicked()), SLOT(btnSetLeftClicked()));
    connect(btnSetRight, SIGNAL(clicked()), SLOT(btnSetRightClicked()));
    connect(btnSetLeftRight, SIGNAL(clicked()), SLOT(btnSetLeftRightClicked()));
}
    const QString AVRecordControl::qssSelected = "QPushButton {font: 100 20px \"Serif\";color: #FFFFFF; border: 2px solid #007aff; border-radius: 10px; background-color: #007aff;} QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}";
    const QString AVRecordControl::qssNotSelected = "QPushButton {font: 100 20px \"Serif\";color: #007aff; border: 2px solid #007aff; border-radius: 10px; background-color: #f5f5f5;} QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}";

    /**
     * @brief sets a new AV, saves the time and enables necessary buttons
     */
    void AVRecordControl::btnSetAVClicked(){
        totalAV++;
        currentAV = totalAV;

        QString str;
        str.append(QString("%1").arg(currentAV));
        //btnSelAV->setText("AV " + str);
        lstAVTime->append(getTime(currentAV));

        int t = lstAVTime->at(currentAV -1);
        unsigned int m = (t/ 60);
        unsigned int s = (t - 60*m);
        const QString diff = QString("%1:%2")
        .arg(m, 2, 10, QChar('0'))
        .arg(s, 2, 10, QChar('0'));
        //avTime->setText(diff);

        /*btnSelAV->setEnabled(true);
        btnAV->setEnabled(true);
        avTime->setEnabled(true);
        btnPlus->setEnabled(true);
        btnMinus->setEnabled(true);*/

        avSelected = true;
        leftSelected = false;
        rightSelected = false;

        //btnAV->setStyleSheet(qssSelected);
        //btnAVLeft->setStyleSheet(qssNotSelected);
        //btnAVRight->setStyleSheet(qssNotSelected);

        /*if(totalAV > 1)
            btnPrevAV->setEnabled(true);
        btnNextAV->setEnabled(false);*/

        avPressed = true;
    }

    /**
     * @brief sets a new left AV, saves the time and enables necessary buttons, if button was selected
     * otherwise selects button
     */
    void AVRecordControl::btnSetLeftClicked(){
        if(leftPressed){
            leftPressed = false;
            btnSetLeft->setStyleSheet(this->qssNotSelected);
            totalLeftAV++;
            currentLeftAV = totalLeftAV;
            lstLeftAVTime->append(getLeftRightTime(currentLeftAV, "left"));
            //btnAVLeft->setEnabled(true);
            btnSetLeftRight->setStyleSheet(this->qssNotSelected);
            //btnPlus->setEnabled(true);
            //btnMinus->setEnabled(true);
        }
        else {
            leftPressed = true;
            btnSetLeft->setStyleSheet(this->qssSelected);
            if(rightPressed)
                btnSetLeftRight->setStyleSheet(this->qssSelected);
        }
    }

    /**
     * @brief sets a new right AV, saves the time and enables necessary buttons, if button was selected
     * otherwise, selects button
     */
    void AVRecordControl::btnSetRightClicked(){
        if(rightPressed){
            rightPressed = false;
            btnSetRight->setStyleSheet(this->qssNotSelected);
            totalRightAV++;
            currentRightAV = totalRightAV;
            lstRightAVTime->append(getLeftRightTime(currentRightAV, "right"));
            //btnAVRight->setEnabled(true);
            btnSetLeftRight->setStyleSheet(this->qssNotSelected);
            //btnPlus->setEnabled(true);
            //btnMinus->setEnabled(true);
        }
        else {
            rightPressed = true;
            btnSetRight->setStyleSheet(this->qssSelected);
            if(leftPressed)
                btnSetLeftRight->setStyleSheet(this->qssSelected);
        }
    }

    /**
     * @brief sets new left and right AVs, if buttons were selected,
     * otherwise selects the buttons
     */
    void AVRecordControl::btnSetLeftRightClicked(){
        if(rightPressed && leftPressed){
            rightPressed = false;
            leftPressed = false;
            btnSetRight->setStyleSheet(this->qssNotSelected);
            totalRightAV++;
            currentRightAV = totalRightAV;
            lstRightAVTime->append(getLeftRightTime(currentRightAV, "right"));
            btnSetLeft->setStyleSheet(this->qssNotSelected);
            totalLeftAV++;
            currentLeftAV = totalLeftAV;
            lstLeftAVTime->append(getLeftRightTime(currentLeftAV, "left"));
            btnSetLeftRight->setStyleSheet(this->qssNotSelected);
            //btnAVLeft->setEnabled(true);
            //btnAVRight->setEnabled(true);
        }
        else {
            rightPressed = true;
            leftPressed = true;
            btnSetRight->setStyleSheet(this->qssSelected);
            btnSetLeft->setStyleSheet(this->qssSelected);
            btnSetLeftRight->setStyleSheet(this->qssSelected);
        }
    }

    /**
     * @brief updates the lists of the AVs
     */
    void AVRecordControl::updateAVs(){
        if(stopped){
           lstAV->append("true");
           lstLeftAVs->append("false");
           lstRightAVs->append("false");
        }
        if(avPressed){
            lstAV->append("true");
            avPressed = false;
        }
        else
            lstAV->append("false");

        if(leftPressed)
            lstLeftAVs->append("true");
        else
            lstLeftAVs->append("false");
        if(rightPressed)
            lstRightAVs->append("true");
        else
            lstRightAVs->append("false");
    }

    /**
     * @brief calculates the time of the given AV
     * @param currentAV, the AV of which the time is to be returned
     * @return time of currentAV
     */
    int AVRecordControl::getTime(int currentAV){
        int avCount = 0;
        int secs = 0;
        for(int i = 1; i < lstAV->count(); ++i){
           QString s = lstAV->at(i);
           if(avCount == (currentAV -1)){
               if(s == "true"){
                  avCount++;
               }
               else
                   secs++;

           }
           else {
              if(s == "true")
                  avCount++;
           }
        }
        return secs +1;
    }

    /**
     * @brief calculates the time of the given AV
     * @param currentAV, the AV of which the time is to be returned
     * @param leftright, "left" if currentAV is a left AV, "right" if currentAV is a right AVs
     * @return time of currentAV
     */
    int AVRecordControl::getLeftRightTime(int currentAV, QString leftright){
        int avCount = 0;
        int secs = 0;
        if(leftright == "left"){
            for(int i = 1; i < lstLeftAVs->count() -1; ++i){
                QString s = lstLeftAVs->at(i);
                if(avCount == (currentAV -1)){
                    if(s == "true" && lstLeftAVs->at(i +1) == "false"){
                        avCount++;
                    }
                    else if(s == "true")
                        secs++;
                }
                else if(s == "true" && lstLeftAVs->at(i +1) == "false")
                    avCount++;
            }
        }
        else {
            for(int i = 1; i < lstRightAVs->count() -1; ++i){
                QString s = lstRightAVs->at(i);
                if(avCount == (currentAV -1)){
                    if(s == "true" && lstRightAVs->at(i +1) == "false"){
                        avCount++;
                    }
                    else if(s == "true")
                        secs++;
                }
                else if(s == "true" && lstRightAVs->at(i +1) == "false")
                    avCount++;
            }
        }
        return secs +1;
    }
