#ifndef FEEDBACKPOPUP_H
#define FEEDBACKPOPUP_H

#include "../navigation/abstractpopupwidget.h"
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include "../textlineedit.h"
#include "../textedit.h"

class FeedbackPopUp : public AbstractPopUpWidget
{
    Q_OBJECT
public:
    explicit FeedbackPopUp(QWidget *parent = 0);
    ~FeedbackPopUp();

    int getPriority() const{
        return cmbBxPriority->currentData().toInt();
    }

    QString getCategory() const{
        return cmbBxCategory->currentData().toString();
    }

    QString getDescription() const{
        return txtBxDescription->toPlainText();
    }

    bool getAttachScreenshot() const{
        return chbxScreenshot->isChecked();
    }

public slots:
    void onEnter();

private slots:
    void sendData();

private:
    QLabel *lblViewName;
    TextLineEdit *txtBxViewName;
    QLabel *lblScreenshot;
    QCheckBox *chbxScreenshot;
    QLabel *lblDescription;
    TextEdit *txtBxDescription;
    QLabel *lblPriority;
    QComboBox *cmbBxPriority;
    QLabel *lblCategory;
    QComboBox *cmbBxCategory;
};

#endif // FEEDBACKPOPUP_H
