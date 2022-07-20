#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace booleanAlgebra
{

void accumulateAndDoOperationOnWrappedTerm(
        Term & combinedTerm,
        OperatorType const operatorType,
        WrappedTerm const& wrappedTerm);
void accumulateTermsWithAndOperation(
        Term & combinedTerm,
        WrappedTerms const& termsToCombine);
void accumulateTermsWithOrOperation(
        Term & combinedTerm,
        WrappedTerms const& termsToCombine);

}

}
