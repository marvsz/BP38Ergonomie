#include "utilityoption.h"
#include <QHBoxLayout>
#include "numberlineedit.h"

/**
 * @brief Constructs a UtilityOption widget which is a child of parent.
 * @param optionType is either VALUE_OPTION or TEXT_OPTION, if the type is
 * VALUE_OPTION, the option's textfield can only contain numbers, if TEXT_OPTION
 * the textfield can contain characters and numbers.
 * @param parent If parent is 0, the new widget becomes a window.
 * If parent is another widget, this widget becomes a child window inside parent.
 * The new widget is deleted when its parent is deleted.
 */
UtilityOption::UtilityOption(UtilityOptionType optionType, QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;

    this->optionType = optionType;
    if(optionType == TEXT_OPTION)
        this->inputTextField = new TextLineEdit(this);
    else
        this->inputTextField = new NumberLineEdit(this);

    connect(this->inputTextField, SIGNAL(textChanged(QString)), this, SLOT(textChanged()));

    layout->addWidget(this->inputTextField, 1, Qt::AlignCenter);
    this->setLayout(layout);
}

// public functions
/**
 * @brief Getter method for an Option of type TEXT_OPTION
 * @return the current text as QString iff the optionType is
 * TEXT_OPTION, else an empty QString
 */
QString UtilityOption::getTextValue(){
    if(this->optionType == TEXT_OPTION)
        return this->inputTextField->text();
    else
        return "";
}

/**
 * @brief Getter method for an Option of type VALUE_OPTION
 * @return the current QString converted to int iff the optionType is
 * VALUE_OPTION, else NULL
 */
int UtilityOption::getIntValue(){
    if(this->optionType == VALUE_OPTION)
        return this->inputTextField->text().toInt();
    else
        return NULL;
}

/**
 * @brief Sets the textfield's text to the input number as a QString, iff
 * the option is a VALUE_OPTION
 * @param i the value the textfield should be set to
 */
void UtilityOption::setValue(int i){
    if(optionType == VALUE_OPTION)
        this->inputTextField->setText(QString::number(i));
}

/**
 * @brief Sets the textfield's text to the input QString, iff the option
 * is a TEXT_OPTION
 * @param text the text the textfield should be set to
 */
void UtilityOption::setValue(QString text){
    if(optionType == TEXT_OPTION)
        this->inputTextField->setText(text);
}

/**
 * @brief Deletes the content of the textfield
 */
void UtilityOption::clear(){
    this->inputTextField->clear();
}

/**
 * @brief Sets the placeholder text to the specified text
 * @param placeholder the placeholder text to be set
 */
void UtilityOption::setPlaceholder(QString placeholder){
    this->inputTextField->setPlaceholderText(placeholder);
}

// private slots

/**
 * @brief emits a <valueChanged>"("<QString>")" signal if optionType is
 * TEXT_OPTION and a <valueChanged<"("<int>")" signal if the optionType
 * is VALUE_OPTION
 */
void UtilityOption::textChanged(){
    if(optionType == TEXT_OPTION)
        emit valueChanged(this->inputTextField->text());
    else if (optionType == VALUE_OPTION)
        emit valueChanged(this->inputTextField->text().toInt());
}

void UtilityOption::setMinimumHeight(int minh){
    this->inputTextField->setMinimumHeight(minh);
}

void UtilityOption::setMinimumWidth(int minw){
    this->inputTextField->setMinimumWidth(minw);
}

void UtilityOption::setMinimumSize(int minw, int minh){
    this->inputTextField->setMinimumSize(minw, minh);
}

void UtilityOption::setMaximumHeight(int maxh){
    this->inputTextField->setMaximumHeight(maxh);
}

void UtilityOption::setMaximumWidth(int maxw){
    this->inputTextField->setMaximumWidth(maxw);
}

void UtilityOption::setMaximumSize(int maxw, int maxh){
    this->inputTextField->setMaximumSize(maxw, maxh);
}

