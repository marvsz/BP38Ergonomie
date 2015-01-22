#include "activityview.h"
#include "separator.h"
#include "flickcharm.h"
#include "detailedlistitem.h"
#include "iconconstants.h"

ActivityView::ActivityView(QWidget *parent) :
    QWidget(parent),
    mainLayout(new QVBoxLayout),
    productListLayout(new QVBoxLayout),
    activityListLayout(new QVBoxLayout),
    lblViewName(new QLabel(tr("Activities"))),
    btnBack(new QPushButton()),
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

    btnBack->setFixedSize(45, 45);
    btnBack->setObjectName("leftIcon");
    connect(btnBack, SIGNAL(clicked()), this, SIGNAL(back()));

    btnMoreProducts->setFixedSize(45, 45);
    btnMoreProducts->setObjectName("editIcon");
    connect(btnMoreProducts, SIGNAL(clicked()), this, SIGNAL(showProductView()));

    QGridLayout *navigationBarLayout = new QGridLayout;
    navigationBarLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewName, 0, 1, 1, 1, Qt::AlignCenter);
    navigationBarLayout->addWidget(new QLabel(), 0, 2, 1, 1, 0);

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

    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addLayout(newActivityLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addWidget(scActivities);

    setLayout(mainLayout);
}

// GETTER
QString ActivityView::getDescription() const {
    return txtBxActivityDescription->text();
}

int ActivityView::getRepetitions() const {
    return numBxActivityRepetitions->getValue();
}

int ActivityView::getSelectedProduct() const {
    return this->selectedProductID;
}

// PRIVATE SLOTS
void ActivityView::btnBackClicked(){
    emit back();
}

void ActivityView::btnAddClicked(){
    emit createActivity();
    txtBxActivityDescription->clear();
    numBxActivityRepetitions->clear();
}

void ActivityView::selectedProductChanged(int id){
    selectedProductID = id;
    emit selectedProduct(id);
}

// PUBLIC SLOTS
void ActivityView::addProduct(int id, const QString &name, const QString &productNumber){
    DetailedListItem *newListItem = new DetailedListItem(0, IconConstants::ICON_PRODUCT, name, productItemScheme, false, true, false);
    newListItem->setID(id);
    QList<QStringList> values = QList<QStringList>() << (QStringList() << productNumber);
    newListItem->setValues(values);
    newListItem->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    connect(newListItem, SIGNAL(selected(int)), this, SLOT(selectedProductChanged(int)));
    connect(this, SIGNAL(selectedProduct(int)), newListItem, SLOT(selectExclusiveWithID(int)));
    productListLayout->addWidget(newListItem);
}

void ActivityView::clearProducts(){
    QLayoutItem *item;
    while((item = productListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

void ActivityView::setSelectedProduct(int id){
    selectedProductChanged(id);
}

void ActivityView::setActivity(const QString &description, int repetitions, int selectedProductID){
    txtBxActivityDescription->setText(description);
    numBxActivityRepetitions->setValue(repetitions);
    this->selectedProductID = selectedProductID;
}

void ActivityView::addActivity(int id, const QString &description, int repetitions){
    DetailedListItem *newListItem = new DetailedListItem(0, IconConstants::ICON_ACTIVITY, description, activityItemScheme, true, false, true);
    newListItem->setID(id);
    QList<QStringList> values = QList<QStringList>() << (QStringList() << QString::number(repetitions));
    newListItem->setValues(values);
    connect(newListItem, SIGNAL(clicked()), this, SIGNAL(showWorkProcessView()));
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(deleteActivity(int)));
    connect(newListItem, SIGNAL(pressed(int)), this, SIGNAL(selectActivity(int)));
    activityListLayout->addWidget(newListItem);
}

void ActivityView::clearActivities(){
    QLayoutItem *item;
    while((item = activityListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}
