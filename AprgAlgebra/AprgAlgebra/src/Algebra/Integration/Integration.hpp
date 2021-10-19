#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

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
    Term integrateWithDefiniteValues(
            Term const& term,
            AlbaNumber const& lowerValue,
            AlbaNumber const& higherValue) const;

    Term integrateTerm(Term const& term) const;
    Monomial integrateConstant(Constant const& constant) const;    Monomial integrateVariable(Variable const& variable) const;
    Monomial integrateMonomial(Monomial const& monomial) const;
    Polynomial integratePolynomial(Polynomial const& polynomial) const;
    Term integrateExpression(Expression const& expression) const;    Term integrateFunction(Function const& functionObject) const;

private:
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
    Term integrateFunctionOnly(Function const& functionObject) const;
    void integrateTermUsingSubstitution(
            Term & result,
            Term const& term) const;
    void integrateBySubstitutionAndUsingANewVariable(
            Term & result,
            Term const& mainTerm,
            Term const& termToSubstituteToVariable) const;
    Term getTermWithNewVariableSubstitution(
            Term const& mainTerm,
            Term const& termToSubstituteToVariable) const;
    void integrateUsingChainRuleIfPossible(
            Term & result,
            TermsWithDetails const& termsWithDetailsInMultiplicationAndDivision) const;
    void integrateUsingChainRuleIfPossible(
            Term & result,
            Term const& firstOuterTerm,
            Term const& firstInnerTerm,
            Term const& secondTerm) const;
    void findInnerAndOuterTermForChainRule(
            Term & innerTerm,
            Term & outerTerm) const;
    Term divideFirstTermAndDerivativeOfSecondTerm(
            Term const& firstTerm,
            Term const& secondTerm) const;
    void integrateRecognizedFunctionsIfPossible(Term & result, TermsWithDetails const& termsWithDetails) const;
    void simplifyForIntegration(Term& term) const;
    bool isVariableToIntegrate(std::string const& variableName) const;
    bool isVariableToIntegrateNotFoundInTerm(Term const& term) const;
    bool wouldDifferentiationYieldToAConstant(Term const& term) const;
    std::string m_nameOfVariableToIntegrate;
};

}

}
