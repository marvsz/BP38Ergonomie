#ifndef GRAPHTIMELINEVIEW_H
#define GRAPHTIMELINEVIEW_H

#include <QLabel>
#include <QPainter>
#include <QPicture>
#include <QScrollArea>
#include <QMainWindow>

class GraphTimelineView : public QMainWindow
{
    Q_OBJECT
public:
    explicit GraphTimelineView(QWidget *parent = 0);

public slots:
    void updateGraph(QList<bool> *lstAV, QList<bool> *lstLeftAVs, QList<bool> *lstRightAVs);

private:
    int paintX;

    QLabel *graph;
    QPicture picture;
    QPainter painter;
    QScrollArea *graphArea;
};

#endif // GRAPHTIMELINEVIEW_H