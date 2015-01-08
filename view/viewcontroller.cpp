#include "viewcontroller.h"

ViewController::ViewController(QWidget *parent) :
    QStackedWidget(parent)
{
    previousViews = new QStack<int>();
    mainMenuView = new MainMenu;
    metaDataView = new MetaDataView;
    workplaceListView = new WorkplaceListView;
    workplaceView = new WorkplaceView;
    lineView = new LineView;
    shiftPauseView = new ShiftPauseView;
    productView = new ProductView;
    commentView = new CommentView;
    employeeView = new EmployeeView;
    documentationView = new DocumentationView;

    // MAIN MENU
    connect(mainMenuView, SIGNAL(metaDataViewSelected()), this, SLOT(goToMetaDataView()));
    connect(mainMenuView, SIGNAL(workplaceListViewSelected()), this, SLOT(goToWorkplaceListView()));
    connect(mainMenuView, SIGNAL(newRecordingViewSelected()), this, SLOT(goToDocumentationView()));

    // METADATA VIEW
    connect(metaDataView, SIGNAL(showMainMenu()), this, SLOT(backToView()));
    connect(metaDataView, SIGNAL(showWorkplaceListView()), this, SLOT(goToWorkplaceListView()));
    connect(metaDataView, SIGNAL(saveMetaData()), this, SLOT(saveMetaDataRequested()));

    // WORKPLACE LIST VIEW
    connect(workplaceListView, SIGNAL(showPreviousView()), this, SLOT(backToView()));
    connect(workplaceListView, SIGNAL(showNewWorkplaceView()), this, SLOT(goToWorkplaceView()));
    connect(workplaceListView, SIGNAL(showWorkplace(int)), this, SLOT(goToWorkplaceView(int)));
    connect(workplaceListView, SIGNAL(deleteWorkplace(int)), this, SLOT(deleteWorkplaceRequested(int)));

    // WORKPLACE VIEW
    connect(workplaceView, SIGNAL(back()), this, SLOT(backToView()));
    connect(workplaceView, SIGNAL(save()), this, SLOT(saveWorkplaceRequested()));
    connect(workplaceView, SIGNAL(forward()), this, SLOT(goToDocumentationView()));
    connect(workplaceView, SIGNAL(showLineView()), this, SLOT(goToLineView()));
    connect(workplaceView, SIGNAL(showShiftAndPauseView()), this, SLOT(goToShiftAndPauseView()));
    connect(workplaceView, SIGNAL(showEmployeeView()), this, SLOT(goToEmployeeView()));
    connect(workplaceView, SIGNAL(showProductView()), this, SLOT(goToProductView()));
    connect(workplaceView, SIGNAL(showCommentView()), this, SLOT(goToCommentView()));

    // LINE VIEW
    connect(lineView, SIGNAL(back()), this, SLOT(backToView()));
    connect(lineView, SIGNAL(deleteLine(int)), this, SLOT(deleteLineRequested(int)));
    connect(lineView, SIGNAL(saveLine()), this, SLOT(saveLineRequested()));
    connect(lineView, SIGNAL(saveSelectedLine(int)), this, SLOT(saveSelectedLineRequested(int)));

    // SHIFTPAUSE VIEW
    connect(shiftPauseView, SIGNAL(back()), this, SLOT(backToView()));

    // EMPLOYEE VIEW
    connect(employeeView, SIGNAL(back()), this, SLOT(backToView()));

    // PRODUCT VIEW
    connect(productView, SIGNAL(back()), this, SLOT(backToView()));
    connect(productView, SIGNAL(deleteProduct(int)), this, SLOT(deleteProductRequested(int)));
    connect(productView, SIGNAL(saveProduct()), this, SLOT(saveProductRequested()));
    connect(productView, SIGNAL(saveSelectedProducts()), this, SLOT(saveSelectedProductsRequested()));

    // COMMENT VIEW
    connect(commentView, SIGNAL(back()), this, SLOT(backToView()));
    connect(commentView, SIGNAL(save()), this, SLOT(saveCommentRequested()));

    // DOCUMENTATION VIEW
    connect(documentationView, SIGNAL(showPreviousView()), this, SLOT(backToView()));

    // ADD ALL VIEWS
    this->addWidget(mainMenuView);
    this->addWidget(metaDataView);
    this->addWidget(workplaceListView);
    this->addWidget(workplaceView);
    this->addWidget(lineView);
    this->addWidget(shiftPauseView);
    this->addWidget(employeeView);
    this->addWidget(productView);
    this->addWidget(commentView);
    this->addWidget(documentationView);

    setCurrentIndex(ViewController::MAIN_MENU_VIEW);
}

