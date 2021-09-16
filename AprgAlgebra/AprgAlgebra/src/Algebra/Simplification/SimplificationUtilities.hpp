#pragma once

#include <Algebra/Term/TermTypes/Expression.hpp>

namespace alba
{

namespace algebra
{

namespace Simplification
{

bool simplifyToACommonDenominatorForExpressionAndReturnIfChanged(Expression & expression);
bool tryToAddSubtractTermsOverTermsAndReturnIfChanged(Expression & addSubtractExpression);
void simplifyTermsWithDetailsInExpressionToACommonDenominator(Expression & expression);

}

}

}
