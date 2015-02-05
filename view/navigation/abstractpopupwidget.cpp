#include "abstractpopupwidget.h"
#include "separator.h"

AbstractPopUpWidget::AbstractPopUpWidget(const QString &title, QWidget *parent) : TitledWidget(title, parent),
    mainLayout(new QGridLayout),
    btnClose(new QPushButton()),
    btnConfirm(new QPushButton()),
    lblTitle(new QLabel())
{
    setObjectName("PopUpWidget");
    lblTitle->setText(getTitle());

    btnClose->setObjectName("btnCancelIcon");
    btnClose->setFixedSize(45, 45);
    connect(btnClose, SIGNAL(clicked()), this, SIGNAL(close()));

    btnConfirm->setFixedSize(45, 45);
    switch(getConfirmMode()){
    case ConfirmMode::ACCEPT:
        btnConfirm->setObjectName("btnSaveIcon");
        break;
    case ConfirmMode::SEND:
        btnConfirm->setObjectName("btnSendIcon");
        break;
    default: break;
    }
    connect(btnConfirm, SIGNAL(clicked()), this, SIGNAL(confirm()));

    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(btnConfirm, 0, 0, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(lblTitle, 0, 1, 1, 1, Qt::AlignCenter);
    mainLayout->addWidget(btnClose, 0, 2, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 1, 0, 1, 3, 0);

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    TitledWidget::setLayout(mainLayout);
}

AbstractPopUpWidget::~AbstractPopUpWidget()
{

}

//PUBLIC
void AbstractPopUpWidget::setLayout(QLayout *layout){
    mainLayout->addLayout(layout, 2, 0, 1, 3, 0);
}


