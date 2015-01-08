#ifndef DETAILEDLISTITEM_H
#define DETAILEDLISTITEM_H

#include <QAbstractButton>
#include <QGridLayout>
#include <QPushButton>
#include <QList>
#include <QCheckBox>
#include <QLabel>
#include <QPixmap>

class DetailedListItem : public QAbstractButton
{
    Q_OBJECT
public:
    explicit DetailedListItem(QWidget *parent = 0, const QString &iconPath = "", const QString &name = "", const QList<QStringList> &scheme = QList<QStringList>(), bool isDeletable = false, bool isCheckable = false, bool hasForwardLabel = false);

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
    void deselectUnequalID(int id);
    void deselect(int id);
    void select();
    void deselect();

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
    QLabel *lblIcon;
    QPixmap icon;
    QLabel *lblName;
    QPushButton *btnDelete;
    QCheckBox *checkBox;
    QLabel *lblForward;

    QList<QList<QLabel*>> listLblValues;
};

#endif // DETAILEDLISTITEM_H
