#ifndef ROTATIONGROUPLISTVIEW_H
#define ROTATIONGROUPLISTVIEW_H
#include "../view/navigation/simplenavigateablewidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>

class RotationGroupListView : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    explicit RotationGroupListView(QWidget *parent = 0);

    bool hasAdditionalNavigation() const {
        return true;
    }

    QList<QAbstractButton*> * getAdditionalNavigation() const;

signals:
    void create();
    void selected(int id);
    void remove(int id);

public slots:
    void clear();
    void addRotationGroup(int id, const QString &name, const QString &wpCount, const QString &totalDuration);

private slots:
    void btnPlusClicked();
    void dliRotationGroupClicked(int id);

private:
    QPushButton *btnPlus;
    QVBoxLayout *listContentLayout;
    QScrollArea *scRotationGroups;

    const QList<QStringList> rotationGroupCaptions = QList<QStringList>() << (QStringList() << tr("Workplace Count") <<tr("Total Duration"));

};

#endif // ROTATIONGROUPLISTVIEW_H
