#ifndef TOOLVIEW_H
#define TOOLVIEW_H

#include <QLabel>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include "owncon.h"
#include "textcon.h"
#include "textqpushbutton.h"
#include "ownqpushbutton.h"
#include "listcon.h"

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
    TextCon *type;
    OwnCon *last;
    OwnCon *weg;
    TextCon *hand;
    QWidget *main;
    QWidget *control;
    ListCon *tools;
};

#endif // ToolView_H