void ViewController::goToMetaDataView(){
    goToView(ViewController::METADATA_VIEW);
}

void ViewController::goToWorkplaceListView(){
    emit updateWorkplaceList();
    goToView(ViewController::WORKPLACELIST_VIEW);
}

void ViewController::goToWorkplaceView(){
    emit createWorkplace();
    goToView(ViewController::WORKPLACE_VIEW);
}

void ViewController::goToWorkplaceView(int id){
    emit updateWorkplace(id);
    goToView(ViewController::WORKPLACE_VIEW);
}

void ViewController::goToLineView(){
    emit updateLineView();
    goToView(ViewController::LINE_VIEW);
}

void ViewController::goToShiftAndPauseView(){
    goToView(ViewController::SHIFTPAUSE_VIEW);
}

void ViewController::goToEmployeeView(){
    emit updateEmployeeView();
    goToView(ViewController::EMPLOYEE_VIEW);
}

void ViewController::goToProductView(){
    emit updateProductView();
    goToView(ViewController::PRODUCT_VIEW);
}

void ViewController::goToCommentView(){
    emit updateCommentView();
    goToView(ViewController::COMMENT_VIEW);
}

void ViewController::goToDocumentationView(){
    goToView(ViewController::DOCUMENTATION_VIEW);
}


// METADATAVIEW GETTER/SETTER

void ViewController::saveMetaDataRequested(){
    emit saveMetaData();
}

// GETTER

QString ViewController::getAnalystLastName() const{
    return metaDataView->getAnalystLastName();
}

QString ViewController::getAnalystFirstName() const {
    return metaDataView->getAnalystFirstName();
}

QString ViewController::getAnalystEmployer() const {
    return metaDataView->getAnalystEmployer();
}

QString ViewController::getAnalystExperience() const {
    return metaDataView->getAnalystExperience();
}

QString ViewController::getCorporationName() const {
    return metaDataView->getCorporationName();
}

QString ViewController::getFactoryName() const {
    return metaDataView->getFactoryName();
}

QString ViewController::getFactoryStreet() const {
    return metaDataView->getFactoryStreet();
}

int ViewController::getFactoryZip() const {
    return metaDataView->getFactoryZip();
}

QString ViewController::getFactoryCity() const {
    return metaDataView->getFactoryCity();
}

QString ViewController::getFactoryCountry() const {
    return metaDataView->getFactoryCountry();
}

QString ViewController::getFactoryContact() const {
    return metaDataView->getFactoryContact();
}

int ViewController::getFactoryEmployeeCount() const {
    return metaDataView->getFactoryEmployeeCount();
}

QDateTime ViewController::getRecordTimeBegin() const {
    return metaDataView->getRecordTimeBegin();
}

QDateTime ViewController::getRecordTimeEnd() const {
    return metaDataView->getRecordTimeEnd();
}

// SETTER SLOTS

void ViewController::setAnalyst(const QString &lastName, const QString &firstName, const QString &experience){
    metaDataView->setAnalyst(lastName, firstName, experience);
}

void ViewController::setEmployer(const QString &employer){
    metaDataView->setEmployer(employer);
}

void ViewController::setCorporation(const QString &name){
    metaDataView->setCorporation(name);
}

void ViewController::setFactory(const QString &name, const QString &street, int zip, const QString &city, const QString &country, const QString &contact, int employeeCount){
    metaDataView->setFactory(name, street, zip, city, country, contact, employeeCount);
}

