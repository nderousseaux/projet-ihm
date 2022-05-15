#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class FileDownloader : public QObject
{
 Q_OBJECT
 public:
  explicit FileDownloader(QUrl imageUrl, QObject *parent = 0);
  virtual ~FileDownloader();
  QByteArray downloadedData() const;
  QUrl getUrl();

 signals:
  void downloaded();

 private slots:
  void fileDownloaded(QNetworkReply* pReply);
  private:
  QNetworkAccessManager m_WebCtrl;
  QByteArray m_DownloadedData;
  QUrl m_url;
};

#endif // FILEDOWNLOADER_Hc
