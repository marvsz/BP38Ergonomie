#ifndef ROTATIONGROUPVIEW_H
#define ROTATIONGROUPVIEW_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include "../view/navigation/simplenavigateablewidget.h"
#include "../view/textlineedit.h"
#include "../view/numberlineedit.h"

class RotationGroupView : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    explicit RotationGroupView(QWidget *parent = 0);

    QString getName() const;

    int getWorkplaceDuration() const;
    int getSelectedWorkplace() const;

signals:
    void createRotationGroupTaskEntry();
    void removeRotationGroupTaskEntry(int id);
    void selectedWorkplaceChanged(int id);

public slots:

    void setRotationGroupName(const QString &name);
    void setRotationGroupDuration(int duration);
    void setWorkplaceDuration(int duration);

    void addRotationGroupTask(int id, const QString &name, int duration);
    void clearRotationGroupTasks();

    void addWorkplace(int id, const QString &name, int duration);
    void clearWorkplaces();

private slots:
    void setSelectedWorkplace(int id);
    void btnAddClicked();

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

    static const QList<QStringList> rotationGroupTaskCaptions;
    static const QList<QStringList> workplaceCaptions;

};

#endif // ROTATIONGROUPVIEW_H
