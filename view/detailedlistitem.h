#ifndef DETAILEDLISTITEM_H
#define DETAILEDLISTITEM_H

#include <QAbstractButton>
#include <QGridLayout>
#include <QPushButton>
#include <QList>
#include <QLabel>
#include <QPixmap>

class DetailedListItem : public QAbstractButton
{
    Q_OBJECT
public:
    explicit DetailedListItem(QWidget *parent = 0, const QString &iconPath = "", const QString &name = "", const QList<QStringList> &scheme = QList<QStringList>(), bool isDeletable = false);

    int getID() const;
    void setID(int id);

signals:
    void deleteItem(int id);
    void pressed(int id);

public slots:
    void setValues(const QList<QStringList> &values);

private slots:
    void itemPressed();
    void deleteItem();

protected:
    void paintEvent(QPaintEvent *e);

private:
    int id;
    QGridLayout *layout;
    QLabel *lblIcon;
    QPixmap icon;
    QLabel *lblName;
    QPushButton *btnDelete;
    QLabel *lblForward;

    QList<QList<QLabel*>> listLblValues;
};

#endif // DETAILEDLISTITEM_H
