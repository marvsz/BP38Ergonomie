#include "workplaceview.h"
#include "../separator.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>

WorkplaceView::WorkplaceView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Workplace"), parent),
    id(-1),
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
    timeCycleTime(new TimeLineEdit(this)),
    additions(new QList<DetailedListItem*>())

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

    additions->append(line);
    additions->append(employee);
    additions->append(activity);
    additions->append(comment);

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
    for(int i = 0; i < additions->count(); ++i){
        additionsLayout->addWidget(additions->at(i));
    }

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

WorkplaceView::WorkplaceView(int id, QWidget *parent) : WorkplaceView(parent){
    this->id = id;
}

//public slots
QList<QAbstractButton*> * WorkplaceView::getAdditionalNavigation() const{
    QList<QAbstractButton*> *additions = new QList<QAbstractButton*>();
    additions->append(btnEmployees);
    return additions;
}

void WorkplaceView::setName(const QString &name){
    txtBxName->setText(name);
}

void WorkplaceView::setDescription(const QString &description){
    txtBxDescription->setText(description);
}

void WorkplaceView::setCode(const QString &code){
    txtBxCode->setText(code);
}

void WorkplaceView::setWomanPercentage(int womenPercentage){
    numBxWomanPercentage->setValue(womenPercentage);
}

void WorkplaceView::setBasicTime(const QTime &basic){
    timeBasicTime->setTime(basic);
}

void WorkplaceView::setSetupTime(const QTime &setup){
    timeSetupTime->setTime(setup);
}

void WorkplaceView::setRestTime(const QTime &rest){
    timeRestTime->setTime(rest);
}

void WorkplaceView::setAllowanceTime(const QTime &allowance){
    timeAllowanceTime->setTime(allowance);
}

void WorkplaceView::setCycleTime(const QTime &cycle){
    timeCycleTime->setTime(cycle);
}

void WorkplaceView::setLine(const QString &name, const QString &description){
    QList<QStringList> values = QList<QStringList>() << (QStringList() << name) << (QStringList() << description);
    line->setValues(values);
}

void WorkplaceView::setComment(const QString &problemName, const QString &measureName){
    QList<QStringList> values = QList<QStringList>() << (QStringList() << problemName) << (QStringList() << measureName);
    comment->setValues(values);
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
    emit showPopUp(PopUpType::EMPlOYEE_POPUP);
}

// GETTER
QString WorkplaceView::getName() const{
    return txtBxName->text();
}

QString WorkplaceView::getDescription() const{
    return txtBxDescription->text();
}

QString WorkplaceView::getCode() const{
    return txtBxCode->text();
}

int WorkplaceView::getWomanPercentage() const{
    return numBxWomanPercentage->getValue();
}

QTime WorkplaceView::getBasicTime() const{
    return timeBasicTime->getTime();
}

QTime WorkplaceView::getSetupTime() const{
    return timeSetupTime->getTime();
}

QTime WorkplaceView::getRestTime() const{
    return timeRestTime->getTime();
}

QTime WorkplaceView::getAllowanceTime() const{
    return timeAllowanceTime->getTime();
}

QTime WorkplaceView::getCycleTime() const{
    return timeCycleTime->getTime();
}
