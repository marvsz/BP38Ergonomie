#ifndef ROTATIONGROUPVIEW_H
#define ROTATIONGROUPVIEW_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include "../interfaces/irotationgroup.h"
#include "../interfaces/irotationgrouptasklist.h"
#include "../interfaces/iworkplacelist.h"
#include "../navigation/simplenavigateablewidget.h"
#include "../textlineedit.h"
#include "../numberlineedit.h"

class RotationGroupView : public SimpleNavigateableWidget, IRotationGroup, IWorkplaceList, IRotationGroupTaskList
{
    Q_OBJECT
    Q_INTERFACES(IRotationGroupTaskList)
    Q_INTERFACES(IRotationGroup)
    Q_INTERFACES(IWorkplaceList)
public:
    explicit RotationGroupView(QWidget *parent = 0);

    bool hasAdditionalNavigation() const{
        return true;
    }

    QList<QAbstractButton*> * getAdditionalNavigation() const;

    QString getName() const;

    int getWorkplaceDuration() const;
    int getSelectedWorkplace() const;

signals:
    void saveRotationGroup(QHash<QString, QVariant> values);
    void createRotationGroupTask(QHash<QString, QVariant> values);
    void deleteRotationGroupTask(int id);
    void selectRotationGroupTask(int id);

    void createWorkplace(QHash<QString, QVariant> values);
    void deleteWorkplace(int id);
    void selectWorkplace(int id);

public slots:
    void setRotationGroup(QHash<QString, QVariant> values);

    void addRotationGroupTask(QHash<QString, QVariant> values);
    void updateRotationGroupTask(QHash<QString, QVariant> values);
    void removeRotationGroupTask(int id);
    void clearRotationGroupTasks();

    void addWorkplace(QHash<QString, QVariant> values);
    void updateWorkplace(QHash<QString, QVariant> values);
    void removeWorkplace(int id);
    void clearWorkplaces();

private slots:
    void setSelectedWorkplace(int id);
    void btnAddClicked();
    void btnAddWorkplaceClicked();

private:
    int id;
    int selectedWorkplaceID;

    QLabel *lblName;
    QLabel *lblTotalDuration;

    TextLineEdit *txtBxName;
    QLabel *lblTotalDurationValue;

    QWidget *rotationGroupTaskListContent;
    QWidget *workplaceListContent;
    QVBoxLayout *rotationGroupTaskListLayout;
    QVBoxLayout *workplaceListLayout;
    QScrollArea *scRotationGroupTasks;
    QScrollArea *scWorkplaces;

    QLabel *lblAddWorkplace;
    QLabel *lblWorkplaceDuration;
    NumberLineEdit *numBxWorkplaceDuration;

    QPushButton *btnAdd;
    QPushButton *btnAddWorkplace;

    static const QList<QStringList> rotationGroupTaskCaptions;
    static const QList<QStringList> workplaceCaptions;

};

#endif // ROTATIONGROUPVIEW_H
