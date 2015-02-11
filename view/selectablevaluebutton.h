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

    bool isCheckable() const {
        return true;
    }

    int getID() const;
    void setID(int id);

    void setSelected(bool isSelected);
    bool isSelected() const;

    QVariant getValue() const;
    void setValue(const QVariant &value);

signals:
    void clickedWithID(int id);

private slots:
    void btnClicked();

private:
    int id;
    QVariant value;
    bool selected;
};

#endif // SelectableValueButton_H
