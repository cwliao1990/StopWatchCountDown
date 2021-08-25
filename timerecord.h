#ifndef TIMEFORMAT_H
#define TIMEFORMAT_H

#include <QObject>
#include <QTime>
#include <QMetaType>
#include <QDataStream>

class TimeRecord: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString lapTime READ getLapTime CONSTANT)
    Q_PROPERTY(QString spiltTime READ getSpiltTime CONSTANT)
    Q_PROPERTY(QString lapIndex READ getLapIndex CONSTANT)

public:

    explicit TimeRecord(QObject *parent = nullptr);
    //TimeRecord();
    TimeRecord& operator=(const TimeRecord& source)
    {
        m_lapIndex = source.m_lapIndex;
        m_lapTime = source.m_lapTime;
        m_spiltTime = source.m_spiltTime;
        return *this;
    }
    void setLapIndex(QString lapIndex);
    void setLapTime(QString lapTime);
    void setSpiltTime(QString spiltTime);

    QString getLapIndex() {return m_lapIndex;};
    QString getLapTime() {return m_lapTime;};
    QString getSpiltTime() {return m_spiltTime;};
    QString getFormatedTime();

    static QString getFormatedTime(QTime* t);
    friend QDataStream& operator<<(QDataStream &ds, const TimeRecord &timeRecord);//cwl_未使用
    friend QDataStream& operator>>(QDataStream &ds, TimeRecord &timeRecord);//cwl_未使用

signals:

private:
    QString m_lapIndex;
    QString m_lapTime;
    QString m_spiltTime;
};
//Q_DECLARE_METATYPE(TimeRecord); //cwl_未使用
//QDataStream& operator << (QDataStream& out, const TimeRecord &timeRecord);
//QDataStream& operator >> (QDataStream& in, TimeRecord &timeRecord);
#endif // TIMEFORMAT_H
