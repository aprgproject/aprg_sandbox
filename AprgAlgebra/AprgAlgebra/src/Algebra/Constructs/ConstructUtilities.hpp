#pragma once

#include <Algebra/Constructs/PolynomialOverPolynomial.hpp>
#include <Algebra/Constructs/TermRaiseToANumber.hpp>
#include <Algebra/Constructs/TermsOverTerms.hpp>

namespace alba
{

namespace algebra
{

PolynomialOverPolynomialOptional createPolynomialOverPolynomialFromTermIfPossible(Term const& term);
TermsOverTerms createTermsOverTermsFromTerm(Term const& term);
TermRaiseToANumber createTermRaiseToANumberFromTerm(Term const& term);
TermRaiseToANumber createTermRaiseToANumberFromMonomial(Monomial const& monomial);
TermRaiseToANumber createTermRaiseToANumberFromPolynomial(Polynomial const& polynomial);
TermRaiseToANumber createTermRaiseToANumberFromExpression(Expression const& expression);
void createTermRaiseToANumberFromRaiseToPowerExpression(
        TermRaiseToANumber & result,
        Expression const& expression);
void createTermRaiseToANumberFromMultiplicationAndDivisionExpression(
        TermRaiseToANumber & result,
        Expression const& expression);

}

}
