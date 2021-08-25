#ifndef STOPWATCH_H
#define STOPWATCH_H
#define TIME_INTERVAL 10

#include <QObject>
#include <QDebug>
#include <QQmlListProperty>
#include <QSettings>
#include "timerecord.h"

class StopWatch : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString timeDisplay READ getTimeDisplay WRITE setTimeDisplay NOTIFY timeDisplayChanged)
    Q_PROPERTY(QQmlListProperty<QObject> timeRecordList READ getTimeRecordList NOTIFY timeRecordListChanged)

public:
    explicit StopWatch(QObject *parent = nullptr);
    ~StopWatch();

    Q_INVOKABLE void setStopWatchRun(bool bRun);
    Q_INVOKABLE void addNewTimeRecord(TimeRecord* savedTimeRecord = NULL);
    Q_INVOKABLE void reset();
    Q_INVOKABLE void setTimeDisplay(const QString &newTimeDisplay);
    const QString &getTimeDisplay() const;

    QQmlListProperty<QObject> getTimeRecordList();
    static TimeRecord* getIntervalTimeRecord(TimeRecord* timeRecord1, TimeRecord* timeRecord2);
//    static int timeRecordListCount(QQmlListProperty<QObject> *list); //cwl_尚未確認必要性
//    static QObject* timeRecordListAt(QQmlListProperty<QObject> *list, int i); //cwl_尚未確認必要性
signals:
    void timeDisplayChanged();
    void timeRecordListChanged();

public slots:
    void timeIncrease();

private:
    QList<QObject*> m_timeRecordList;
    QTimer *m_timer;
    QTime m_runTime;
    QTime m_lastCumulativeTime;
    QString m_timeDisplay;
    QList<QString> m_settingList;
};

#endif // STOPWATCH_H
