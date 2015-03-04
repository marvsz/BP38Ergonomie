#ifndef FTPHANDLER_H
#define FTPHANDLER_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>

class FtpHandler : public QObject
{
    Q_OBJECT
public:
    explicit FtpHandler(QObject *parent = 0);
    ~FtpHandler();

    void uploadFile(const QString &filename);
    void downloadFile(const QString &filename, const QString &downloadLocation);

    void setUser(const QString &username, const QString &password = "");
    void setPort(int port);
    void setServer(const QString &address);

signals:
    void progress(int progress);
    void started();
    void finished(const QString filename);
    void error(const QString &error);

private slots:
    void managerFinished(QNetworkReply *reply);
    void progress(qint64 bytesSend, qint64 totalBytes);

private:
    class FTPCommand
    {
    public:
        enum Mode {DOWNLOAD, UPLOAD};

        static FTPCommand* createUploadCommand(const QUrl &url, const QString &filename, QFile *data)
        {
            return new FTPCommand(url, filename, data);
        }

        static FTPCommand* createDownloadCommand(const QUrl &url, const QString &filename, const QString &downloadLocation)
        {
            return new FTPCommand(url, filename, downloadLocation);
        }

        ~FTPCommand()
        {

        }

        Mode getMode() const
        {
            return mode;
        }
        QUrl getUrl() const
        {
            return url;
        }
        QString getFilename() const
        {
            return filename;
        }
        QString getDownloadLocation() const
        {
            if(mode == Mode::DOWNLOAD)
                return downloadLocation;
            return "";
        }
        QFile* getUploadData() const
        {
            if(mode == Mode::UPLOAD)
                return data;
            return 0;
        }

    private:
        explicit FTPCommand(const QUrl &url, const QString &filename) :
            url(url),
            filename(filename)
        {

        }

        explicit FTPCommand(const QUrl &url, const QString &filename, const QString &downloadLocation) :
            FTPCommand(url, filename)
        {
            mode = Mode::DOWNLOAD;
            this->downloadLocation = downloadLocation;
        }

        explicit FTPCommand(const QUrl &url, const QString &filename, QFile *data) :
            FTPCommand(url, filename)
        {
            mode = Mode::UPLOAD;
            this->data = data;
        }

        Mode mode;
        QUrl url;
        QString filename;
        QString downloadLocation;
        QFile *data;
    };
    enum State {IDLE, BUSY};

    State state;

    QString username;
    QString password;
    int port;
    QString address;

    QNetworkAccessManager *manager;

    QList<FTPCommand*> cmdList;

    void sheduleCommand(FTPCommand *cmd);
    void processCommand();

};

#endif // FTPHANDLER_H
