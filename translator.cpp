#include "translator.h"
#include <QDebug>

QTranslator* Translator::currentTranslator = 0;
Translators Translator::translators;

Translator::Translator(QObject *parent, QApplication *app) :
    QObject(parent),
    application(app)
{
}

Translator::~Translator()
{

}

void Translator::loadTranslations(const QString &dir){
    loadTranslations(QDir(dir));
}

void Translator::loadTranslations(const QDir& dir)
{
    QString filter = "*_*.qm";
    QDir::Filters filters = QDir::Files | QDir::Readable;
    QDir::SortFlags sort = QDir::Name;
    QFileInfoList entries = dir.entryInfoList(QStringList() << filter, filters, sort);
    foreach (QFileInfo file, entries)
    {
        QStringList parts = file.baseName().split("_");
        QString language = parts.at(parts.count() - 2).toLower();
        QString country  = parts.at(parts.count() - 1).toUpper();

        QTranslator* translator = new QTranslator();
        if (translator->load(file.absoluteFilePath()))
        {
            QString locale = language + "_" + country;
            translators.insert(locale, translator);
        }
    }
}

const QStringList Translator::getAvailableLanguages(){
    return QStringList(translators.keys());
}

void Translator::setLanguage(const QString &language){
    if(currentTranslator){
        application->removeTranslator(currentTranslator);
    }

    currentTranslator = translators.value(language, 0);
    if(currentTranslator){
        application->installTranslator(currentTranslator);
    }
}

QTranslator* Translator::getCurrentTranslator(){
    return currentTranslator;
}
