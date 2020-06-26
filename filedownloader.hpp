#ifndef FILEDOWNLOADER_HPP
#define FILEDOWNLOADER_HPP

#include <QObject>
#include <QFile>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class FileDownloader : public QObject
{
    Q_OBJECT
        QFile *file;
    public:
        explicit FileDownloader(QObject *parent = 0) : QObject(parent) {}
        virtual ~FileDownloader() { delete file; }
        bool isEnd = false;

        void downloadFileFromURL(const QString &url, const QString &filePath);

    private slots:
        void onDownloadFileComplete(QNetworkReply *reply);
};

#endif // FILEDOWNLOADER_HPP
