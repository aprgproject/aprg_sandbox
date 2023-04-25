#pragma once

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <WcdmaToolsConfiguration.hpp>

namespace wcdmaToolsGui {

class QImage;

class StepHandlerThread : public QThread {
    Q_OBJECT
    enum class ThreadState { Killed, Active, Inactive };

public:
    StepHandlerThread(WcdmaToolsConfiguration& configuration);
    ~StepHandlerThread();
    void execute();
signals:
    void executionDone();

protected:
    void run() Q_DECL_OVERRIDE;

private:
    QMutex m_mutex;
    QWaitCondition m_condition;
    WcdmaToolsConfiguration& m_configuration;
    ThreadState m_state;
};

}  // namespace wcdmaToolsGui
