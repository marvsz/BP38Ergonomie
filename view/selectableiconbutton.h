#ifndef SELECTABLEICONBUTTON_H
#define SELECTABLEICONBUTTON_H

#include <QPushButton>

class SelectableIconButton : public QPushButton
{
    Q_OBJECT
public:
    explicit SelectableIconButton(int id = 0, QWidget *parent = 0);

    bool isCheckable() const {
        return true;
    }

    int getID() const;
    void setID(int id);

signals:
    void clickedWithID(int id);

public slots:

private slots:
    void btnClicked();

private:
    int id;

};

#endif // SELECTABLEICONBUTTON_H
