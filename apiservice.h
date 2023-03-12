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
    static QNetworkAccessManager *accessManager;
public:
    static QJsonDocument extracted();
    static QJsonDocument MakeRequest(QString requestStr);
};

#endif // APISERVICE_H
