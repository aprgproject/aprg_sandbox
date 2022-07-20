#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace booleanAlgebra
{

Term simplifyAndConvertExpressionToSimplestTerm(Expression const& expression);
Term convertExpressionToSimplestTerm(Expression const& expression);

}

}
