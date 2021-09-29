#include "stopwatch.h"
#include <QDebug>
#include <QtCore>
StopWatch::StopWatch(QObject *parent) : QObject(parent) {
  m_timer = NULL;

  QSettings settings(QSettings::NativeFormat, QSettings::UserScope, "Demo",
                     "StopWatch-CountDown");
  m_settingList = settings.value("m_settingList").value<QList<QString>>();
  qDebug() << m_settingList;
  int i = 0;
  while (i < m_settingList.size()) {
    TimeRecord *timeRecord = new TimeRecord();
    timeRecord->setLapIndex(m_settingList[i++]);
    timeRecord->setLapTime(m_settingList[i++]);
    timeRecord->setSpiltTime(m_settingList[i++]);
    m_timeRecordList.append(timeRecord);
  }
  m_timeDisplay =
      settings.value("m_timeDisplay", "00:00:00.00").value<QString>();
  m_runTime = settings.value("m_runTime", QTime(0, 0)).value<QTime>();
  m_lastCumulativeTime =
      settings.value("m_lastCumulativeTime", QTime(0, 0)).value<QTime>();
  setTimeDisplay(m_runTime.toString("hh:mm:ss.zzz").left(11));
}

StopWatch::~StopWatch() {
  if (m_timer != NULL) {
    m_timer = NULL;
    delete m_timer;
  }
  qDebug() << "(Destruction) myList Size =" << m_settingList.size();
  QSettings settings(QSettings::NativeFormat, QSettings::UserScope, "Demo",
                     "StopWatch-CountDown");
  settings.setValue("m_settingList", QVariant::fromValue(m_settingList));
  settings.setValue("m_runTime", QVariant::fromValue(m_runTime));
  settings.setValue("m_lastCumulativeTime",
                    QVariant::fromValue(m_lastCumulativeTime));

  foreach (QObject *t, m_timeRecordList) { delete t; }
}

void StopWatch::setStopWatchRun(bool bRun) {
  if (bRun) {
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeIncrease()));
    m_timer->start(TIME_INTERVAL);
  } else {
    m_timer->stop();
  }
}

void StopWatch::addNewTimeRecord(TimeRecord *savedTimeRecord) {

  if ((m_timeRecordList.size()) > 8)
    return;
  QTime totalTime = m_runTime;
  QTime lapTime = QTime(0, 0);
  lapTime = lapTime.addMSecs(-totalTime.msecsTo(m_lastCumulativeTime));
  TimeRecord *timeRecord = new TimeRecord();
  timeRecord->setLapIndex(
      QString("%1").arg(m_timeRecordList.size() + 1, 1, 10, QChar('0')));
  timeRecord->setLapTime(lapTime.toString("hh:mm:ss.zzz").left(11));
  timeRecord->setSpiltTime(totalTime.toString("hh:mm:ss.zzz").left(11));
  m_lastCumulativeTime = totalTime;
  m_timeRecordList.insert(0, timeRecord);

  m_settingList.insert(0, timeRecord->getSpiltTime());
  m_settingList.insert(0, timeRecord->getLapTime());
  m_settingList.insert(0, timeRecord->getLapIndex());
  qDebug() << "m_settingList Size =" << m_settingList.size()
           << "m_timeRecordList Size =" << m_timeRecordList.size();
  emit timeRecordListChanged();
}

void StopWatch::reset() {
  qDebug() << "myList Size =" << m_settingList.size();
  m_settingList.clear();

  if (m_timer != NULL) {
    m_timer = NULL;
    delete m_timer;
  }

  m_timeRecordList.clear();
  foreach (QObject *t, m_timeRecordList) { delete t; }
  emit timeRecordListChanged();

  m_runTime.setHMS(0, 0, 0);
  m_lastCumulativeTime.setHMS(0, 0, 0);
  setTimeDisplay(m_runTime.toString("hh:mm:ss.zzz").left(11));
}

const QString &StopWatch::getTimeDisplay() const { return m_timeDisplay; }

void StopWatch::setTimeDisplay(const QString &newTimeDisplay) {
  if (m_timeDisplay == newTimeDisplay)
    return;
  m_timeDisplay = newTimeDisplay;
  emit timeDisplayChanged();
}

void StopWatch::timeIncrease() {
  m_runTime = m_runTime.addMSecs(TIME_INTERVAL);
  setTimeDisplay(m_runTime.toString("hh:mm:ss.zzz").left(11));
}

QQmlListProperty<QObject> StopWatch::getTimeRecordList() {
  return QQmlListProperty<QObject>(this, m_timeRecordList);
}
