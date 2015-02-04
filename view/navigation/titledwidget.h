#ifndef TITLEDWIDGET_H
#define TITLEDWIDGET_H

#include <QWidget>
#include "viewtype.h"

class TitledWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TitledWidget(const QString &title, QWidget *parent = 0):
    QWidget(parent),
    title(title){

    }

    ~TitledWidget(){

    }

    const QString getTitle() const{
        return title;
    }

signals:
    void show(ViewType type);

private:
    const QString title;
};

#endif // TITLEDWIDGET_H
