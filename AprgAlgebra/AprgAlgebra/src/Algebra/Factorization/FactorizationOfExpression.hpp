#pragma once

#include <Algebra/Constructs/TermsRaiseToNumbers.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>

namespace alba {

namespace algebra {

namespace Factorization {

Terms factorizeAnExpression(Expression const& expression);
Terms factorizeAnExpressionWithConfigurationChanged(Expression const& expression);

TermsRaiseToNumbers factorizeToTermsRaiseToNumbers(Expression const& expression);
TermsRaiseToNumbers factorizeToTermsRaiseToNumbersForAdditionAndSubtraction(Expression const& expression);
TermsRaiseToNumbers factorizeToTermsRaiseToNumbersForMultiplicationAndDivision(Expression const& expression);
TermsRaiseToNumbers factorizeToTermsRaiseToNumbersForRaiseToPower(Expression const& expression);

void retrieveConstantAndNonConstantFactors(
    std::vector<TermsRaiseToNumbers>& nonConstantFactorsPerAddends, AlbaNumbers& constantFactors,
    TermsWithDetails const& originalTermsWithDetails);
AlbaNumber getGcfOfConstants(AlbaNumbers const& constantFactorsPerAddends);
void retrieveCommonNonConstantFactors(
    TermsRaiseToNumbers& commonNonConstantFactors,
    std::vector<TermsRaiseToNumbers> const& nonConstantFactorsPerAddends);
TermsRaiseToNumbers getFactorizedItemsForAdditionAndSubtraction(
    Expression const& expression, AlbaNumbers const& constantFactorsPerAddends,
    std::vector<TermsRaiseToNumbers> const& nonConstantFactorsPerAddends, AlbaNumber const& constantGcf,
    TermsRaiseToNumbers const& commonNonConstantFactors);
void putRemainingConstantFactorAsAnInnerMultiplier(
    TermsWithDetails& innerMultipliers, AlbaNumber const& constantFactorOfOriginalAddend,
    AlbaNumber const& constantGcf);
void putRemainingNonConstantFactorsAsInnerMultipliers(
    TermsWithDetails& innerMultipliers, TermsRaiseToNumbers const& nonConstantFactorsOfOriginalAddend,
    TermsRaiseToNumbers const& commonNonConstantFactors);
void putRemainingInnerMultipliersAsOuterAddend(
    TermsWithDetails& outerAddends, TermsWithDetails const& innerMultipliers, TermWithDetails const& originalAddend);
TermsRaiseToNumbers getFactorizedItemsBasedFromCollectedData(
    AlbaNumber const& constantGcf, TermsRaiseToNumbers const& commonNonConstantFactors,
    TermsWithDetails const& outerAddends);

bool dontFactorizeBaseBecauseBaseIsARaiseToPowerExpression(Term const& base);
bool dontFactorizeBecauseThereIsSquareRootOfNegativeNumber(Term const& base, AlbaNumber const& exponent);
}  // namespace Factorization

}  // namespace algebra

}  // namespace alba
