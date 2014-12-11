#include "textlineedit.h"
#include <QGuiApplication>

TextLineEdit::TextLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    connect(this, SIGNAL(editingFinished()), QGuiApplication::inputMethod(), SLOT(hide()));
}
