#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <QStackedWidget>
#include "mainwindow.h"
#include "mainmenu.h"
#include "toolview.h"
#include "actionforceview.h"

class ViewController : public QStackedWidget
{
    Q_OBJECT
public:
    explicit ViewController(QWidget *parent = 0);
    static const int MENU_VIEW = 0;
    static const int ANGLE_VIEW = 1;
    static const int TOOL_VIEW = 2;
    static const int ACTION_FORCE_VIEW = 3;

signals:

public slots:
    void setMenuView();
    void setAngleView();
    void setToolView();
    void setActionForceView();

private:
    MainMenu *menuView;
    MainWindow *anglesView;
    ToolView *toolView;
    ActionForceView *actionForceView;
};

#endif // VIEWCONTROLLER_H
