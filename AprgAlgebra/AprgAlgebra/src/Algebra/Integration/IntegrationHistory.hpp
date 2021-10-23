#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Container/AlbaSingleton.hpp>

#include <string>

namespace alba
{
namespace algebra
{

enum class IntegrationPurpose
{
    NotSet,
    IntegrationByParts,
    Trigonometric,
    Substitution,
    PartialFraction,
    NoChange
};
class IntegrationHistory : public AlbaSingleton<IntegrationHistory>
{
private:
    IntegrationHistory(IntegrationHistory const&) = delete;
    IntegrationHistory & operator = (IntegrationHistory const&) = delete;

public:
    IntegrationHistory();
    IntegrationPurpose getLastIntegrationPurpose() const;
    std::string getEnumShortString(IntegrationPurpose const purpose);

    void setLastIntegrationPurpose(IntegrationPurpose const purpose);
    void clear();

    void log(Term const& input, IntegrationPurpose const purpose, Term const& output);
    void performStepsBeforeIntegration(IntegrationPurpose const purpose);
    void performStepsAfterIntegration();

private:
    IntegrationPurpose m_lastIntegrationPurpose;
    IntegrationPurpose m_previousIntegrationPurpose;
};

}
}
