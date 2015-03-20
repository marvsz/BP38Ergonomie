#include "timelineedit.h"
#include <QRegularExpressionValidator>

const QRegularExpression TimeLineEdit::regExMS = QRegularExpression("^([0-5]?[0-9]:[0-5]?[0-9])?$");
const QRegularExpression TimeLineEdit::regExHM = QRegularExpression("^((0?[0-9]|1[0-9]|2[0-3]):[0-5]?[0-9])?$");
const QRegularExpression TimeLineEdit::regExHMS = QRegularExpression("^((0?[0-9]|1[0-9]|2[0-3]):[0-5]?[0-9]:[0-5]?[0-9])?$");

TimeLineEdit::TimeLineEdit(QWidget *parent, TimeLineType type) :
    TextLineEdit(parent),
    type(type)
{
    QRegularExpression regEx;
    switch(this->type){
    case(TimeLineType::MINUTE_SECOND):
        regEx = regExMS;
        break;
    case(TimeLineType::HOUR_MINUTE):
        regEx = regExHM;
        break;
    case(TimeLineType::HOUR_MINUTE_SECOND):
        regEx = regExHMS;
        break;
    }
    this->setValidator(new QRegularExpressionValidator(regEx));
    this->setInputMethodHints(Qt::ImhDialableCharactersOnly);

    connect(this, SIGNAL(editingFinished()), this, SLOT(updateTime()));
}

QTime TimeLineEdit::getTime() const{
    return this->currentTime;
}

void TimeLineEdit::setTime(const QTime &time){
    if(time.isValid())
        currentTime = time;
    else
        currentTime = QTime::currentTime();
    updateText();
}

void TimeLineEdit::increaseHour(){
    QTime oldTime = currentTime;
    currentTime = currentTime.addSecs(3600);
    if(currentTime == QTime(0,0) || currentTime < oldTime)
        emit dayIncreased();
    updateText();
}

void TimeLineEdit::increaseMinute(){
    QTime oldTime = currentTime;
    currentTime = currentTime.addSecs(60);
    if(currentTime == QTime(0,0) || currentTime < oldTime)
        emit dayIncreased();
    updateText();
}

void TimeLineEdit::decreaseHour(){
    QTime oldTime = currentTime;
    currentTime = currentTime.addSecs(-3600);
    if(currentTime == QTime(0,0) || currentTime > oldTime)
        emit dayDecreased();
    updateText();
}

void TimeLineEdit::decreaseMinute(){
    QTime oldTime = currentTime;
    if(currentTime == QTime(0,0) || currentTime > oldTime)
        emit dayDecreased();
    currentTime = currentTime.addSecs(-60);
    updateText();
}

void TimeLineEdit::updateText(){
    switch(this->type){
    case(TimeLineType::MINUTE_SECOND):
        setText(currentTime.toString("mm:ss"));
        break;
    case(TimeLineType::HOUR_MINUTE):
        setText(currentTime.toString("HH:mm"));
        break;
    case(TimeLineType::HOUR_MINUTE_SECOND):
        setText(currentTime.toString("HH:mm:ss"));
        break;
    }
    emit timeChanged();
}

void TimeLineEdit::updateTime(){
    QStringList hms = this->text().split(":");
    switch(this->type){
    case(TimeLineType::MINUTE_SECOND):
        if(hms.length() == 2)
            currentTime = QTime(0, hms.at(0).toInt(), hms.at(1).toInt());
        break;
    case(TimeLineType::HOUR_MINUTE):
        if(hms.length() == 2)
            currentTime = QTime(hms.at(0).toInt(), hms.at(1).toInt());
        break;
    case(TimeLineType::HOUR_MINUTE_SECOND):
        if(hms.length() == 3)
            currentTime = QTime(hms.at(0).toInt(), hms.at(1).toInt(), hms.at(2).toInt(), 0);
        break;
    }
}
