#ifndef FEEDBACKVIEW_H
#define FEEDBACKVIEW_H

#include "navigation/abstractpopupwidget.h"
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include "textlineedit.h"
#include "textedit.h"

class FeedbackView : public AbstractPopUpWidget
{
    Q_OBJECT
public:
    explicit FeedbackView(QWidget *parent = 0);
    ~FeedbackView();

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

protected:
    ConfirmMode getConfirmMode() const{
        return ConfirmMode::SEND;
    }

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

#endif // FEEDBACKVIEW_H
