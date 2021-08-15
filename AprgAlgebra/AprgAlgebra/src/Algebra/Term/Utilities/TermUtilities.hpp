#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>
#include <Math/Number/AlbaNumberTypes.hpp>

namespace alba
{

namespace algebra
{

bool isNonEmptyOrNonOperatorType(Term const& term);
bool isNonEmptyOrNonOperatorOrNonExpressionType(Term const& term);

AlbaNumberPairs evaluateAndGetInputOutputPair(
        AlbaNumbers const& numbers,
        std::string const& variableName,        Term const& term);

}

}
