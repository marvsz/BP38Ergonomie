#ifndef WORKPLACELISTVIEW_H
#define WORKPLACELISTVIEW_H

#include "detailedlistitem.h"
#include <QWidget>
#include <QPushButton>
#include <QScrollArea>

class WorkplaceListView : public QWidget
{
    Q_OBJECT
public:
    explicit WorkplaceListView(QWidget *parent = 0);

signals:
    void showPreviousView();
    void showNewWorkplaceView();

public slots:
    void updateWorkplaces(const QStringList &workplaces);
    void backButtonClicked();
    void forwardButtonClicked();

private:
    QPushButton *btnBack;
    QPushButton *btnForward;
    QList<DetailedListItem> *workplaces;
    QScrollArea *scWorkplaces;
};

#endif // WORKPLACELISTVIEW_H
