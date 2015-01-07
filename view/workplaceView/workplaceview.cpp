#include "workplaceview.h"
#include "separator.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>

WorkplaceView::WorkplaceView(QWidget *parent) :
    QWidget(parent),
    id(-1),
    lblViewDescription(new QLabel("Arbeitsplatz")),
    lblName(new QLabel("Bezeichnung:")),
    lblDescription(new QLabel("Beschreibung:")),
    lblCode(new QLabel("Arbeitsplatz Code:")),
    lblPercentageWoman(new QLabel("Nutzerpopulation:")),
    txtBxName(new TextLineEdit()),
    txtBxDescription(new TextLineEdit()),
    txtBxCode(new TextLineEdit()),
    numBxWomanPercentage(new NumberLineEdit()),
    btnCancel(new QPushButton("Abbruch")),
    btnSave(new QPushButton("Speichern")),
    btnGoOnWithWorkProcesses(new QPushButton("Weiter zu den Arbeitsvorgängen")),
    additions(new QList<DetailedListItem*>())
{
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(btnCancelClicked()));
    connect(btnGoOnWithWorkProcesses, SIGNAL(clicked()), this, SLOT(btnGoOnWithWorkProcessesClicked()));
    btnCancel->setObjectName("btnNavigation");

    QList<QStringList> lineList;
    QStringList lineListOne;
    lineListOne << "Bezeichnung";
    QStringList lineListTwo;
    lineListTwo << "Beschreibung";
    lineList << lineListOne << lineListTwo;

    QList<QStringList> shiftList;
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
    employeeList << employeeListOne << employeeListTwo;

    QList<QStringList> productList;

    QList<QStringList> commentList;
    QStringList commentListOne;
    commentListOne << "Problembezeichnung";
    QStringList commentListTwo;
    commentListTwo << "Maßnahmenbezeichnung";
    commentList << commentListOne << commentListTwo;

    line = new DetailedListItem(this, "", "Linie", lineList, false);
    shift = new DetailedListItem(this, "", "Schicht- und Pausendaten", shiftList, false);
    employee = new DetailedListItem(this, "", "Mitarbeiterdaten", employeeList, false);
    product = new DetailedListItem(this, "", "Produkte", productList, false);
    comment = new DetailedListItem(this, "", "Bemerkungen", commentList, false);

    connect(line, SIGNAL(clicked()), this, SLOT(lineViewSelected()));
    connect(shift, SIGNAL(clicked()), this, SLOT(shiftPauseViewSelected()));
    connect(employee, SIGNAL(clicked()), this, SLOT(employeeViewSelected()));
    connect(product, SIGNAL(clicked()), this, SLOT(productViewSelected()));
    connect(comment, SIGNAL(clicked()), this, SLOT(commentViewSelected()));

    additions->append(line);
    additions->append(shift);
    additions->append(employee);
    additions->append(product);
    additions->append(comment);

    QGridLayout *navigationBarLayout = new QGridLayout;
    navigationBarLayout->addWidget(btnCancel, 0, 0, 1, 1, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewDescription, 0, 1, 1, 1, Qt::AlignCenter);
    navigationBarLayout->addWidget(new QLabel(), 0, 2, 1, 1, Qt::AlignRight);

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

    QHBoxLayout *bottomLineLayout = new QHBoxLayout;
    bottomLineLayout->addWidget(btnSave, 0, Qt::AlignCenter);
    bottomLineLayout->addWidget(btnGoOnWithWorkProcesses, 0, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addLayout(workplaceMetaDataLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addLayout(additionsLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addLayout(bottomLineLayout);
    mainLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

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


//private slots
void WorkplaceView::btnSaveClicked(){
    if(id == -1)
        emit save();
    else
        emit save(id);
}

void WorkplaceView::btnCancelClicked(){
    emit showPreviousView();
}

void WorkplaceView::btnGoOnWithWorkProcessesClicked(){
    emit showWorkprocessView();
}

void WorkplaceView::lineViewSelected(){
    emit showLineView();
}

void WorkplaceView::shiftPauseViewSelected(){
    emit showShiftAndPauseView();
}

void WorkplaceView::employeeViewSelected(){
    emit showEmployeeView();
}

void WorkplaceView::productViewSelected(){
    emit showProductView();
}

void WorkplaceView::commentViewSelected(){
    emit showCommentView();
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
