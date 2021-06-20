#pragma once

#include <Equation/Term/Term.hpp>
#include <Equation/Term/TermsWithAssociation.hpp>

namespace alba
{

namespace equation
{

void accumulateAndDoOperationOnTermDetails(
        Term & combinedTerm,
        OperatorLevel const operatorLevel,
        TermsWithAssociation::TermWithDetails const& termWithDetails);
void accumulateTermsForAdditionAndSubtraction(
        Term & combinedTerm,
        TermsWithAssociation::TermsWithDetails const& termsToCombine);
void accumulateTermsForMultiplicationAndDivision(
        Term & combinedTerm,
        TermsWithAssociation::TermsWithDetails const& termsToCombine);
void accumulateTermsForRaiseToPower(
        Term & combinedTerm,
        TermsWithAssociation::TermsWithDetails const& termsToCombine);

}

}
