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

    // METADATAVIEW GETTER
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

    // WORKPLACE VIEW GETTER
    QString getWorkplaceName() const;
    QString getWorkplaceDescription() const;
    QString getWorkplaceCode() const;
    int getWorkplaceWomanPercentage() const;

    // LINE VIEW GETTER
    QString getLineName() const;
    QString getLineDescription() const;
    int getLineWorkplaceCount() const;

    // SHIFTPAUSE VIEW GETTER
    QTime getShiftBegin() const;
    QTime getShiftEnd() const;
    QTime getShiftCycleTime() const;
    int getShiftQuantity() const;

    QTime getShiftSetupTime() const;
    QTime getShiftBasicTime() const;
    QTime getShiftRestTime() const;
    QTime getShiftAllowanceTime() const;

    QTime getShiftBreakBegin() const;
    QTime getShiftBreakEnd() const;

    // EMPLOYEE VIEW GETTER
    int getEmployeeGender() const;
    int getEmployeeAge() const;
    int getEmployeeHeight() const;
    QString getEmployeeStaffNumber() const;
    QString getEmployeeNote() const;

    // PRODUCT VIEW GETTER
    QString getProductName() const;
    QString getProductNumber() const;
    int getProductTotalPercentage() const;

    // COMMENT VIEW GETTER
    QString getCommentProblemName() const;
    QString getCommentProblemDescription() const;
    QString getCommentMeasureName() const;
    QString getCommentMeasureDescription() const;
    QString getCommentWorkerPerception() const;

signals:
    void saveMetaData();
    void updateMetaData();

    void updateWorkplaceList();
    void updateWorkplace(int id);
    void createWorkplace();
    void deleteWorkplace(int id);
    void setSelectedWorkplace(int id);

    void saveWorkplace();

    void updateLineView();
    void saveLine();

    void updateProductView();
    void saveProduct();
    void deleteProduct(int id);

    void updateCommentView();
    void saveComment();

    void updateEmployeeView();
    void saveEmployee();

public slots:

    void setAnalyst(const QString &lastName, const QString &firstName, const QString &experience);
    void setEmployer(const QString &employer);
    void setCorporation(const QString &name);
    void setFactory(const QString &name, const QString &street, int zip, const QString &city, const QString &country, const QString &contact, int employeeCount);
    void setRecordTime(const QDateTime &begin, const QDateTime &end);

    // WORKPLACE LIST VIEW
    void addWorkplace(int id, const QString &name, const QString &description, const QString &code);
    void clearWorkplaceList();

    // WORKPLACE VIEW SETTER
    void setWorkplaceMetaData(const QString &name, const QString &description, const QString &code, int percentageWoman);

    // LINE VIEW SETTER
    void setLine(const QString &name, const QString &description, int workplaceCount);
    void addLine(int id, const QString &name);
    void clearLines();

    // SHIFTPAUSE VIEW SETTER
    void setShift(const QString &shiftType, const QTime &shiftBegin, const QTime &shiftEnd);
    void setShiftBreak(const QTime &breakBegin, const QTime &breakEnd);
    void setShiftWorkplaceTimes(const QTime &basicTime, const QTime &setupTime, const QTime &restTime, const QTime &allowanceTime, const QTime &cycleTime);

    // EMPLOYEE VIEW SETTER
    void setEmployee(int gender, int age, int height, const QString &staffNumber, const QString &note);

    // PRODUCT VIEW SETTER
    void setProduct(const QString &name, const QString &number, int totalPercentage);
    void addProduct(int id, const QString &name);
    void clearProducts();

    // COMMENT VIEW SETTER
    void setComment(const QString &problemName, const QString &problemDesc, const QString &measureName, const QString &measureDesc, const QString &workerPerception);

private slots:

    void backToView();

    void goToMetaDataView();
    void goToWorkplaceListView();
    void goToWorkplaceView();
    void goToWorkplaceView(int id);
    void goToLineView();
    void goToShiftAndPauseView();
    void goToEmployeeView();
    void goToProductView();
    void goToCommentView();
    void goToDocumentationView();

    void saveMetaDataRequested();
    void saveWorkplaceRequested();
    void saveCommentRequested();
    void saveProductRequested();
    void saveLineRequested();
    void saveEmloyeeRequested();

    void deleteWorkplaceClicked(int id);
    void deleteProductClicked(int id);

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
