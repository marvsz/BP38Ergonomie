#ifndef WORKPLACEVIEW_H
#define WORKPLACEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QList>
#include "detailedlistitem.h"
#include "numberlineedit.h"

class WorkplaceView : public QWidget
{
    Q_OBJECT
public:
    explicit WorkplaceView(QWidget *parent = 0);
    explicit WorkplaceView(int id, QWidget *parent = 0);

signals:
    void save(int id);
    void save();
    void showWorkprocessView();
    void showPreviousView();

    void showLineView();
    void showShiftAndPauseView();
    void showEmployeeView();
    void showProductView();
    void showCommentView();

public slots:
    void setWorkplaceMetaData(const QString &name, const QString &description, const QString &code, int percentageWoman);

private slots:
    void btnSaveClicked();
    void btnCancelClicked();
    void btnGoOnWithWorkProcessesClicked();

    void lineViewSelected();
    void shiftPauseViewSelected();
    void employeeViewSelected();
    void productViewSelected();
    void commentViewSelected();

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

    QPushButton *btnCancel;
    QPushButton *btnSave;
    QPushButton *btnGoOnWithWorkProcesses;

    DetailedListItem *line;
    DetailedListItem *shift;
    DetailedListItem *employee;
    DetailedListItem *product;
    DetailedListItem *comment;

    QList<DetailedListItem*> *additions;
};

#endif // WORKPLACEVIEW_H
