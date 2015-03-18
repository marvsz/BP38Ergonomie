#include "workplaceview.h"
#include "../separator.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>

WorkplaceView::WorkplaceView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Workplace"), parent),
    btnEmployees(new QPushButton(this)),
    lblName(new QLabel(tr("Name:"))),
    lblDescription(new QLabel(tr("Description:"))),
    lblCode(new QLabel(tr("Code:"))),
    lblPercentageWoman(new QLabel(tr("User population:"))),
    txtBxName(new TextLineEdit()),
    txtBxDescription(new TextLineEdit()),
    txtBxCode(new TextLineEdit()),
    numBxWomanPercentage(new NumberLineEdit()),
    lblGuidelineTimes(new QLabel(tr("Guideline times  [mm:ss]"), this)),
    lblSetupTime(new QLabel(tr("Setup time:"), this)),
    lblBasicTime(new QLabel(tr("Basic time:"), this)),
    lblRestTime(new QLabel(tr("Rest time:"), this)),
    lblAllowanceTime(new QLabel(tr("Deploy time:"),this)),
    lblCycleTime(new QLabel(tr("Cycle time:"))),
    timeSetupTime(new TimeLineEdit(this)),
    timeBasicTime(new TimeLineEdit(this)),
    timeRestTime(new TimeLineEdit(this)),
    timeAllowanceTime(new TimeLineEdit(this)),
    timeCycleTime(new TimeLineEdit(this))
{
    btnEmployees->setObjectName("employeeIcon");
    btnEmployees->setFixedSize(45, 45);
    connect(btnEmployees, SIGNAL(clicked()), this, SLOT(showEmployeeView()));

    lblGuidelineTimes->setObjectName("lblHeader");

    txtBxName->setPlaceholderText(tr("name of the workplace"));
    txtBxDescription->setPlaceholderText(tr("description of the workplace"));
    txtBxCode->setPlaceholderText(tr("code of the workplace"));

    timeBasicTime->setMaximumWidth(100);
    timeBasicTime->setAlignment(Qt::AlignCenter);
    timeSetupTime->setMaximumWidth(100);
    timeSetupTime->setAlignment(Qt::AlignCenter);
    timeRestTime->setMaximumWidth(100);
    timeRestTime->setAlignment(Qt::AlignCenter);
    timeAllowanceTime->setMaximumWidth(100);
    timeAllowanceTime->setAlignment(Qt::AlignCenter);
    timeCycleTime->setMaximumWidth(100);
    timeCycleTime->setAlignment(Qt::AlignCenter);

    QGridLayout *timeLayout = new QGridLayout;

    timeLayout->addWidget(lblSetupTime, 0, 0, 1, 1, Qt::AlignRight);
    timeLayout->addWidget(timeSetupTime, 0, 1, 1, 2, Qt::AlignLeft);
    timeLayout->addWidget(lblBasicTime, 0, 2, 1, 1, Qt::AlignRight);
    timeLayout->addWidget(timeBasicTime, 0, 3, 1, 1, Qt::AlignLeft);
    timeLayout->addWidget(lblRestTime, 0, 4, 1, 1, Qt::AlignRight);
    timeLayout->addWidget(timeRestTime, 0, 5, 1, 1, Qt::AlignLeft);
    timeLayout->addWidget(lblAllowanceTime, 0, 6, 1, 1, Qt::AlignRight);
    timeLayout->addWidget(timeAllowanceTime, 0, 7, 1, 1, Qt::AlignLeft);
    timeLayout->addWidget(lblCycleTime, 0, 8, 1, 1, Qt::AlignRight);
    timeLayout->addWidget(timeCycleTime, 0, 9, 1, 1, Qt::AlignLeft);

    QList<QStringList> lineList;
    QStringList lineListOne;
    lineListOne << tr("label");
    QStringList lineListTwo;
    lineListTwo << tr("description");
    lineList << lineListOne << lineListTwo;

    QList<QStringList> activityList;

    QList<QStringList> commentList;
    QStringList commentListOne;
    commentListOne << tr("problem label");
    QStringList commentListTwo;
    commentListTwo << tr("sanction label");
    commentList << commentListOne << commentListTwo;

    line = new DetailedListItem(this, "lineIcon", tr("line"), lineList, false, false, true);
    activity = new DetailedListItem(this, "activityIcon", tr("activities"), activityList, false, false, true);
    comment = new DetailedListItem(this, "commentIcon", tr("remarks"), commentList, false, false, true);
    employee = new DetailedListItem(this, "employeeIcon", tr("employee"), QList<QStringList>(), false, false, true);

    connect(line, SIGNAL(clicked()), this, SLOT(btnLineClicked()));
    connect(activity, SIGNAL(clicked()), this, SLOT(btnActivityClicked()));
    connect(comment, SIGNAL(clicked()), this, SLOT(btnCommentClicked()));
    connect(employee, SIGNAL(clicked()), this, SLOT(btnEmployeeClicked()));

    QGridLayout *workplaceMetaDataLayout = new QGridLayout;
    workplaceMetaDataLayout->addWidget(lblName, 0, 0, 1, 1, 0);
    workplaceMetaDataLayout->addWidget(txtBxName, 0, 1, 1, 1, 0);
    workplaceMetaDataLayout->addWidget(lblDescription, 0, 2, 1, 1, 0);
    workplaceMetaDataLayout->addWidget(txtBxDescription, 0, 3, 1, 1, 0);
    workplaceMetaDataLayout->addWidget(lblCode, 1, 0, 1, 1, 0);
    workplaceMetaDataLayout->addWidget(txtBxCode, 1, 1, 1, 1, 0);
    workplaceMetaDataLayout->addWidget(lblPercentageWoman, 1, 2, 1, 1, 0);
    workplaceMetaDataLayout->addWidget(numBxWomanPercentage, 1, 3, 1, 1, 0);

    QVBoxLayout *additionsLayout = new QVBoxLayout;
    additionsLayout->addWidget(line);
    additionsLayout->addWidget(employee);
    additionsLayout->addWidget(activity);
    additionsLayout->addWidget(comment);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(workplaceMetaDataLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addWidget(lblGuidelineTimes);
    mainLayout->addLayout(timeLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addLayout(additionsLayout);
    mainLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    setLayout(mainLayout);
}

//public slots
void WorkplaceView::setWorkplace(QHash<QString, QVariant> values){
    txtBxName->setText(values.value(DBConstants::COL_WORKPLACE_NAME).toString());
    txtBxDescription->setText(values.value(DBConstants::COL_WORKPLACE_DESCRIPTION).toString());
    txtBxCode->setText(values.value(DBConstants::COL_WORKPLACE_CODE).toString());
    numBxWomanPercentage->setValue(values.value(DBConstants::COL_WORKPLACE_PERCENTAGE_WOMAN).toInt());
    QTime time = QTime(0, 0);
    timeAllowanceTime->setTime(time.addSecs(values.value(DBConstants::COL_WORKPLACE_ALLOWANCE_TIME).toInt()));
    timeBasicTime->setTime(time.addSecs(values.value(DBConstants::COL_WORKPLACE_BASIC_TIME).toInt()));
    timeCycleTime->setTime(time.addSecs(values.value(DBConstants::COL_WORKPLACE_CYCLE_TIME).toInt()));
    timeRestTime->setTime(time.addSecs(values.value(DBConstants::COL_WORKPLACE_REST_TIME).toInt()));
    timeSetupTime->setTime(time.addSecs(values.value(DBConstants::COL_WORKPLACE_SETUP_TIME).toInt()));
}

void WorkplaceView::setSavedLine(QHash<QString, QVariant> values){
    QList<QStringList> lineList = QList<QStringList>()<<(QStringList()<<values.value(DBConstants::COL_LINE_NAME).toString())<<(QStringList()<<values.value(DBConstants::COL_LINE_DESCRIPTION).toString());
    line->setValues(lineList);
    line->setID(values.value(DBConstants::COL_LINE_ID).toInt());
}

void WorkplaceView::setSavedComment(QHash<QString, QVariant> values){
    QList<QStringList> commentList = QList<QStringList>()<<(QStringList()<<values.value(DBConstants::COL_COMMENT_PROBLEM_NAME).toString())<<(QStringList()<<values.value(DBConstants::COL_COMMENT_MEASURE_NAME).toString());
    comment->setValues(commentList);
    comment->setID(values.value(DBConstants::COL_COMMENT_ID).toInt());
}

void WorkplaceView::onLeaving(){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_WORKPLACE_NAME, txtBxName->text());
    values.insert(DBConstants::COL_WORKPLACE_DESCRIPTION, txtBxDescription->text());
    values.insert(DBConstants::COL_WORKPLACE_CODE, txtBxCode->text());
    values.insert(DBConstants::COL_WORKPLACE_PERCENTAGE_WOMAN, numBxWomanPercentage->getValue());
    QTime time = QTime(0, 0);
    values.insert(DBConstants::COL_WORKPLACE_ALLOWANCE_TIME, time.secsTo(timeAllowanceTime->getTime()));
    values.insert(DBConstants::COL_WORKPLACE_BASIC_TIME, time.secsTo(timeBasicTime->getTime()));
    values.insert(DBConstants::COL_WORKPLACE_CYCLE_TIME, time.secsTo(timeCycleTime->getTime()));
    values.insert(DBConstants::COL_WORKPLACE_REST_TIME, time.secsTo(timeRestTime->getTime()));
    values.insert(DBConstants::COL_WORKPLACE_SETUP_TIME, time.secsTo(timeSetupTime->getTime()));
    emit saveWorkplace(values);
}

QList<QAbstractButton*> * WorkplaceView::getAdditionalNavigation() const{
    QList<QAbstractButton*> *additions = new QList<QAbstractButton*>();
    additions->append(btnEmployees);
    return additions;
}

//private slots
void WorkplaceView::showEmployeeView(){
    emit showView(ViewType::EMPLOYEE_LIST_VIEW);
}

void WorkplaceView::btnLineClicked(){
    emit showView(ViewType::LINE_VIEW);
}

void WorkplaceView::btnActivityClicked(){
    emit showView(ViewType::ACTIVITY_VIEW);
}

void WorkplaceView::btnCommentClicked(){
    emit showView(ViewType::COMMENT_VIEW);
}

void WorkplaceView::btnEmployeeClicked(){
    emit showPopUp(PopUpType::EMPLOYEE_POPUP);
}

