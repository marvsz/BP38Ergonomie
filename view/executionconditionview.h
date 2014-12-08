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

public slots:

private slots:
    void moreExecutionConditionSelected();

private:
    QWidget *mainContent;
    QScrollArea *scMainContent;
    QVBoxLayout *lytOptions;
    QHBoxLayout *mainContentLayout;


    MoreExecutionCondition *moreExecutionCondition;

    SelectableValueButton *btnMoreExecutionCondition;

    SelectableValueButton *currentSelectedBtn;


};

#endif // EXECUTIONCONDITIONVIEW_H
