#pragma once

#include <Optional/AlbaOptional.hpp>
#include <TcomToolsConfiguration.hpp>

#include <QMutex>
#include <QThread>
#include <QWaitCondition>

namespace tcomToolsGui
{

class QImage;

class StepHandlerThread : public QThread
{
    Q_OBJECT
    enum class ThreadState
    {
        Killed,
        Active,
        Inactive
    };
public:
    StepHandlerThread(QObject *parent = 0);
    ~StepHandlerThread();
    void execute(TcomToolsConfiguration const& configuration);
signals:
    void executionDone();
protected:
    void run() Q_DECL_OVERRIDE;
private:
    QMutex m_mutex;
    QWaitCondition m_condition;
    TcomToolsConfiguration m_configuration;
    ThreadState m_state;
};

}
