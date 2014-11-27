#ifndef OWNQPUSHBUTTON_H
#define OWNQPUSHBUTTON_H

#include <QPushButton>
#include <QString>
#include <QWidget>

class OwnQPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit OwnQPushButton(int id = 0, int value = 0, QString unitSymbol = "", int min = 0, int max = 0, QWidget *parent = 0);

    void setSelected(bool isSelected);
    bool isSelected() const;
    int getID() const;
    int getValue() const;
    void setValue(int value);
    int getMin() const;
    void setMin(int min);
    int getMax() const;
    void setMax(int max);
    void setUnitSymbol(QString unitSymbol);
    QString getUnitSymbol()const;


signals:
    void pressedWithID(int id);
    void valueChanged();

public slots:
    void changeValue(int value);
    void setSelectedByValue(int value);

private slots:
    void qpbtnPressed();

private:
    bool isSel;
    int id;
    int value;
    int min;
    int max;
    QString unitSymbol;
    const QString qssSelected = "QPushButton {font: 100 26px \"Serif\";color: #FFFFFF; border-width: 2px; border-radius: 10px; border-style: solid; border-color: #007aff; background-color: #007aff;} QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}";
    const QString qssNotSelected = "QPushButton {font: 100 26px \"Serif\";color: #007aff; border-width: 2px; border-radius: 10px; border-style: solid; border-color: #007aff; background-color: #f5f5f5;} QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}";

    bool isValueInRange(int value) const;

};

#endif // OWNQPUSHBUTTON_H
