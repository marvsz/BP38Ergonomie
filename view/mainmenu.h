#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>

class MainMenu : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = 0);

signals:
    void angleViewSelected();
    void toolViewSelected();
    void actionForceViewSelected();
    void executionConditionViewSelected();

public slots:
    void openAngleView();
    void openTransportView();
    void openActionForceView();
    void openExecutionConditionView();

private:
    QPushButton *angleView;
    QPushButton *toolView;
    QPushButton *actionForceView;
    QPushButton *executionConditionView;
};

#endif // MAINMENU_H
