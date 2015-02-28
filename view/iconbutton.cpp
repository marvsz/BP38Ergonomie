#include "iconbutton.h"
#include <QStylePainter>
#include <QStyleOption>

IconButton::IconButton(QWidget *parent, const QString &iconPath, const QString &text) :
    QAbstractButton(parent),
    layout(new QGridLayout()),
    icon(QIcon(iconPath)),
    lblIcon(new QPushButton()),
    lblText(new QLabel(text)),
    lblSpacer(new QLabel())
{
    lblIcon->setObjectName("btnIcon");
    lblIcon->setIcon(icon);
    lblIcon->setIconSize(QSize(32, 32));
    connect(lblIcon, SIGNAL(clicked()), this, SIGNAL(clicked()));

    lblText->setObjectName("lblLight");
    lblSpacer->setObjectName("lblLight");

    layout->addWidget(lblIcon, 0, 0, 1, 1, Qt::AlignLeft);
    layout->addWidget(lblText, 0, 1, 1, 1, Qt::AlignCenter);
    layout->addWidget(lblSpacer, 0, 2, 1, 1, Qt::AlignRight);

    setLayout(layout);
}

void IconButton::setIcon(const QIcon &icon){
    lblIcon->setIcon(icon);
    lblIcon->setIconSize(QSize(32, 32));
}

void IconButton::setIconSize(const QSize &size){
    lblIcon->setIconSize(size);
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
