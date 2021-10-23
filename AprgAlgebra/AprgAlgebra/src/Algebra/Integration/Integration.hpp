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

    struct TrigonometryFunctionExponents
    {
        AlbaNumber sinExponent;
        AlbaNumber cosExponent;
        AlbaNumber tanExponent;
        AlbaNumber cscExponent;
        AlbaNumber secExponent;
        AlbaNumber cotExponent;
    };

    struct TrigonometricSubstitutionDetails
    {
        bool isTrigonometricSubstitutionPossible;
        std::string thetaName;
        Term a;
        Term u;
        Term aSquaredAndUSquared;
        Term uEquivalent;
        Term thetaEquivalent;
        Term aSquaredAndUSquaredEquivalent;
        Term theta;
        Term opposite, adjacent, hypotenuse;
    };

    struct Configuration
    {
        bool shouldFixTrigonometricFunctions;        Simplification::SimplificationOfExpression::ConfigurationDetails expressionSimplification;
    };

    using ListOfIntegrationByPartsTerms = std::vector<IntegrationByPartsTerms>;
    using InputTermToTrigonometryFunctionExponentsMap = std::map<Term, TrigonometryFunctionExponents>;
    using Configurations = std::vector<Configuration>;

    Integration(std::string const& nameOfVariableToIntegrate);

    Term integrate(Term const& term) const;
    Term integrate(Constant const& constant) const;
    Term integrate(Variable const& variable) const;    Term integrate(Monomial const& monomial) const;
    Term integrate(Polynomial const& polynomial) const;
    Term integrate(Expression const& expression) const;
    Term integrate(Function const& functionObject) const;

    Term integrateWithPlusC(Term const& term) const;
    Term integrateWithDefiniteValues(Term const& term, AlbaNumber const& lowerValueInInterval, AlbaNumber const& higherValueInInterval) const;

    Monomial integrateConstant(Constant const& constant) const;
    Monomial integrateVariable(Variable const& variable) const;
    Term integrateMonomial(Monomial const& monomial) const;
    Term integratePolynomial(Polynomial const& polynomial) const;
    Term integrateExpression(Expression const& expression) const;
    Term integrateFunction(Function const& functionObject) const;

