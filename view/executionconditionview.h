#ifndef EXECUTIONCONDITIONVIEW_H
#define EXECUTIONCONDITIONVIEW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "selectablevaluebutton.h"
#include "moreexecutioncondition.h"

class ExecutionConditionView : public QMainWindow
{
    Q_OBJECT
public:
    explicit ExecutionConditionView(QWidget *parent = 0);

signals:
    void menuViewSelected();

public slots:
    void openMenuView();

private slots:
    void moreExecutionConditionSelected();

private:
    QWidget *main;
    QWidget *mainContent;
    QScrollArea *scMainContent;
    QGridLayout *mainLayout;
    QVBoxLayout *lytOptions;
    QHBoxLayout *mainContentLayout;


    QPushButton *btnBack;
    QLabel *lblViewName;

    MoreExecutionCondition *moreExecutionCondition;

    SelectableValueButton *btnMoreExecutionCondition;

    SelectableValueButton *currentSelectedBtn;


};

#endif // EXECUTIONCONDITIONVIEW_H
