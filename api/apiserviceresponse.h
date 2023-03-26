#ifndef APISERVICERESPONSE_H
#define APISERVICERESPONSE_H
#include <QJsonDocument>

class ApiServiceResponse // об'єкт сервісу
{
private:
    QJsonDocument response;
public:
    ApiServiceResponse(QJsonDocument response_service) : response (response_service)
    {

    };
    QJsonDocument get_response(); // умовний request від об'єкту сервісу
};

#endif // APISERVICERESPONSE_H
