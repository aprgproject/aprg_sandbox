#include "IntegrationHistory.hpp"

namespace alba
{

namespace algebra
{

IntegrationHistory::IntegrationHistory()
    : m_lastIntegrationPurpose(IntegrationPurpose::NotSet)
{}

IntegrationPurpose IntegrationHistory::getLastIntegrationPurpose() const
{
    return m_lastIntegrationPurpose;
}

void IntegrationHistory::setLastIntegrationPurpose(
        IntegrationPurpose const purpose)
{
    if(IntegrationPurpose::NoChange != purpose)
    {
        m_lastIntegrationPurpose =  purpose;
    }
}

void IntegrationHistory::clear()
{
    m_lastIntegrationPurpose =  IntegrationPurpose::NotSet;
}


}

}
