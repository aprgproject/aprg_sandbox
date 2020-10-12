#include "BtsPrintReaderWithRollback.hpp"

#include <iostream>

using namespace std;

namespace tcomToolsBackend
{

bool BtsPrintReaderWithRollback::isGood() const
{
    return m_inputStream.good();
}

BtsLogPrint BtsPrintReaderWithRollback::getPrint()
{
    if(isGood())
    {
        if(m_isPreviousPrintValid)
        {
            m_isPreviousPrintValid = false;
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

void BtsPrintReaderWithRollback::rollBackGetPrint()
{
    if(m_isPreviousPrintValid)
    {
        cout<<"Double rollback of prints detected, possible print drop, please implement line put back in stream to avoid this."<<endl;
    }
    m_isPreviousPrintValid = true;
}

void BtsPrintReaderWithRollback::openIfNeeded(string const& filePath)
{
    if(!m_inputStream.is_open())
    {
        m_inputStream.open(filePath);
    }
}

}
