#include "avrecordcontrol.h"

#include <QBoxLayout>

/**
 * @brief constructs a new RecordControl responsible for keeping track
 * of all AVs and selecting AVs
 * @param parent
 */
AVRecordControl::AVRecordControl(QWidget *parent) : QMainWindow(parent)
  , btnSetAv(new SelectableValueButton(10,0))
  , btnSetLeft(new SelectableValueButton(11,0))
  , btnSetRight(new SelectableValueButton(12,0))
  , btnSetLeftRight(new SelectableValueButton(13,0))
  , lstAV(new QList<bool>)
  , lstLeftAVs(new QList<bool>)
  , lstRightAVs(new QList<bool>)
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
  , windowMinimized(false)
  , totalAV(0)
  , totalLeftAV(0)
  , totalRightAV(0)
  , currentAV(0)
  , currentLeftAV(0)
  , currentRightAV(0)
  , avTime(new QLineEdit("00:00"))
  , btnSelAV(new SelectableValueButton(0,0))
  , btnAV(new SelectableValueButton(1,0))
  , btnAVLeft(new SelectableValueButton(2,0))
  , btnAVRight(new SelectableValueButton(3,0))
  , btnPlus(new QPushButton("+"))
  , btnMinus(new QPushButton("-"))
  , btnNextAV(new QPushButton(">"))
  , btnPrevAV(new QPushButton("<"))
  , graphView(new GraphTimelineView)
{
    QWidget *main = new QWidget();

    QHBoxLayout *mainLayout = new QHBoxLayout();
    QVBoxLayout *avSetLayout = new QVBoxLayout();

    avSetLayout->addWidget(btnSetLeft);
    avSetLayout->addWidget(btnSetRight);
    avSetLayout->addWidget(btnSetAv);

    mainLayout->addWidget(graphView);
    mainLayout->addLayout(avSetLayout);

    main->setLayout(mainLayout);
    this->setCentralWidget(main);
    this->setFixedHeight(175);

    btnSetAv->setFixedSize(45,45);
    btnSetLeft->setFixedSize(45,45);
    btnSetRight->setFixedSize(45,45);
    btnSetLeftRight->setFixedSize(45, 100);

    btnSetAv->setEnabled(false);

    btnPlus->setFixedSize(45,45);
    btnMinus->setFixedSize(45,45);
    btnNextAV->setFixedSize(45,45);
    btnPrevAV->setFixedSize(45,45);
    btnAVLeft->setFixedSize(70, 45);
    btnAVRight->setFixedSize(70, 45);
    btnAV->setFixedSize(70, 45);
    btnSelAV->setFixedSize(105, 45);
    avTime->setFixedSize(105,45);
    avTime->setInputMask("00:99");
    avTime->setAlignment(Qt::AlignCenter);

    btnSetAv->setText("AV");
    btnSetLeft->setText("L");
    btnSetRight->setText("R");
    btnSetLeftRight->setText("L/R");

    btnAV->setText("AV");
    btnAVLeft->setText("Links");
    btnAVRight->setText("Rechts");
    btnSelAV->setText("leer");

    btnSelAV->setEnabled(false);
    btnAV->setEnabled(false);
    btnAVLeft->setEnabled(false);
    btnAVRight->setEnabled(false);
    avTime->setEnabled(false);
    btnPlus->setEnabled(false);
    btnMinus->setEnabled(false);
    btnNextAV->setEnabled(false);
    btnPrevAV->setEnabled(false);

    connect(btnSetAv, SIGNAL(clicked()), SLOT(btnSetAVClicked()));
    connect(btnSetLeft, SIGNAL(clicked()), SLOT(btnSetLeftClicked()));
    connect(btnSetRight, SIGNAL(clicked()), SLOT(btnSetRightClicked()));
    connect(btnSetLeftRight, SIGNAL(clicked()), SLOT(btnSetLeftRightClicked()));
    connect(btnSelAV, SIGNAL(clicked()), SLOT(btnSelAVClicked()));
    connect(btnAV, SIGNAL(clicked()), SLOT(btnAVClicked()));
    connect(btnAVLeft, SIGNAL(clicked()), SLOT(btnAVLeftClicked()));
    connect(btnAVRight, SIGNAL(clicked()), SLOT(btnAVRightClicked()));
    connect(btnPlus, SIGNAL(clicked()), SLOT(btnPlusClicked()));
    connect(btnMinus, SIGNAL(clicked()), SLOT(btnMinusClicked()));
    connect(btnNextAV, SIGNAL(clicked()), SLOT(btnNextAVClicked()));
    connect(btnPrevAV, SIGNAL(clicked()), SLOT(btnPrevAVClicked()));
}
    /**
     * @brief sets a new AV, saves the time and enables necessary buttons
     */
    void AVRecordControl::btnSetAVClicked(){
        totalAV++;
        currentAV = totalAV;

        QString str;
        str.append(QString("%1").arg(currentAV));
        btnSelAV->setText("AV " + str);
        lstAVTime->append(getTime(currentAV));

        int t = lstAVTime->at(currentAV -1);
        unsigned int m = (t/ 60);
        unsigned int s = (t - 60*m);
        const QString diff = QString("%1:%2")
        .arg(m, 2, 10, QChar('0'))
        .arg(s, 2, 10, QChar('0'));
        avTime->setText(diff);

        btnSelAV->setEnabled(true);
        btnAV->setEnabled(true);
        avTime->setEnabled(true);
        btnPlus->setEnabled(true);
        btnMinus->setEnabled(true);

        avSelected = true;
        leftSelected = false;
        rightSelected = false;

        btnAV->setSelected(true);
        btnAVLeft->setSelected(false);
        btnAVRight->setSelected(false);

        if(totalAV > 1)
            btnPrevAV->setEnabled(true);
        btnNextAV->setEnabled(false);

        avPressed = true;
    }

    /**
     * @brief sets a new left AV, saves the time and enables necessary buttons, if button was selected
     * otherwise selects button
     */
    void AVRecordControl::btnSetLeftClicked(){
        if(leftPressed){
            leftPressed = false;
            btnSetLeft->setSelected(false);
            totalLeftAV++;
            currentLeftAV = totalLeftAV;
            lstLeftAVTime->append(getLeftRightTime(currentLeftAV, "left"));
            btnAVLeft->setEnabled(true);
            btnSetLeftRight->setSelected(false);
            btnPlus->setEnabled(true);
            btnMinus->setEnabled(true);
        }
        else {
            leftPressed = true;
            btnSetLeft->setSelected(true);
            if(rightPressed)
                btnSetLeftRight->setSelected(true);
        }
    }

    /**
     * @brief sets a new right AV, saves the time and enables necessary buttons, if button was selected
     * otherwise, selects button
     */
    void AVRecordControl::btnSetRightClicked(){
        if(rightPressed){
            rightPressed = false;
            btnSetRight->setSelected(false);
            totalRightAV++;
            currentRightAV = totalRightAV;
            lstRightAVTime->append(getLeftRightTime(currentRightAV, "right"));
            btnAVRight->setEnabled(true);
            btnSetLeftRight->setSelected(false);
            btnPlus->setEnabled(true);
            btnMinus->setEnabled(true);
        }
        else {
            rightPressed = true;
            btnSetRight->setSelected(true);
            if(leftPressed)
                btnSetLeftRight->setSelected(true);
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
            btnSetRight->setSelected(false);
            totalRightAV++;
            currentRightAV = totalRightAV;
            lstRightAVTime->append(getLeftRightTime(currentRightAV, "right"));
            btnSetLeft->setSelected(false);
            totalLeftAV++;
            currentLeftAV = totalLeftAV;
            lstLeftAVTime->append(getLeftRightTime(currentLeftAV, "left"));
            btnSetLeftRight->setSelected(false);
            btnAVLeft->setEnabled(true);
            btnAVRight->setEnabled(true);
        }
        else {
            rightPressed = true;
            leftPressed = true;
            btnSetRight->setSelected(true);
            btnSetLeft->setSelected(true);
            btnSetLeftRight->setSelected(true);
        }
    }

    /**
     * @brief updates the lists of the AVs
     */
    void AVRecordControl::updateAVs(){
        if(stopped){
           lstAV->append(true);
           lstLeftAVs->append(false);
           lstRightAVs->append(false);
        }
        if(avPressed){
            lstAV->append(true);
            avPressed = false;
        }
        else
            lstAV->append(false);

        if(leftPressed)
            lstLeftAVs->append(true);
        else
            lstLeftAVs->append(false);
        if(rightPressed)
            lstRightAVs->append(true);
        else
            lstRightAVs->append(false);
    }

    /**
     * @brief relays the necessary inforamtion to the graph, in order
     * for it to update
     */
    void AVRecordControl::updateGraph(){
        graphView->updateGraph(lstAV, lstLeftAVs, lstRightAVs);
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
           bool s = lstAV->at(i);
           if(avCount == (currentAV -1)){
               if(s == true){
                  avCount++;
               }
               else
                   secs++;
           }
           else {
              if(s == true)
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
                bool s = lstLeftAVs->at(i);
                if(avCount == (currentAV -1)){
                    if(s == true && lstLeftAVs->at(i +1) == false){
                        avCount++;
                    }
                    else if(s == true)
                        secs++;
                }
                else if(s == true && lstLeftAVs->at(i +1) == false)
                    avCount++;
            }
        }
        else {
            for(int i = 1; i < lstRightAVs->count() -1; ++i){
                bool s = lstRightAVs->at(i);
                if(avCount == (currentAV -1)){
                    if(s == true && lstRightAVs->at(i +1) == false){
                        avCount++;
                    }
                    else if(s == true)
                        secs++;
                }
                else if(s == true && lstRightAVs->at(i +1) == false)
                    avCount++;
            }
        }
        return secs +1;
    }

    /**
     * @brief AVRecordControl::btnSelAVClicked
     */
    void AVRecordControl::btnSelAVClicked(){
        //TODO
    }

    /**
     * @brief AVRecordControl::btnAVClicked
     */
    void AVRecordControl::btnAVClicked(){
        currentAV = 1;
        btnPrevAV->setEnabled(false);
        if(currentAV == totalAV)
            btnNextAV->setEnabled(false);
        else
            btnNextAV->setEnabled(true);
        QString str;
        str.append(QString("%1").arg(currentAV));
        btnSelAV->setText("AV " + str);

        if(!windowMinimized){
            int t = lstAVTime->at(currentAV -1);

            unsigned int m = (t/ 60);
            unsigned int s = (t - 60*m);
            const QString diff = QString("%1:%2")
            .arg(m, 2, 10, QChar('0'))
            .arg(s, 2, 10, QChar('0'));
            avTime->setText(diff);
        }
        avSelected = true;
        leftSelected = false;
        rightSelected = false;
        btnAV->setSelected(true);
        btnAVLeft->setSelected(false);
        btnAVRight->setSelected(false);
    }

    /**
     * @brief AVRecordControl::btnAVLeftClicked
     */
    void AVRecordControl::btnAVLeftClicked(){
        currentLeftAV = 1;
        btnPrevAV->setEnabled(false);
        if(currentLeftAV == totalLeftAV)
            btnNextAV->setEnabled(false);
        else
            btnNextAV->setEnabled(true);
        QString str;
        str.append(QString("%1").arg(currentLeftAV));
        btnSelAV->setText("L " + str);

        if(!windowMinimized){
            int t = lstLeftAVTime->at(currentLeftAV -1);

            unsigned int m = (t/ 60);
            unsigned int s = (t - 60*m);
            const QString diff = QString("%1:%2")
            .arg(m, 2, 10, QChar('0'))
            .arg(s, 2, 10, QChar('0'));
            avTime->setText(diff);
        }
        avSelected = false;
        leftSelected = true;
        rightSelected = false;
        btnAV->setSelected(false);
        btnAVLeft->setSelected(true);
        btnAVRight->setSelected(false);
    }

    /**
     * @brief AVRecordControl::btnAVRightClicked
     */
    void AVRecordControl::btnAVRightClicked(){
        currentRightAV = 1;
        btnPrevAV->setEnabled(false);
        if(currentRightAV == totalRightAV)
            btnNextAV->setEnabled(false);
        else
            btnNextAV->setEnabled(true);
        QString str;
        str.append(QString("%1").arg(currentRightAV));
        btnSelAV->setText("R " + str);

        if(!windowMinimized){
            int t = lstRightAVTime->at(currentRightAV -1);

            unsigned int m = (t/ 60);
            unsigned int s = (t - 60*m);
            const QString diff = QString("%1:%2")
            .arg(m, 2, 10, QChar('0'))
            .arg(s, 2, 10, QChar('0'));
            avTime->setText(diff);
        }
        avSelected = false;
        leftSelected = false;
        rightSelected = true;
        btnAV->setSelected(false);
        btnAVLeft->setSelected(false);
        btnAVRight->setSelected(true);
    }

    /**
     * @brief increases the time of the selected AV by one
     */
    void AVRecordControl::btnPlusClicked(){
        if(avSelected){
           int o = lstAVTime->at(currentAV -1) +1;
           lstAVTime->replace(currentAV -1, o);

           int t = lstAVTime->at(currentAV -1);

           unsigned int m = (t/ 60);
           unsigned int s = (t - 60*m);
           const QString diff = QString("%1:%2")
           .arg(m, 2, 10, QChar('0'))
           .arg(s, 2, 10, QChar('0'));
           avTime->setText(diff);
        }
        else if(leftSelected){
            int o = lstLeftAVTime->at(currentLeftAV -1) +1;
            lstLeftAVTime->replace(currentLeftAV -1, o);

            int t = lstLeftAVTime->at(currentLeftAV -1);

            unsigned int m = (t/ 60);
            unsigned int s = (t - 60*m);
            const QString diff = QString("%1:%2")
            .arg(m, 2, 10, QChar('0'))
            .arg(s, 2, 10, QChar('0'));
            avTime->setText(diff);
        }
        else {
            int o = lstRightAVTime->at(currentRightAV -1) +1;
            lstRightAVTime->replace(currentRightAV -1, o);

            int t = lstRightAVTime->at(currentRightAV -1);

            unsigned int m = (t/ 60);
            unsigned int s = (t - 60*m);
            const QString diff = QString("%1:%2")
            .arg(m, 2, 10, QChar('0'))
            .arg(s, 2, 10, QChar('0'));
            avTime->setText(diff);
        }
    }

    /**
     * @brief decreases the time of the selected AV by one
     */
    void AVRecordControl::btnMinusClicked(){
        if(avSelected){
           int o = lstAVTime->at(currentAV -1) -1;
           lstAVTime->replace(currentAV -1, o);

           int t = lstAVTime->at(currentAV -1);

           unsigned int m = (t/ 60);
           unsigned int s = (t - 60*m);
           const QString diff = QString("%1:%2")
           .arg(m, 2, 10, QChar('0'))
           .arg(s, 2, 10, QChar('0'));
           avTime->setText(diff);
        }
        else if(leftSelected){
            int o = lstLeftAVTime->at(currentLeftAV -1) -1;
            lstLeftAVTime->replace(currentLeftAV -1, o);

            int t = lstLeftAVTime->at(currentLeftAV -1);

            unsigned int m = (t/ 60);
            unsigned int s = (t - 60*m);
            const QString diff = QString("%1:%2")
            .arg(m, 2, 10, QChar('0'))
            .arg(s, 2, 10, QChar('0'));
            avTime->setText(diff);
        }
        else {
            int o = lstRightAVTime->at(currentRightAV -1) -1;
            lstRightAVTime->replace(currentRightAV -1, o);

            int t = lstRightAVTime->at(currentRightAV -1);

            unsigned int m = (t/ 60);
            unsigned int s = (t - 60*m);
            const QString diff = QString("%1:%2")
            .arg(m, 2, 10, QChar('0'))
            .arg(s, 2, 10, QChar('0'));
            avTime->setText(diff);
        }
    }

    /**
     * @brief AVRecordControl::btnNextAVClicked
     */
    void AVRecordControl::btnNextAVClicked(){
        if(avSelected){
            currentAV++;
            QString str;
            str.append(QString("%1").arg(currentAV));
            btnSelAV->setText("AV " + str);
            btnPrevAV->setEnabled(true);
            if(currentAV  == totalAV)
                btnNextAV->setEnabled(false);

            if(!windowMinimized){
                int t = lstAVTime->at(currentAV -1);

                unsigned int m = (t/ 60);
                unsigned int s = (t - 60*m);
                const QString diff = QString("%1:%2")
                .arg(m, 2, 10, QChar('0'))
                .arg(s, 2, 10, QChar('0'));
                avTime->setText(diff);
            }
        }
        else if(leftSelected){
            currentLeftAV++;
            QString str;
            str.append(QString("%1").arg(currentLeftAV));
            btnSelAV->setText("L " + str);
            btnPrevAV->setEnabled(true);
            if(currentLeftAV  == totalLeftAV)
                btnNextAV->setEnabled(false);

            if(!windowMinimized){
                int t = lstLeftAVTime->at(currentLeftAV -1);

                unsigned int m = (t/ 60);
                unsigned int s = (t - 60*m);
                const QString diff = QString("%1:%2")
                .arg(m, 2, 10, QChar('0'))
                .arg(s, 2, 10, QChar('0'));
                avTime->setText(diff);
            }
        }
        else {
            currentRightAV++;
            QString str;
            str.append(QString("%1").arg(currentRightAV));
            btnSelAV->setText("R " + str);
            btnPrevAV->setEnabled(true);
            if(currentRightAV  == totalRightAV)
                btnNextAV->setEnabled(false);

            if(!windowMinimized){
                int t = lstRightAVTime->at(currentRightAV -1);

                unsigned int m = (t/ 60);
                unsigned int s = (t - 60*m);
                const QString diff = QString("%1:%2")
                .arg(m, 2, 10, QChar('0'))
                .arg(s, 2, 10, QChar('0'));
                avTime->setText(diff);
            }
        }
    }

    /**
     * @brief AVRecordControl::btnPrevAVClicked
     */
    void AVRecordControl::btnPrevAVClicked(){
        if(avSelected){
            currentAV--;
            QString str;
            str.append(QString("%1").arg(currentAV));
            btnSelAV->setText("AV " + str);
            btnNextAV->setEnabled(true);
            if(currentAV == 1)
                btnPrevAV->setEnabled(false);

            if(!windowMinimized){
                int t = lstAVTime->at(currentAV -1);

                unsigned int m = (t/ 60);
                unsigned int s = (t - 60*m);
                const QString diff = QString("%1:%2")
                .arg(m, 2, 10, QChar('0'))
                .arg(s, 2, 10, QChar('0'));
                avTime->setText(diff);
            }
        }
        else if(leftSelected){
            currentLeftAV--;
            QString str;
            str.append(QString("%1").arg(currentLeftAV));
            btnSelAV->setText("L " + str);
            btnNextAV->setEnabled(true);
            if(currentLeftAV == 1)
                btnPrevAV->setEnabled(false);

           if(!windowMinimized){
                int t = lstLeftAVTime->at(currentLeftAV -1);

                unsigned int m = (t/ 60);
                unsigned int s = (t - 60*m);
                const QString diff = QString("%1:%2")
                .arg(m, 2, 10, QChar('0'))
                .arg(s, 2, 10, QChar('0'));
                avTime->setText(diff);
            }
        }
        else {
            currentRightAV--;
            QString str;
            str.append(QString("%1").arg(currentRightAV));
            btnSelAV->setText("R " + str);
            btnNextAV->setEnabled(true);
            if(currentRightAV == 1)
                btnPrevAV->setEnabled(false);

            if(!windowMinimized){
                int t = lstRightAVTime->at(currentRightAV -1);

                unsigned int m = (t/ 60);
                unsigned int s = (t - 60*m);
                const QString diff = QString("%1:%2")
                .arg(m, 2, 10, QChar('0'))
                .arg(s, 2, 10, QChar('0'));
                avTime->setText(diff);
            }
        }
    }

    void AVRecordControl::btnAVClickedWithID(int id){
        avSelected = true;
        leftSelected = false;
        rightSelected = false;

        currentAV = id;
        btnAV->setSelected(true);
        btnAVLeft->setSelected(false);
        btnAVRight->setSelected(false);

        QString str;
        str.append(QString("%1").arg(currentAV));
        btnSelAV->setText("AV " + str);

        if(currentAV == 1)
            btnPrevAV->setEnabled(false);
        else
            btnPrevAV->setEnabled(true);
        if(currentAV  == totalAV)
            btnNextAV->setEnabled(false);
        else
            btnNextAV->setEnabled(true);

        if(!windowMinimized){
            int t = lstAVTime->at(currentAV -1);

            unsigned int m = (t/ 60);
            unsigned int s = (t - 60*m);
            const QString diff = QString("%1:%2")
            .arg(m, 2, 10, QChar('0'))
            .arg(s, 2, 10, QChar('0'));
            avTime->setText(diff);
        }

    }

    void AVRecordControl::btnLeftClickedWithID(int id){
        avSelected = false;
        leftSelected = true;
        rightSelected = false;

        currentLeftAV = id;
        btnAV->setSelected(false);
        btnAVLeft->setSelected(true);
        btnAVRight->setSelected(false);

        QString str;
        str.append(QString("%1").arg(currentLeftAV));
        btnSelAV->setText("L " + str);

        if(currentLeftAV == 1)
            btnPrevAV->setEnabled(false);
        else
            btnPrevAV->setEnabled(true);
        if(currentLeftAV  == totalLeftAV)
            btnNextAV->setEnabled(false);
        else
            btnNextAV->setEnabled(true);

        if(!windowMinimized){
            int t = lstLeftAVTime->at(currentLeftAV -1);

            unsigned int m = (t/ 60);
            unsigned int s = (t - 60*m);
            const QString diff = QString("%1:%2")
            .arg(m, 2, 10, QChar('0'))
            .arg(s, 2, 10, QChar('0'));
            avTime->setText(diff);
        }
    }

    void AVRecordControl::btnRightClickedWithID(int id){
        avSelected = false;
        leftSelected = false;
        rightSelected = true;

        currentRightAV = id;
        btnAV->setSelected(false);
        btnAVLeft->setSelected(false);
        btnAVRight->setSelected(true);

        QString str;
        str.append(QString("%1").arg(currentRightAV));
        btnSelAV->setText("R " + str);

        if(currentRightAV == 1)
            btnPrevAV->setEnabled(false);
        else
            btnPrevAV->setEnabled(true);
        if(currentRightAV  == totalRightAV)
            btnNextAV->setEnabled(false);
        else
            btnNextAV->setEnabled(true);

        if(!windowMinimized){
            int t = lstRightAVTime->at(currentRightAV -1);

            unsigned int m = (t/ 60);
            unsigned int s = (t - 60*m);
            const QString diff = QString("%1:%2")
            .arg(m, 2, 10, QChar('0'))
            .arg(s, 2, 10, QChar('0'));
            avTime->setText(diff);
        }
    }
