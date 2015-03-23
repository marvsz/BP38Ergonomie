#ifndef ERRORREPORTER
#define ERRORREPORTER

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include "standardpaths.h"

class ErrorReporter
{
public:
    static void reportError(const QString &errorMessage){
        QFile file(StandardPaths::errorLog());
        if(file.open(QIODevice::Append | QFile::Text)){
            QTextStream out(&file);
            out<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz")<<" "
              <<errorMessage<<"\n";
            file.close();
        }
    }

    static QStringList getErrorLog(){
        QFile file(StandardPaths::errorLog());
        if(file.open(QIODevice::ReadOnly)){
            QStringList lines = QStringList();
            QTextStream in(&file);
            while(!in.atEnd())
                lines.append(in.readLine());
            file.close();
            return lines;
        }
    }
};

#endif // ERRORREPORTER

