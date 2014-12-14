#ifndef DOCUMENTATIONVIEW_H
#define DOCUMENTATIONVIEW_H

#include <QWidget>
#include <QTabWidget>
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
    QTabWidget *tabs;
    StopWatch *timer;
    //QPushButton* backButton;
    QPushButton* cameraButton;
    QQuickView view;

};

#endif // DOCUMENTATIONVIEW_H
