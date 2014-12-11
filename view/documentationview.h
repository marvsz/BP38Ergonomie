#ifndef DOCUMENTATIONVIEW_H
#define DOCUMENTATIONVIEW_H

#include <QWidget>
#include <QTabWidget>
#include <QTabBar>
#include "stopwatch.h"

class DocumentationView : public QWidget
{
    Q_OBJECT
public:
    explicit DocumentationView(QWidget *parent = 0);

signals:

public slots:

private:
    QTabWidget *tabs;
    StopWatch *timer;
    QPushButton* backButton;
    QPushButton* cameraButton;
};

#endif // DOCUMENTATIONVIEW_H
