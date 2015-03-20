#ifndef ROTATIONGROUPTASKVIEW_H
#define ROTATIONGROUPTASKVIEW_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include "../interfaces/irotationgrouptask.h"
#include "../interfaces/irotationgrouptaskentrylist.h"
#include "../interfaces/iworkplacelist.h"
#include "../navigation/simplenavigateablewidget.h"
#include "../textlineedit.h"
#include "../numberlineedit.h"

class RotationGroupTaskView : public SimpleNavigateableWidget, IRotationGroupTask, IWorkplaceList, IRotationGroupTaskEntryList
{
    Q_OBJECT
    Q_INTERFACES(IRotationGroupTaskEntryList)
    Q_INTERFACES(IRotationGroupTask)
    Q_INTERFACES(IWorkplaceList)
public:
    explicit RotationGroupTaskView(QWidget *parent = 0);

    bool hasAdditionalNavigation() const{
        return true;
    }

    QList<QAbstractButton*> * getAdditionalNavigation() const;

    QString getName() const;

    int getWorkplaceDuration() const;
    int getSelectedWorkplace() const;

signals:
    void saveRotationGroupTask(QHash<QString, QVariant> values);
    void createRotationGroupTaskEntry(QHash<QString, QVariant> values);
    void deleteRotationGroupTaskEntry(int id);

    void createWorkplace(QHash<QString, QVariant> values);
    void deleteWorkplace(int id);
    void selectWorkplace(int id);

public slots:
    void setRotationGroupTask(QHash<QString, QVariant> values);

    void addRotationGroupTaskEntry(QHash<QString, QVariant> values);
    void removeRotationGroupTaskEntry(int id);
    void clearRotationGroupTaskEntries();

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

    QWidget *rotationGroupTaskEntryListContent;
    QWidget *workplaceListContent;
    QVBoxLayout *rotationGroupTaskEntryListLayout;
    QVBoxLayout *workplaceListLayout;
    QScrollArea *scRotationGroupTaskEntries;
    QScrollArea *scWorkplaces;

    QLabel *lblAddWorkplace;
    QLabel *lblWorkplaceDuration;
    NumberLineEdit *numBxWorkplaceDuration;

    QPushButton *btnAdd;
    QPushButton *btnAddWorkplace;

    const QList<QStringList> rotationGroupTaskEntryCaptions = QList<QStringList>() << (QStringList() << tr("Duration:"));
    const QList<QStringList> workplaceCaptions = QList<QStringList>();// << (QStringList() << tr("Duration:"));

};

#endif // ROTATIONGROUPTASKVIEW_H
