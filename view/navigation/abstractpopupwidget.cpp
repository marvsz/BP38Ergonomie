#include "abstractpopupwidget.h"
#include "../separator.h"
#include <QStyleOption>
#include <QPainter>

AbstractPopUpWidget::AbstractPopUpWidget(ConfirmMode mode, const QString &title, QWidget *parent) : TitledWidget(title, parent),
    mainContentLayout(new QGridLayout),
    btnClose(new QPushButton()),
    btnConfirm(new QPushButton()),
    lblTitle(new QLabel())
{
    lblTitle->setText(getTitle());

    btnClose->setObjectName("cancelIcon");
    btnClose->setFixedSize(45, 45);
    connect(btnClose, SIGNAL(clicked()), this, SIGNAL(cancel()));
    connect(btnClose, SIGNAL(clicked()), this, SIGNAL(closePopUp()));

    btnConfirm->setFixedSize(45, 45);
    switch(mode){
    case ConfirmMode::ACCEPT:
        btnConfirm->setObjectName("saveIcon");
        break;
    case ConfirmMode::SEND:
        btnConfirm->setObjectName("sendIcon");
        break;
    default: break;
    }
    connect(btnConfirm, SIGNAL(clicked()), this, SIGNAL(confirm()));
    mainContentLayout->setMargin(10);
    mainContentLayout->addWidget(btnConfirm, 0, 0, 1, 1, Qt::AlignLeft);
    mainContentLayout->addWidget(lblTitle, 0, 1, 1, 1, Qt::AlignCenter);
    mainContentLayout->addWidget(btnClose, 0, 2, 1, 1, Qt::AlignRight);
    mainContentLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 1, 0, 1, 3, 0);

    TitledWidget::setLayout(mainContentLayout);
}

AbstractPopUpWidget::~AbstractPopUpWidget()
{

}

//PUBLIC
void AbstractPopUpWidget::setLayout(QLayout *layout){
    mainContentLayout->addLayout(layout, 2, 0, 1, 3, 0);
}

//PRIVATE
void AbstractPopUpWidget::paintEvent(QPaintEvent *){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


