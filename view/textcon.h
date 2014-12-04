#ifndef TEXTCON_H
#define TEXTCON_H

#include <QWidget>
#include <QLineEdit>
#include <QGroupBox>
#include <QVector>
#include <QString>
#include <QLabel>
#include "textqpushbutton.h"

class TextCon : public QGroupBox
{
    Q_OBJECT
public:
    explicit TextCon(int btnCount, QString btnValues[], QWidget *parent = 0);
    void setText(QString text);
    QString getText() const;

signals:

public slots:

private slots:
    void lblTextHasChanged();
    void btnTextHasClicked(int id);

private:

    int btnCount;
    QLabel *lblValue;
    QLabel *lblText;
    QVector<TextQPushButton*> btnTexts;

    void btnHighlight(QString text);

};

#endif // TEXTCON_H
