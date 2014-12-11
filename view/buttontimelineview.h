#ifndef BUTTONTIMELINEVIEW_H
#define BUTTONTIMELINEVIEW_H

#include <QBoxLayout>
#include <QPushButton>
#include <QMainWindow>

namespace Ui {
class ButtonTimelineView;
}

class ButtonTimelineView : public QMainWindow
{
    Q_OBJECT

public:
    explicit ButtonTimelineView(QWidget *parent = 0);

    QHBoxLayout *leftButtonLayout;
    QHBoxLayout *rightButtonLayout;
    QHBoxLayout *avButtonLayout;

    QPushButton *btnPlus;
    QPushButton *btnMinus;

private slots:
    void btnPlusClicked();
    void btnMinusClicked();

private:
    QWidget *main;
    QWidget *mainButton;

};

#endif // BUTTONTIMELINEVIEW_H
