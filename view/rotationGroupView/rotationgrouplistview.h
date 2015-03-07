#ifndef ROTATIONGROUPLISTVIEW_H
#define ROTATIONGROUPLISTVIEW_H

#include "../navigation/simplenavigateablewidget.h"
#include "../interfaces/irotationgrouplist.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>

class RotationGroupListView : public SimpleNavigateableWidget, IRotationGroupList
{
    Q_OBJECT
    Q_INTERFACES(IRotationGroupList)
public:
    explicit RotationGroupListView(QWidget *parent = 0);

    bool hasAdditionalNavigation() const {
        return true;
    }

    QList<QAbstractButton*> * getAdditionalNavigation() const;

signals:
    void createRotationGroup(QHash<QString, QVariant> values);
    void deleteRotationGroup(int id);
    void selectRotationGroup(int id);

public slots:
    void addRotationGroup(QHash<QString, QVariant> values);
    void updateRotationGroup(QHash<QString, QVariant> values);
    void removeRotationGroup(int id);
    void clearRotationGroups();

private slots:
    void btnPlusClicked();
    void dliRotationGroupClicked(int id);

private:
    const QList<QStringList> rotationGroupCaptions = QList<QStringList>() << (QStringList() << tr("Workplace Count") <<tr("Total Duration"));
    QPushButton *btnPlus;
    QVBoxLayout *listContentLayout;
    QScrollArea *scRotationGroups;
};

#endif // ROTATIONGROUPLISTVIEW_H
