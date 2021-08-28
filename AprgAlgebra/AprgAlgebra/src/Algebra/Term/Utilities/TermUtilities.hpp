#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/Number/AlbaNumberTypes.hpp>

namespace alba
{

namespace algebra
{

bool isNegatedTermSimpler(Term const& term, Term const& negatedTerm);
bool isNonEmptyOrNonOperatorType(Term const& term);
bool isNonEmptyOrNonOperatorOrNonExpressionType(Term const& term);
bool isRadicalTerm(Term const& term);

AlbaNumberPairs evaluateAndGetInputOutputPair(
        AlbaNumbers const& numbers,
        std::string const& variableName,
        Term const& term);

}

}
