#ifndef SCRAPIMAGE_HPP
#define SCRAPIMAGE_HPP
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>
#include <QRegularExpression>
#include <QDir>
#include <QEventLoop>

class ScrapImage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool downloadInProgress READ downloadInProgress WRITE setdownloadInProgress NOTIFY downloadInProgressChanged)
public:
    explicit ScrapImage(QObject *parent = nullptr);
    virtual ~ScrapImage(){ setdownloadInProgress(false); }
    Q_INVOKABLE void parse(QString url, bool all, int from, int to);
    void loadAllPages(int index, int chapter);
    bool downloadInProgress();
    void setdownloadInProgress(bool value);
private:
    QNetworkAccessManager *manager;
    QString mangaName;
    QString link;
    bool m_downloadInProgress;

private slots:
//    void onPageLoaded(QNetworkReply*);
signals:
    void downloadInProgressChanged(bool value);


};

#endif // SCRAPIMAGE_HPP
