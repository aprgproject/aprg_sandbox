#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

#include <vector>

namespace alba
{
namespace algebra
{

class Integration
{
public:
    using Configuration=Simplification::SimplificationOfExpression::ConfigurationDetails;
    using Configurations=std::vector<Configuration>;

    Integration(std::string const& nameOfVariableToIntegrate);

    Term integrate(Term const& term) const;    Term integrate(Constant const& constant) const;
    Term integrate(Variable const& variable) const;
    Term integrate(Monomial const& monomial) const;
    Term integrate(Polynomial const& polynomial) const;    Term integrate(Expression const& expression) const;
    Term integrate(Function const& functionObject) const;

    Term integrateWithPlusC(Term const& term) const;
    Term integrateWithDefiniteValues(
            Term const& term,
            AlbaNumber const& lowerValueInInterval,
            AlbaNumber const& higherValueInInterval) const;

    Term integrateTerm(Term const& term) const;
    Monomial integrateConstant(Constant const& constant) const;
    Monomial integrateVariable(Variable const& variable) const;
    Monomial integrateMonomial(Monomial const& monomial) const;
    Polynomial integratePolynomial(Polynomial const& polynomial) const;
    Term integrateExpression(Expression const& expression) const;
    Term integrateFunction(Function const& functionObject) const;

private:
    Term integrateAsTermOrExpressionIfNeeded(
            Expression const& expression) const;
    void integrateSimplifiedExpressionOnly(
            Term & result,
            Expression const& expression,
            Configuration const& configuration) const;
    void integrateTermsInAdditionOrSubtraction(
            Term & result,
            TermsWithDetails const& termsWithDetails) const;
    void integrateTermsInMultiplicationOrDivision(
            Term & result,
            TermsWithDetails const& termsWithDetails) const;
    void integrateTermsInRaiseToPower(
            Term & result,
            TermsWithDetails const& termsWithDetails) const;
    void integrateConstantRaiseToTerm(
            Term & result,
            AlbaNumber const& base,
            Term const& exponent) const;
    void integrateTermRaiseToConstant(
            Term & result,
            Term const& base,
            AlbaNumber const& exponent) const;
    void integrateTermRaiseToTerm(
            Term & result,
            Term const& firstTerm,
            Term const& secondTerm) const;
    Term integrateFunctionOnly(Function const& functionObject) const;
    void integrateTermUsingSubstitutionWithMaxDepth(
            Term & result,
            Term const& term,
            Configuration const& configuration) const;
    void integrateTermUsingSubstitution(
            Term & result,
            Term const& term,
            Configuration const& configuration) const;
    void integrateBySubstitutionAndUsingANewVariable(
            Term & result,
            Term const& mainTerm,
            Term const& termToSubstituteToVariable,
            Configuration const& configuration) const;
    Term getTermWithNewVariableSubstitution(
            Term const& mainTerm,
            Term const& termToSubstituteWithVariable) const;    void integrateUsingChainRuleInReverseIfPossible(
            Term & result,
            TermsWithDetails const& termsWithDetailsInMultiplicationAndDivision) const;
    void integrateUsingChainRuleInReverseIfPossible(            Term & result,
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
    void simplifyForIntegration(Term & term, Configuration const& configuration) const;
    Configuration getConfigurationWithFactors() const;
    Configuration getConfigurationWithCommonDenominator() const;
    bool isVariableToIntegrate(std::string const& variableName) const;
    bool isVariableToIntegrateNotFoundInTerm(Term const& term) const;
    bool wouldDifferentiationYieldToAConstant(Term const& term) const;    std::string m_nameOfVariableToIntegrate;
};

}
}
