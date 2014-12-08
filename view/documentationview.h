#ifndef DOCUMENTATIONVIEW_H
#define DOCUMENTATIONVIEW_H

#include <QDialog>
#include <QTabWidget>
#include "stopwatch.h"

class DocumentationView : public QDialog
{
    Q_OBJECT
public:
    explicit DocumentationView(QWidget *parent = 0);

signals:

public slots:

private:
    QTabWidget *tabs;
    StopWatch *timer;
};

#endif // DOCUMENTATIONVIEW_H
