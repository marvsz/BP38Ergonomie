#include "activityview.h"
#include "../separator.h"
#include "../flickcharm.h"
#include "../detailedlistitem.h"
#include "../../databaseHandler/dbconstants.h"

ActivityView::ActivityView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Activities"), parent),
    mainLayout(new QVBoxLayout),
    productListLayout(new QVBoxLayout),
    activityListLayout(new QVBoxLayout),
    productListContent(new QWidget()),
    activityListContent(new QWidget()),
    scProducts(new QScrollArea()),
    scActivities(new QScrollArea()),
    lblAddActivity(new QLabel(tr("Add Activity"))),
    lblActivityDescription(new QLabel(tr("Description:"))),
    lblActivityRepetitions(new QLabel(tr("Repetitions:"))),
    lblChooseProduct(new QLabel(tr("Choose Product"))),
    txtBxActivityDescription(new TextLineEdit()),
    numBxActivityRepetitions(new NumberLineEdit()),
    btnAdd(new QPushButton()),
    btnMoreProducts(new QPushButton())
{
    productListContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scProducts->setWidget(productListContent);
    scProducts->setWidgetResizable(true);
    scProducts->setFixedHeight(200);
    scProducts->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    scProducts->setObjectName("saBordered");
    productListContent->setLayout(productListLayout);

    FlickCharm *flickCharmProducts = new FlickCharm(this);
    flickCharmProducts->activateOn(scProducts);

    activityListContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scActivities->setWidget(activityListContent);
    scActivities->setWidgetResizable(true);
    activityListContent->setLayout(activityListLayout);

    FlickCharm *flickCharmActivities = new FlickCharm(this);
    flickCharmActivities->activateOn(scActivities);

    btnMoreProducts->setFixedSize(45, 45);
    btnMoreProducts->setObjectName("editIcon");
    connect(btnMoreProducts, SIGNAL(clicked()), this, SLOT(btnProductsClicked()));

    btnAdd->setFixedSize(45, 45);
    btnAdd->setObjectName("plusIcon");
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(btnAddClicked()));

    lblAddActivity->setObjectName("lblHeader");
    txtBxActivityDescription->setPlaceholderText(tr("description"));
    txtBxActivityDescription->setMinimumWidth(300);
    numBxActivityRepetitions->setPlaceholderText(tr("amout of repetitions"));
    numBxActivityRepetitions->setMinimumWidth(300);
    lblChooseProduct->setObjectName("lblHeader");

    lblAddActivity->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    lblActivityDescription->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    txtBxActivityDescription->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    lblActivityRepetitions->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    numBxActivityRepetitions->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    btnAdd->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    lblChooseProduct->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    btnMoreProducts->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    QGridLayout *newActivityLayout = new QGridLayout;
    newActivityLayout->setContentsMargins(0,0,0,0);
    newActivityLayout->addWidget(lblAddActivity, 0, 0, 1, 2, 0);
    newActivityLayout->addWidget(lblActivityDescription, 1, 0, 2, 1, 0);
    newActivityLayout->addWidget(txtBxActivityDescription, 1, 1, 2, 1, Qt::AlignLeft);
    newActivityLayout->addWidget(lblActivityRepetitions, 3, 0, 2, 1, 0);
    newActivityLayout->addWidget(numBxActivityRepetitions, 3, 1, 2, 1, Qt::AlignLeft);
    newActivityLayout->addWidget(btnAdd, 5, 1, 1, 1, Qt::AlignCenter);
    newActivityLayout->addWidget(lblChooseProduct, 0, 2, 1, 1, Qt::AlignCenter);
    newActivityLayout->addWidget(scProducts, 1, 2, 4, 1, Qt::AlignTop);
    newActivityLayout->addWidget(btnMoreProducts, 5, 2, 1, 1, Qt::AlignCenter);

    mainLayout->addLayout(newActivityLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addWidget(scActivities);

    productListLayout->setAlignment(Qt::AlignTop);
    activityListLayout->setAlignment(Qt::AlignTop);

    setLayout(mainLayout);
}

// PUBLIC SLOTS

