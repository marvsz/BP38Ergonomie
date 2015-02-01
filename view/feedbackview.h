#ifndef FEEDBACKVIEW_H
#define FEEDBACKVIEW_H

#include "navigation/simplenavigateablewidget.h"
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include "textlineedit.h"
#include "textedit.h"

class FeedbackView : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    explicit FeedbackView(QWidget *parent = 0);
    ~FeedbackView();

    void reset();
    void setScreenshotPath(const QString &path);
    void setLoggingPath(const QString &path);
    void setViewName(const QString &name);
signals:

public slots:

private:
    QString screenshotPath;
    QString loggingPath;
    QString viewName;

    QPushButton *btnSend;

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
