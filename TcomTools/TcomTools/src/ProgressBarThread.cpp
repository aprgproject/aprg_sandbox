#include <ProgressBarThread.hpp>

#include <QtWidgets>
#include <StepHandler.hpp>

using namespace std;

namespace tcomToolsGui
{

ProgressBarThread::ProgressBarThread(QObject *parent)
    : QThread(parent)
    , m_mutex()
    , m_condition()
    , m_state(ThreadState::Stopped)
{}

ProgressBarThread::~ProgressBarThread()
{
    m_mutex.lock();
    m_state = ThreadState::Killed;
    m_mutex.unlock();
    m_condition.wakeOne();
    wait();
}

void ProgressBarThread::startUpdatingProgressBar()
{
    m_mutex.lock();
    m_state = ThreadState::Started;
    m_mutex.unlock();
    m_condition.wakeAll();
}

void ProgressBarThread::stopUpdatingProgressBar()
{
    m_mutex.lock();
    m_state = ThreadState::Stopped;
    m_mutex.unlock();
}

void ProgressBarThread::run()
{
    forever
    {
        if(m_state == ThreadState::Stopped)
        {
            m_mutex.lock();
            m_condition.wait(&m_mutex);
            m_mutex.unlock();
        }
        else if(m_state == ThreadState::Started)
        {
            emit triggerUpdateProgressBar();
            msleep(500);
        }
        else if(m_state == ThreadState::Killed)
        {
            return;
        }
    }
}

}