void ViewController::setRecordTime(const QDateTime &begin, const QDateTime &end){
    metaDataView->setRecordTime(begin, end);
}

// WORKPLACE LIST VIEW SETTER

void ViewController::addWorkplace(int id, const QString &name, const QString &description, const QString &code){
    workplaceListView->addWorkplace(id, name, description, code);
}

void ViewController::clearWorkplaceList(){
    workplaceListView->clear();
}

void ViewController::deleteWorkplaceRequested(int id){
    emit deleteWorkplace(id);
}

// WORKPLACE VIEW GETTER/SETTER

// SLOTS

void ViewController::saveWorkplaceRequested(){
    emit saveWorkplace();
}

void ViewController::setWorkplaceLine(const QString &name, const QString &description){
    workplaceView->setLine(name, description);
}

void ViewController::setWorkplaceComment(const QString &problemName, const QString &measureName){
    workplaceView->setComment(problemName, measureName);
}


// SETTER
void ViewController::setWorkplaceMetaData(const QString &name, const QString &description, const QString &code, int percentageWoman){
    workplaceView->setWorkplaceMetaData(name, description, code, percentageWoman);
}

// GETTER
QString ViewController::getWorkplaceName() const {
    return workplaceView->getName();
}

QString ViewController::getWorkplaceDescription() const {
    return workplaceView->getDescription();
}

QString ViewController::getWorkplaceCode() const{
    return workplaceView->getCode();
}

int ViewController::getWorkplaceWomanPercentage() const{
    return workplaceView->getWomanPercentage();
}


// LINE VIEW GETTER/SETTER

// SLOTS
void ViewController::saveLineRequested(){
    emit saveLine();
}

void ViewController::saveSelectedLineRequested(int id){
    emit saveSelectedLine(id);
}

void ViewController::deleteLineRequested(int id){
    emit deleteLine(id);
}

// SETTER

void ViewController::setLine(const QString &name, const QString &description, int workplaceCount){
    lineView->setLine(name, description, workplaceCount);
}

void ViewController::addLine(int id, const QString &name){
    lineView->addLine(id, name);
}

void ViewController::clearLines(){
    lineView->clearLines();
}

void ViewController::setSelectedLine(int id){
    lineView->setSelectedLine(id);
}


// GETTER
QString ViewController::getLineName() const{
    return lineView->getName();
}

QString ViewController::getLineDescription() const{
    return lineView->getDescription();
}

int ViewController::getLineWorkplaceCount() const{
    return lineView->getWorkplaceCount();
}

// SHIFTPAUSE VIEW GETTER/SETTER
QTime ViewController::getShiftBegin() const{
    return shiftPauseView->getShiftBegin();
}

QTime ViewController::getShiftEnd() const{
    return shiftPauseView->getShiftEnd();
}

QTime ViewController::getShiftCycleTime() const{
    return shiftPauseView->getCycleTime();
}

int ViewController::getShiftQuantity() const{
    return shiftPauseView->getQuantity();
}

QTime ViewController::getShiftSetupTime() const{
    return shiftPauseView->getSetupTime();
}

QTime ViewController::getShiftBasicTime() const{
    return shiftPauseView->getBasicTime();
}

QTime ViewController::getShiftRestTime() const{
    return shiftPauseView->getRestTime();
}

QTime ViewController::getShiftAllowanceTime() const{
    return shiftPauseView->getAllowanceTime();
}

QTime ViewController::getShiftBreakBegin() const{
    return shiftPauseView->getBreakBegin();
}

QTime ViewController::getShiftBreakEnd() const{
    return shiftPauseView->getBreakEnd();
}

void ViewController::setShift(const QString &shiftType, const QTime &shiftBegin, const QTime &shiftEnd){
    shiftPauseView->setShift(shiftType, shiftBegin, shiftEnd);
}

void ViewController::setShiftBreak(const QTime &breakBegin, const QTime &breakEnd){
    shiftPauseView->setBreak(breakBegin, breakEnd);
}

