#include "utils/timeconverter.h"

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

QString TimeConverter::getLastQuarterUnixTime()
{
    return QString::number(getCurrentTime() - SIX_HOURS_IN_SECONDS);
}

QString TimeConverter::getLastWeekUnixTime()
{
    return QString::number(getCurrentTime() - ONE_WEEK_IN_SECONDS);
}

QString TimeConverter::getLast5MinuteInSeconds()
{
    return QString::number(getCurrentTime() - 5 * 60);
}

QString TimeConverter::getLast15MinuteInSeconds()
{
    return QString::number(getCurrentTime() - 15 * 60);
}

QString TimeConverter::getLast2HourInSeconds()
{
    return QString::number(getCurrentTime() - 60 * 60);
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
