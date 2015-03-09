#ifndef DOCUMENTATIONVIEW_H
#define DOCUMENTATIONVIEW_H

#include "../navigation/simplenavigateablewidget.h"
#include <QStackedWidget>
#include <QComboBox>
#include <QHash>
#include <QStack>
#include "../timerView/timerviewcontroller.h"

/**
 * @brief The DocumentationView contains all view elements needed when
 * documenting a workflow.
 * A StopWatch is always present in the bottom area, the top area
 * contains a QCombobox with the different criteria views as options:
 * AngleView, TransportView, ActionForceView, ExecutionConditionView.
 * The main content of the different view is in the mid area on a
 * QStackedWidget.
 */
class DocumentationView : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    explicit DocumentationView(QWidget *parent = 0);

    bool hasInteralNavigation() const{
        return true;
    }

    QWidget * getInternalNavigation() const{
        return views;
    }
    ViewType getCurrentView() const;

    void showStartView(ViewType type);

    void registerView(TitledWidget *widget, ViewType type);
    void setTimerViewController(TimerViewController *timerViewController);

signals:
    void update(ViewType type);
    void save(ViewType type);

public slots:
    void onLeaving();

private slots:
    void showGant();
    void hideGant();

    void saveCurrentView();
    void changeView(int index);
private:
    int indexBeforeTimeLineView;
    bool registeredTimerViewController;

    QComboBox *views;
    QStackedWidget *mainContent;
    QVBoxLayout *mainLayout;

    TimerViewController *timerViewController;

    QHash<ViewType, TitledWidget*> *viewTypeToWidget;
    QHash<ViewType, int> *viewTypeToIndex;
    ViewType currentView;
};

#endif // DOCUMENTATIONVIEW_H
