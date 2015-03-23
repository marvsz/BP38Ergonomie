#include "separator.h"
#include <QStyleOption>
#include <QPainter>

Separator::Separator(Qt::Orientation orientation, int thickness, QWidget *parent) :
    QWidget(parent)
{
    if(orientation == Qt::Horizontal){
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        this->setFixedHeight(thickness);
    }
    else{
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        this->setFixedWidth(thickness);
    }

}

Separator::~Separator(){

}

//Private methods
void Separator::paintEvent(QPaintEvent *event){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
