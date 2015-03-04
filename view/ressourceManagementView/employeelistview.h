#ifndef EMPLOYEELISTVIEW_H
#define EMPLOYEELISTVIEW_H

#include "../navigation/simplenavigateablewidget.h"
#include "../detailedlistitem.h"
#include <QPushButton>
#include <QScrollArea>

class EmployeeListView : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    EmployeeListView(QWidget *parent = 0);

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
    void addEmployee(int id, const QString &name, const QString &description, const QString &personalID);

private slots:
    void btnPlusClicked();
    void dliEmployeeClicked(int id);

private:
    static const QList<QStringList> employeeCaptions;
    QPushButton *btnPlus;
    QVBoxLayout *listContentLayout;
    QScrollArea *scEmployees;
};

#endif // EMPLOYEELISTVIEW_H
