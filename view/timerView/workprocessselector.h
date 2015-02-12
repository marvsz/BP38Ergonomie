#ifndef WORKPROCESSSELECTOR_H
#define WORKPROCESSSELECTOR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class WorkProcessSelector : public QWidget
{
    Q_OBJECT
public:
    explicit WorkProcessSelector(QWidget *parent = 0);
    ~WorkProcessSelector();

signals:
    void nextAV();
    void previousAV();

public slots:
    void setSelectedAV(int avNum);
    void setAVPrefix(const QString &pref);
    void setSelectedAVNone();
    void setHasPreviousAV(bool hasPrevious);
    void setHasNextAV(bool hasNext);

private:
    QPushButton *btnRight;
    QPushButton *btnLeft;
    QLabel *lblSelectedAV;

    QString prefix;
};

#endif // WORKPROCESSSELECTOR_H
