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
#include "workplaceView/commentview.h"
#include "workplaceView/activityview.h"
#include "documentationview.h"
#include "ressourceManagementView/ressourcemanagementview.h"
#include "ressourceManagementView/equipmentview.h"
#include "ressourceManagementView/productview.h"
#include "ressourceManagementView/transportationview.h"

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
    static const int EMPLOYEE_VIEW = 5;
    static const int ACTIVITY_VIEW = 6;
    static const int COMMENT_VIEW = 7;
    static const int DOCUMENTATION_VIEW = 8;
    static const int RESSOURCE_MANAGEMENT_VIEW = 9;
    static const int PRODUCT_VIEW = 10;
    static const int EQUIPMENT_VIEW = 11;
    static const int TRANSPORTATION_VIEW = 12;
    static const int SETTINGS_VIEW = 13;

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

    QTime getWorkplaceCycleTime() const;
    QTime getWorkplaceSetupTime() const;
    QTime getWorkplaceBasicTime() const;
    QTime getWorkplaceRestTime() const;
    QTime getWorkplaceAllowanceTime() const;

    // LINE VIEW GETTER
    QString getLineName() const;
    QString getLineDescription() const;
    int getLineWorkplaceCount() const;

    // EMPLOYEE VIEW GETTER
    int getEmployeeGender() const;
    int getEmployeeAge() const;
    int getEmployeeHeight() const;
    QString getEmployeeStaffNumber() const;
    QString getEmployeeNote() const;

    // COMMENT VIEW GETTER
    QString getCommentProblemName() const;
    QString getCommentProblemDescription() const;
    QString getCommentMeasureName() const;
    QString getCommentMeasureDescription() const;
    QString getCommentWorkerPerception() const;

    // RESSOURCE MANAGEMENT VIEW
    // EQUIPMENT VIEW GETTER
    QString getEquipmentName() const;
    int getEquipmentRecoilIntensity() const;
    int getEquipmentRecoilCount() const;
    int getEquipmentVibrationIntensity() const;
    int getEquipmentVibrationCount() const;

    // PRODUCT VIEW GETTER
    QString getProductName() const;
    QString getProductNumber() const;
    int getProductTotalPercentage() const;

    // TRANSPORTATION VIEW GETTER
    QString getTransportationName() const;
    int hasTransportationFixedRoller() const;
    int hasTransportationBrakes() const;
    int getTransportationEmptyWeight() const;
    int getTransportationMaxLoad() const;

signals:
    // METADATA VIEW
    void saveMetaData();
    void updateMetaData();

    // WORKPLACELIST VIEW
    void updateWorkplaceList();
    void updateWorkplace(int id);
    void updateWorkplace();
    void createWorkplace();
    void deleteWorkplace(int id);
    void setSelectedWorkplace(int id);

    // WORKPLACE VIEW
    void saveWorkplace();

    // LINE VIEW
    void updateLineView();
    void saveLine();
    void saveSelectedLine(int id);
    void deleteLine(int id);

    // COMMENT VIEW
    void updateCommentView();
    void saveComment();

    // ACTIVITY VIEW
    void updateActivityView();
    void saveActivity();
    void deleteActivity();

    // EMPLOYEE VIEW
    void updateEmployeeView();
    void saveEmployee();

    //DOCUMENTATION VIEW

    //WORKPROCESS
    void createWorkprocess(int type, const QTime &start, const QTime &end);

    // RESSOURCE MANAGEMENT VIEW

    // EQUIPMENT VIEW
    void updateEquipmentView();
    void saveEquipment();
    void deleteEquipment(int id);

    // PRODUCT VIEW
    void updateProductView();
    void saveProduct();
    void deleteProduct(int id);

    // TRANSPORTATION VIEW
    void updateTransportationView();
    void saveTransportation();
    void deleteTransportation(int id);


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
    void setWorkplaceLine(const QString &name, const QString &description);
    void setWorkplaceComment(const QString &problemName, const QString &measureName);
    void setShiftWorkplaceTimes(const QTime &basicTime, const QTime &setupTime, const QTime &restTime, const QTime &allowanceTime, const QTime &cycleTime);

    // LINE VIEW SETTER
    void setLine(const QString &name, const QString &description, int workplaceCount);
    void addLine(int id, const QString &name);
    void clearLines();
    void setSelectedLine(int id);

    // EMPLOYEE VIEW SETTER
    void setEmployee(int gender, int age, int height, const QString &staffNumber, const QString &note);

    // EQUIPMENT VIEW SETTER
    void setEquipment(const QString &name, int recoilIntensity, int recoilCount, int vibrationIntensity, int vibrationCount);
    void addEquipment(int id, const QString &name, int recoilIntensity, int recoilCount, int vibrationIntensity, int vibrationCount);
    void clearEquipment();

    // PRODUCT VIEW SETTER
    void setProduct(const QString &name, const QString &number, int totalPercentage);
    void addProduct(int id, const QString &name);
    void clearProducts();

    // TRANSPORTATION VIEW SETTER
    void setTransportation(const QString &name, int hasFixedRoller, int hasBrakes, int emptyWeight, int maxLoad);
    void addTransportation(int id, const QString &name, int hasFixedRoller, int hasBrakes, int emptyWeight, int maxLoad);
    void clearTransportations();

    // COMMENT VIEW SETTER
    void setComment(const QString &problemName, const QString &problemDesc, const QString &measureName, const QString &measureDesc, const QString &workerPerception);


private slots:

    void backToView();

    void goToMetaDataView();
    void goToWorkplaceListView();
    void goToWorkplaceView();
    void goToWorkplaceView(int id);
    void goToLineView();
    void goToEmployeeView();
    void goToActivityView();
    void goToCommentView();
    void goToDocumentationView();
    void goToRessourceManagementView();
    void goToSettingsView();
    void goToEquipmentView();
    void goToProductView();
    void goToTransportationView();

private:
    QStack<int> *previousViews;
    MainMenu *mainMenuView;
    MetaDataView *metaDataView;
    WorkplaceListView *workplaceListView;
    WorkplaceView *workplaceView;
    LineView *lineView;
    EmployeeView *employeeView;
    ActivityView *activityView;
    CommentView *commentView;
    DocumentationView *documentationView;
    RessourceManagementView *ressourceManagementView;
    ProductView *productView;
    EquipmentView *equipmentView;
    TransportationView *transportationView;

    void goToView(int index);
};

#endif // VIEWCONTROLLER_H
