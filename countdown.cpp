 #include "countdown.h"
#include <QMessageBox>
#include <QDebug>
#include <QSound>
#include <QSoundEffect>
CountDown::CountDown(QObject *parent) : QObject(parent)
{
    m_time = QTime(0, 0, 0, 0);
    m_timeDisplay = m_time.toString("hh:mm.ss.zzz").left(11);
    m_isRun = false;
    connect(&m_displayTimer, SIGNAL(timeout()), this, SLOT(timeDecrease()));
    connect(&m_alarmTimer, SIGNAL(timeout()), this, SLOT(timeUp()));
}

CountDown::~CountDown()
{

}

void CountDown::setCountDownRun(bool bRun)
{
    if(bRun) {
        m_displayTimer.start(10);
        qDebug() << m_time.msecsTo(QTime(0, 0));
        m_alarmTimer.start(-m_time.msecsTo(QTime(0, 0)));
        m_isRun = true;
        emit isRunChanged();
    }
    else {
        m_displayTimer.stop();
        m_alarmTimer.stop();
        m_isRun = false;
        emit isRunChanged();
    }

}

void CountDown::setHMS(int hr, int min, int sec) //cwl_check input time is valid
{
    qDebug() << hr << min << sec;
    m_time.setHMS(hr, min, sec);
    setTimeDisplay(m_time.toString("hh:mm.ss.zzz").left(11));
}

const QString &CountDown::getTimeDisplay() const
{
    return m_timeDisplay;
}

void CountDown::setTimeDisplay(const QString &newTimeDisplay)
{
    if (m_timeDisplay == newTimeDisplay)
        return;
    m_timeDisplay = newTimeDisplay;
    emit timeDisplayChanged();
}

const bool &CountDown::getIsRun() const
{
    return m_isRun;
}

void CountDown::timeDecrease()
{
    m_time = m_time.addMSecs(-10);
    setTimeDisplay(m_time.toString("hh:mm.ss.zzz").left(11));
}

void CountDown::timeUp()
{
    setCountDownRun(false);
    setHMS(0, 0, 0);
//    QSoundEffect effect;
//    effect.setSource(QUrl::fromLocalFile("notificationBell.wav"));
//    effect.setLoopCount(QSoundEffect::Infinite);
//    effect.setVolume(0.25f);
//    effect.play();
    //QSound bell(":/sound/ex.wav");//cwl_不能正確運作
    QSound bell(":/sound/notificationBell.wav");
    bell.play();
    QMessageBox msgBox(QMessageBox::Warning, "Warning", "Time's up.");
    msgBox.setDefaultButton(QMessageBox::Close);
    msgBox.exec();

}
