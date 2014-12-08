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
#include "generalexecutioncondition.h"

class ExecutionConditionView : public QMainWindow
{
    Q_OBJECT
public:
    explicit ExecutionConditionView(QWidget *parent = 0);

signals:

public slots:

private slots:
    void moreExecutionConditionSelected();
    void generalExecutionConditionSelected();

private:
    QWidget *mainContent;
    QScrollArea *scMainContent;
    QVBoxLayout *lytOptions;
    QHBoxLayout *mainContentLayout;


    MoreExecutionCondition *moreExecutionCondition;
    GeneralExecutionCondition *generalExecutionCondition;

    SelectableValueButton *btnMoreExecutionCondition;
    SelectableValueButton *btnGeneralExecutionCondition;

    SelectableValueButton *currentSelectedBtn;


};

#endif // EXECUTIONCONDITIONVIEW_H
