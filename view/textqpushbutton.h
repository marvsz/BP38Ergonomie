#ifndef TEXTQPUSHBUTTON_H
#define TEXTQPUSHBUTTON_H

#include <QPushButton>
#include <QString>
#include <QWidget>

class TextQPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit TextQPushButton(int id = 0, QString text = "", QWidget *parent = 0);

    void setSelected(bool isSelected);
    bool isSelected() const;
    int getID() const;

signals:
    void pressedWithID(int id);
    void textChanged();

public slots:
    void changeText(QString text);
    void setSelectedByText(QString text);

private slots:
    void qpbtnPressed();

private:
    bool isSel;
    int id;
    const QString qssSelected = "QPushButton {font: 75 22pt \"Serif\";color: #FFFFFF; border-width: 3px; border-radius: 10px; border-style: solid; border-color: #007aff; background-color: #007aff;} QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}";
    const QString qssNotSelected = "QPushButton {font: 75 22pt \"Serif\";color: #007aff; border-width: 3px; border-radius: 10px; border-style: solid; border-color: #007aff; background-color: #efeff4;} QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}";
};

#endif // OWNQPUSHBUTTON_H
