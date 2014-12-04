#include "viewcontroller.h"

ViewController::ViewController(QWidget *parent) :
    QStackedWidget(parent)
{
    menuView = new MainMenu;
    anglesView = new MainWindow;
    toolView = new ToolView;

    connect(menuView, SIGNAL(angleViewSelected()), this, SLOT(setAngleView()));
    connect(menuView, SIGNAL(toolViewSelected()), this, SLOT(setToolView()));
    connect(anglesView, SIGNAL(menuViewSelected()),this, SLOT(setMenuView()));
    connect(toolView, SIGNAL(menuViewSelected()),this, SLOT(setMenuView()));

    this->addWidget(menuView);
    this->addWidget(anglesView);
    this->addWidget(toolView);

    setCurrentIndex(ViewController::MENU_VIEW);
}

void ViewController::setMenuView(){
    setCurrentIndex(ViewController::MENU_VIEW);
}

void ViewController::setAngleView(){
    setCurrentIndex(ViewController::ANGLE_VIEW);
}

void ViewController::setToolView(){
    setCurrentIndex(ViewController::TOOL_VIEW);
}