void ActivityView::addActivity(QHash<QString, QVariant> values){
    DetailedListItem *newListItem = new DetailedListItem(this, "activityIcon", values.value(DBConstants::COL_ACTIVITY_DESCRIPTION).toString(), activityItemScheme, true, false, true, false, true);
    newListItem->setID(values.value(DBConstants::COL_ACTIVITY_ID).toInt());

    QList<QStringList> dliValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_ACTIVITY_REPETITIONS).toString());
    newListItem->setValues(dliValues);
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(deleteActivity(int)));
    connect(newListItem, SIGNAL(pressed(int)), this, SLOT(dliActivityClicked(int)));
    connect(newListItem, SIGNAL(editItem(int)), this, SLOT(editActivityClicked(int)));
    activityListLayout->addWidget(newListItem);
}

void ActivityView::updateActivity(QHash<QString, QVariant> values){
    QLayoutItem *item;
    int id = values.value(DBConstants::COL_ACTIVITY_ID).toInt();
    int i = 0;
    while((item = activityListLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            dli->setName(values.value(DBConstants::COL_ACTIVITY_DESCRIPTION).toString());
            QList<QStringList> dliValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_ACTIVITY_REPETITIONS).toString());
            dli->setValues(dliValues);
            break;
        }
        i++;
    }
}

void ActivityView::removeActivity(int id){
    QLayoutItem *item;
    int i = 0;
    while((item = activityListLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            activityListLayout->removeItem(item);
            delete item->widget();
            delete item;
            break;
        }
        i++;
    }
}

void ActivityView::clearActivities(){
    QLayoutItem *item;
    while((item = activityListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

void ActivityView::addProduct(QHash<QString, QVariant> values){
    QList<QStringList> dliValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_PRODUCT_NUMBER).toString());
    DetailedListItem *newListItem = new DetailedListItem(this, "productIcon", values.value(DBConstants::COL_PRODUCT_NAME).toString(), productItemScheme, false, true, false, false, false);
    newListItem->setValues(dliValues);
    newListItem->setID(values.value(DBConstants::COL_PRODUCT_ID).toInt());
    connect(newListItem, SIGNAL(selected(int)), this, SLOT(selectedProductChanged(int)));
    connect(newListItem, SIGNAL(deselected(int)), this, SLOT(deselectProduct(int)));
    connect(this, SIGNAL(selectedProduct(int)), newListItem, SLOT(selectExclusiveWithID(int)));
    productListLayout->addWidget(newListItem);
}

void ActivityView::updateProduct(QHash<QString, QVariant> values){
    QLayoutItem *item;
    int id = values.value(DBConstants::COL_PRODUCT_ID).toInt();
    int i = 0;
    while((item = productListLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            QList<QStringList> dliValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_PRODUCT_NUMBER).toString());
            dli->setName(values.value(DBConstants::COL_PRODUCT_NAME).toString());
            dli->setValues(dliValues);
            break;
        }
        i++;
    }
}

void ActivityView::removeProduct(int id){
    QLayoutItem *item;
    int i = 0;
    while((item = productListLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            productListLayout->removeItem(item);
            delete item->widget();
            delete item;
            break;
        }
        i++;
    }
}

void ActivityView::clearProducts(){
    QLayoutItem *item;
    while((item = productListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

// PRIVATE SLOTS
void ActivityView::editActivityClicked(int id){
    emit editActivity(id);
    emit showPopUp(PopUpType::ACTIVITY_POPUP);
}

void ActivityView::btnAddClicked(){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_ACTIVITY_DESCRIPTION, txtBxActivityDescription->text());
    values.insert(DBConstants::COL_ACTIVITY_REPETITIONS, numBxActivityRepetitions->getValue());
    values.insert(DBConstants::COL_ACTIVITY_PRODUCT_ID, selectedProductID);
    emit createActivity(values);
    txtBxActivityDescription->clear();
    numBxActivityRepetitions->clear();
    selectedProduct(-1);
}

void ActivityView::selectedProductChanged(int id){
    selectedProductID = id;
    emit selectedProduct(id);
}

void ActivityView::deselectProduct(int id){
    if(id == selectedProductID)
        selectedProductID = 0;
}

void ActivityView::btnProductsClicked(){
    emit showPopUp(PopUpType::CREATE_PRODUCT_POPUP);
}

void ActivityView::dliActivityClicked(int id){
    emit selectActivity(id);
    emit showView(ViewType::DOCUMENTATION_VIEW);
}

