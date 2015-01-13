#ifndef DOCUMENTATIONVIEW_H
#define DOCUMENTATIONVIEW_H

#include <QWidget>
#include <QTabWidget>
#include <QStackedWidget>
#include <QComboBox>
#include <QTabBar>
#include <QQuickView>
#include <QQmlEngine>
#include "bodyPostureView//bodypostureview.h"
#include "appliedforceview.h"
#include "executionconditionview.h"
#include "workprocessmetadataview.h"
#include "loadhandlingview.h"
#include "timerView/timerviewcontroller.h"
#include "timerView/ganttimerview.h"
/**
 * @brief The DocumentationView contains all view elements needed when
 * documenting a workflow.
 * A StopWatch is always present in the bottom area, the top area
 * contains a QCombobox with the different criteria views as options:
 * AngleView, TransportView, ActionForceView, ExecutionConditionView.
 * The main content of the different view is in the mid area on a
 * QStackedWidget.
 */
class DocumentationView : public QWidget
{
    Q_OBJECT
public:
    explicit DocumentationView(QWidget *parent = 0);

    void setBodyPostureView(BodyPostureView *bodyPostureView);
    void setLoadHandlingView(LoadHandlingView *loadHandlingView);
    void setAppliedForceView(AppliedForceView *appliedForceView);
    void setExecutionConditionView(ExecutionConditionView *executionConditionView);
    void setWorkprocessMetaDataView(WorkProcessMetaDataView *workprocessMetaDataView);

    void setTimerViewController(TimerViewController *timerViewController);

    void setupViews();

signals:
    void showPreviousView();
    void createWorkProcess(int type, const QTime &start, const QTime &end);

public slots:


private slots:
    void showCamera();
    void hideCamera();
    void leftAvPressed();
    void rightAvPressed();
    void avPressed();
    void showGant();
    void hideGant();
    void backButtonClicked();

private:
    int indexBeforeTimeLineView;
    QPushButton* backButton;
    QComboBox *views;
    QPushButton* cameraButton;
    QStackedWidget *mainContent;
    GantTimerView *gantView;
    TimerViewController *timerView;
    QQuickView *cameraView;

    BodyPostureView *bodyPostureView;
    LoadHandlingView *loadHandlingView;
    AppliedForceView *appliedForceView;
    ExecutionConditionView *executionConditionView;
    WorkProcessMetaDataView *workprocessMetaDataView;

    TimerViewController *timerViewController;
};

#endif // DOCUMENTATIONVIEW_H
