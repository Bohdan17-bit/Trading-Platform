#ifndef APISERVICE_H
#define APISERVICE_H

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include <QtNetwork>

class ApiService
{
private:
    ApiService(){};
public:
    static QJsonDocument MakeRequestChartData(QString requestStr);
};

#endif // APISERVICE_H
