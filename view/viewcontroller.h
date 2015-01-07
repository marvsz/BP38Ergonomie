#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <QStackedWidget>
#include <QStack>
#include "mainmenu.h"
#include "metadataview.h"
#include "workplaceView/workplacelistview.h"
#include "workplaceView/workplaceview.h"
#include "workplaceView/lineview.h"
#include "workplaceView/employeeview.h"
#include "workplaceView/shiftpauseview.h"
#include "workplaceView/productview.h"
#include "workplaceView/commentview.h"
#include "documentationview.h"

class ViewController : public QStackedWidget
{
    Q_OBJECT
public:
    explicit ViewController(QWidget *parent = 0);

    static const int MAIN_MENU_VIEW = 0;
    static const int METADATA_VIEW = 1;
    static const int WORKPLACELIST_VIEW = 2;
    static const int WORKPLACE_VIEW = 3;
    static const int LINE_VIEW = 4;
    static const int SHIFTPAUSE_VIEW = 5;
    static const int EMPLOYEE_VIEW = 6;
    static const int PRODUCT_VIEW = 7;
    static const int COMMENT_VIEW = 8;
    static const int DOCUMENTATION_VIEW = 9;

    QString getAnalystLastName() const;
    QString getAnalystFirstName() const;
    QString getAnalystEmployer() const;
    QString getAnalystExperience() const;

    QString getCorporationName() const;

    QString getFactoryName() const;
    QString getFactoryStreet() const;
    int getFactoryZip() const;
    QString getFactoryCity() const;
    QString getFactoryCountry() const;
    QString getFactoryContact() const;
    int getFactoryEmployeeCount() const;

    QDateTime getRecordTimeBegin() const;
    QDateTime getRecordTimeEnd() const;

signals:
    void saveMetaData();
    void updateMetaData();
    void updateWorkplaceList();

public slots:

    void setAnalyst(const QString &lastName, const QString &firstName, const QString &experience);
    void setEmployer(const QString &employer);
    void setCorporation(const QString &name);
    void setFactory(const QString &name, const QString &street, int zip, const QString &city, const QString &country, const QString &contact, int employeeCount);
    void setRecordTime(const QDateTime &begin, const QDateTime &end);

    void addWorkplace(const QString &name, const QString &description, const QString &code);
    void clearWorkplaceList();

private slots:

    void goToMetaDataView();
    void goToWorkplaceListView();
    void goToWorkplaceView();
    void goToLineView();
    void goToShiftAndPauseView();
    void goToEmployeeView();
    void goToProductView();
    void goToCommentView();
    void goToDocumentationView();

    void saveMetaDataRequested();
    void backToView();

private:
    QStack<int> *previousViews;
    MainMenu *mainMenuView;
    MetaDataView *metaDataView;
    WorkplaceListView *workplaceListView;
    WorkplaceView *workplaceView;
    LineView *lineView;
    ShiftPauseView *shiftPauseView;
    EmployeeView *employeeView;
    ProductView *productView;
    CommentView *commentView;
    DocumentationView *documentationView;

    void goToView(int index);
};

#endif // VIEWCONTROLLER_H
