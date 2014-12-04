#include "seperator.h"

Seperator::Seperator(Qt::Orientation orientation, int thickness, QWidget *parent) :
    QFrame(parent)
{
    if(orientation == Qt::Horizontal){
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        this->setFixedHeight(thickness);
    }
    else{
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        this->setFixedWidth(thickness);
    }

    //this->setStyleSheet("QWidget {background-color: #c8c7cc; margin: 10px 10px 10px 10px;}");
}
