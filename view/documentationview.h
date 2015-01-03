#ifndef DOCUMENTATIONVIEW_H
#define DOCUMENTATIONVIEW_H

#include <QWidget>
#include <QTabWidget>
#include <QStackedWidget>
#include <QComboBox>
#include <QTabBar>
#include <QQuickView>
#include <QQmlEngine>
#include "stopwatch.h"
#include "angleview.h"
#include "buttontimelineview.h"

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

signals:
    void showMainMenu();

public slots:

private slots:
    void showCamera();
    void hideCamera();
    void leftAvPressed();
    void rightAvPressed();
    void avPressed();
    void maximizeBtnTimeLineView();
    void minimizeBtnTimeLineView();
    void backButtonClicked();

private:
    int indexBeforeTimeLineView;
    QPushButton* backButton;
    QComboBox *views;
    QPushButton* cameraButton;
    QStackedWidget *mainContent;
    QQuickView *cameraView;
    StopWatch *timer;
    ButtonTimelineView *btnTimeLineView;
    AngleView *angleView;
};

#endif // DOCUMENTATIONVIEW_H
