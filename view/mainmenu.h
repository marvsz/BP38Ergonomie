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

public slots:
    void openAngleView();
    void openToolView();

private:
    QPushButton *angleView;
    QPushButton *toolView;
};

#endif // MAINMENU_H
