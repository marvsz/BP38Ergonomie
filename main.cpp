#include <QApplication>
#include <QTranslator>
#include <QFile>
#include <QTextStream>
#include "control/controller.h"
#include "translator.h"
#include <QDebug>
//#include <opencv2/core/core.hpp>
//Q_DECLARE_METATYPE(cv::Mat)


QString stringFromResource(const QString &resName)
{
    QFile file(resName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream ts(&file);
    return ts.readAll();
}

#if defined(Q_OS_IOS)
extern "C" int qtmn(int argc, char **argv)
#else
int main(int argc, char *argv[])
#endif
{
    //qRegisterMetaType<cv::Mat>();

    /*QFile file(":/assets/settings.csv");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QStringList settings;
    QString line = in.readLine();
    settings = line.split(',');
    qDebug()<<settings.at(0);
    qDebug()<<settings.at(1);
    file.close();*/

    QApplication a(argc, argv);

    //if(settings.at(1) == "green")
      //  a.setStyleSheet(stringFromResource(":/assets/stylesheetGreen.qss"));
    //else
        a.setStyleSheet(stringFromResource(":/assets/stylesheet.qss"));

    a.setAttribute(Qt::AA_UseHighDpiPixmaps, true);

    Translator t(&a);
    t.loadTranslations(":/translations");

    //if(settings.at(0) == "german")
        t.setLanguage("trans_DE");
    //else
      //  t.setLanguage("trans_EN");

    Controller c(0, &a, &t);
    /*QTranslator translator;
    translator.load(":/translations/ergo_trans_de");
    a.installTranslator(&translator);*/

    return a.exec();
}
