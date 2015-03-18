#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QAbstractButton>
#include <QGridLayout>
#include <QIcon>
#include <QPushButton>
#include <QLabel>

class IconButton : public QAbstractButton
{
    Q_OBJECT
public:
    explicit IconButton(QWidget *parent = 0, const QString &iconPath = "", const QString &text = "");

    void setIcon(const QString &objectName);
    void setText(const QString &text);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);
    QSize sizeHint() const;

private:
    QGridLayout *layout;
    QIcon icon;
    QPushButton *lblIcon;
    QLabel *lblText;
    QLabel *lblSpacer;
};

#endif // ICONBUTTON_H
