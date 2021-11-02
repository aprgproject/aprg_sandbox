#include "IntegrationHistory.hpp"

#include <Macros/AlbaMacros.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

IntegrationHistory::IntegrationHistory()
{}

unsigned int IntegrationHistory::getDepth() const
{
    return m_recordOfIntegrationPurposes.size();
}

IntegrationPurpose IntegrationHistory::getLastIntegrationPurpose() const
{
    IntegrationPurpose result(IntegrationPurpose::NotSet);
    if(!m_recordOfIntegrationPurposes.empty())
    {
        result = m_recordOfIntegrationPurposes.back();
    }
    return result;
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

void IntegrationHistory::addIntegrationPurpose(
        IntegrationPurpose const purpose)
{
    if(IntegrationPurpose::NoChange != purpose)
    {
        m_recordOfIntegrationPurposes.emplace_back(purpose);
    }
}

void IntegrationHistory::clear()
{
    m_recordOfIntegrationPurposes.clear();
}

void IntegrationHistory::logBefore(
        Term const& , //input,
        IntegrationPurpose const ) //purpose)
{}

void IntegrationHistory::logAfter(
        Term const& , //input,
        IntegrationPurpose const , //purpose,
        Term const& ) //output)
{}

void IntegrationHistory::performStepsBeforeIntegration(
        IntegrationPurpose const purpose)
{
    addIntegrationPurpose(purpose);
}

void IntegrationHistory::performStepsAfterIntegration()
{
    if(!m_recordOfIntegrationPurposes.empty())
    {
        m_recordOfIntegrationPurposes.pop_back();
    }
}


}

}
