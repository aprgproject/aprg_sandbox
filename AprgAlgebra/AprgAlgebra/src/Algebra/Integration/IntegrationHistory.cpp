#include "IntegrationHistory.hpp"

#include <Macros/AlbaMacros.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

IntegrationHistory::IntegrationHistory()
    : m_lastIntegrationPurpose(IntegrationPurpose::NotSet)
    , m_previousIntegrationPurpose(IntegrationPurpose::NotSet)
{}

IntegrationPurpose IntegrationHistory::getLastIntegrationPurpose() const
{
    return m_lastIntegrationPurpose;
}

string IntegrationHistory::getEnumShortString(
        IntegrationPurpose const purpose)
{
    switch(purpose)
    {
    ALBA_MACROS_CASE_ENUM_SHORT_STRING(IntegrationPurpose::NotSet, "NotSet")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(IntegrationPurpose::IntegrationByParts, "IntegrationByParts")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(IntegrationPurpose::Trigonometric, "Trigonometric")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(IntegrationPurpose::Substitution, "Substitution")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(IntegrationPurpose::PartialFraction, "PartialFraction")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(IntegrationPurpose::NoChange, "NoChange")
            default:
        return "default";
    }
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
    m_previousIntegrationPurpose =  IntegrationPurpose::NotSet;
}

void IntegrationHistory::log(
        Term const& , //input,
        IntegrationPurpose const , //purpose,
        Term const& ) //output)
{

}

void IntegrationHistory::performStepsBeforeIntegration(
        IntegrationPurpose const purpose)
{
    m_previousIntegrationPurpose = m_lastIntegrationPurpose;
    setLastIntegrationPurpose(purpose);
}

void IntegrationHistory::performStepsAfterIntegration()
{
    setLastIntegrationPurpose(m_previousIntegrationPurpose);
}


}

}
