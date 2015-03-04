#include "ftphandler.h"
#include <QFileInfo>

FtpHandler::FtpHandler(QObject *parent) : QObject(parent),
    state(State::IDLE),
    username("anonymous"),
    password(""),
    port(21),
    address("localhost"),
    manager(new QNetworkAccessManager(this)),
    cmdList(QList<FTPCommand*>())
{
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply*)));
}

FtpHandler::~FtpHandler()
{
}

// PUBLIC METHODS
void FtpHandler::uploadFile(const QString &filename)
{
    QFileInfo file(filename);
    if(file.exists())
        {
            QUrl url(QString("ftp://%1/%2").arg(address).arg(file.fileName()));
            url.setUserName(username);
            url.setPassword(password);
            url.setPort(port);
            sheduleCommand(FTPCommand::createUploadCommand(url, filename, new QFile(filename)));
        }
    else
        emit error(tr("File does not exists!"));
}

void FtpHandler::downloadFile(const QString &filename, const QString &downloadLocation)
{
    QUrl url(QString("ftp://%1/%2").arg(address).arg(filename));
    url.setUserName(username);
    url.setPassword(password);
    url.setPort(port);
    sheduleCommand(FTPCommand::createDownloadCommand(url, filename, downloadLocation));
}

//PRIVATE SLOTS
void FtpHandler::managerFinished(QNetworkReply *reply)
{
    if(reply->error() != QNetworkReply::NetworkError::NoError)
        emit error(reply->errorString());

    FTPCommand *finishedCommand = cmdList.takeFirst();
    if(finishedCommand->getMode() == FTPCommand::Mode::DOWNLOAD)
        {
            QByteArray data = reply->readAll();
            QString downloadedFileName = QString("%1/%2").arg(finishedCommand->getDownloadLocation()).arg(finishedCommand->getFilename());
            QFile *file = new QFile(downloadedFileName);
            if(file->open(QIODevice::ReadWrite))
                {
                    file->write(data);
                    file->close();
                }
            else
                emit error(QString(tr("Could not save downloaded File: %1")).arg(finishedCommand->getFilename()));
        }

    if(!cmdList.isEmpty())
        processCommand();
    else
        state = State::IDLE;

    emit finished(finishedCommand->getFilename());
    reply->deleteLater();
    delete finishedCommand;
}

void FtpHandler::progress(qint64 bytesSend, qint64 totalBytes)
{
    int percentage = ( 100 * (double) bytesSend) / (double) totalBytes;
    emit progress(percentage);
}

//PRIVATE METHODS
void FtpHandler::sheduleCommand(FTPCommand *cmd)
{
    cmdList.append(cmd);
    if(state == State::IDLE)
        processCommand();
}

void FtpHandler::processCommand()
{
    if(!cmdList.isEmpty())
        {
            emit started();
            state = BUSY;
            FTPCommand *curCmd = cmdList.first();
            if(curCmd->getMode() == FTPCommand::Mode::DOWNLOAD)
                {
                    QNetworkReply *reply = manager->get(QNetworkRequest(curCmd->getUrl()));
                    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(progress(qint64,qint64)));
                }
            else if(curCmd->getMode() == FTPCommand::Mode::UPLOAD)
                {
                    QFile *data = curCmd->getUploadData();
                    if(data->open(QIODevice::ReadOnly))
                        {
                            QNetworkReply *reply = manager->put(QNetworkRequest(curCmd->getUrl()), data);
                            connect(reply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(progress(qint64,qint64)));
                        }
                    else
                        emit error(tr("Could not read file: Permission denied!"));
                }
        }
}

// GETTER / SETTER
void FtpHandler::setUser(const QString &username, const QString &password)
{
    this->username = username;
    this->password = password;
}

void FtpHandler::setPort(int port)
{
    this->port = port;
}

void FtpHandler::setServer(const QString &address)
{
    this->address = address;
}
