#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

class IntegrationForFiniteCalculus
{
public:
    IntegrationForFiniteCalculus(std::string const& nameOfVariableToIntegrate);

    Term integrate(Term const& term) const;
    Term integrate(Constant const& constant) const;
    Term integrate(Variable const& variable) const;
    Term integrate(Monomial const& monomial) const;
    Term integrate(Polynomial const& polynomial) const;
    Term integrate(Expression const& expression) const;
    Term integrate(Function const& functionObject) const;

    Term integrateWithPlusC(Term const& term) const;
    Term integrateWithDefiniteValues(
            Term const& term,
            AlbaNumber const& lowerValue,
            AlbaNumber const& higherValue) const;

    Term integrateTerm(Term const& term) const;
    Monomial integrateConstant(Constant const& constant) const;
    Polynomial integrateVariable(Variable const& variable) const;
    Term integrateMonomial(Monomial const& monomial) const;
    Term integratePolynomial(Polynomial const& polynomial) const;
    Term integrateExpression(Expression const& expression) const;
    Term integrateFunction(Function const& functionObject) const;

private:
    Monomial integrateMonomialInFallingPower(
            Monomial const& monomial) const;
    Polynomial integratePolynomialInFallingPower(
            Polynomial const& polynomial) const;
    Polynomial convertMonomialWithPositiveExponentsFromRegularPowerToFallingPower(
            Monomial const& monomial) const;
    Polynomial convertMonomialWithPositiveExponentsFromFallingPowerToRegularPower(
            Monomial const& monomial) const;
    Polynomial convertPolynomialWithPositiveExponentsFromRegularPowerToFallingPower(
            Polynomial const& polynomial) const;
    Polynomial convertPolynomialWithPositiveExponentsFromFallingPowerToRegularPower(
            Polynomial const& polynomial) const;
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
            AlbaNumber const& base,
            Term const& exponent) const;
    Term integrateTermRaiseToConstant(
            Term const& base,
            AlbaNumber const& exponent) const;
    Term integrateTermRaiseToTerm(
            Term const& firstTerm,
            Term const& secondTerm) const;
    bool isVariableToIntegrate(std::string const& variableName) const;
    std::string m_nameOfVariableToIntegrate;
};

}

}
