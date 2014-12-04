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

public slots:
    void openAngleView();
    void openToolView();
    void openActionForceView();

private:
    QPushButton *angleView;
    QPushButton *toolView;
    QPushButton *actionForceView;
};

#endif // MAINMENU_H
