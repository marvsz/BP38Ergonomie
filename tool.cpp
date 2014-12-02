#include "tool.h"
#include "textqpushbutton.h"

Tool::Tool(int id, QString name, QVector<bool> opts, QWidget *parent) :
    TextQPushButton(id, name, parent)
{
    this->id = id;
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
