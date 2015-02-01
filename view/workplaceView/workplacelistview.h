#ifndef WORKPLACELISTVIEW_H
#define WORKPLACELISTVIEW_H

#include "detailedlistitem.h"
#include "navigation/simplenavigateablewidget.h"
#include <QPushButton>
#include <QScrollArea>

class WorkplaceListView : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    explicit WorkplaceListView(QWidget *parent = 0);

    bool hasAdditionalNavigation() const{
        return true;
    }

    QList<QAbstractButton*> * getAdditionalNavigation() const;

signals:
    void create();
    void selected(int id);
    void remove(int id);

public slots:
    void clear();
    void addWorkplace(int id, const QString &name, const QString &description, const QString &code);

private slots:
    void btnPlusClicked();
    void dliWorkplaceClicked(int id);

private:
    static const QList<QStringList> workplaceCaptions;
    QPushButton *btnPlus;
    QVBoxLayout *listContentLayout;
    QScrollArea *scWorkplaces;
};

#endif // WORKPLACELISTVIEW_H
