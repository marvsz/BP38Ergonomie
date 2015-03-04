#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QTranslator>
#include <QStringList>
#include <QDir>
#include <QApplication>

typedef QHash<QString, QTranslator*> Translators;

class Translator : QObject
{
    Q_OBJECT

public:
    explicit Translator(QObject *parent = 0, QApplication *app = 0);
    ~Translator();

    static void loadTranslations(const QString& dir);
    static void loadTranslations(const QDir& dir);
    static const QStringList getAvailableLanguages();

public slots:
    void setLanguage(const QString& language);
    QTranslator* getCurrentTranslator();

private:
    QApplication *application;
    static QTranslator* currentTranslator;
    static Translators translators;
};

#endif // TRANSLATOR_H
