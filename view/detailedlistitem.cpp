#include "detailedlistitem.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QSpacerItem>

DetailedListItem::DetailedListItem(QWidget *parent, const QString &iconPath, const QString &name, const QList<QStringList> &scheme, bool isDeletable) :
    QAbstractButton(parent),
    layout(new QGridLayout),
    lblIcon(new QLabel()),
    icon(QPixmap(iconPath)),
    lblName(new QLabel(name)),
    btnDelete(new QPushButton()),
    lblForward(new QLabel(">")),
    listLblValues(QList<QList<QLabel*>>())
{
    QWidget *groupBox = new QWidget;
    groupBox->setObjectName("detailedListItemWidget");

    QVBoxLayout *mainLayout = new QVBoxLayout;

    // SETTINGS FOR GENERAL ELEMENTS
    lblName->setObjectName("detailedListItemWidgetName");
    if(!icon.isNull())
        icon.scaled(50, 50);
    lblIcon->setPixmap(icon);
    lblIcon->setFixedSize(50, 50);
    btnDelete->setFixedSize(45, 45);
    btnDelete->setObjectName("detailedListItemDelete");
    connect(btnDelete, SIGNAL(clicked()), this, SLOT(deleteItem()));

    // ADD SCHEME (DESCRIPTIONS)
    for(int i = 0; i < scheme.count(); ++i){
        QList<QLabel*> listLblsRow;
        for(int j = 0; j < scheme.at(i).count(); ++j){

            QLabel *lblCaption = new QLabel(scheme.at(i).at(j));
            lblCaption->setObjectName("detailedListItemCaption");

            QLabel *lblValue = new QLabel("");
            lblValue->setMinimumWidth(100);
            lblValue->setObjectName("detailedListItemValue");

            listLblsRow.append(lblValue);

            layout->addWidget(lblCaption, i+1, 1+2*j, 1, 1, Qt::AlignLeft);
            layout->addWidget(lblValue, i+1, 2+2*j, 1, 1, Qt::AlignLeft);
        }
        listLblValues.append(listLblsRow);
    }

    // ADD GENERAL ELEMENTS (OR SPACERS)
    layout->addWidget(lblIcon, 0, 0, layout->rowCount(), 1, Qt::AlignLeft);
    layout->addWidget(lblName, 0, 1, 1, layout->columnCount(), Qt::AlignLeft);

    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, layout->columnCount(), layout->rowCount(), 1, 0);
    if(isDeletable){
        layout->addWidget(btnDelete, 0, layout->columnCount(), layout->rowCount(), 1, Qt::AlignRight);
    }
    else {
        layout->addItem(new QSpacerItem(50, 0), 0, layout->columnCount(), layout->rowCount(), 1, Qt::AlignRight);
    }

    layout->addWidget(lblForward, 0, layout->columnCount(), layout->rowCount(), 1, Qt::AlignRight);
    groupBox->setLayout(layout);
    mainLayout->addWidget(groupBox);
    setLayout(mainLayout);

    connect(this, SIGNAL(pressed()), this, SLOT(itemPressed()));
}

void DetailedListItem::paintEvent(QPaintEvent *e){
    QWidget::paintEvent(e);
}

void DetailedListItem::deleteItem(){
    emit deleteItem(id);
}

void DetailedListItem::itemPressed(){
    emit pressed(id);
}

void DetailedListItem::setValues(const QList<QStringList> &values){
    for(int i = 0; i < values.count(); ++i){
        for(int j = 0; j < values.at(i).count(); ++j){
            listLblValues.at(i).at(j)->setText(values.at(i).at(j));
        }
    }
}


int DetailedListItem::getID() const{
    return id;
}
void DetailedListItem::setID(int id){
    this->id = id;
}
