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
    void leftStarted(const QTime &startTime);
    void leftEnded(const QTime &endTime);
    void rightStarted(const QTime &startTime);
    void rightEnded(const QTime &endTime);
    void basicStarted(const QTime &startTime);
    void basicEnded(const QTime &endTime);
    void initialize(QVector<QVariant> *leftWPs, QVector<QVariant> *rightWPs, QVector<QVariant> *basicWPs);
    void updateGraphTimeLine(const QTime &currentTime);

private:
    int paintX;

    QLabel *graph;
    QPicture picture;
    QPainter painter;
    QScrollArea *graphArea;

    QVector<QVariant> *leftWPs;
    QVector<QVariant> *rightWPs;
    QVector<QVariant> *basicWPs;
};

#endif // GRAPHTIMELINEVIEW_H
