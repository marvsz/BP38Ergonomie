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
<<<<<<< HEAD
    void show(ViewType type);
    void showPopUp(PopUpType type);

public slots:
    virtual void onLeaving(){
    }

    virtual void onEnter(){

    }
=======
    void showView(ViewType type);
>>>>>>> origin/Unstable

private:
    const QString title;
};

#endif // TITLEDWIDGET_H
