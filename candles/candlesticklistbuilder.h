#ifndef CANDLESTICKLISTBUILDER_H
#define CANDLESTICKLISTBUILDER_H

#include "candlesticklist.h"
#include "api/apiserviceresponse.h"
#include <QtCharts/QCandleStickSet>

class CandleStickListBuilder : public CandleStickList
{
private:
    ApiServiceResponse apiServiceResponse;
public:
    CandleStickListBuilder(ApiServiceResponse response) : apiServiceResponse(response)
    {

    }
    QList<QtCharts::QCandlestickSet*> get_list_candlestick() override;
};

#endif // CANDLESTICKLISTBUILDER_H
