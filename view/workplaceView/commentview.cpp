#include "commentview.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include "separator.h"

CommentView::CommentView(QWidget *parent) : SimpleNavigateableWidget(tr("Remarks"), parent),
    lblProblem(new QLabel(tr("problems"))),
    lblProblemName(new QLabel(tr("label:"))),
    lblProblemDescription(new QLabel(tr("description:"))),
    lblMeasure(new QLabel(tr("sanction"))),
    lblMeasureName(new QLabel(tr("label:"))),
    lblMeasureDescription(new QLabel(tr("description:"))),
    lblWorkerPerception(new QLabel(tr("remarks of the factory"))),
    lblWorkerPerceptionDescription(new QLabel(tr("description:"))),
    txtBxProblemName(new TextLineEdit()),
    txtBxProblemDescription(new TextEdit()),
    txtBxMeasureName(new TextLineEdit()),
    txtBxMeasureDescription(new TextEdit()),
    txtBxPerceptionDescription(new TextEdit())
{
    lblProblem->setObjectName("lblHeader");
    lblMeasure->setObjectName("lblHeader");
    lblWorkerPerception->setObjectName("lblHeader");

    txtBxProblemName->setPlaceholderText(tr("name of the problem"));
    txtBxProblemDescription->setPlaceholderText(tr("description of the problem"));
    txtBxMeasureName->setPlaceholderText(tr("name of the measure"));
    txtBxMeasureDescription->setPlaceholderText(tr("description of the mesaure"));
    txtBxPerceptionDescription->setPlaceholderText(tr("the workers annotation"));

    QGridLayout *commentLayout = new QGridLayout;
    commentLayout->addWidget(lblProblem, 0, 0, 1, 2, 0);
    commentLayout->addWidget(lblProblemName, 1, 0, 1, 1, 0);
    commentLayout->addWidget(txtBxProblemName, 1, 1, 1, 1, 0);
    commentLayout->addWidget(lblProblemDescription, 2, 0, 1, 1, 0);
    commentLayout->addWidget(txtBxProblemDescription, 2, 1, 1, 1, 0);
    commentLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 3, 0, 1, 2, 0);
    commentLayout->addWidget(lblMeasure, 4, 0, 1, 2, 0);
    commentLayout->addWidget(lblMeasureName, 5, 0, 1, 1, 0);
    commentLayout->addWidget(txtBxMeasureName, 5, 1, 1, 1, 0);
    commentLayout->addWidget(lblMeasureDescription, 6, 0, 1, 1, 0);
    commentLayout->addWidget(txtBxMeasureDescription, 6, 1, 1, 1, 0);
    commentLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 7, 0, 1, 2, 0);
    commentLayout->addWidget(lblWorkerPerception, 8, 0, 1, 2, 0);
    commentLayout->addWidget(lblWorkerPerceptionDescription, 9, 0, 1, 1, 0);
    commentLayout->addWidget(txtBxPerceptionDescription, 9, 1, 1, 1, 0);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addLayout(commentLayout);

    setLayout(mainLayout);
}

CommentView::~CommentView()
{

}

//PUBLIC SLOTS
void CommentView::setComment(const QString &problemName, const QString &problemDesc, const QString &measureName, const QString &measureDesc, const QString &workerPerception){
    txtBxProblemName->setText(problemName);
    txtBxProblemDescription->setText(problemDesc);
    txtBxMeasureName->setText(measureName);
    txtBxMeasureDescription->setText(measureDesc);
    txtBxPerceptionDescription->setText(workerPerception);
}

//GETTER
QString CommentView::getProblemName() const{
    return txtBxProblemName->text();
}
QString CommentView::getProblemDescription() const{
    return txtBxProblemDescription->toPlainText();
}
QString CommentView::getMeasureName() const{
    return txtBxMeasureName->text();
}
QString CommentView::getMeasureDescription() const{
    return txtBxMeasureDescription->toPlainText();
}
QString CommentView::getWorkerPerception() const{
    return txtBxPerceptionDescription->toPlainText();
}
