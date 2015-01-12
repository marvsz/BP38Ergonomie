#include "activityview.h"
#include "separator.h"
#include "flickcharm.h"
#include "detailedlistitem.h"

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
    txtBxActivityDescription(new TextLineEdit()),
    numBxActivityRepetitions(new NumberLineEdit()),
    btnAdd(new QPushButton()),
    btnMoreProducts(new QPushButton())
{
    productListContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scProducts->setWidget(productListContent);
    scProducts->setFixedHeight(200);
    scProducts->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    scProducts->setWidgetResizable(true);
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
    numBxActivityRepetitions->setPlaceholderText(tr("amout of repetitions"));

    QGridLayout *newActivityLayout = new QGridLayout;
    newActivityLayout->setContentsMargins(0,0,0,0);
    newActivityLayout->addWidget(lblAddActivity, 0, 0, 1, 2, 0);
    newActivityLayout->addWidget(lblActivityDescription, 1, 0, 1, 1, 0);
    newActivityLayout->addWidget(txtBxActivityDescription, 1, 1, 1, 1, Qt::AlignLeft);
    newActivityLayout->addWidget(lblActivityRepetitions, 2, 0, 1, 1, 0);
    newActivityLayout->addWidget(numBxActivityRepetitions, 2, 1, 1, 1, Qt::AlignLeft);
    newActivityLayout->addWidget(btnAdd, 3, 1, 1, 1, Qt::AlignCenter);
    newActivityLayout->addWidget(scProducts, 0, 2, 3, 1, 0);
    newActivityLayout->addWidget(btnMoreProducts, 3, 2, 1, 1, Qt::AlignCenter);

    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addLayout(newActivityLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addWidget(scActivities);

    setLayout(mainLayout);

    addProduct(1, "Test1");
    addProduct(2, "Test2");
    addProduct(3, "Test3");
    addProduct(4, "Test4");

    addActivity(1, "Tolle Aktivität");
    addActivity(2, "Doofe Aktivität");
    addActivity(3, "Langweilig Aktivität");
    addActivity(4, "Super Aktivität");
    addActivity(4, "Scheiß Aktivität");
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
    emit productSelected(selectedProductID);
}

void ActivityView::btnAddClicked(){
    emit saveActivity();
    txtBxActivityDescription->clear();
    numBxActivityRepetitions->clear();
}

void ActivityView::selectedProductChanged(int id){
    selectedProductID = id;
    emit productSelected(id);
}

// PUBLIC SLOTS
void ActivityView::addProduct(int id, const QString &name){
    DetailedListItem *newListItem = new DetailedListItem(this, "", name, QList<QStringList>(), false, true, false);
    newListItem->setID(id);
    newListItem->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    connect(newListItem, SIGNAL(selected(int)), this, SLOT(selectedProductChanged(int)));
    connect(this, SIGNAL(productSelected(int)), newListItem, SLOT(selectExclusiveWithID(int)));
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

void ActivityView::addActivity(int id, const QString &description){
    DetailedListItem *newListItem = new DetailedListItem(0, "", description, QList<QStringList>(), true, false, true);
    newListItem->setID(id);
    connect(newListItem, SIGNAL(pressed(int)), this, SIGNAL(showWorkProcessView(int)));
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(deleteActivity(int)));
    activityListLayout->addWidget(newListItem);
}

void ActivityView::clearActivities(){
    QLayoutItem *item;
    while((item = activityListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}