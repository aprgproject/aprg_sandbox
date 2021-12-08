#pragma once

#include <Algebra/Constructs/PolynomialOverPolynomial.hpp>
#include <Algebra/Constructs/TermsRaiseToNumbers.hpp>
#include <Algebra/Integration/IntegrationHistory.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>
#include <Math/Matrix/AlbaMatrix.hpp>
#include <Math/Number/AlbaNumberTypes.hpp>

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
        bool shouldFixTrigonometricFunctions;
        Simplification::SimplificationOfExpression::ConfigurationDetails expressionSimplification;
    };

    using ListOfIntegrationByPartsTerms = std::vector<IntegrationByPartsTerms>;
    using InputTermToTrigonometryFunctionExponentsMap = std::map<Term, TrigonometryFunctionExponents>;
    using Configurations = std::vector<Configuration>;

    Integration(std::string const& nameOfVariableToIntegrate);

    bool isConvergent(Term const& term, AlbaNumber const& lowerEnd, AlbaNumber const& higherEnd);

    Term integrate(Term const& term) const;
    Term integrate(Constant const& constant) const;
    Term integrate(Variable const& variable) const;
    Term integrate(Monomial const& monomial) const;
    Term integrate(Polynomial const& polynomial) const;
    Term integrate(Expression const& expression) const;
    Term integrate(Function const& functionObject) const;

    Term integrateWithPlusC(Term const& term) const;
    Term integrateAtDefiniteValues(Term const& term, AlbaNumber const& lowerEnd, AlbaNumber const& higherEnd) const;
    Term integrateAtDefiniteTerms(Term const& term, Term const& lowerEnd, Term const& higherEnd) const;

    Monomial integrateConstant(Constant const& constant) const;
    Monomial integrateVariable(Variable const& variable) const;
    Term integrateMonomial(Monomial const& monomial) const;
    Term integratePolynomial(Polynomial const& polynomial) const;
    Term integrateExpression(Expression const& expression) const;
    Term integrateFunction(Function const& functionObject) const;

