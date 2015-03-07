#include <QApplication>
#include <QTranslator>
#include <QFile>
#include <QTextStream>
#include "control/controller.h"
#include "translator.h"

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
    Translator t(&a);
    t.loadTranslations(":/translations");

    if(!settings.empty()){
        if(settings.at(1) == "green")
            a.setStyleSheet(stringFromResource(":/assets/stylesheetGreen.qss"));
        else
            a.setStyleSheet(stringFromResource(":/assets/stylesheet.qss"));
        if(settings.at(0) == "german")
            t.setLanguage("trans_DE");
        else
            t.setLanguage("trans_EN");
    }
    else {
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);
        out<<"german"<<','<<"blue";
        a.setStyleSheet(stringFromResource(":/assets/stylesheet.qss"));
        t.setLanguage("trans_DE");
    }
    a.setAttribute(Qt::AA_UseHighDpiPixmaps, true);

    Controller c(0, &a, &t);

    return a.exec();
}
