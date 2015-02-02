#include "workplaceview.h"
#include "separator.h"
#include "iconconstants.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>

WorkplaceView::WorkplaceView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Workplace"), parent),
    id(-1),
    lblName(new QLabel(tr("label:"))),
    lblDescription(new QLabel(tr("description:"))),
    lblCode(new QLabel(tr("workstation code:"))),
    lblPercentageWoman(new QLabel(tr("user population:"))),
    txtBxName(new TextLineEdit()),
    txtBxDescription(new TextLineEdit()),
    txtBxCode(new TextLineEdit()),
    numBxWomanPercentage(new NumberLineEdit()),
    lblAllowedTime(new QLabel(tr("initial time"), this)),
    lblSetupTime(new QLabel(tr("setup time:"), this)),
    lblBasicTime(new QLabel(tr("halt! hammer time:"), this)),
    lblRestTime(new QLabel(tr("rest time:"), this)),
    lblAllowanceTime(new QLabel(tr("deploy time:"),this)),
    lblCycleTime(new QLabel(tr("cycle time:"))),
    timeSetupTime(new TimeLineEdit(this)),
    timeBasicTime(new TimeLineEdit(this)),
    timeRestTime(new TimeLineEdit(this)),
    timeAllowanceTime(new TimeLineEdit(this)),
    timeCycleTime(new TimeLineEdit(this)),
    additions(new QList<DetailedListItem*>())

{
    lblAllowedTime->setObjectName("lblHeader");

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
    timeLayout->addWidget(timeSetupTime, 0, 1, 1, 1, Qt::AlignLeft);
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

    /*QList<QStringList> shiftList;
    QStringList shiftListOne;
    shiftListOne << "Schichtart" << "Stückzahl" << "Taktzeit";
    QStringList shiftListTwo;
    shiftListTwo << "Begin" << "Ende";
    shiftList << shiftListOne << shiftListTwo;

    QList<QStringList> employeeList;
    QStringList employeeListOne;
    employeeListOne << "Geschlecht" << "Alter" << "Größe";
    QStringList employeeListTwo;
    employeeListTwo << "Anmerkung";
    employeeList << employeeListOne << employeeListTwo;*/

    QList<QStringList> activityList;

    QList<QStringList> commentList;
    QStringList commentListOne;
    commentListOne << tr("problem label");
    QStringList commentListTwo;
    commentListTwo << tr("sanction label");
    commentList << commentListOne << commentListTwo;

    line = new DetailedListItem(this, IconConstants::ICON_LINE, tr("line"), lineList, false, false, true);
    activity = new DetailedListItem(this, IconConstants::ICON_ACTIVITY, tr("activities"), activityList, false, false, true);
    comment = new DetailedListItem(this, IconConstants::ICON_COMMENT, tr("remarks"), commentList, false, false, true);

    connect(line, SIGNAL(clicked()), this, SLOT(btnLineClicked()));
    connect(activity, SIGNAL(clicked()), this, SLOT(btnActivityClicked()));
    connect(comment, SIGNAL(clicked()), this, SLOT(btnCommentClicked()));

    additions->append(line);
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
    mainLayout->addWidget(lblAllowedTime);
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
void WorkplaceView::setWorkplaceMetaData(const QString &name, const QString &description, const QString &code, int percentageWoman){
    txtBxName->setText(name);
    txtBxDescription->setText(description);
    txtBxCode->setText(code);
    numBxWomanPercentage->setValue(percentageWoman);
}

void WorkplaceView::setLine(const QString &name, const QString &description){
    QList<QStringList> values = QList<QStringList>() << (QStringList() << name) << (QStringList() << description);
    line->setValues(values);
}

void WorkplaceView::setComment(const QString &problemName, const QString &measureName){
    QList<QStringList> values = QList<QStringList>() << (QStringList() << problemName) << (QStringList() << measureName);
    comment->setValues(values);
}

void WorkplaceView::setWorkplaceTimes(const QTime &basicTime, const QTime &setupTime, const QTime &restTime, const QTime &allowanceTime, const QTime &cycleTime){
    timeBasicTime->setValue(basicTime);
    timeSetupTime->setValue(setupTime);
    timeRestTime->setValue(restTime);
    timeAllowanceTime->setValue(allowanceTime);
    timeCycleTime->setValue(cycleTime);
}

//private slots
void WorkplaceView::btnLineClicked(){
    emit show(ViewType::LINE_VIEW);
}

void WorkplaceView::btnActivityClicked(){
    emit show(ViewType::ACTIVITY_VIEW);
}

void WorkplaceView::btnCommentClicked(){
    emit show(ViewType::COMMENT_VIEW);
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
    return timeBasicTime->getValue();
}

QTime WorkplaceView::getSetupTime() const{
    return timeSetupTime->getValue();
}

QTime WorkplaceView::getRestTime() const{
    return timeRestTime->getValue();
}

QTime WorkplaceView::getAllowanceTime() const{
    return timeAllowanceTime->getValue();
}

QTime WorkplaceView::getCycleTime() const{
    return timeCycleTime->getValue();
}
