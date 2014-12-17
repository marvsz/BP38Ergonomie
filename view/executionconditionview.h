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
#include "utilitylistcontrol.h"
#include "producedproductexecutioncondition.h"

class ExecutionConditionView : public QMainWindow
{
    Q_OBJECT
public:
    explicit ExecutionConditionView(QWidget *parent = 0);

signals:

public slots:

private slots:
    void moreExecutionConditionSelected();
    void utilitiesExecutionConditionSelected();
    void generalExecutionConditionSelected();
    void producedProductExecutionConditionSelected();

private:
    QWidget *mainContent;
    QScrollArea *scMainContent;
    QVBoxLayout *lytOptions;
    QHBoxLayout *mainContentLayout;


    MoreExecutionCondition *moreExecutionCondition;
    UtilityListControl *utilitiesExecutionCondition;
    GeneralExecutionCondition *generalExecutionCondition;
    ProducedProductExecutionCondition *producedProductExecutionCondition;

    SelectableValueButton *btnMoreExecutionCondition;
    SelectableValueButton *btnUtilitiesExecutionCondition;
    SelectableValueButton *btnGeneralExecutionCondition;
    SelectableValueButton *btnProducedProductExecutionCondition;

    SelectableValueButton *currentSelectedBtn;
    QWidget *currentShownWidget;

    void showHide(SelectableValueButton *btn, QWidget *content);


};

#endif // EXECUTIONCONDITIONVIEW_H
