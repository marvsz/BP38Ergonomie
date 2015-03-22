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
    explicit DetailedListItem(QWidget *parent = 0, const QString &objectName = "btnIcon", const QString &name = "", const QList<QStringList> &scheme = QList<QStringList>(), bool isDeletable = false, bool isCheckable = false, bool hasForwardButton = false, bool canBeAdded = false, bool isEditable = false);

    int getID() const;
    void setID(int id);
    QString getName() const;

signals:
    void deleteItem(int id);
    void addItem(int id);
    void editItem(int id);
    void pressed(int id);
    void selected(int id);
    void deselected(int id);

public slots:
    void setValues(const QList<QStringList> &values);
    void setName(const QString &name);
    void changeSelection();
    void select(int id);
    void selectExclusiveWithID(int id);
    void deselect(int id);
    void select();
    void deselect();

private slots:
    void itemPressed();
    void deleteItem();
    void addItem();
    void editItem();

protected:
    void paintEvent(QPaintEvent *);

private:
    int id;

    bool isCheckable;

    QGridLayout *layout;
    QPushButton *lblIcon;
    QIcon icon;
    QLabel *lblName;
    QPushButton *btnDelete;
    QPushButton *btnAdd;
    QPushButton *btnEdit;
    QCheckBox *checkBox;
    QPushButton *btnForward;

    QList<QList<QLabel*>> listLblValues;
};

#endif // DETAILEDLISTITEM_H
