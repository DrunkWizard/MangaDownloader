#include "scrapimage.hpp"
#include "filedownloader.hpp"


ScrapImage::ScrapImage(QObject *parent) : QObject(parent), manager(new QNetworkAccessManager(this))
{
}
void ScrapImage::parse(QString url, bool all, int from, int to){
    link = url;
    QRegularExpression mangaNameRegExp(".net/.*");
    QRegularExpressionMatch match = mangaNameRegExp.match(url);
    if(match.hasMatch())
        mangaName = match.captured(0);
    mangaName.remove(0, 5);
    QDir().mkdir(QDir::currentPath() + R"(/Library/)" + mangaName);

    if(all){
        QNetworkAccessManager *netManager(new QNetworkAccessManager(this));
        QNetworkRequest request(url);
        QNetworkReply *reply = netManager->post(request, "");
        connect(reply, &QNetworkReply::finished,
                [this, reply](){
            QString buff = reply->readAll();
            QRegularExpression lastChapterRegExp("<a href=\"/" + mangaName + ".*a>");
            QRegularExpression findNumber("\\d+");
            QRegularExpressionMatch matchOnPage = lastChapterRegExp.match(buff);
            QString stringFromPage;
            QString lastChapter;
            if(matchOnPage.hasMatch())
                stringFromPage = matchOnPage.captured(0);
            QRegularExpressionMatch matchNumber = findNumber.match(stringFromPage);
            if(matchNumber.hasMatch())
                lastChapter = matchNumber.captured(0);
            int lastChapterNumber = lastChapter.toInt();
            for(int chapter = 1; chapter <= lastChapterNumber; chapter++){
                QDir().mkdir(QDir::currentPath() + R"(/Library/)" + "/" + mangaName+ "/" + "chapter " + QString::number(chapter));
                loadAllPages(0, chapter);
            }
            return;
        });
    }
    else{
        for(int chapter = from; chapter < to + 1; chapter++){
            QDir().mkdir(QDir::currentPath() + R"(/Library/)" + "/" + mangaName+ "/" + "chapter " + QString::number(chapter));
            loadAllPages(0, chapter);
            }
        }
    }

void ScrapImage::loadAllPages(int index, int chapter){
    QNetworkRequest request(link + "/" + QString::number(chapter) + "/" + QString::number(index + 1));
    QNetworkReply *reply = manager->post(request, "");
    connect(reply, &QNetworkReply::finished,
            [this, reply, index, chapter](){
        if(reply->error() != QNetworkReply::NoError){
            qDebug() << "All pages loaded";
            setdownloadInProgress(false);
            return;
        }
        else{
            setdownloadInProgress(true);
            QString buff = reply->readAll();
            FileDownloader *load = new FileDownloader();
            QString imgUrl;
            QRegularExpression imgRegExp("src=.*https://.*\.imggur\.net/.*\.jpg");
            QRegularExpressionMatch match = imgRegExp.match(buff);
            if(match.hasMatch())
                imgUrl = match.captured(0);
            imgUrl.remove(0, 5);
            imgUrl.replace("https", "http");
            load->downloadFileFromURL(imgUrl, QDir::currentPath() + R"(/Library/)" + "/" + mangaName+ "/" + "chapter " + QString::number(chapter));
            loadAllPages(index + 1, chapter);
            if(load->isEnd){
                load->deleteLater();
            }
        }
    });
}

bool ScrapImage::downloadInProgress()
{
    return m_downloadInProgress;
}

void ScrapImage::setdownloadInProgress(bool value)
{
    if(value == m_downloadInProgress)
        return;
    m_downloadInProgress = value;
    emit downloadInProgressChanged(value);
}
