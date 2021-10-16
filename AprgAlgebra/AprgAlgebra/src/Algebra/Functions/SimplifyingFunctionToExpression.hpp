#pragma once

#include <Algebra/Term/TermTypes/Expression.hpp>
#include <Algebra/Term/TermTypes/Function.hpp>

namespace alba
{

namespace algebra
{

Expression simplifyTrigometricFunctionToExpressionIfPossible(Function const& functionAsParameter);

}

}
