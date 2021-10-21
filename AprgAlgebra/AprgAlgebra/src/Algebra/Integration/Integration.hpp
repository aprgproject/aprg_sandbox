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
    struct IntegrationByPartsTerms
    {
        Term uTimesDvToIntegrate;
        Term uTimesV;
        Term vTimesDuToIntegrate;
    };
    using ListOfIntegrationByPartsTerms = std::vector<IntegrationByPartsTerms>;
    using Configuration = Simplification::SimplificationOfExpression::ConfigurationDetails;
    using Configurations = std::vector<Configuration>;

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
            AlbaNumber const& lowerValueInInterval,
            AlbaNumber const& higherValueInInterval) const;

    Monomial integrateConstant(Constant const& constant) const;
    Monomial integrateVariable(Variable const& variable) const;
    Term integrateMonomial(Monomial const& monomial) const;
    Term integratePolynomial(Polynomial const& polynomial) const;
    Term integrateExpression(Expression const& expression) const;
    Term integrateFunction(Function const& functionObject) const;

private:
    //Monomial
    Term integrateMonomialWhenExponentIsNegativeOne(
            Monomial const& monomial) const;
    Monomial integrateMonomialWhenExponentIsNotNegativeOne(
            Monomial const& monomial) const;

    //Function
    Term integrateFunctionOnly(
            Function const& functionObject) const;
    void integrateRecognizedFunctionsSquared(
            Term & result,
            Term const& base) const;
    void integrateSinRaiseToAConstant(
            Term & result,
            Term const& base,
            AlbaNumber const& exponent) const;
    void integrateCosRaiseToAConstant(
            Term & result,
            Term const& base,
            AlbaNumber const& exponent) const;

    //Expression
    Term integrateAsTermOrExpressionIfNeeded(            Expression const& expression) const;
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
    void integrateNonChangingTermRaiseToChangingTerm(
            Term & result,
            Term const& base,
            Term const& exponent) const;
    void integrateChangingTermRaiseToNonChangingTerm(
            Term & result,
            Term const& base,
            Term const& exponent) const;
    void integrateChangingTermRaiseToChangingTerm(
            Term & result,
            Term const& firstTerm,
            Term const& secondTerm) const;    void integrateTermUsingSubstitutionWithMaxDepth(
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
            Term const& termToSubstituteWithVariable) const;
    void integrateNonChangingAndChangingTermsInMultiplicationOrDivision(
            Term& result,
            TermsWithDetails const& termsWithDetails) const;
    void integrateByTryingTwoTermsInMultiplicationAndDivision(
            Term & result,
            TermsWithDetails const& termsWithDetailsInMultiplicationAndDivision) const;    void integrateUsingChainRuleInReverseIfPossible(
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
    void integrateByProcessingAsPolynomialsOverPolynomials(
            Term & result,
            Term const& term) const;
    void integrateUsingIntegrationByParts(
            Term & result,
            Term const& term) const;
    void integrateUsingIntegrationByPartsByTermAndOne(
            Term & result,
            Term const& term) const;
    void integrateUsingIntegrationByPartsByTryingTwoTerms(
            Term & result,
            Term const& term) const;
    void integrateUsingIntegrationByPartsByTryingTwoTermsWithDifferentOrder(
            Term & result,
            Term const& term,
            Term const& firstTerm,
            Term const& secondTerm) const;
    void integrateUsingIntegrationByParts(
            Term & result,
            Term const& term,
            Term const& f,
            Term const& gPrime) const;
    void integrateUsingPreviousIntegrationByPartsTerms(
            Term & result,
            ListOfIntegrationByPartsTerms const& listOfIntegrationByPartsTerms,
            Term const& termToIntegrate) const;
    void segregateNonChangingAndChangingTerms(
            TermsWithDetails const& termsToSegregate,
            TermsWithDetails & nonChangingTerms,
            TermsWithDetails & changingTerms) const;
    void setIsIntegrationUsingSubstitutionAllowed(bool const isIntegrationUsingSubstitutionAllowed);
    void setIsIntegrationByPartsAllowed(bool const isIntegrationByPartsAllowed);
    void simplifyForIntegration(Term & term, Configuration const& configuration) const;    void finalizeTermForIntegration(Term & term) const;
    Configuration getConfigurationWithFactors() const;
    Configuration getConfigurationWithCommonDenominator() const;
    bool isVariableToIntegrate(std::string const& variableName) const;
    bool isChangingTerm(Term const& term) const;
    bool wouldDifferentiationYieldToAConstant(Term const& term) const;
    std::string m_nameOfVariableToIntegrate;
    bool m_isIntegrationUsingSubstitutionAllowed;    bool m_isIntegrationByPartsAllowed;
};

}

}
