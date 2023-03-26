#ifndef TIMECONVERTER_H
#define TIMECONVERTER_H

#include <QString>
#include <ctime>
#include <QDebug>

class TimeConverter
{
private:

    TimeConverter();

    static const int SIX_HOURS_IN_SECONDS = 60 * 60 * 6;
    static const int DAY_IN_SECONDS = 60 * 60 * 24;
    static const int ONE_WEEK_IN_SECONDS = 7 * 60 * 60 * 24;

    static const int MINUTE_5 = 5 * 60;
    static const int MINUTE_15 = 15 * 60;
    static const int HOUR_2 = 2 * 60 * 60;

    static int getCurrentTime();

public:

    static QString get5MinuteInSeconds();
    static QString get15MinuteInSeconds();
    static QString get2HourInSeconds();

    static QString getLast5MinuteInSeconds();
    static QString getLast15MinuteInSeconds();
    static QString getLast2HourInSeconds();

    static QString getCurrentUnixTime();

    static QString getLastQuarterUnixTime(); // 72 точки для 5 хвилинного графіку 6 hours total
    static QString getLastOneDayUnixTime(); // 96 точок для 15 хвилинного графіку 24 hours total
    static QString getLastWeekUnixTime(); // 84 точки для 2 годинного графіку 24*7 hours total

};

#endif // TIMECONVERTER_H
