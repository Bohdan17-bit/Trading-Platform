#include "apiservice.h"
#include <qeventloop.h>
#include <QDebug>


ApiService::ApiService()
{
    accessManager = new QNetworkAccessManager();
}

ApiService& ApiService::getInstance()
{
    static ApiService instance;
    return instance;
}

QJsonDocument ApiService::MakeRequest(QString requestStr)
{
    ApiService& service = getInstance();
    QNetworkRequest request((QUrl(requestStr)));
    request.setTransferTimeout(3000);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = service.accessManager->get(request);
    QEventLoop eventLoop;
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();
    QByteArray response_data = reply->readAll();
    reply->deleteLater();
    return QJsonDocument::fromJson(response_data);
}

