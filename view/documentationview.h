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

/**
 * @brief The DocumentationView contains all view elements needed when
 * documenting a workflow.
 * A StopWatch is always present in the bottom area, the top area
 * contains a QTabWidget with the different criteria views as tabs:
 * AngleView, TransportView, ActionForceView, ExecutionConditionView.
 */
class DocumentationView : public QWidget
{
    Q_OBJECT
public:
    explicit DocumentationView(QWidget *parent = 0);

signals:

public slots:

private slots:
    void showCamera();
    void hideCamera();
private:
    // TAB SOLUTION
    // QTabWidget *tabs;

    // COMBOBOX SOLUTION
    QPushButton* backButton;
    QComboBox *views;
    QPushButton* cameraButton;
    QStackedWidget *mainContent;
    QQuickView cameraView;
    StopWatch *timer;

};

#endif // DOCUMENTATIONVIEW_H