private:
    //Monomial
    Term integrateMonomialWhenExponentIsNegativeOne(Monomial const& monomial) const;
    Monomial integrateMonomialWhenExponentIsNotNegativeOne(Monomial const& monomial) const;

    //Expression
    Term integrateAsTermOrExpressionIfNeeded(Expression const& expression) const;    void integrateSimplifiedExpressionOnly(Term & result, Expression const& expression, Configuration const& configuration) const;
    void integrateTermsInAdditionOrSubtraction(Term & result, TermsWithDetails const& termsWithDetails) const;
    void integrateTermsInMultiplicationOrDivision(Term & result, TermsWithDetails const& termsWithDetails) const;
    void integrateTermsInRaiseToPower(Term & result, TermsWithDetails const& termsWithDetails) const;
    void integrateTermUsingSubstitutionWithMaxDepth(Term & result, Term const& term, Configuration const& configuration) const;
    void integrateTermUsingSubstitution(Term & result, Term const& term, Configuration const& configuration) const;
    void integrateBySubstitutionAndUsingANewVariable(Term & result, Term const& mainTerm, Term const& termToSubstituteToVariable, Configuration const& configuration) const;
    Term substituteToNewVariable(Term const& mainTerm, Term const& termToSubstituteWithVariable) const;
    Term substituteBackToOldVariable(Term const& mainTerm, std::string const& newVariableName, Term const& termForNewVariable) const;
    void integrateUsingTrigonometricSubstitutionIfPossible(Term & result, Term const& mainTerm, Term const& termToSubstitute, Configuration const& configuration) const;
    void integrateUsingTrigonometricSubstitution(Term & result, Term const& mainTerm, Term const& aSquareAndUSquared, Term const& aSquaredWithSign, Term const& uSquaredWithSign, Configuration const& configuration) const;
    TrigonometricSubstitutionDetails calculateTrigonometricSubstitutionDetails(Term const& a, Term const& u, Term const& aSquaredAndUSquared, bool const isANegative, bool const isUNegative) const;
    Term substituteToTrigonometricFunctions(Term const& mainTerm, TrigonometricSubstitutionDetails const& details) const;
    Term substituteFromTrigonometricFunctionsBackToNormal(Term const& mainTerm, TrigonometricSubstitutionDetails const& details) const;
    void integrateNonChangingAndChangingTermsInMultiplicationOrDivision(Term& result, TermsWithDetails const& termsWithDetails) const;
    void integrateChangingTermsInMultiplicationOrDivision(Term & result, TermsWithDetails const& changingTerms) const;
    void integrateByTryingTwoTermsInMultiplicationOrDivision(Term & result, TermsWithDetails const& termsWithDetailsInMultiplicationOrDivision) const;
    void integrateUsingChainRuleInReverseIfPossible(Term & result, Term const& firstOuterTerm, Term const& firstInnerTerm, Term const& secondTerm) const;
    void findInnerAndOuterTermForChainRule(Term & innerTerm, Term & outerTerm) const;
    Term divideFirstTermAndDerivativeOfSecondTerm(Term const& firstTerm, Term const& secondTerm) const;
    void integrateByProcessingAsPolynomialsOverPolynomials(Term & result, Term const& term) const;    void integrateByTryingIntegrationByParts(Term & result, Term const& term) const;
    void integrateUsingIntegrationByPartsByOneTermAndOne(Term & result, Term const& term) const;
    void integrateUsingIntegrationByPartsByTryingTwoTerms(Term & result, Term const& term) const;
    void integrateUsingIntegrationByPartsByTryingTwoTermsWithDifferentOrder(Term & result, Term const& term, Term const& firstTerm, Term const& secondTerm) const;
    void integrateUsingIntegrationByPartsAndCheckingPreviousValues(Term & result, Term const& term, Term const& u, Term const& dv) const;
    void integrateUsingPreviousIntegrationByPartsTerms(Term & result, ListOfIntegrationByPartsTerms const& listOfIntegrationByPartsTerms, Term const& termToIntegrate) const;
    void integrateUsingIntegrationByParts(Term & result, ListOfIntegrationByPartsTerms & listOfIntegrationByPartsTerms, Term const& term, Term const& u, Term const& dv) const;
    void integrateNonChangingTermRaiseToChangingTerm(Term & result, Term const& base, Term const& exponent) const;
    void integrateChangingTermRaiseToNonChangingTerm(Term & result, Term const& base, Term const& exponent) const;
    void integrateChangingTermRaiseToChangingTerm(Term & result, Term const& firstTerm, Term const& secondTerm) const;

    //Function
    Term integrateFunctionOnly(Function const& functionObject) const;
    void retrieveInputTermsAndTrigonometricExponents(InputTermToTrigonometryFunctionExponentsMap & inputTermToExponents, TermsOverTerms::BaseToExponentMap & remainingTerms, TermsOverTerms::BaseToExponentMap const& termToCheck) const;    void integrateTrigonometricCombinationsIfPossible(Term & result, TermsOverTerms::BaseToExponentMap const& remainingTerms, InputTermToTrigonometryFunctionExponentsMap const& inputTermToExponents) const;
    void integrateUsingKnownTrigonometricCombinations(Term & result, TrigonometryFunctionExponents const& exponents, Term const& functionInputTerm) const;
    void integrateRecognizedFunctionsSquared(Term & result, Term const& base) const;
    void integrateSinRaiseToAnIntegerGreaterThanOne(Term & result, Term const& functionInputTerm, unsigned int const exponent) const;
    void integrateCosRaiseToAnIntegerGreaterThanOne(Term & result, Term const& functionInputTerm, unsigned int const exponent) const;
    void integrateTanRaiseToAnIntegerGreaterThanOne(Term & result, Term const& functionInputTerm, unsigned int const exponent) const;
    void integrateCscRaiseToAnIntegerGreaterThanOne(Term & result, Term const& functionInputTerm, unsigned int const exponent) const;
    void integrateSecRaiseToAnIntegerGreaterThanOne(Term & result, Term const& functionInputTerm, unsigned int const exponent) const;
    void integrateCotRaiseToAnIntegerGreaterThanOne(Term & result, Term const& functionInputTerm, unsigned int const exponent) const;
    void integrateSinAndCosCombinationWithExponentsGreaterThanOne(Term & result, Term const& functionInputTerm, unsigned int const sinExponent, unsigned int const cosExponent) const;
    void integrateCscAndCotCombinationWithExponentsGreaterThanOne(Term & result, Term const& functionInputTerm, unsigned int const cscExponent, unsigned int const cotExponent) const;
    void integrateSecAndTanCombinationWithExponentsGreaterThanOne(Term & result, Term const& functionInputTerm, unsigned int const secExponent, unsigned int const tanExponent) const;

    //Miscellaneous
    void segregateNonChangingAndChangingTerms(TermsWithDetails const& termsToSegregate, TermsWithDetails & nonChangingTerms, TermsWithDetails & changingTerms) const;
    void convertLeftHandSideAndRightHandSideIfLogarithmic(Term & leftHandSide, Term & rightHandSide) const;
    void putReducedSineSquaredToDoubleAngleCosineTerms(Term & outputTerm, Term const& inputTerm, unsigned int const exponent) const;
    void putReducedCosineSquaredToDoubleAngleCosineTerms(Term & outputTerm, Term const& inputTerm, unsigned int const exponent) const;
    void putTangentSquaredToSecantSquaredTerms(Term & outputTerm, Term const& inputTerm, unsigned int const exponent) const;    void putCosecantSquaredToCotangentSquaredTerms(Term & outputTerm, Term const& inputTerm, unsigned int const exponent) const;
    void putSecantSquaredToTangentSquaredTerms(Term & outputTerm, Term const& inputTerm, unsigned int const exponent) const;
    void putCotangentSquaredToCosecantSquaredTerms(Term & outputTerm, Term const& inputTerm, unsigned int const exponent) const;
    TrigonometryFunctionExponents fixTrigonometricExponents(TrigonometryFunctionExponents const& oldExponents) const;
    void setIsIntegrationUsingSubstitutionAllowed(bool const isIntegrationUsingSubstitutionAllowed);
    void setIsIntegrationByPartsAllowed(bool const isIntegrationByPartsAllowed);
    void simplifyForIntegration(Term & term, Configuration const& configuration) const;
    void simplifyAndFixTrigonometricFunctions(Term & term, bool const shouldFixTrigonometricFunctions) const;
    void finalizeTermForIntegration(Term & term) const;
    Configuration getConfigurationWithoutFactors() const;
    Configuration getConfigurationWithFactors() const;
    Configuration getConfigurationWithCommonDenominator() const;
    bool isVariableToIntegrate(std::string const& variableName) const;
    bool isChangingTerm(Term const& term) const;
    bool hasExponentialExpression(Term const& term) const;
    bool wouldDifferentiationYieldToAConstant(Term const& term) const;
    bool areExponentsSame(TrigonometryFunctionExponents const& oldExponents, TrigonometryFunctionExponents const& newExponents) const;
    std::string m_nameOfVariableToIntegrate;
    bool m_isIntegrationUsingSubstitutionAllowed;
    bool m_isIntegrationByPartsAllowed;
};

}
}
