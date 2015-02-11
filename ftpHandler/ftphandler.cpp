#include "ftphandler.h"
#include <QFileInfo>

FtpHandler::FtpHandler(QObject *parent) : QObject(parent),
    username("anonymous"),
    password(""),
    port(21),
    address("localhost"),
    manager(new QNetworkAccessManager())
{
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply*)));
}

FtpHandler::~FtpHandler()
{
    delete manager;
}

// PUBLIC METHODS
void FtpHandler::uploadFile(const QString &filename){
    QFileInfo file(filename);
    if(file.exists()){
        QUrl url(QString("ftp:://%1/%2").arg(address).arg(file.fileName()));
        url.setUserName(username);
        url.setPassword(password);
        url.setPort(port);

        QFile *data = new QFile(filename);
        if(data->open(QIODevice::ReadOnly)){
            emit started();
            QNetworkReply *reply = manager->put(QNetworkRequest(url), data);
            connect(reply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(uploadProgress(qint64,qint64)));
        }
        else
            errorOccurred("Could not read file: Permission denied!");
    }
    else
        errorOccurred("File does not exists!");
}

//PRIVATE SLOTS
void FtpHandler::managerFinished(QNetworkReply *reply){
    if(reply->error() != QNetworkReply::NetworkError::NoError)
        errorOccurred(reply->errorString());
    emit finished();
    reply->deleteLater();
}

void FtpHandler::uploadProgress(qint64 bytesSend, qint64 totalBytes){
    int percentage = ( 100 * (double) bytesSend) / (double) totalBytes;
    emit progress(percentage);
}

//PRIVATE METHODS

void FtpHandler::errorOccurred(const QString &msg){
    lastError = msg;
    emit error();
}

// GETTER / SETTER
QString FtpHandler::getLastError() const{
    return lastError;
}


void FtpHandler::setUser(const QString &username, const QString &password){
    this->username = username;
    this->password = password;
}

void FtpHandler::setPort(int port){
    this->port = port;
}

void FtpHandler::setServer(const QString &address){
    this->address = address;
}
