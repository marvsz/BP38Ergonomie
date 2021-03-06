#include <QApplication>
#include <QTranslator>
#include <QFile>
#include <QTextStream>
#include "control/controller.h"

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
    QApplication a(argc, argv);

    a.setStyleSheet(stringFromResource(":/assets/stylesheet.qss"));
    a.setAttribute(Qt::AA_UseHighDpiPixmaps, true);

    QTranslator translator;
    translator.load(":/ergo_trans_de");
    a.installTranslator(&translator);


    Controller c;


    return a.exec();
}
