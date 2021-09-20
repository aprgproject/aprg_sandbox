#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

class Differentiation
{
public:
    Differentiation(std::string const& variableName);

    Term differentiate(Term const& term) const;
    Term differentiate(Constant const& ) const;
    Term differentiate(Variable const& variable) const;
    Term differentiate(Monomial const& monomial) const;
    Term differentiate(Polynomial const& polynomial) const;
    Term differentiate(Expression const& expression) const;
    Term differentiate(Function const& functionObject) const;

    Monomial differentiateMonomial(Monomial const& monomial) const;
    Polynomial differentiatePolynomial(Polynomial const& polynomial) const;

    Term differentiateTwoMultipliedTerms(Term const& term1, Term const& term2) const;
    Term differentiateTwoDividedTerms(Term const& numerator, Term const& denominator) const;

    Term differentiateExpression(Expression const& expression) const;
    Term differentiateFunction(Function const& functionObject) const;

private:
    Term differentiateTermsInAdditionOrSubtraction(
            TermsWithDetails const& termsWithDetails) const;
    Term differentiateTermsInMultiplicationOrDivision(
            TermsWithDetails const& termsWithDetails) const;
    Term differentiateFunctionOnly(Function const& functionObject) const;
    std::string m_variableName;
};
}

}