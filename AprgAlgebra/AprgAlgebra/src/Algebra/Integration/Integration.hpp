#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

namespace alba
{

namespace algebra
{

class Integration
{
public:
    Integration(std::string const& nameOfVariableToIntegrate);

    Term integrate(Term const& term) const;
    Term integrate(Constant const& constant) const;
    Term integrate(Variable const& variable) const;
    Term integrate(Monomial const& monomial) const;
    Term integrate(Polynomial const& polynomial) const;
    Term integrate(Expression const& expression) const;
    Term integrate(Function const& functionObject) const;

    Term integrateWithPlusC(Term const& term) const;

    Term integrateTerm(Term const& term) const;
    Monomial integrateConstant(Constant const& constant) const;
    Monomial integrateVariable(Variable const& variable) const;
    Monomial integrateMonomial(Monomial const& monomial) const;
    Polynomial integratePolynomial(Polynomial const& polynomial) const;
    Term integrateExpression(Expression const& expression) const;
    Term integrateFunction(Function const& functionObject) const;

private:
    bool isVariableToIntegrate(std::string const& variableName) const;
    Term integrateUsingChainRule(
            Term const& outerTerm,
            Term const& innerTerm) const;
    Term integrateAsTermOrExpressionIfNeeded(
            Expression const& expression) const;
    Term integrateSimplifiedExpressionOnly(
            Expression const& expression) const;
    Term integrateTermsInAdditionOrSubtraction(
            TermsWithDetails const& termsWithDetails) const;
    Term integrateTermsInMultiplicationOrDivision(
            TermsWithDetails const& termsWithDetails) const;
    Term integrateTermsInRaiseToPower(
            TermsWithDetails const& termsWithDetails) const;
    Term integrateConstantRaiseToTerm(
            AlbaNumber const& number,
            Term const& term) const;
    Term integrateTermRaiseToConstant(
            Term const& term,
            AlbaNumber const& number) const;
    Term integrateTermRaiseToTerm(
            Term const& firstTerm,
            Term const& secondTerm) const;
    Term integrateFunctionOnly(Function const& functionObject) const;
    AlbaNumber getDegreeForVariableToIntegrate(Term const& term) const;
    void simplifyForIntegration(Term& term) const;
    std::string m_nameOfVariableToIntegrate;
};
}

}