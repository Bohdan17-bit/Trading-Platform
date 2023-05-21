#include "apiservice.h"
#include <qeventloop.h>
#include <QDebug>

QNetworkAccessManager* ApiService::accessManager = new QNetworkAccessManager();

QJsonDocument ApiService::MakeRequest(QString requestStr)
{
    QNetworkRequest request((QUrl(requestStr)));
    request.setTransferTimeout(3000);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = accessManager->get(request);
    while (!reply->isFinished())
    {
        qApp->processEvents();
    }
    QByteArray response_data = reply->readAll();
    reply->deleteLater();
    return QJsonDocument::fromJson(response_data);
}
