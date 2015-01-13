#include "analystselectionview.h"
#include "viewcontroller.h"
#include "separator.h"

AnalystSelectionView::AnalystSelectionView(QWidget *parent) :
    QWidget(parent),
    btnCreateAnalyst(new QPushButton(tr("Create new Analyst"))),
    lblAnalyst(new QLabel(tr("analyst"), this)),
    lblAnalystLastName(new QLabel(tr("last name:"), this)),
    lblAnalystFirstName(new QLabel(tr("prename:"), this)),
    lblAnalystEmployer(new QLabel(tr("employer:"), this)),
    lblAnalystExperience(new QLabel(tr("experience:"), this)),
    txtBxAnalystLastName(new TextLineEdit(this)),
    txtBxAnalystFirstName(new TextLineEdit(this)),
    txtBxAnalystEmployer(new TextLineEdit(this)),
    txtBxAnalystExperience(new TextLineEdit(this)),
    createAnalyst(new QWidget(this)),
    listContentLayout(new QVBoxLayout)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QGridLayout *newAnalystLayout = new QGridLayout;

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

    createAnalyst->setLayout(newAnalystLayout);
    createAnalyst->hide();



    btnCreateAnalyst->setMinimumSize(300, 60);
    lblAnalyst->setObjectName("lblHeader");


    mainLayout->addWidget(lblAnalyst);
    mainLayout->addLayout(newAnalystLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addWidget(createAnalyst);
    mainLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    setLayout(mainLayout);

    connect(btnCreateAnalyst, SIGNAL(clicked), this, SLOT(showCreateAnalyst()));
}

void AnalystSelectionView::showCreateAnalyst(){
    btnCreateAnalyst->setEnabled(false);

    createAnalyst->show();

}

void AnalystSelectionView::dliPressed(int id){
    emit select(id);
    emit forward();
}

void AnalystSelectionView::add(int id, const QString &lastName, const QString &firstName){
    QString name = lastName + firstName;

    DetailedListItem *newListItem = new DetailedListItem(this, "", name, QList<QStringList>(), true, false, true);

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





