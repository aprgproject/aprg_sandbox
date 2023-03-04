#include "BtsPrintReaderWithRollback.hpp"

#include <iostream>

using namespace std;

namespace wcdmaToolsBackend
{

BtsPrintReaderWithRollback::BtsPrintReaderWithRollback()
    : m_isRollbackActivated(false)
{}

void BtsPrintReaderWithRollback::clear()
{
    m_isRollbackActivated = false;
    m_previousPrint.clear();
}

bool BtsPrintReaderWithRollback::isGood() const
{
    return m_inputStream.good();
}

BtsLogPrint BtsPrintReaderWithRollback::getPrint()
{
    if(isGood())
    {
        if(m_isRollbackActivated)
        {
            m_isRollbackActivated = false;
            return m_previousPrint;
        }
        else
        {
            m_inputStream >> m_previousPrint;
            return m_previousPrint;
        }
    }
    return BtsLogPrint{};
}

void BtsPrintReaderWithRollback::rollBackPrint()
{
    if(m_isRollbackActivated)
    {
        cout<<"Double rollback of prints detected, possible print drop, please implement line put back in stream to avoid this.\n";
    }
    m_isRollbackActivated = true;
}
void BtsPrintReaderWithRollback::openIfNeeded(string const& filePath)
{
    if(!m_inputStream.is_open())    {
        m_inputStream.open(filePath);
    }
}

double BtsPrintReaderWithRollback::getCurrentLocation()
{
    return m_inputStream.tellg();
}

}
