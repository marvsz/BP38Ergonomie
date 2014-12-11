#ifndef SelectableValueButton_H
#define SelectableValueButton_H

#include <QPushButton>
#include <QWidget>

class SelectableValueButton : public QPushButton
{
    Q_OBJECT
public:
    explicit SelectableValueButton(int id, int value, QWidget *parent = 0);

    int getID() const;
    void setID(int id);
    void setSelected(bool isSelected);
    bool isSelected() const;
    void setFontSize(int fontSize);
    int getValue();
    void setValue(int value);

        int getMaxFontSize() const;

signals:
    void pressedWithID(int id);

public slots:

private slots:
    void qpbtnPressed();

private:
    int id;
    bool isSel;
    int value;
    int fontSize;

    static const QString qssHead;
    static const QString qssSelected;
    static const QString qssNotSelected;


};

#endif // SelectableValueButton_H
