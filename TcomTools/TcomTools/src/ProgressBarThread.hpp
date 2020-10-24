#pragma once

#include <Optional/AlbaOptional.hpp>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <TcomToolsConfiguration.hpp>

namespace tcomToolsGui
{

class QImage;

class ProgressBarThread : public QThread
{
    Q_OBJECT
    enum class ThreadState
    {
        Killed,
        Started,
        Stopped
    };
public:
    ProgressBarThread(QObject *parent = 0);
    ~ProgressBarThread();
    void startUpdatingProgressBar();
    void stopUpdatingProgressBar();
signals:
    void triggerUpdateProgressBar();
protected:
    void run() Q_DECL_OVERRIDE;
private:
    QMutex m_mutex;
    QWaitCondition m_condition;
    ThreadState m_state;
};

}
