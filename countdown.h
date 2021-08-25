#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QObject>
#include <QTime>
#include <QTimer>
#include "timerecord.h"
class CountDown : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString timeDisplay READ getTimeDisplay WRITE setTimeDisplay NOTIFY timeDisplayChanged)
    Q_PROPERTY(bool isRun READ getIsRun NOTIFY isRunChanged)

public:
    explicit CountDown(QObject *parent = nullptr);
    ~CountDown();

    Q_INVOKABLE void setCountDownRun(bool bRun);
    Q_INVOKABLE void setHMS(int hr, int min, int sec);
    Q_INVOKABLE int getHour() {return m_time.hour();};
    Q_INVOKABLE int getMin() {return m_time.minute();};
    Q_INVOKABLE int getSec() {return m_time.second();};
    const QString &getTimeDisplay() const;
    void setTimeDisplay(const QString &newTimeDisplay);
    const bool &getIsRun() const;

signals:
    void timeDisplayChanged();
    void isRunChanged();

public slots:
    void timeDecrease();
    void timeUp();
private:
    QTimer m_displayTimer;
    QTimer m_alarmTimer;
    QTime m_time;
    QString m_timeDisplay;
    bool m_isRun;
};

#endif // COUNTDOWN_H
