#include "apiservice.h"
#include <qeventloop.h>

QNetworkAccessManager* ApiService::accessManager = new QNetworkAccessManager();

QJsonDocument ApiService::MakeRequest(QString requestStr)
{
    QNetworkRequest request((QUrl(requestStr)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = accessManager->get(request);
    while (!reply->isFinished())
    {
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }
    QByteArray response_data = reply->readAll();
    reply->deleteLater();
    return QJsonDocument::fromJson(response_data);
}
