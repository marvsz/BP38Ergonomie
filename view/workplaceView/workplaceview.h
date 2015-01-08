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

    QString getName() const;
    QString getDescription() const;
    QString getCode() const;
    int getWomanPercentage() const;

signals:
    void save();
    void back();
    void forward();

    void showLineView();
    void showShiftAndPauseView();
    void showEmployeeView();
    void showProductView();
    void showCommentView();

public slots:
    void setWorkplaceMetaData(const QString &name, const QString &description, const QString &code, int percentageWoman);
    void setLine(const QString &name, const QString &description);
    void setComment(const QString &problemName, const QString &measureName);


private slots:
    void btnBackClicked();
    void btnForwardClicked();

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

    QPushButton *btnBack;
    QPushButton *btnForward;

    DetailedListItem *line;
    DetailedListItem *product;
    DetailedListItem *comment;

    QList<DetailedListItem*> *additions;
};

#endif // WORKPLACEVIEW_H
