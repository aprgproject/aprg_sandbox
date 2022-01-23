#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Container/AlbaSingleton.hpp>

#include <string>
#include <vector>

namespace alba
{

namespace algebra
{

enum class IntegrationPurpose
{
    NotSet,
    IntegrationByParts,
    Trigonometric,
    TrigonometricSubstitution,
    Substitution,
    PartialFraction,
    NoChange};

using IntegrationPurposes = std::vector<IntegrationPurpose>;
class IntegrationHistory : public AlbaSingleton<IntegrationHistory>
{
private:
    IntegrationHistory(IntegrationHistory const&) = delete;
    IntegrationHistory & operator = (IntegrationHistory const&) = delete;

public:
    IntegrationHistory();
    bool didThisIntegrationPurposeAlreadyHappened(IntegrationPurpose const purpose) const;
    unsigned int getDepth() const;
    IntegrationPurpose getLastIntegrationPurpose() const;
    std::string getEnumShortString(IntegrationPurpose const purpose) const;

    void addIntegrationPurpose(IntegrationPurpose const purpose);
    void clear();
    void logBefore(Term const& input, IntegrationPurpose const purpose);
    void logAfter(Term const& input, IntegrationPurpose const purpose, Term const& output);
    void performStepsBeforeIntegration(IntegrationPurpose const purpose);    void performStepsAfterIntegration();

private:
    IntegrationPurposes m_recordOfIntegrationPurposes;
};

}

}
