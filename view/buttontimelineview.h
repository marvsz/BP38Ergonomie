#ifndef BUTTONTIMELINEVIEW_H
#define BUTTONTIMELINEVIEW_H

#include <QBoxLayout>
#include <QPushButton>
#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>

namespace Ui {
class ButtonTimelineView;
}

class ButtonTimelineView : public QMainWindow
{
    Q_OBJECT

public:
    explicit ButtonTimelineView(QWidget *parent = 0);

    void clearButtons();

    QHBoxLayout *leftButtonLayout;
    QHBoxLayout *rightButtonLayout;
    QHBoxLayout *avButtonLayout;
    QPushButton *btnPlus;
    QPushButton *btnMinus;

    int currentTime;

private slots:
    void btnZoomInClicked();
    void btnZoomOutClicked();
    void btnPlusClicked();
    void btnMinusClicked();

private:
    QWidget *main;
    QWidget *mainButton;

    QLabel *lblOccurrences;
    QLineEdit *occurrences;
    QPushButton *btnZoomIn;
    QPushButton *btnZoomOut;

    int count;
};

#endif // BUTTONTIMELINEVIEW_H
