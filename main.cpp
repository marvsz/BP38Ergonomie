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
    QStringList settings;
    QFile file(StandardPaths::configFile());
    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        QString line = in.readLine();
        settings = line.split(',');
    }

    QApplication a(argc, argv); 
    QTranslator t;

    if(!settings.empty()){
        if(settings.at(1) == "green")
            a.setStyleSheet(stringFromResource(":/assets/stylesheetGreen.qss"));
        else
            a.setStyleSheet(stringFromResource(":/assets/stylesheet.qss"));
        if(settings.at(0) == "german")
            t.load(":/translations/ergo_trans_de");
        else
            t.load(":/translations/ergo_trans_en");
    }
    else {
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);
        out<<"german"<<','<<"blue"<<','<<"nTrue"<<','<<"tTrue";
        a.setStyleSheet(stringFromResource(":/assets/stylesheet.qss"));
        t.load(":/translations/ergo_trans_de");
    }
    a.installTranslator(&t);
    a.setAttribute(Qt::AA_UseHighDpiPixmaps, true);

    Controller c(0, &a);

    return a.exec();
}
