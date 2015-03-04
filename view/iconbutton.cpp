#include "iconbutton.h"
#include <QStylePainter>
#include <QStyleOption>

IconButton::IconButton(QWidget *parent, const QString &objectName, const QString &text) :
    QAbstractButton(parent),
    layout(new QGridLayout()),
    lblIcon(new QPushButton()),
    lblText(new QLabel(text)),
    lblSpacer(new QLabel())
{
    lblIcon->setObjectName(objectName);
    lblIcon->setFixedSize(45, 45);
    connect(lblIcon, SIGNAL(clicked()), this, SIGNAL(clicked()));

    lblText->setObjectName("lblLight");
    lblSpacer->setObjectName("lblLight");

    layout->addWidget(lblIcon, 0, 0, 1, 1, Qt::AlignLeft);
    layout->addWidget(lblText, 0, 1, 1, 1, Qt::AlignCenter);
    layout->addWidget(lblSpacer, 0, 2, 1, 1, Qt::AlignRight);

    setLayout(layout);
}

void IconButton::setIcon(const QString &objectName){
    lblIcon->setObjectName(objectName);
    lblIcon->style()->unpolish(lblIcon);
    lblIcon->style()->polish(lblIcon);
}

void IconButton::setText(const QString &text){
    lblText->setText(text);
}

void IconButton::paintEvent(QPaintEvent *e){
    QStylePainter p(this);
    QStyleOption opt;
    opt.initFrom(this);
    p.drawPrimitive(QStyle::PE_Widget, opt);
}

QSize IconButton::sizeHint() const{
    return QSize(300, lblIcon->iconSize().height());
}
