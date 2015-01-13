#include "analystselectionview.h"
#include "viewcontroller.h"
#include "separator.h"
#include <QVBoxLayout>

AnalystSelectionView::AnalystSelectionView(QWidget *parent) :
    QWidget(parent),
    btnCreateAnalyst(new QPushButton(tr("Create new Analyst"))),
    lblAnalyst(new QLabel(tr("analyst"), this)),
    lblAnalystLastName(new QLabel(tr("last name:"), this)),
    lblAnalystEmployer(new QLabel(tr("employer:"), this)),
    lblAnalystFirstName(new QLabel(tr("prename:"), this)),
    txtBxAnalystLastName(new TextLineEdit(this)),
    txtBxAnalystFirstName(new TextLineEdit(this)),
    txtBxAnalystEmployer(new TextLineEdit(this)),
    txtBxAnalystExperience(new TextLineEdit(this)),
    //spacer1(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed),
    //spacer2(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed),
    analysts(new QList<DetailedListItem*>())
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QVBoxLayout *listContentLayout = new QVBoxLayout;
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


    btnCreateAnalyst->setMinimumSize(300, 60);
    lblAnalyst->setObjectName("lblHeader");

    lblAnalystLastName->setVisible(false);
    lblAnalystFirstName->setVisible(false);
    lblAnalystEmployer->setVisible(false);
    lblAnalystExperience->setVisible(false);
    txtBxAnalystLastName->setVisible(false);
    txtBxAnalystFirstName->setVisible(false);
    txtBxAnalystEmployer->setVisible(false);
    txtBxAnalystExperience->setVisible(false);

    mainLayout->addWidget(lblAnalyst);
    mainLayout->addLayout(newAnalystLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addLayout(existingAnalystsLayout);
    mainLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    setLayout(mainLayout);

    connect(btnCreateAnalyst, SIGNAL(clicked), this, SLOT(showCreateAnalyst()));
}

void AnalystSelectionView::showCreateAnalyst(){
    btnCreateAnalyst->setEnabled(false);

    lblAnalystLastName->setVisible(true);
    lblAnalystFirstName->setVisible(true);
    lblAnalystEmployer->setVisible(true);
    lblAnalystExperience->setVisible(true);
    txtBxAnalystLastName->setVisible(true);
    txtBxAnalystFirstName->setVisible(true);
    txtBxAnalystEmployer->setVisible(true);
    txtBxAnalystExperience->setVisible(true);

}

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

void AnalystSelectionView::dliPressed(int id){
    emit select(id);
    emit forward();
}



