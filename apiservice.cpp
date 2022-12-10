#include "apiservice.h"
#include <qeventloop.h>

QJsonDocument ApiService::MakeRequestChartData(QString requestStr)
{
    QNetworkRequest request((QUrl(requestStr)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkAccessManager accessManager;
    QNetworkReply *reply = accessManager.get(request);
    while (!reply->isFinished())
    {
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }
    QByteArray response_data = reply->readAll();
    reply->deleteLater();
    return QJsonDocument::fromJson(response_data);
}
