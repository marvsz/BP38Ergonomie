#include "textedit.h"
#include <QGuiApplication>

TextEdit::TextEdit(QWidget *parent) : QTextEdit(parent)
{
    connect(this, SIGNAL(editingFinished()), QGuiApplication::inputMethod(), SLOT(hide()));
}

TextEdit::~TextEdit()
{

}

