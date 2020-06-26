#include "filedownloader.hpp"

void FileDownloader::downloadFileFromURL(const QString &url, const QString &filePath) {

    const QString fileName = filePath + url.right(url.size() - url.lastIndexOf("/"));
    file = new QFile();
    file->setFileName(fileName);
    file->open(QIODevice::WriteOnly);
    if (!file->isOpen()) {
        return;
    }

    QNetworkAccessManager *manager = new QNetworkAccessManager;

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(onDownloadFileComplete(QNetworkReply *)));
    manager->get(request);
}

void FileDownloader::onDownloadFileComplete(QNetworkReply *reply) {
    connect(reply, &QNetworkReply::readyRead,
            [this](){
        isEnd = true;
    });
    if (!file->isWritable()) {
        return;
    }
    file->write(reply->readAll());
    file->close();
    reply -> deleteLater();
}
