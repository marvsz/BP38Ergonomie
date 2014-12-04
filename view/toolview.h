#ifndef TOOLVIEW_H
#define TOOLVIEW_H

#include <QLabel>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include "valuecontrol.h"
#include "listcontrol.h"

namespace Ui {
class ToolView;
}

class ToolView : public QMainWindow
{
    Q_OBJECT

public:
    explicit ToolView(QString windowName = "", QWidget *parent = 0);
    ~ToolView();

signals:
    void menuViewSelected();

private slots:
    void openMenuView();

private:
    QPushButton *backButton;
    QLabel *label;
    QLabel *lblViewName;
    ValueControl *type;
    ValueControl *last;
    ValueControl *weg;
    ValueControl *hand;
    QWidget *main;
    QWidget *control;
    ListControl *tools;
};

#endif // ToolView_H
