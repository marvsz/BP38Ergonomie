#ifndef DETAILEDLISTITEM_H
#define DETAILEDLISTITEM_H

#include <QAbstractButton>
#include <QGridLayout>
#include <QPushButton>
#include <QList>
#include <QCheckBox>
#include <QLabel>
#include <QIcon>

class DetailedListItem : public QAbstractButton
{
    Q_OBJECT
public:
    explicit DetailedListItem(QWidget *parent = 0, const QString &iconPath = "", const QString &name = "", const QList<QStringList> &scheme = QList<QStringList>(), bool isDeletable = false, bool isCheckable = false, bool hasForwardButton = false);

    int getID() const;
    void setID(int id);

signals:
    void deleteItem(int id);
    void pressed(int id);
    void selected(int id);
    void deselected(int id);

public slots:
    void setValues(const QList<QStringList> &values);
    void changeSelection();
    void select(int id);
    void selectExclusiveWithID(int id);
    void deselect(int id);
    void select();
    void deselect();
    void checkState(int id);

private slots:
    void itemPressed();
    void deleteItem();

protected:
    void paintEvent(QPaintEvent *e);

private:
    int id;
    bool isCheckable;
    bool isDeletable;

    QGridLayout *layout;
    QPushButton *lblIcon;
    QIcon icon;
    QLabel *lblName;
    QPushButton *btnDelete;
    QCheckBox *checkBox;
    QPushButton *btnForward;

    QList<QList<QLabel*>> listLblValues;
};

#endif // DETAILEDLISTITEM_H
