#include "timerecord.h"

TimeRecord::TimeRecord(QObject *parent)
{
    m_lapIndex = "";
    m_lapTime = "";
    m_spiltTime = "";
}

//TimeRecord::TimeRecord()
//{
//    m_lapIndex = "";
//    m_lapTime = "";
//    m_spiltTime = "";
//}

QDataStream& operator<<(QDataStream &ds, const TimeRecord &timeRecord)
{

//    QString lap = timeRecord.getLapIndex();
//    ds << timeRecord.getLapIndex() << timeRecord.m_lapTime<< timeRecord.m_spiltTime;
    return ds;
}

QDataStream& operator>>(QDataStream &ds, TimeRecord &timeRecord)
{

    QString lapIndex;
    QString lapTime;
    QString spiltTime;

    ds >> lapIndex >> lapTime >> spiltTime;

    timeRecord.setLapIndex(lapIndex);
    timeRecord.setLapTime(lapTime);
    timeRecord.setSpiltTime(spiltTime);

    return ds;
}

void TimeRecord::setLapIndex(QString lapIndex)
{
    m_lapIndex = lapIndex;
}

void TimeRecord::setLapTime(QString lapTime)
{
    m_lapTime = lapTime;
}

void TimeRecord::setSpiltTime(QString spiltTime)
{
    m_spiltTime = spiltTime;
}

//const QString TimeRecord::getLapIndex()
//{
//    return m_lapIndex;
//}

//const QString TimeRecord::getLapTime()
//{
//    return m_lapTime;
//}

//const QString TimeRecord::getSpiltTime()
//{
//    return m_spiltTime;
//}

QString TimeRecord::getFormatedTime()
{
    QString formatedTime = "";
//    formatedTime = QString("%1:%2:%3.%4")
//                       .arg(m_.hour(), 2, 10, QChar('0'))
//                       .arg(timeRecord->m_min, 2, 10, QChar('0'))
//                       .arg(timeRecord->m_sec, 2, 10, QChar('0'))
//                       .arg(timeRecord->m_ts, 2, 10, QChar('0'));
    return formatedTime;
}

QString TimeRecord::getFormatedTime(QTime* t)
{
    QString formatedTime = "";
    //formatedTime = t->toString("hh:mm:ss.zzz");
    formatedTime = QString("%1:%2:%3.%4")
                       .arg(t->hour(), 2, 10, QChar('0'))
                       .arg(t->minute(), 2, 10, QChar('0'))
                       .arg(t->second(), 2, 10, QChar('0'))
                       .arg(t->msec()/10, 2, 10, QChar('0'));
    return formatedTime;
}

