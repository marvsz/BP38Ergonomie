#include "tool.h"
#include "textqpushbutton.h"

int Tool::idCounter = 0;

Tool::Tool(QString name, QVector<bool> opts, QWidget *parent) :
    TextQPushButton(idCounter++, name, parent)
{
    this->setName(name);
    this->options = opts;
}

bool Tool::getOption(int index)
{
    return this->options.at(index);
}

void Tool::setOption(int index, bool b)
{
    this->options.replace(index, b);
}

void Tool::setName(QString name)
{
    this->name = name;
    this->setText(name);
}
