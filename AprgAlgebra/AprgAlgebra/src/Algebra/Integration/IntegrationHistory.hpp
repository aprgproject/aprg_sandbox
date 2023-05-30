#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>
#include <vector>

namespace alba {

namespace algebra {

enum class IntegrationPurpose {
    NotSet,
    IntegrationByParts,
    Trigonometric,
    TrigonometricSubstitution,
    Substitution,
    PartialFraction,
    NoChange
};

using IntegrationPurposes = std::vector<IntegrationPurpose>;

class IntegrationHistory {
public:
    IntegrationHistory();
    bool didThisIntegrationPurposeAlreadyHappened(IntegrationPurpose const purpose) const;
    int getDepth() const;
    IntegrationPurpose getLastIntegrationPurpose() const;
    std::string getEnumShortString(IntegrationPurpose const purpose) const;

    void performStepsBeforeIntegration(Term const& input, IntegrationPurpose const purpose);
    void performStepsAfterIntegration(Term const& input, IntegrationPurpose const purpose, Term const& output);
    void clear();

private:
    void addIntegrationPurpose(IntegrationPurpose const purpose);
    void logBefore(Term const& input, IntegrationPurpose const purpose);
    void logAfter(Term const& input, IntegrationPurpose const purpose, Term const& output);
    IntegrationPurposes m_recordOfIntegrationPurposes;
};

}  // namespace algebra

}  // namespace alba
