#include "lineview.h"
#include "separator.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

LineView::LineView(QWidget *parent) : QWidget(parent),
    lblViewName(new QLabel("Linie")),
    lblSelectLine(new QLabel("Linie wählen:")),
    lblAddLine(new QLabel("Linie hinzufügen:")),
    lblName(new QLabel("Bezeichnung:")),
    lblWorkplaceCount(new QLabel("Arbeitsplatzanzahl:")),
    lblDescription(new QLabel("Beschreibung:")),
    txtBxName(new TextLineEdit()),
    numBxWorkplaceCount(new NumberLineEdit()),
    txtBxDescription(new TextEdit()),
    btnBack(new QPushButton("Zurück")),
    btnAdd(new QPushButton("Hinzufügen"))
{
    btnBack->setObjectName("btnNavigation");

    connect(btnBack, SIGNAL(clicked()), this, SLOT(btnBackClicked()));

    connect(btnAdd, SIGNAL(clicked()), this, SLOT(btnAddCicked()));

    QGridLayout *navigationBarLayout = new QGridLayout;
    navigationBarLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewName, 0, 1, 1, 1, Qt::AlignCenter);
    navigationBarLayout->addWidget(new QLabel(), 0, 2, 1, 1, 0);

    QVBoxLayout *lineSelectLayout = new QVBoxLayout;
    lineSelectLayout->addWidget(lblSelectLine);

    QGridLayout *lineAddLayout = new QGridLayout;
    lineAddLayout->addWidget(lblAddLine, 0, 1, 1, 2, 0);
    lineAddLayout->addWidget(lblName, 1, 0, 1, 1, 0);
    lineAddLayout->addWidget(txtBxName, 1, 1, 1, 1, 0);
    lineAddLayout->addWidget(lblWorkplaceCount, 1, 2, 1, 1, 0);
    lineAddLayout->addWidget(numBxWorkplaceCount, 1, 3, 1, 1, 0);
    lineAddLayout->addWidget(lblDescription, 2, 0, 1, 4, 0);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addLayout(lineSelectLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addLayout(lineAddLayout);
    mainLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    setLayout(mainLayout);
}

LineView::~LineView(){

}

//PUBLIC SLOTS
void LineView::setLine(const QString &name, const QString &description, int workplaceCount){
    txtBxName->setText(name);
    txtBxDescription->setText(description);
    numBxWorkplaceCount->setValue(workplaceCount);
}

void LineView::addLine(int id, const QString &name){

}

void LineView::clearLines(){

}

//PRIVATE SLOTS
void LineView::btnBackClicked(){
    emit back();
}

void LineView::btnAddCicked(){
    emit saveLine();
}

void LineView::selectedLineChanged(int id){
    emit saveSelectedLine(id);
}

//GETTER and SETTER
QString LineView::getName() const{
    return txtBxName->text();
}
QString LineView::getDescription() const{
    return txtBxDescription->toPlainText();
}
int LineView::getWorkplaceCount() const{
    return numBxWorkplaceCount->getValue();
}
