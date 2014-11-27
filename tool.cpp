#include "tool.h"
#include "textqpushbutton.h"

Tool::Tool(int id, QString name, bool opt1, bool opt2, QWidget *parent) :
    TextQPushButton(id, name, parent)
{
    this->id = id;
    this->setName(name);
    this->setOpt1(opt1);
    this->setOpt2(opt2);
}

bool Tool::getOpt1()
{
    return this->opt1;
}

bool Tool::getOpt2()
{
    return this->opt2;
}

void Tool::setOpt1(bool b)
{
    this->opt1 = b;
}

void Tool::setOpt2(bool b)
{
    this->opt2 = b;
}

void Tool::setName(QString name)
{
    this->name = name;
    this->setText(name);
}
