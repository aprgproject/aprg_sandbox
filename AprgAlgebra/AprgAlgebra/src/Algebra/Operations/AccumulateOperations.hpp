#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermsWithAssociation.hpp>

namespace alba
{

namespace algebra
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
