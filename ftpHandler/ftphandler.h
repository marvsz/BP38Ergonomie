#ifndef FTPHANDLER_H
#define FTPHANDLER_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class FtpHandler : public QObject
{
    Q_OBJECT
public:
    explicit FtpHandler(QObject *parent = 0);
    ~FtpHandler();

    void uploadFile(const QString &filename);

    QString getLastError() const;

    void setUser(const QString &username, const QString &password = "");
    void setPort(int port);
    void setServer(const QString &address);

signals:
    void progress(int progress);
    void started();
    void finished();
    void error();

private slots:
    void managerFinished(QNetworkReply *reply);
    void uploadProgress(qint64 bytesSend, qint64 totalBytes);

private:
    QString username;
    QString password;
    int port;
    QString address;

    QString lastError;

    QNetworkAccessManager *manager;

    void errorOccurred(const QString &msg);
};

#endif // FTPHANDLER_H
