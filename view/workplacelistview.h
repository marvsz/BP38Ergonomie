#ifndef WORKPLACELISTVIEW_H
#define WORKPLACELISTVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QListView>
#include <QStringList>
#include <QStringListModel>

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
    QListView *workplaceListView;
    QStringListModel *workplaceList;
};

#endif // WORKPLACELISTVIEW_H