private:
    //Internal integration
    Term integrateIntenally(Term const& term) const;
    Term integrateInternallyWithPurpose(Term const& term, IntegrationPurpose const purpose) const;

    //For Monomial
    Term integrateMonomialWhenExponentIsNegativeOne(Monomial const& monomial) const;
    Monomial integrateMonomialWhenExponentIsNotNegativeOne(Monomial const& monomial) const;

    //For Expression
    Term integrateAsTermOrExpressionIfNeeded(Expression const& expression) const;
    void integrateSimplifiedExpressionOnly(Term & result, Expression const& expression, Configuration const& configuration) const;
    void integrateTermsInAdditionOrSubtraction(Term & result, Expression const& expression) const;
    void integrateTermsInMultiplicationOrDivision(Term & result, Expression const& expression) const;
    void integrateTermsInRaiseToPower(Term & result, Expression const& expression) const;

    //For Function
    Term integrateFunctionInternally(Function const& functionObject) const;
    void integrateFunctionOnly(Term & result, Function const& functionObject) const;
    void integrateRecognizedFunctionsSquared(Term & result, Term const& functionTerm) const;

    // Changing and non changing
    void integrateNonChangingAndChangingTermsInMultiplicationOrDivision(Term& result, TermsWithDetails const& termsWithDetails) const;
    void integrateChangingTermsInMultiplicationOrDivision(Term & result, TermsWithDetails const& changingTerms) const;
    void integrateNonChangingTermRaiseToChangingTerm(Term & result, Term const& base, Term const& exponent) const;
    void integrateChangingTermRaiseToNonChangingTerm(Term & result, Term const& base, Term const& exponent) const;
    void integrateChangingTermRaiseToChangingTerm(Term & result, Term const& firstTerm, Term const& secondTerm) const;
    void segregateNonChangingAndChangingTerms(TermsWithDetails const& termsToSegregate, TermsWithDetails & nonChangingTerms, TermsWithDetails & changingTerms) const;

    //Substitution
    void integrateTermUsingSubstitutionWithMaxDepth(Term & result, Term const& term, Configuration const& configuration) const;
    void integrateTermUsingSubstitution(Term & result, Term const& term, Configuration const& configuration) const;
    void integrateBySubstitutionAndUsingANewVariable(Term & result, Term const& mainTerm, Term const& termForNewVariable, Configuration const& configuration) const;
    Term substituteToNewVariable(Term const& mainTerm, Term const& termForNewVariable) const;
    Term substituteBackToOldVariable(Term const& mainTerm, std::string const& newVariableName, Term const& termForNewVariable) const;

    //Trignometric Substitution
    void integrateTermUsingTrigonometricSubstitution(Term & result, Term const& term) const;
    void integrateUsingTrigonometricSubstitutionByFindingTwoTerms(Term & result, Term const& mainTerm, Term const& termToSubstitute) const;
    void integrateUsingTrigonometricSubstitutionWithDeterminedTerms(Term & result, Term const& mainTerm, Term const& aSquaredAndUSquared, Term const& aSquaredWithSign, Term const& uSquaredWithSign) const;
    TrigonometricSubstitutionDetails calculateTrigonometricSubstitutionDetails(Term const& a, Term const& u, Term const& aSquaredAndUSquared, bool const isANegative, bool const isUNegative) const;
    Term substituteToTrigonometricFunctions(Term const& mainTerm, TrigonometricSubstitutionDetails const& details) const;
    Term substituteFromTrigonometricFunctionsBackToNormal(Term const& mainTerm, TrigonometricSubstitutionDetails const& details) const;

    //Reverse chain rule
    void integrateInMultiplicationOrDivisionByTryingReverseChainRule(Term & result, TermsWithDetails const& termsWithDetailsInMultiplicationOrDivision) const;
    void integrateUsingReverseChainRule(Term & result, Term const& firstOuterTerm, Term const& firstInnerTerm, Term const& secondTerm) const;
    void findInnerAndOuterTermForChainRule(Term & innerTerm, Term & outerTerm) const;
    Term divideFirstTermAndDerivativeOfSecondTerm(Term const& firstTerm, Term const& secondTerm) const;

    //Polynomial over polynomial
    void integrateAsPolynomialOverPolynomialIfPossible(Term & result, Term const& term, bool const canProceedToPartialPolynomialFractions) const;
    void integrateAsPolynomialOverPolynomial(Term & result, PolynomialOverPolynomial const& polynomialOverPolynomial, std::string const& variableName, bool const canProceedToPartialPolynomialFractions) const;

    //Partial Fraction
    void integrateUsingPartialFractionPolynomials(Term & result, std::string const& variableName, Polynomial const& numerator, Polynomial const& denominator) const;
    void retrievePartialFractions(Polynomials & partialNumerators, Polynomials & partialDenominators, std::string const& originalVariableName, TermsRaiseToNumbers const& factorsWithExponents) const;
    Polynomial getTotalNumeratorWithNewVariables(Polynomial const& originalDenominator, Polynomials const& partialNumerators, Polynomials const& partialDenominators) const;
    VariableNamesSet getNamesOfNewVariablesForPartialFraction(std::string const& originalVariableName, Polynomial const& numeratorWithNewVariables) const;
    AlbaNumbersSet getExponentsForPartialFraction(std::string const& originalVariableName, Polynomial const& numeratorWithNewVariables) const;
    void fillInMatrixForPartialFractions(AlbaMatrix<AlbaNumber> & matrixWithNewVariables, std::string const& originalVariableName, VariableNamesSet const& newVariableNames, AlbaNumbersSet const& exponents, Polynomial const& originalNumerator, Polynomial const& numeratorWithNewVariables) const;
    void fillInMatrixForPartialFractionsWithVariableValues(AlbaMatrix<AlbaNumber> & matrixWithNewVariables, std::string const& originalVariableName, VariableNamesSet const& newVariableNames, AlbaNumbersSet const& exponents, Polynomial const& numeratorWithNewVariables) const;
    void fillInMatrixForPartialFractionsWithOutputValues(AlbaMatrix<AlbaNumber> & matrixWithNewVariables, std::string const& originalVariableName, VariableNamesSet const& newVariableNames, AlbaNumbersSet const& exponents, Polynomial const& originalNumerator) const;
    void integratePartialFractionsBasedOnSolvedMatrix(Term & result, AlbaMatrix<AlbaNumber> const& solvedMatrix, VariableNamesSet const& newVariableNames, Polynomials const& partialNumerators, Polynomials const& partialDenominators) const;
    Polynomial getPartialNumeratorForPartialFractions(unsigned int const degree, std::string const& variableName) const;
    std::string getNewVariableNameForPartialFractions() const;

    // Integration by parts
    void integrateByTryingIntegrationByParts(Term & result, Term const& term) const;
    void integrateUsingIntegrationByPartsByOneTermAndOne(Term & result, Term const& term) const;
    void integrateUsingIntegrationByPartsByTryingTwoTerms(Term & result, Term const& term) const;
    void integrateUsingIntegrationByPartsByTryingTwoTermsWithDifferentOrder(Term & result, Term const& term, Term const& firstTerm, Term const& secondTerm) const;
    void integrateUsingIntegrationByPartsAndCheckingPreviousValues(Term & result, Term const& term, Term const& u, Term const& dv) const;
    void integrateUsingPreviousIntegrationByPartsTerms(Term & result, ListOfIntegrationByPartsTerms const& listOfIntegrationByPartsTerms, Term const& termToIntegrate) const;
    void integrateUsingIntegrationByParts(Term & result, ListOfIntegrationByPartsTerms & listOfIntegrationByPartsTerms, Term const& term, Term const& u, Term const& dv) const;

    //Trigonometry
    void retrieveInputTermsAndTrigonometricExponents(InputTermToTrigonometryFunctionExponentsMap & inputTermToExponents, TermsRaiseToNumbers & remainingTerms, TermsRaiseToNumbers const& termsWithExponentsToCheck) const;
    void integrateTrigonometricCombinationsIfPossible(Term & result, TermsRaiseToNumbers const& remainingTerms, InputTermToTrigonometryFunctionExponentsMap const& inputTermToExponents) const;
    void integrateUsingKnownTrigonometricCombinations(Term & result, TrigonometryFunctionExponents const& exponents, Term const& functionInputTerm) const;
    void integrateSinRaiseToAnIntegerGreaterThanOne(Term & result, Term const& functionInputTerm, unsigned int const exponent) const;
    void integrateCosRaiseToAnIntegerGreaterThanOne(Term & result, Term const& functionInputTerm, unsigned int const exponent) const;
    void integrateTanRaiseToAnIntegerGreaterThanOne(Term & result, Term const& functionInputTerm, unsigned int const exponent) const;
    void integrateCscRaiseToAnIntegerGreaterThanOne(Term & result, Term const& functionInputTerm, unsigned int const exponent) const;
    void integrateSecRaiseToAnIntegerGreaterThanOne(Term & result, Term const& functionInputTerm, unsigned int const exponent) const;
    void integrateCotRaiseToAnIntegerGreaterThanOne(Term & result, Term const& functionInputTerm, unsigned int const exponent) const;
    void integrateSinAndCosCombinationWithExponentsGreaterThanOne(Term & result, Term const& functionInputTerm, unsigned int const sinExponent, unsigned int const cosExponent) const;
    void integrateCscAndCotCombinationWithExponentsGreaterThanOne(Term & result, Term const& functionInputTerm, unsigned int const cscExponent, unsigned int const cotExponent) const;
    void integrateSecAndTanCombinationWithExponentsGreaterThanOne(Term & result, Term const& functionInputTerm, unsigned int const secExponent, unsigned int const tanExponent) const;
    TrigonometryFunctionExponents getTrigonometricExponentsSuitableForIntegration(TrigonometryFunctionExponents const& oldExponents) const;
    void putReducedSineSquaredToDoubleAngleCosineTerms(Term & outputTerm, Term const& inputTerm, unsigned int const exponent) const;
    void putReducedCosineSquaredToDoubleAngleCosineTerms(Term & outputTerm, Term const& inputTerm, unsigned int const exponent) const;
    void putTangentSquaredToSecantSquaredTerms(Term & outputTerm, Term const& inputTerm, unsigned int const exponent) const;
    void putCosecantSquaredToCotangentSquaredTerms(Term & outputTerm, Term const& inputTerm, unsigned int const exponent) const;
    void putSecantSquaredToTangentSquaredTerms(Term & outputTerm, Term const& inputTerm, unsigned int const exponent) const;
    void putCotangentSquaredToCosecantSquaredTerms(Term & outputTerm, Term const& inputTerm, unsigned int const exponent) const;

    //Simplify
    void simplifyForIntegration(Term & term, Configuration const& configuration) const;
    void simplifyAndFixTrigonometricFunctions(Term & term, bool const shouldFixTrigonometricFunctions) const;
    void fixTrigonometricFunctionsBasedFromExponents(Term& term, InputTermToTrigonometryFunctionExponentsMap const& trigFunctionsInputTermToExponents, TermsRaiseToNumbers const& remainingTermsWithExponents) const;
    void putTrigonometricFunctionsWithExponents(TermsRaiseToNumbers & newTerms, Term const& inputTerm, TrigonometryFunctionExponents const& exponents) const;

    //Integration configurations
    Configuration getConfigurationWithFactors() const;
    Configuration getConfigurationWithCommonDenominator() const;
    Configuration getConfigurationWithoutFactors() const;
    Configuration getConfigurationWithCombiningRadicals() const;

    //Finalize steps
    void finalizeTermForIntegration(Term & term) const;

    //Miscellaneous
    bool isVariableToIntegrate(std::string const& variableName) const;
    bool isChangingTerm(Term const& term) const;
    bool hasNonChangingTermRaiseToChangingTerm(Term const& term) const;
    bool wouldDifferentiationYieldToAConstant(Term const& term) const;
    bool areExponentsSame(TrigonometryFunctionExponents const& exponents1, TrigonometryFunctionExponents const& exponents2) const;
    bool isIntegrationUsingSubstitutionAllowed(Term const& term) const;
    bool isIntegrationByPartsAllowed(Term const& term) const;
    bool isIntegrationByPartialFractionAllowed() const;
    std::string m_nameOfVariableToIntegrate;
    IntegrationHistory & m_history;
};

}

}
