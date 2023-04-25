#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba {

namespace algebra {

class IntegrationForFiniteCalculus {
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
    Term integrateAtDefiniteValues(Term const& term, AlbaNumber const& lowerEnd, AlbaNumber const& higherEnd) const;

    Term integrateTerm(Term const& term) const;
    Monomial integrateConstant(Constant const& constant) const;
    Polynomial integrateVariable(Variable const& variable) const;
    Term integrateMonomial(Monomial const& monomial) const;
    Term integratePolynomial(Polynomial const& polynomial) const;
    Term integrateExpression(Expression const& expression) const;
    Term integrateFunction(Function const& functionObject) const;

private:
    // For Monomial and Polynomial
    Monomial integrateMonomialInFallingPower(Monomial const& monomial) const;
    Polynomial integratePolynomialInFallingPower(Polynomial const& polynomial) const;
    Polynomial convertMonomialWithPositiveExponentsFromRegularPowerToFallingPower(Monomial const& monomial) const;
    Polynomial convertMonomialWithPositiveExponentsFromFallingPowerToRegularPower(Monomial const& monomial) const;
    Polynomial convertPolynomialWithPositiveExponentsFromRegularPowerToFallingPower(Polynomial const& polynomial) const;
    Polynomial convertPolynomialWithPositiveExponentsFromFallingPowerToRegularPower(Polynomial const& polynomial) const;

    // For Expression
    Term integrateAsTermOrExpressionIfNeeded(Expression const& expression) const;
    Term integrateSimplifiedExpressionOnly(Expression const& expression) const;
    Term integrateTermsInAdditionOrSubtraction(Expression const& expression) const;
    Term integrateTermsInMultiplicationOrDivision(Expression const& expression) const;
    Term integrateTermsInRaiseToPower(Expression const& expression) const;
    Term integrateNonChangingTermRaiseToChangingTerm(Term const& base, Term const& exponent) const;
    Term integrateChangingTermRaiseToNonChangingTerm(Term const& base, Term const& exponent) const;
    Term integrateChangingTermRaiseToChangingTerm(Term const& firstTerm, Term const& secondTerm) const;

    // For changing and non changing
    void integrateNonChangingAndChangingTermsInMultiplicationOrDivision(
        Term& result, TermsWithDetails const& termsWithDetails) const;
    void integrateChangingTermsInMultiplicationOrDivision(Term& result, TermsWithDetails const&) const;
    void segregateNonChangingAndChangingTerms(
        TermsWithDetails const& termsToSegregate, TermsWithDetails& nonChangingTerms,
        TermsWithDetails& changingTerms) const;

    bool isVariableToIntegrate(std::string const& variableName) const;
    bool isChangingTerm(Term const& term) const;
    std::string m_nameOfVariableToIntegrate;
};

}  // namespace algebra

}  // namespace alba
