#include <StepHandlerThread.hpp>

#include <QtWidgets>
#include <StepHandler.hpp>

using namespace std;

namespace tcomToolsGui
{

StepHandlerThread::StepHandlerThread(QObject *parent)
    : QThread(parent)
    , m_mutex()
    , m_condition()
    , m_configuration()
    , m_state(ThreadState::ToBeIgnored)
{
}

StepHandlerThread::~StepHandlerThread()
{
    m_mutex.lock();
    m_state = ThreadState::ToBeDestroyed;
    m_mutex.unlock();
    m_condition.wakeOne();
    wait();
}

void StepHandlerThread::execute(TcomToolsConfiguration & configuration)
{
    m_mutex.lock();
    m_state = ThreadState::ToBeExecutionToBeStarted;
    m_configuration = configuration;
    m_mutex.unlock();
    m_condition.wakeOne();
}

void StepHandlerThread::run()
{
    forever
    {
        m_mutex.lock();
        m_condition.wait(&m_mutex);
        m_mutex.unlock();

        if(m_state == ThreadState::ToBeDestroyed)
        {
            return;
        }
        else if(m_state == ThreadState::ToBeExecutionToBeStarted)
        {
            StepHandler stepHandler(m_configuration);
            stepHandler.execute();
            emit finished();
        }
    }
}

}
