#include "StepHandlerThread.hpp"

#include <StepHandler.hpp>

#include <QtWidgets>
using namespace std;

namespace wcdmaToolsGui{

StepHandlerThread::StepHandlerThread(WcdmaToolsConfiguration & configuration)
    : QThread(nullptr)
    , m_mutex()
    , m_condition()
    , m_configuration(configuration)
    , m_state(ThreadState::Inactive)
{}

StepHandlerThread::~StepHandlerThread()
{
    m_mutex.lock();
    m_state = ThreadState::Killed;
    m_mutex.unlock();
    m_condition.wakeOne();
    wait();
}

void StepHandlerThread::execute()
{
    m_mutex.lock();
    m_state = ThreadState::Active;
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

        if(m_state == ThreadState::Active)
        {
            StepHandler stepHandler;
            stepHandler.execute(m_configuration);
            emit executionDone();
        }
        else if(m_state == ThreadState::Killed)
        {
            return;
        }
    }
}

}
