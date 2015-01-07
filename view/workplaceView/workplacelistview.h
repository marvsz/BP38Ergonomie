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
    void clear();
    void addWorkplace(int id, const QString &name, const QString &description, const QString &code);

    void backButtonClicked();
    void forwardButtonClicked();

private:
    static const QList<QStringList> workplaceCaptions;
    QPushButton *btnBack;
    QPushButton *btnForward;
    QVBoxLayout *listContentLayout;
    QScrollArea *scWorkplaces;
};

#endif // WORKPLACELISTVIEW_H
