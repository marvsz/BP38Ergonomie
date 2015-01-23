#ifndef SelectableValueButton_H
#define SelectableValueButton_H

#include <QPushButton>
#include <QWidget>
#include <QVariant>

class SelectableValueButton : public QPushButton
{
    Q_OBJECT
public:
    explicit SelectableValueButton(int id, const QVariant &value, QWidget *parent = 0);

    int getID() const;
    void setID(int id);

    void setSelected(bool isSelected);
    bool isSelected() const;

    QVariant getValue() const;
    void setValue(const QVariant &value);

signals:
    void clickedWithID(int id);
    //void clickedWithID(int id, SelectableValueButton *btn);

public slots:

private slots:
    void btnClicked();

private:
    int id;
    bool isSel;
    QVariant value;

    static const QString qssSelected;
    static const QString qssNotSelected;


};

#endif // SelectableValueButton_H
