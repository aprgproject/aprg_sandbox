#pragma once

#include <AlbaOptional.hpp>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <TcomToolsConfiguration.hpp>

namespace tcomToolsGui
{

enum class ThreadState
{
    ToBeDestroyed,
    ToBeExecutionToBeStarted,
    ToBeIgnored
};

class QImage;

class StepHandlerThread : public QThread
{
    Q_OBJECT

public:
    StepHandlerThread(QObject *parent = 0);
    ~StepHandlerThread();
    void execute(TcomToolsConfiguration & configuration);
signals:
    void finished();
protected:
    void run() Q_DECL_OVERRIDE;
private:
    QMutex m_mutex;
    QWaitCondition m_condition;
    TcomToolsConfiguration m_configuration;
    ThreadState m_state;
};

}