void ViewController::setShiftWorkplaceTimes(const QTime &basicTime, const QTime &setupTime, const QTime &restTime, const QTime &allowanceTime, const QTime &cycleTime){
    shiftPauseView->setWorkplaceTimes(basicTime, setupTime, restTime, allowanceTime, cycleTime);
}


// EMPLOYEE VIEW GETTER/SETTER

// SLOTS
void ViewController::saveEmloyeeRequested(){
    emit saveEmployee();
}

// SETTER
void ViewController::setEmployee(int gender, int age, int height, const QString &staffNumber, const QString &note){
    employeeView->setEmployee(gender, age, height, staffNumber, note);
}

// GETTER
int ViewController::getEmployeeGender() const{
    return employeeView->getGender();
}

int ViewController::getEmployeeAge() const{
    return employeeView->getAge();
}

int ViewController::getEmployeeHeight() const{
    return employeeView->getHeight();
}

QString ViewController::getEmployeeStaffNumber() const{
    return employeeView->getStaffNumber();
}

QString ViewController::getEmployeeNote() const{
    return employeeView->getNote();
}

// PRODUCT VIEW GETTER/SETTER

// SLOTS
void ViewController::deleteProductRequested(int id){
    emit deleteProduct(id);
}

void ViewController::saveProductRequested(){
    emit saveProduct();
}

void ViewController::saveSelectedProductsRequested(){
    emit saveSelectedProducts();
}

// SETTER
void ViewController::setProduct(const QString &name, const QString &number, int totalPercentage){
    productView->setProduct(name, number, totalPercentage);
}

void ViewController::addProduct(int id, const QString &name){
    productView->addProduct(id, name);
}

void ViewController::clearProducts(){
    productView->clearProducts();
}

void ViewController::setProductSelected(int id){
    productView->setProductSelected(id);
}

// GETTER
QString ViewController::getProductName() const{
    return productView->getName();
}

QString ViewController::getProductNumber() const{
    return productView->getNumber();
}

int ViewController::getProductTotalPercentage() const{
    return productView->getTotalPercentage();
}

QList<int> ViewController::getSelectedProducts() const{
    return productView->getSelectedIDs();
}



// COMMENT VIEW GETTER/SETTER
//SLOTS
void ViewController::saveCommentRequested(){
    emit saveComment();
}

//SETTER
void ViewController::setComment(const QString &problemName, const QString &problemDesc, const QString &measureName, const QString &measureDesc, const QString &workerPerception){
    commentView->setComment(problemName, problemDesc, measureName, measureDesc, workerPerception);
}

// GETTER
QString ViewController::getCommentProblemName() const{
    return commentView->getProblemName();
}

QString ViewController::getCommentProblemDescription() const{
    return commentView->getProblemDescription();
}

QString ViewController::getCommentMeasureName() const{
    return commentView->getMeasureName();
}

QString ViewController::getCommentMeasureDescription() const{
    return commentView->getMeasureDescription();
}

QString ViewController::getCommentWorkerPerception() const{
    return commentView->getWorkerPerception();
}

// SET VIEWS AND PUSH/POP
void ViewController::backToView(){
    int nextView = previousViews->pop();
    switch(nextView){
        case ViewController::MAIN_MENU_VIEW:
            break;
        case ViewController::METADATA_VIEW:
            break;
        case ViewController::WORKPLACELIST_VIEW:
            emit updateWorkplaceList();
            break;
        case ViewController::WORKPLACE_VIEW:
            emit updateWorkplace();
            break;
        case ViewController::LINE_VIEW:
            emit updateLineView();
            break;
        case ViewController::SHIFTPAUSE_VIEW:
            break;
        case ViewController::EMPLOYEE_VIEW:
            emit updateEmployeeView();
            break;
        case ViewController::PRODUCT_VIEW:
            emit updateProductView();
            break;
        case ViewController::COMMENT_VIEW:
            emit updateCommentView();
            break;
        case ViewController::DOCUMENTATION_VIEW:
            break;
        default:
            break;
    }
    ViewController::setCurrentIndex(nextView);
}

void ViewController::goToView(int index){
    previousViews->push(currentIndex());
    setCurrentIndex(index);
}

