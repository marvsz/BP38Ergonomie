#ifndef WORKPLACEVIEW_H
#define WORKPLACEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QList>
#include "timelineedit.h"
#include "detailedlistitem.h"
#include "numberlineedit.h"

class WorkplaceView : public QWidget
{
    Q_OBJECT
public:
    explicit WorkplaceView(QWidget *parent = 0);
    explicit WorkplaceView(int id, QWidget *parent = 0);

    QString getName() const;
    QString getDescription() const;
    QString getCode() const;
    int getWomanPercentage() const;

    QTime getBasicTime() const;
    QTime getSetupTime() const;
    QTime getRestTime() const;
    QTime getAllowanceTime() const;
    QTime getCycleTime() const;

signals:
    void save();
    void back();

    void showLineView();
    void showActivityView();
    void showCommentView();

public slots:
    void setWorkplaceMetaData(const QString &name, const QString &description, const QString &code, int percentageWoman);
    void setLine(const QString &name, const QString &description);
    void setComment(const QString &problemName, const QString &measureName);
    void setWorkplaceTimes(const QTime &basicTime, const QTime &setupTime, const QTime &restTime, const QTime &allowanceTime, const QTime &cycleTime);

private slots:
    void btnBackClicked();
    void btnLineClicked();
    void btnActivityClicked();
    void btnCommentClicked();

private:
    int id;

    QLabel *lblViewDescription;
    QLabel *lblName;
    QLabel *lblDescription;
    QLabel *lblCode;
    QLabel *lblPercentageWoman;

    TextLineEdit *txtBxName;
    TextLineEdit *txtBxDescription;
    TextLineEdit *txtBxCode;
    NumberLineEdit *numBxWomanPercentage;

    QLabel* lblAllowedTime;
    QLabel* lblSetupTime;
    QLabel* lblBasicTime;
    QLabel* lblRestTime;
    QLabel* lblAllowanceTime;
    QLabel* lblCycleTime;

    TimeLineEdit* timeSetupTime;
    TimeLineEdit* timeBasicTime;
    TimeLineEdit* timeRestTime;
    TimeLineEdit* timeAllowanceTime;
    TimeLineEdit* timeCycleTime;

    QPushButton *btnBack;
    QPushButton *btnCancel;
    QPushButton *btnSave;

    DetailedListItem *line;
    DetailedListItem *activity;
    DetailedListItem *comment;

    QList<DetailedListItem*> *additions;
};

#endif // WORKPLACEVIEW_H
