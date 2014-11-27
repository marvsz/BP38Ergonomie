#ifndef BUTTONWITHID_H
#define BUTTONWITHID_H

#include <QPushButton>
#include <QWidget>

class ButtonWithID : public QPushButton
{
    Q_OBJECT
public:
    explicit ButtonWithID(int id, QWidget *parent = 0);

    int getID() const;
    void setSelected(bool isSelected);
    bool isSelected() const;

signals:
    void pressedWithID(int id);

public slots:

private slots:
    void qpbtnPressed();

private:
    int id;
    bool isSel;
    const QString qssSelected = "QPushButton {font: 100 26px \"Serif\";color: #FFFFFF; border: 2px solid #007aff; border-radius: 10px; background-color: #007aff;} QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}";
    const QString qssNotSelected = "QPushButton {font: 100 26px \"Serif\";color: #007aff; border: 2px solid #007aff; border-radius: 10px; background-color: #f5f5f5;} QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}";
};

#endif // BUTTONWITHID_H
