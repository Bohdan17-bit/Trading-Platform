#include "timeconverter.h"

int TimeConverter::getCurrentTime()
{
    return std::time(0);
}

QString TimeConverter::getCurrentUnixTime()
{
    return QString::number(getCurrentTime());
}

QString TimeConverter::getLastOneDayUnixTime()
{
    return QString::number(getCurrentTime() - DAY_IN_SECONDS);
}

QString TimeConverter::getFourHoursUnixTime()
{
    return QString::number(getCurrentTime() - FOUR_HOURS_IN_SECOND);
}

QString TimeConverter::getLastHalfDayUnixTime()
{
    return QString::number(getCurrentTime() - HALF_DAY_IN_SECOND);
}

QString TimeConverter::getOneAndHalfHourUnixTime()
{
    return QString::number(getCurrentTime() - ONE_AND_HALF_HOURS_IN_SECOND);
}

QString TimeConverter::get5MinuteInSeconds()
{
    return QString::number(5 * 60);
}

QString TimeConverter::get15MinuteInSeconds()
{
    return QString::number(15 * 60);
}

QString TimeConverter::get2HourInSeconds()
{
    return QString::number(2 * 60 * 60);
}
