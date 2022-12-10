#ifndef TIMECONVERTER_H
#define TIMECONVERTER_H

#include <QString>
#include <ctime>
#include <QDebug>

class TimeConverter
{
private:

    TimeConverter();

    static const int WEEK_IN_SECONDS = 7 * 60 * 60 * 24;
    static const int DAY_IN_SECONDS = 60 * 60 * 22;
    static const int HALF_DAY_IN_SECOND = 60 * 60 * 12;
    static const int FOUR_HOURS_IN_SECOND = 60 * 60 * 4;
    static const int ONE_AND_HALF_HOURS_IN_SECOND = 60 * 60 * 1.5;

    static const int MINUTE_5 = 5 * 60;
    static const int MINUTE_15 = 15 * 60;
    static const int HOUR_2 = 2 * 60 * 60;

    static int getCurrentTime();

public:

    static QString get5MinuteInSeconds();
    static QString get15MinuteInSeconds();
    static QString get2HourInSeconds();

    static QString getCurrentUnixTime();
    static QString getLastHalfDayUnixTime();
    static QString getFourHoursUnixTime();
    static QString getOneAndHalfHourUnixTime();
    static QString getTwoHoursUnixTime();
    static QString getLastOneDayUnixTime();
};

#endif // TIMECONVERTER_H
