#include "analystselectionview.h"
#include "separator.h"
#include "iconconstants.h"
#include "flickcharm.h"

AnalystSelectionView::AnalystSelectionView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Analyst selection"), parent),
    status(false),
    btnMaximize(new QPushButton()),
    btnMinimize(new QPushButton()),
    btnCreateAnalyst(new QPushButton()),
    lblAnalyst(new QLabel(tr("Choose or create new profile"), this)),
    lblAnalystLastName(new QLabel(tr("last name:"), this)),
    lblAnalystFirstName(new QLabel(tr("prename:"), this)),
    lblAnalystEmployer(new QLabel(tr("employer:"), this)),
    lblAnalystExperience(new QLabel(tr("experience:"), this)),
    txtBxAnalystLastName(new TextLineEdit(this)),
    txtBxAnalystFirstName(new TextLineEdit(this)),
    txtBxAnalystEmployer(new TextLineEdit(this)),
    txtBxAnalystExperience(new TextLineEdit(this)),
    createAnalyst(new QWidget(this)),
    listContentLayout(new QVBoxLayout()),
    scAnalysts(new QScrollArea(this))
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *maximizedFooterLayout = new QHBoxLayout;
    QGridLayout *newAnalystLayout = new QGridLayout;

    maximizedFooterLayout->addWidget(btnMinimize,0,Qt::AlignLeft);
    maximizedFooterLayout->addWidget(btnCreateAnalyst,0,Qt::AlignRight);

    QWidget *maximizedFooter = new QWidget;
    maximizedFooter->setLayout(maximizedFooterLayout);

    newAnalystLayout->addWidget(lblAnalystLastName, 0, 0, 1, 1, 0);
    newAnalystLayout->addWidget(txtBxAnalystLastName, 0, 1, 1, 1, 0);
    newAnalystLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 0, 2, 1, 1, 0);
    newAnalystLayout->addWidget(lblAnalystFirstName, 0, 3, 1, 1, 0);
    newAnalystLayout->addWidget(txtBxAnalystFirstName, 0, 4, 1, 1, 0);
    newAnalystLayout->addWidget(lblAnalystEmployer, 1, 0, 1, 1, 0);
    newAnalystLayout->addWidget(txtBxAnalystEmployer, 1, 1, 1, 1, 0);
    newAnalystLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 1, 2, 1, 1, 0);
    newAnalystLayout->addWidget(lblAnalystExperience, 1, 3, 1, 1, 0);
    newAnalystLayout->addWidget(txtBxAnalystExperience, 1, 4, 1, 1, 0);
    newAnalystLayout->addWidget(maximizedFooter, 2, 0, 1, 10, 0);

    createAnalyst->setLayout(newAnalystLayout);
    createAnalyst->hide();

    btnMaximize->setFixedSize(45, 45);
    btnMaximize->setObjectName("downIcon");

    btnMinimize->setFixedSize(45, 45);
    btnMinimize->setObjectName("upIcon");
    btnMinimize->hide();

    btnCreateAnalyst->setFixedSize(45, 45);
    btnCreateAnalyst->setObjectName("plusIcon");

    lblAnalyst->setObjectName("lblHeader");

    QWidget *listContent = new QWidget;
    listContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scAnalysts->setWidget(listContent);
    scAnalysts->setWidgetResizable(true);
    scAnalysts->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    listContent->setLayout(listContentLayout);
    listContentLayout->setAlignment(Qt::AlignTop);

    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scAnalysts);

    mainLayout->addWidget(lblAnalyst);
    mainLayout->addWidget(btnMaximize);
    mainLayout->setAlignment(btnMaximize, Qt::AlignLeft);
    mainLayout->addWidget(createAnalyst);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addWidget(scAnalysts);

    setLayout(mainLayout);

    connect(btnMaximize, SIGNAL(clicked()), this, SLOT(btnMaximizeClicked()));
    connect(btnMinimize, SIGNAL(clicked()), this, SLOT(btnMinimizeClicked()));
    connect(btnCreateAnalyst, SIGNAL(clicked()), this, SLOT(btnCreateAnalystClicked()));
}

void AnalystSelectionView::btnMaximizeClicked(){
    btnMaximize->hide();
    createAnalyst->show();
    btnMinimize->show();
}

void AnalystSelectionView::btnMinimizeClicked(){
    btnMaximize->show();
    createAnalyst->hide();
    btnMinimize->hide();
}

void AnalystSelectionView::dliPressed(int id){
    emit select(id);
    emit showView(ViewType::MAIN_MENU_VIEW);
}

void AnalystSelectionView::btnCreateAnalystClicked(){
    emit create();
    txtBxAnalystLastName->clear();
    txtBxAnalystFirstName->clear();
    txtBxAnalystEmployer->clear();
    txtBxAnalystExperience->clear();
}

void AnalystSelectionView::add(int id, const QString &lastName, const QString &firstName){
    QString name = lastName + ", " + firstName;

    DetailedListItem *newListItem = new DetailedListItem(this, IconConstants::ICON_USER, name, QList<QStringList>(), true, false, true);

    newListItem->setID(id);
    connect(newListItem, SIGNAL(pressed(int)), this, SLOT(dliPressed(int)));
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(remove(int)));
    listContentLayout->addWidget(newListItem);
}

void AnalystSelectionView::clear(){
    QLayoutItem *item;
    while((item = listContentLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

// GETTER

QString AnalystSelectionView::getAnalystLastName() const {
    return txtBxAnalystLastName->text();
}

QString AnalystSelectionView::getAnalystFirstName() const {
    return txtBxAnalystFirstName->text();
}

QString AnalystSelectionView::getAnalystEmployer() const {
    return txtBxAnalystEmployer->text();
}

QString AnalystSelectionView::getAnalystExperience() const {
    return txtBxAnalystExperience->text();
}





