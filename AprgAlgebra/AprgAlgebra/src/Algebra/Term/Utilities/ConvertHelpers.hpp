#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

bool canBeConvertedToMonomial(Term const& term);
bool canBeConvertedToPolynomial(Term const& term);

Term simplifyAndConvertMonomialToSimplestTerm(Monomial const& monomial);
Term simplifyAndConvertPolynomialToSimplestTerm(Polynomial const& polynomial);
Term simplifyAndConvertExpressionToSimplestTerm(Expression const& expression);
Term simplifyAndConvertFunctionToSimplestTerm(Function const& functionAsParameter);
Term convertExpressionToSimplestTerm(Expression const& expression);
Term convertFunctionToSimplestTerm(Function const& functionAsParameter);
Term convertValueTermStringToTerm(std::string const& valueTerm);

}

}
