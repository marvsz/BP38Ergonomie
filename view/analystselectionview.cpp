#include "analystselectionview.h"
#include "viewcontroller.h"
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
    txtBxAnalystExperience(new TextLineEdit(this))
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QGridLayout *newAnalystLayout = new QGridLayout;


    btnCreateAnalyst->setMinimumSize(300, 60);
    lblAnalyst->setObjectName("lblHeader");

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
