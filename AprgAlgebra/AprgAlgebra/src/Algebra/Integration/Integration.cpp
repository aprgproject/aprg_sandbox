#include "Integration.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Constructs/TermRaiseToANumber.hpp>
#include <Algebra/Constructs/TermRaiseToTerms.hpp>
#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Functions/FunctionUtilities.hpp>
#include <Algebra/KnownExpressionsAndEquations/TrigonometricEquations.hpp>
#include <Algebra/Integration/IntegrationUtilities.hpp>
#include <Algebra/Isolation/IsolationOfOneVariableOnEqualityEquation.hpp>
#include <Algebra/Retrieval/SubTermsRetriever.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Substitution/SubstitutionOfTermsToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/RetrieveHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <algorithm>


using namespace alba::algebra::Functions;
using namespace alba::algebra::Simplification;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{
namespace algebra
{

Integration::Integration(
        string const& nameOfVariableToIntegrate)
    : m_nameOfVariableToIntegrate(nameOfVariableToIntegrate)
    , m_isIntegrationUsingSubstitutionAllowed(true)
    , m_isIntegrationByPartsAllowed(true)
{}

Term Integration::integrate(
        Term const& term) const
{
    Term result;
    if(term.isConstant())
    {
        result = integrate(term.getConstantConstReference());
    }
    else if(term.isVariable())
    {
        result = integrate(term.getVariableConstReference());
    }
    else if(term.isMonomial())
    {
        result = integrate(term.getMonomialConstReference());
    }
    else if(term.isPolynomial())
    {
        result = integrate(term.getPolynomialConstReference());
    }
    else if(term.isExpression())
    {
        result = integrate(term.getExpressionConstReference());
    }
    else if(term.isFunction())
    {
        result = integrate(term.getFunctionConstReference());
    }
    return result;
}

Term Integration::integrate(
        Constant const& constant) const
{
    return Term(integrateConstant(constant));
}

Term Integration::integrate(
        Variable const& variable) const
{
    Term result(integrateVariable(variable));
    result.simplify();
    return result;
}

Term Integration::integrate(
        Monomial const& monomial) const
{
    Term result(integrateMonomial(monomial));
    result.simplify();
    return result;
}

Term Integration::integrate(
        Polynomial const& polynomial) const
{
    Term result(integratePolynomial(polynomial));
    result.simplify();
    return result;
}

Term Integration::integrate(
        Expression const& expression) const
{
    return integrateExpression(expression);
}

Term Integration::integrate(
        Function const& functionObject) const
{
    return integrateFunction(functionObject);
}

Term Integration::integrateWithPlusC(
        Term const& term) const
{
    Term result(createExpressionIfPossible({integrate(term), Term("+"), Term(C)}));
    finalizeTermForIntegration(result);
    return result;
}

Term Integration::integrateWithDefiniteValues(
        Term const& term,
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval) const
{
    return substituteValuesAndGetDifference(
                integrate(term),
                m_nameOfVariableToIntegrate,
                lowerValueInInterval,
                higherValueInInterval);
}

Monomial Integration::integrateConstant(
        Constant const& constant) const
{
    return Monomial(constant.getNumberConstReference(), {{m_nameOfVariableToIntegrate, 1}});
}

Monomial Integration::integrateVariable(
        Variable const& variable) const
{
    Monomial result;
    string const& nameOfVariable(variable.getVariableName());
    if(isVariableToIntegrate(nameOfVariable))
    {
        result = Monomial(AlbaNumber::createFraction(1, 2), {{variable.getVariableName(), 2}});
    }
    else
    {
        result = Monomial(1, {{variable.getVariableName(), 1}, {m_nameOfVariableToIntegrate, 1}});
    }
    return result;
}

Term Integration::integrateMonomial(
        Monomial const& monomial) const
{
    Term result;
    AlbaNumber exponentForVariable = monomial.getExponentForVariable(m_nameOfVariableToIntegrate);
    if(exponentForVariable == -1)
    {
        result = Term(integrateMonomialWhenExponentIsNegativeOne(monomial));
    }
    else
    {
        result = Term(integrateMonomialWhenExponentIsNotNegativeOne(monomial));
    }
    result.simplify();
    return result;
}

Term Integration::integratePolynomial(
        Polynomial const& polynomial) const
{
    Term result;
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        result = result + integrateMonomial(monomial);
    }
    result.simplify();
    return result;
}

Term Integration::integrateExpression(
        Expression const& expression) const
{
    Term result(integrateAsTermOrExpressionIfNeeded(expression));
    finalizeTermForIntegration(result);
    return result;
}

Term Integration::integrateFunction(
        Function const& functionObject) const
{
    Term result(integrateFunctionOnly(functionObject));
    finalizeTermForIntegration(result);
    return result;
}

Term Integration::integrateMonomialWhenExponentIsNegativeOne(
        Monomial const& monomial) const
{
    Monomial retainedMonomial(monomial);
    retainedMonomial.putVariableWithExponent(m_nameOfVariableToIntegrate, 0);
    Term result = retainedMonomial * getNaturalLogarithmOfTheAbsoluteValueOfTerm(Term(m_nameOfVariableToIntegrate));
    return result;
}

Monomial Integration::integrateMonomialWhenExponentIsNotNegativeOne(
        Monomial const& monomial) const
{
    Monomial result(monomial);
    bool hasVariabletoIntegrate(false);
    for(auto const& variableExponentPair :
        monomial.getVariablesToExponentsMapConstReference())
    {
        string const& variableName(variableExponentPair.first);
        AlbaNumber const& exponent(variableExponentPair.second);
        if(isVariableToIntegrate(variableName))
        {
            result.putVariableWithExponent(variableName, exponent+1);
            result.divideNumber(exponent+1);
            hasVariabletoIntegrate = true;
        }
    }
    if(!hasVariabletoIntegrate)
    {
        result.putVariableWithExponent(m_nameOfVariableToIntegrate, 1);
    }
    return result;
}

Term Integration::integrateAsTermOrExpressionIfNeeded(
        Expression const& expression) const
{
    Term result;
    Configurations configurations{getConfigurationWithFactors(), getConfigurationWithCommonDenominator()};
    for(Configuration const& configuration : configurations)
    {
        Term simplifiedTerm(expression);
        simplifyForIntegration(simplifiedTerm, configuration);
        if(simplifiedTerm.isExpression())
        {
            integrateSimplifiedExpressionOnly(result, simplifiedTerm.getExpressionConstReference(), configuration);
        }
        else
        {
            result = integrate(simplifiedTerm);
        }
        if(!result.isEmpty())
        {
            break;
        }
    }
    if(result.isEmpty())
    {
        result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
    }
    return result;
}

void Integration::integrateSimplifiedExpressionOnly(
        Term & result,
        Expression const& expression,
        Configuration const& configuration) const
{
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    if(OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel())
    {
        integrateTermsInAdditionOrSubtraction(result, termsWithDetails);
    }
    else if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        integrateTermsInMultiplicationOrDivision(result, termsWithDetails);
    }
    else if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
    {
        integrateTermsInRaiseToPower(result, termsWithDetails);
    }
    if(result.isEmpty())
    {
        integrateTermUsingSubstitutionWithMaxDepth(result, Term(expression), configuration);
    }
    if(result.isEmpty())
    {
        integrateByTryingIntegrationByParts(result, Term(expression));
    }
}

void Integration::integrateTermsInAdditionOrSubtraction(
        Term & result,
        TermsWithDetails const& termsWithDetails) const{
    Expression accumulatedExpression(createOrCopyExpressionFromATerm(Constant(0)));
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        Term const& currentTerm(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        Term integratedTerm(integrate(currentTerm));
        if(termWithDetails.hasPositiveAssociation())
        {
            accumulatedExpression.putTermWithAdditionIfNeeded(integratedTerm);
        }
        else
        {
            accumulatedExpression.putTermWithSubtractionIfNeeded(integratedTerm);
        }
    }
    result = Term(accumulatedExpression);
}

void Integration::integrateTermsInMultiplicationOrDivision(
        Term & result,
        TermsWithDetails const& termsWithDetails) const
{
    integrateByProcessingAsPolynomialsOverPolynomials(
                result,
                Term(Expression(OperatorLevel::MultiplicationAndDivision, termsWithDetails)));
    integrateNonChangingAndChangingTermsInMultiplicationOrDivision(result, termsWithDetails);
}

void Integration::integrateTermsInRaiseToPower(
        Term & result,
        TermsWithDetails const& termsWithDetails) const
{
    TermRaiseToTerms termRaiseToTerms(termsWithDetails);
    termRaiseToTerms.simplify();
    Term firstTerm(termRaiseToTerms.getBase());
    Term secondTerm(termRaiseToTerms.getCombinedExponents());
    bool isFirstAChangingTerm = isChangingTerm(firstTerm);
    bool isSecondAChangingTerm = isChangingTerm(secondTerm);
    if(!isFirstAChangingTerm && !isSecondAChangingTerm)
    {
        result = termRaiseToTerms.getCombinedTerm() * Term(m_nameOfVariableToIntegrate);
    }
    else if(!isFirstAChangingTerm && isSecondAChangingTerm)
    {
        integrateNonChangingTermRaiseToChangingTerm(result, firstTerm, secondTerm);
    }
    else if(isFirstAChangingTerm && !isSecondAChangingTerm)
    {
        integrateChangingTermRaiseToNonChangingTerm(result, firstTerm, secondTerm);
    }
    else
    {
        integrateChangingTermRaiseToChangingTerm(result, firstTerm, secondTerm);
    }
}

void Integration::integrateTermUsingSubstitutionWithMaxDepth(
        Term & result,
        Term const& term,
        Configuration const& configuration) const
{
    if(m_isIntegrationUsingSubstitutionAllowed)
    {
        constexpr unsigned int MAX_DEPTH=2;
        static unsigned int depth=0;
        depth++;
        if(depth <= MAX_DEPTH)
        {
            integrateTermUsingSubstitution(result, term, configuration);
        }
        depth--;
    }
}

void Integration::integrateTermUsingSubstitution(
        Term & result,
        Term const& term,
        Configuration const& configuration) const
{
    Term simplifiedTerm(term);
    simplifyForIntegration(simplifiedTerm, configuration);
    Terms subTerms(retrieveSubTerms(simplifiedTerm));
    for(Term const& subTerm : subTerms)
    {
        if(!subTerm.isConstant() && !subTerm.isVariable() && isChangingTerm(subTerm))
        {
            integrateBySubstitutionAndUsingANewVariable(result, simplifiedTerm, subTerm, configuration);
            integrateUsingTrigonometricSubstitutionIfPossible(result, simplifiedTerm, subTerm, configuration);
            if(!result.isEmpty())
            {
                break;
            }
        }
    }
}
void Integration::integrateBySubstitutionAndUsingANewVariable(
        Term & result,
        Term const& mainTerm,
        Term const& termForNewVariable,
        Configuration const& configuration) const
{
    Term termToIntegrateWithNewVariable(substituteToNewVariable(mainTerm, termForNewVariable));
    simplifyForIntegration(termToIntegrateWithNewVariable, configuration);
    if(!isChangingTerm(termToIntegrateWithNewVariable))
    {
        string newVariableName(createVariableNameForSubstitution(termForNewVariable));
        Integration integrationWithNewVariable(newVariableName);
        Term integratedTermWithNewVariable(integrationWithNewVariable.integrate(termToIntegrateWithNewVariable));
        if(!isNotANumber(integratedTermWithNewVariable))
        {
            result = substituteBackToOldVariable(integratedTermWithNewVariable, newVariableName, termForNewVariable);
        }
    }
}

Term Integration::substituteToNewVariable(
        Term const& mainTerm,
        Term const& termForNewVariable) const
{
    Differentiation differentiation(m_nameOfVariableToIntegrate);
    Term derivative(differentiation.differentiate(termForNewVariable));
    Term termForSubstitution = mainTerm/derivative;
    string newVariableName(createVariableNameForSubstitution(termForNewVariable));
    Term newVariable(newVariableName);
    SubstitutionOfTermsToTerms substitutionOfNewVariableDirectMatch({{termForNewVariable, newVariable}});
    Term result(substitutionOfNewVariableDirectMatch.performSubstitutionTo(termForSubstitution));
    if(termForNewVariable.isPolynomial()
            || termForNewVariable.isExpression()
            || termForNewVariable.isFunction())
    {
        Term leftHandSide(newVariable);
        Term rightHandSide(termForNewVariable);
        convertLeftHandSideAndRightHandSideIfLogarithmic(leftHandSide, rightHandSide);
        IsolationOfOneVariableOnEqualityEquation isolationForOldVariable(Equation(leftHandSide, "=", rightHandSide));
        Term termWithOldVariable;
        Term newVariableInTermsOfOldVariable;
        isolationForOldVariable.isolateTermWithVariable(m_nameOfVariableToIntegrate, termWithOldVariable, newVariableInTermsOfOldVariable);
        if(canBeConvertedToMonomial(termWithOldVariable))
        {
            Monomial monomialWithOldVariable(createMonomialIfPossible(termWithOldVariable));
            AlbaNumber exponentForOldVariable(monomialWithOldVariable.getExponentForVariable(m_nameOfVariableToIntegrate));
            monomialWithOldVariable.putVariableWithExponent(m_nameOfVariableToIntegrate, AlbaNumber(0));
            Term isolatedTermWithNewVariable((newVariableInTermsOfOldVariable/monomialWithOldVariable)^(AlbaNumber(1)/exponentForOldVariable));
            isolatedTermWithNewVariable.simplify();
            SubstitutionOfVariablesToTerms substitutionFromOldVariableToNewVariable({{m_nameOfVariableToIntegrate, isolatedTermWithNewVariable}});
            result = substitutionFromOldVariableToNewVariable.performSubstitutionTo(result);
        }
    }
    return result;
}

Term Integration::substituteBackToOldVariable(
        Term const& mainTerm,
        string const& newVariableName,
        Term const& termForNewVariable) const
{
    SubstitutionOfVariablesToTerms substitutionVariableToTerm({{newVariableName, termForNewVariable}});
    return substitutionVariableToTerm.performSubstitutionTo(mainTerm);
}

void Integration::integrateUsingTrigonometricSubstitutionIfPossible(
        Term & result,
        Term const& mainTerm,
        Term const& termToSubstitute,        Configuration const& configuration) const
{
    if(termToSubstitute.isExpression())
    {
        Expression const& expression(termToSubstitute.getExpressionConstReference());
        TermsWithDetails const& expressionTerms(expression.getTermsWithAssociation().getTermsWithDetails());
        if(OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel() && 2 == expressionTerms.size())
        {
            Term const& firstTerm(negateTermIfHasNegativeAssociation(expressionTerms.at(0)));
            Term const& secondTerm(negateTermIfHasNegativeAssociation(expressionTerms.at(1)));
            if(!isChangingTerm(firstTerm))
            {
                integrateUsingTrigonometricSubstitution(result, mainTerm, termToSubstitute, firstTerm, secondTerm, configuration);
            }
            else if(!isChangingTerm(secondTerm))
            {
                integrateUsingTrigonometricSubstitution(result, mainTerm, termToSubstitute, secondTerm, firstTerm, configuration);
            }
        }
    }
    else if(termToSubstitute.isPolynomial())
    {
        Polynomial const& polynomial(termToSubstitute.getPolynomialConstReference());
        Monomials const& monomials(polynomial.getMonomialsConstReference());
        if(2 == monomials.size())
        {
            Term const& firstTerm(Term(monomials.at(0)));
            Term const& secondTerm(Term(monomials.at(1)));
            if(!isChangingTerm(firstTerm))
            {
                integrateUsingTrigonometricSubstitution(result, mainTerm, termToSubstitute, firstTerm, secondTerm, configuration);
            }
            else if(!isChangingTerm(secondTerm))
            {
                integrateUsingTrigonometricSubstitution(result, mainTerm, termToSubstitute, secondTerm, firstTerm, configuration);
            }
        }
    }
}

void Integration::integrateUsingTrigonometricSubstitution(
        Term & result,
        Term const& mainTerm,
        Term const& aSquaredAndUSquared,
        Term const& aSquaredWithSign,
        Term const& uSquaredWithSign,
        Configuration const& configuration) const
{
    bool isANegative(isANegativeTerm(aSquaredWithSign));
    bool isUNegative(isANegativeTerm(uSquaredWithSign));
    Term const& aSquared = convertPositiveTermIfNegative(aSquaredWithSign);
    Term const& uSquared = convertPositiveTermIfNegative(uSquaredWithSign);

    TermRaiseToANumber uToANumber(createTermRaiseToANumberFromTerm(uSquared));
    if(AlbaNumber(2) == uToANumber.getExponent())
    {
        Term a(createExpressionIfPossible({aSquared, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
        Term u(uToANumber.getBase());
        a.simplify();

        TrigonometricSubstitutionDetails details(calculateTrigonometricSubstitutionDetails(a, u, aSquaredAndUSquared, isANegative, isUNegative));
        if(details.isTrigonometricSubstitutionPossible)
        {
            Term termToIntegrateWithTrigSub(substituteToTrigonometricFunctions(mainTerm, details));
            if(!termToIntegrateWithTrigSub.isEmpty())
            {
                simplifyForIntegration(termToIntegrateWithTrigSub, configuration);
                if(!isChangingTerm(termToIntegrateWithTrigSub))
                {
                    Integration integrationUsingTrigSub(details.thetaName);
                    Term integratedTermWithTrigSub(integrationUsingTrigSub.integrate(termToIntegrateWithTrigSub));
                    if(!isNotANumber(integratedTermWithTrigSub))
                    {
                        result = substituteFromTrigonometricFunctionsBackToNormal(integratedTermWithTrigSub, details);
                    }
                }
            }
        }
    }
}

Integration::TrigonometricSubstitutionDetails Integration::calculateTrigonometricSubstitutionDetails(
        Term const& a,
        Term const& u,
        Term const& aSquaredAndUSquared,
        bool const isANegative,
        bool const isUNegative) const
{
    TrigonometricSubstitutionDetails result;
    result.a = a;
    result.u = u;
    result.aSquaredAndUSquared = aSquaredAndUSquared;
    result.thetaName = createVariableNameForSubstitution(u);
    result.theta=Term(result.thetaName);
    if(!isANegative && !isUNegative)
    {
        // use tan
        result.isTrigonometricSubstitutionPossible = true;
        result.uEquivalent = Term(createExpressionIfPossible({a, Term("*"), Term(tan(result.theta))}));
        result.aSquaredAndUSquaredEquivalent = Term(createExpressionIfPossible({a, Term("^"), Term(2), Term("*"), Term(sec(result.theta)), Term("^"), Term(2)}));
        result.thetaEquivalent = Term(arctan(u/a));
        result.opposite = u;
        result.adjacent = a;
        Term hypotenuseSquared(createExpressionIfPossible({a, Term("^"), Term(2), Term("+"), u, Term("^"), Term(2)}));
        result.hypotenuse = Term(createExpressionIfPossible({hypotenuseSquared, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    }
    else if(!isANegative && isUNegative)
    {
        //use sin
        result.isTrigonometricSubstitutionPossible = true;
        result.uEquivalent = Term(createExpressionIfPossible({a, Term("*"), Term(sin(result.theta))}));
        result.aSquaredAndUSquaredEquivalent = Term(createExpressionIfPossible({a, Term("^"), Term(2), Term("*"), Term(cos(result.theta)), Term("^"), Term(2)}));
        result.thetaEquivalent = Term(arcsin(u/a));
        result.opposite = u;
        Term adjacentSquared(createExpressionIfPossible({a, Term("^"), Term(2), Term("-"), u, Term("^"), Term(2)}));
        result.adjacent = Term(createExpressionIfPossible({adjacentSquared, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
        result.hypotenuse = a;
    }
    else if(isANegative && !isUNegative)
    {
        //use sec
        result.isTrigonometricSubstitutionPossible = true;
        result.uEquivalent = Term(createExpressionIfPossible({a, Term("*"), Term(sec(result.theta))}));
        result.aSquaredAndUSquaredEquivalent = Term(createExpressionIfPossible({a, Term("^"), Term(2), Term("*"), Term(tan(result.theta)), Term("^"), Term(2)}));
        result.thetaEquivalent = Term(arcsec(u/a));
        Term oppositeSquared(createExpressionIfPossible({u, Term("^"), Term(2), Term("-"), a, Term("^"), Term(2)}));
        result.opposite = Term(createExpressionIfPossible({oppositeSquared, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
        result.adjacent = a;
        result.hypotenuse = u;
    }
    else
    {
        result.isTrigonometricSubstitutionPossible = false;
    }
    return result;
}

Term Integration::substituteToTrigonometricFunctions(
        Term const& mainTerm,
        TrigonometricSubstitutionDetails const& details) const
{
    Term result;
    Differentiation differentiation(details.thetaName);
    Term duEquivalent(differentiation.differentiate(details.uEquivalent));
    IsolationOfOneVariableOnEqualityEquation isolation(Equation(details.u, "=", details.uEquivalent));
    Term termWithU;
    Term termWithWithoutU;
    isolation.isolateTermWithVariable(m_nameOfVariableToIntegrate, termWithU, termWithWithoutU);
    if(canBeConvertedToMonomial(termWithU))
    {
        Monomial monomialWithOldVariable(createMonomialIfPossible(termWithU));
        AlbaNumber exponentForOldVariable(monomialWithOldVariable.getExponentForVariable(m_nameOfVariableToIntegrate));
        monomialWithOldVariable.putVariableWithExponent(m_nameOfVariableToIntegrate, AlbaNumber(0));
        Term isolatedTermWithTheta((termWithWithoutU/monomialWithOldVariable)^(AlbaNumber(1)/exponentForOldVariable));
        isolatedTermWithTheta.simplify();
        SubstitutionOfTermsToTerms substitutionUToThetaForTermToTerm({{details.aSquaredAndUSquared, details.aSquaredAndUSquaredEquivalent}});
        SubstitutionOfVariablesToTerms substitutionUToThetaForVariableToTerm({{m_nameOfVariableToIntegrate, isolatedTermWithTheta}});
        result = substitutionUToThetaForVariableToTerm.performSubstitutionTo(
                    substitutionUToThetaForTermToTerm.performSubstitutionTo(mainTerm)) * duEquivalent;
    }
    return result;
}

Term Integration::substituteFromTrigonometricFunctionsBackToNormal(
        Term const& mainTerm,
        TrigonometricSubstitutionDetails const& details) const
{
    SubstitutionOfTermsToTerms substitutionThetaToUForTermToTerm;
    substitutionThetaToUForTermToTerm.putTermToTermMapping(Term(sin(details.theta)), Term(details.opposite/details.hypotenuse));
    substitutionThetaToUForTermToTerm.putTermToTermMapping(Term(cos(details.theta)), Term(details.adjacent/details.hypotenuse));
    substitutionThetaToUForTermToTerm.putTermToTermMapping(Term(tan(details.theta)), Term(details.opposite/details.adjacent));
    substitutionThetaToUForTermToTerm.putTermToTermMapping(Term(csc(details.theta)), Term(details.hypotenuse/details.opposite));
    substitutionThetaToUForTermToTerm.putTermToTermMapping(Term(sec(details.theta)), Term(details.hypotenuse/details.adjacent));
    substitutionThetaToUForTermToTerm.putTermToTermMapping(Term(cot(details.theta)), Term(details.adjacent/details.opposite));
    SubstitutionOfVariablesToTerms substitutionThetaToUForVariableToTerm({{details.thetaName, details.thetaEquivalent}});
    return substitutionThetaToUForVariableToTerm.performSubstitutionTo(
                substitutionThetaToUForTermToTerm.performSubstitutionTo(mainTerm));
}

void Integration::integrateNonChangingAndChangingTermsInMultiplicationOrDivision(
        Term& result,        TermsWithDetails const& termsWithDetails) const
{
    TermsWithDetails nonChangingTerms;
    TermsWithDetails changingTerms;
    segregateNonChangingAndChangingTerms(termsWithDetails, nonChangingTerms, changingTerms);
    if(nonChangingTerms.empty())
    {
        integrateChangingTermsInMultiplicationOrDivision(result, changingTerms);
    }
    else
    {
        Term nonChangingTermCombined(Expression(OperatorLevel::MultiplicationAndDivision, nonChangingTerms));
        Term changingTermCombined(1);
        if(!changingTerms.empty())
        {
            changingTermCombined = Term(Expression(OperatorLevel::MultiplicationAndDivision, changingTerms));
        }
        Term integratedChangingTerm(integrate(changingTermCombined));
        if(isNotANumber(integratedChangingTerm))
        {
            result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
        }
        else
        {
            result = nonChangingTermCombined * integratedChangingTerm;
        }
    }
}

void Integration::integrateChangingTermsInMultiplicationOrDivision(
        Term& result,
        TermsWithDetails const& changingTerms) const
{
    TermsOverTerms termsOverTerms(changingTerms);
    TermsOverTerms::BaseToExponentMap termsWithExponentsToCheck;
    termsOverTerms.retrieveBaseToExponentMap(termsWithExponentsToCheck);

    InputTermToTrigonometryFunctionExponentsMap trigFunctionsInputTermToExponents;
    TermsOverTerms::BaseToExponentMap remainingTermsWithExponents;
    retrieveInputTermsAndTrigonometricExponents(trigFunctionsInputTermToExponents, remainingTermsWithExponents, termsWithExponentsToCheck);
    integrateTrigonometricCombinationsIfPossible(result, remainingTermsWithExponents, trigFunctionsInputTermToExponents);

    if(result.isEmpty())
    {
        integrateByTryingTwoTermsInMultiplicationOrDivision(result, changingTerms);
    }
}

void Integration::integrateByTryingTwoTermsInMultiplicationOrDivision(        Term & result,
        TermsWithDetails const& termsWithDetailsInMultiplicationOrDivision) const
{
    unsigned int numberOfTerms(termsWithDetailsInMultiplicationOrDivision.size());
    for(unsigned int i=0; result.isEmpty() && i<numberOfTerms; i++)
    {
        TermsWithDetails termsInFirstTerms(termsWithDetailsInMultiplicationOrDivision);
        termsInFirstTerms.erase(termsInFirstTerms.cbegin() + i);
        Term firstTerm(Expression(OperatorLevel::MultiplicationAndDivision, termsInFirstTerms));
        Term secondTerm(Expression(OperatorLevel::MultiplicationAndDivision, {termsWithDetailsInMultiplicationOrDivision.at(i)}));
        Term innerTermInFirstTerm;
        firstTerm.simplify();
        secondTerm.simplify();
        findInnerAndOuterTermForChainRule(innerTermInFirstTerm, firstTerm);
        if(!innerTermInFirstTerm.isEmpty())
        {
            integrateUsingChainRuleInReverseIfPossible(result, firstTerm, innerTermInFirstTerm, secondTerm);
        }
    }
}

void Integration::integrateUsingChainRuleInReverseIfPossible(
        Term & result,
        Term const& firstOuterTerm,
        Term const& firstInnerTerm,
        Term const& secondTerm) const
{
    Differentiation differentiation(m_nameOfVariableToIntegrate);
    Term firstTermDerivative(differentiation.differentiate(firstInnerTerm));
    Term quotientOfDerivatives = firstTermDerivative/secondTerm;
    if(!isChangingTerm(quotientOfDerivatives))
    {
        string newVariableToIntegrate(createVariableNameForSubstitution(firstInnerTerm));
        SubstitutionOfTermsToTerms substitutionTermToVariable({{firstInnerTerm, Term(newVariableToIntegrate)}});
        Term newFirstOuterTerm(substitutionTermToVariable.performSubstitutionTo(firstOuterTerm));
        Integration integrationWithNewVariable(newVariableToIntegrate);
        Term integratedOuterTermInNewVariable(integrationWithNewVariable.integrate(newFirstOuterTerm));
        SubstitutionOfVariablesToTerms substitutionVariableToTerm({{newVariableToIntegrate, firstInnerTerm}});
        Term integratedOuterTerm(substitutionVariableToTerm.performSubstitutionTo(integratedOuterTermInNewVariable));
        result = integratedOuterTerm / quotientOfDerivatives;
    }
}

void Integration::findInnerAndOuterTermForChainRule(
        Term & innerTerm,
        Term & outerTerm) const
{
    if(outerTerm.isFunction())
    {
        innerTerm = getTermConstReferenceFromBaseTerm(outerTerm.getFunctionConstReference().getInputTermConstReference());
    }
    else if(outerTerm.isExpression())
    {
        Expression const& expression(outerTerm.getExpressionConstReference());
        if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
        {
            TermRaiseToTerms termRaiseToTerms(expression.getTermsWithAssociation().getTermsWithDetails());
            Term base(termRaiseToTerms.getBase());
            Term exponent(termRaiseToTerms.getCombinedExponents());
            Term combinedBaseAndExponent(termRaiseToTerms.getCombinedTerm());
            if(!isChangingTerm(exponent))
            {
                outerTerm = combinedBaseAndExponent;
                innerTerm = base;
            }
            else if(!isChangingTerm(base))
            {
                outerTerm = combinedBaseAndExponent;
                innerTerm = exponent;
            }
        }
        else
        {
            TermRaiseToANumber oldTermRaiseToANumber(createTermRaiseToANumberFromExpression(expression));
            if(oldTermRaiseToANumber.getExponent() != 1)
            {
                outerTerm = oldTermRaiseToANumber.getCombinedTerm();
                innerTerm = oldTermRaiseToANumber.getBase();
            }
        }
    }
}

Term Integration::divideFirstTermAndDerivativeOfSecondTerm(
        Term const& firstTerm,
        Term const& secondTerm) const
{
    Differentiation differentiation(m_nameOfVariableToIntegrate);
    return Term(createExpressionIfPossible({firstTerm, Term("/"), differentiation.differentiate(secondTerm)}));
}

void Integration::integrateByProcessingAsPolynomialsOverPolynomials(
        Term & result,
        Term const& term) const
{
    PolynomialOverPolynomialOptional popOptional(createPolynomialOverPolynomialFromTermIfPossible(term));
    if(popOptional.hasContent())
    {
        PolynomialOverPolynomial & pop(popOptional.getReference());
        PolynomialOverPolynomial::QuotientAndRemainder quotientAndRemainder(pop.simplifyAndDivide());
        if(!quotientAndRemainder.quotient.isEmpty()
                && !hasNegativeExponentsWithVariable(quotientAndRemainder.quotient, m_nameOfVariableToIntegrate))
        {
            result = integrate(quotientAndRemainder.quotient)
                    + integrate(Term(quotientAndRemainder.remainder / pop.getDenominator()));
        }
    }
}

void Integration::integrateByTryingIntegrationByParts(
        Term & result,
        Term const& term) const
{
    if(m_isIntegrationByPartsAllowed)
    {
        integrateUsingIntegrationByPartsByOneTermAndOne(result, term);
        if(result.isEmpty())
        {
            integrateUsingIntegrationByPartsByTryingTwoTerms(result, term);
        }
    }
}

void Integration::integrateUsingIntegrationByPartsByOneTermAndOne(
        Term & result,
        Term const& term) const
{
    bool isAnInverseTrigonometricFunction = term.isFunction()
            && isInverseTrigonometricFunction(term.getFunctionConstReference());
    if(isAnInverseTrigonometricFunction)
    {
        integrateUsingIntegrationByPartsAndCheckingPreviousValues(result, term, term, Term(1));
    }
}

void Integration::integrateUsingIntegrationByPartsByTryingTwoTerms(
        Term & result,
        Term const& term) const{
    if(term.isExpression())
    {
        Expression const& expression(term.getExpressionConstReference());
        if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
        {
            TermsWithDetails const& termsWithDetailsInMultiplicationAndDivision(expression.getTermsWithAssociation().getTermsWithDetails());
            unsigned int numberOfTerms(termsWithDetailsInMultiplicationAndDivision.size());
            for(unsigned int i=0; result.isEmpty() && i<numberOfTerms; i++)
            {
                TermsWithDetails termsInFirstTerms(termsWithDetailsInMultiplicationAndDivision);
                termsInFirstTerms.erase(termsInFirstTerms.cbegin() + i);
                Term firstTerm(Expression(OperatorLevel::MultiplicationAndDivision, termsInFirstTerms));
                Term secondTerm(Expression(OperatorLevel::MultiplicationAndDivision, {termsWithDetailsInMultiplicationAndDivision.at(i)}));
                firstTerm.simplify();
                secondTerm.simplify();
                if(result.isEmpty())
                {
                    integrateUsingIntegrationByPartsByTryingTwoTermsWithDifferentOrder(result, term, firstTerm, secondTerm);
                }
            }
        }
    }
}

void Integration::integrateUsingIntegrationByPartsByTryingTwoTermsWithDifferentOrder(
        Term & result,
        Term const& term,
        Term const& firstTerm,
        Term const& secondTerm) const
{
    integrateUsingIntegrationByPartsAndCheckingPreviousValues(result, term, firstTerm, secondTerm);
    if(result.isEmpty())
    {
        integrateUsingIntegrationByPartsAndCheckingPreviousValues(result, term, secondTerm, firstTerm);
    }
}

void Integration::integrateUsingIntegrationByPartsAndCheckingPreviousValues(
        Term & result,
        Term const& term,
        Term const& u,
        Term const& dv) const
{
    // use static equations here to solve when recursion happens
    // use static depth here to determine when to clear    static ListOfIntegrationByPartsTerms listOfIntegrationByPartsTerms;
    constexpr unsigned int MAX_DEPTH=5;
    constexpr unsigned int MAX_SIZE=5;
    static unsigned int depth=0;
    depth++;

    if(depth < MAX_DEPTH)
    {
        if(listOfIntegrationByPartsTerms.size() < MAX_SIZE)
        {
            integrateUsingPreviousIntegrationByPartsTerms(result, listOfIntegrationByPartsTerms, term);
            if(result.isEmpty())
            {
                integrateUsingIntegrationByParts(result, listOfIntegrationByPartsTerms, term, u, dv);
            }
        }
    }

    depth--;
    if(depth == 0)
    {
        listOfIntegrationByPartsTerms.clear();
    }
}
void Integration::integrateUsingPreviousIntegrationByPartsTerms(
        Term & result,
        ListOfIntegrationByPartsTerms const& listOfIntegrationByPartsTerms,
        Term const& termToIntegrate) const
{
    Term currentTermToIntegrate(termToIntegrate);
    ListOfIntegrationByPartsTerms termsToAnalyze(listOfIntegrationByPartsTerms);
    Term accumulatedUTimesV;
    AlbaNumber accumulatedCoefficient(1);
    bool didAccumulationUpdated(false);
    bool isChanged(true);
    bool isFirstRelationshipFound(true);
    while(isChanged)
    {
        isChanged = false;
        for(unsigned int i=0; i<termsToAnalyze.size(); i++)
        {
            IntegrationByPartsTerms const& integrationByPartsTerms(termsToAnalyze.at(i));
            Term quotient(currentTermToIntegrate/integrationByPartsTerms.vTimesDuToIntegrate);
            quotient.simplify();
            if(quotient.isConstant())
            {
                currentTermToIntegrate = integrationByPartsTerms.uTimesDvToIntegrate;
                accumulatedUTimesV = integrationByPartsTerms.uTimesV - (quotient * accumulatedUTimesV);
                if(isFirstRelationshipFound)
                {
                    accumulatedCoefficient = quotient.getConstantValueConstReference();
                    isFirstRelationshipFound = false;
                }
                else
                {
                    accumulatedCoefficient = AlbaNumber(-1) * quotient.getConstantValueConstReference() * accumulatedCoefficient;
                }
                isChanged = true;
                didAccumulationUpdated = true;
                termsToAnalyze.erase(termsToAnalyze.begin()+i);
                break;
            }
        }
    }
    Term ratio(termToIntegrate/currentTermToIntegrate);
    ratio.simplify();
    if(didAccumulationUpdated && ratio.isConstant())
    {
        result = accumulatedUTimesV * ratio / Term(accumulatedCoefficient+1);
        result.simplify();
    }
}

void Integration::integrateUsingIntegrationByParts(
        Term & result,
        ListOfIntegrationByPartsTerms & listOfIntegrationByPartsTerms,
        Term const& term,
        Term const& u,
        Term const& dv) const
{
    Integration integration(m_nameOfVariableToIntegrate);
    if(!hasExponentialExpression(u))
    {
        Term v(integration.integrate(dv));
        if(!isNotANumber(v))
        {
            Differentiation differentiation(m_nameOfVariableToIntegrate);
            Term du(differentiation.differentiate(u));
            if(!isNotANumber(du))
            {
                Term uTimesV(u*v);
                Term vTimesDu(v*du);
                uTimesV.simplify();
                vTimesDu.simplify();
                listOfIntegrationByPartsTerms.emplace_back(IntegrationByPartsTerms{term, uTimesV, vTimesDu});
                Term integratedVTimesDu(integration.integrate(vTimesDu));
                if(!isNotANumber(integratedVTimesDu))
                {
                    result = uTimesV - integratedVTimesDu;
                }
            }
        }
    }
}

void Integration::integrateNonChangingTermRaiseToChangingTerm(
        Term & result,
        Term const& base,
        Term const& exponent) const
{
    if(wouldDifferentiationYieldToAConstant(exponent))
    {        result = divideFirstTermAndDerivativeOfSecondTerm(Term(createExpressionIfPossible(
        {base, Term("^"), exponent, Term("/"), Term(ln(base))})), exponent);
    }
}

void Integration::integrateChangingTermRaiseToNonChangingTerm(
        Term & result,
        Term const& base,
        Term const& exponent) const
{
    if(wouldDifferentiationYieldToAConstant(base))
    {
        result = divideFirstTermAndDerivativeOfSecondTerm(Term(createExpressionIfPossible(
        {base, Term("^"), Term(exponent+1), Term("/"), Term(exponent+1)})), base);
    }
    else
    {
        if(result.isEmpty() && base.isFunction() && exponent == Term(2))
        {
            integrateRecognizedFunctionsSquared(result, base);
        }
        if(result.isEmpty() && base.isFunction() && exponent.isConstant())
        {
            Function const& functionObject(base.getFunctionConstReference());
            Term const& functionInputTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
            AlbaNumber const& exponentValue(exponent.getConstantValueConstReference());
            string const& functionName(functionObject.getFunctionName());
            bool isExponentGreaterThan1 = exponentValue.isIntegerType() && exponentValue > 1;
            if(functionName == "sin" && isExponentGreaterThan1)
            {
                integrateSinRaiseToAnIntegerGreaterThanOne(result, functionInputTerm, static_cast<unsigned int>(exponentValue.getInteger()));
            }
            else if(functionName == "cos" && isExponentGreaterThan1)
            {
                integrateCosRaiseToAnIntegerGreaterThanOne(result, functionInputTerm, static_cast<unsigned int>(exponentValue.getInteger()));
            }
            else if(functionName == "tan" && isExponentGreaterThan1)
            {
                integrateTanRaiseToAnIntegerGreaterThanOne(result, functionInputTerm, static_cast<unsigned int>(exponentValue.getInteger()));
            }
            else if(functionName == "csc" && isExponentGreaterThan1)
            {
                integrateCscRaiseToAnIntegerGreaterThanOne(result, functionInputTerm, static_cast<unsigned int>(exponentValue.getInteger()));
            }
            else if(functionName == "sec" && isExponentGreaterThan1)
            {
                integrateSecRaiseToAnIntegerGreaterThanOne(result, functionInputTerm, static_cast<unsigned int>(exponentValue.getInteger()));
            }
            else if(functionName == "cot" && isExponentGreaterThan1)
            {
                integrateCotRaiseToAnIntegerGreaterThanOne(result, functionInputTerm, static_cast<unsigned int>(exponentValue.getInteger()));
            }
        }
    }
}

void Integration::integrateChangingTermRaiseToChangingTerm(
        Term & result,        Term const& ,
        Term const& ) const
{
    result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
}

void Integration::segregateNonChangingAndChangingTerms(
        TermsWithDetails const& termsToSegregate,
        TermsWithDetails & nonChangingTerms,
        TermsWithDetails & changingTerms) const
{
    for(TermWithDetails const& termToSegregate : termsToSegregate)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termToSegregate.baseTermSharedPointer));
        if(isChangingTerm(term))
        {
            changingTerms.emplace_back(termToSegregate);
        }
        else
        {
            nonChangingTerms.emplace_back(termToSegregate);
        }
    }
}

void Integration::convertLeftHandSideAndRightHandSideIfLogarithmic(
        Term & leftHandSide,
        Term & rightHandSide) const
{
    if(rightHandSide.isFunction() && isLogarithmicFunction(rightHandSide.getFunctionConstReference()))
    {
        Function const& functionObject(rightHandSide.getFunctionConstReference());
        if("log" == functionObject.getFunctionName())
        {
            leftHandSide = Term(createExpressionIfPossible({Term(10), Term("^"), leftHandSide}));
        }
        else if("ln" == functionObject.getFunctionName())
        {
            leftHandSide = Term(createExpressionIfPossible({getEAsTerm(), Term("^"), leftHandSide}));
        }
        rightHandSide = getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference());
    }
}

Term Integration::integrateFunctionOnly(
        Function const& functionObject) const
{
    Term result;
    Term const& inputTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
    if(wouldDifferentiationYieldToAConstant(inputTerm))
    {
        string const& functionName(functionObject.getFunctionName());
        if("abs" == functionName)
        {
            result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
        }
        else if("sin" == functionName)
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(Term(createExpressionIfPossible({Term(-1), Term("*"), cos(inputTerm)})), inputTerm);
        }
        else if("cos" == functionName)
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(Term(sin(inputTerm)), inputTerm);
        }
        else if("tan" == functionName)
        {
            result = getNaturalLogarithmOfTheAbsoluteValueOfTerm(Term(sec(inputTerm)));
        }
        else if("csc" == functionName)
        {
            result = getNaturalLogarithmOfTheAbsoluteValueOfTerm(Term(csc(inputTerm)) - Term(cot(inputTerm)));
        }
        else if("sec" == functionName)
        {
            result = getNaturalLogarithmOfTheAbsoluteValueOfTerm(Term(sec(inputTerm)) + Term(tan(inputTerm)));
        }
        else if("cot" == functionName)
        {
            result = getNaturalLogarithmOfTheAbsoluteValueOfTerm(Term(sin(inputTerm)));
        }
        else if("sinh" == functionName)
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(Term(cosh(inputTerm)), inputTerm);
        }
        else if("cosh" == functionName)
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(Term(sinh(inputTerm)), inputTerm);
        }
    }
    if(result.isEmpty())
    {
        integrateTermUsingSubstitutionWithMaxDepth(result, Term(functionObject), getConfigurationWithFactors());
    }
    if(result.isEmpty())
    {
        integrateByTryingIntegrationByParts(result, Term(functionObject));
    }
    if(result.isEmpty())
    {
        result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
    }
    return result;
}
void Integration::retrieveInputTermsAndTrigonometricExponents(
        InputTermToTrigonometryFunctionExponentsMap & trigFunctionsInputTermToExponents,
        TermsOverTerms::BaseToExponentMap & remainingTermsWithExponents,
        TermsOverTerms::BaseToExponentMap const& termsWithExponentsToCheck) const
{
    for(auto const& termExponentPair : termsWithExponentsToCheck)
    {
        Term const& base(termExponentPair.first);
        AlbaNumber const& exponent(termExponentPair.second);
        if(base.isFunction() && isTrigonometricFunction(base.getFunctionConstReference()))
        {
            Function const& functionObject(base.getFunctionConstReference());
            Term const& inputTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
            string const& functionName(functionObject.getFunctionName());
            if("sin" == functionName)
            {
                trigFunctionsInputTermToExponents[inputTerm].sinExponent += exponent;
            }
            else if("cos" == functionName)
            {
                trigFunctionsInputTermToExponents[inputTerm].cosExponent += exponent;
            }
            else if("tan" == functionName)
            {
                trigFunctionsInputTermToExponents[inputTerm].tanExponent += exponent;
            }
            else if("csc" == functionName)
            {
                trigFunctionsInputTermToExponents[inputTerm].cscExponent += exponent;
            }
            else if("sec" == functionName)
            {
                trigFunctionsInputTermToExponents[inputTerm].secExponent += exponent;
            }
            else if("cot" == functionName)
            {
                trigFunctionsInputTermToExponents[inputTerm].cotExponent += exponent;
            }
        }
        else
        {
            remainingTermsWithExponents.emplace(base, exponent);
        }
    }
}

void Integration::integrateTrigonometricCombinationsIfPossible(
        Term& result,
        TermsOverTerms::BaseToExponentMap const& remainingTerms,
        InputTermToTrigonometryFunctionExponentsMap const& inputTermToExponents) const
{
    if(remainingTerms.empty() && inputTermToExponents.size() == 1)
    {
        Term const& inputTerm(inputTermToExponents.begin()->first);
        TrigonometryFunctionExponents exponents(inputTermToExponents.begin()->second);
        integrateUsingKnownTrigonometricCombinations(result, exponents, inputTerm);
    }
}

void Integration::integrateUsingKnownTrigonometricCombinations(
        Term& result,
        TrigonometryFunctionExponents const& exponents,
        Term const& functionInputTerm) const
{
    if(exponents.sinExponent.isIntegerType() && exponents.sinExponent > 1
            && exponents.cosExponent.isIntegerType() && exponents.cosExponent > 1
            && exponents.tanExponent == 0
            && exponents.cscExponent == 0
            && exponents.secExponent == 0
            && exponents.cotExponent == 0)
    {
        integrateSinAndCosCombinationWithExponentsGreaterThanOne(
                    result,
                    functionInputTerm,
                    static_cast<unsigned int>(exponents.sinExponent.getInteger()),
                    static_cast<unsigned int>(exponents.cosExponent.getInteger()));
    }
    else if(exponents.sinExponent == 0
            && exponents.cosExponent == 0
            && exponents.tanExponent == 0
            && exponents.cscExponent.isIntegerType() && exponents.cscExponent > 2
            && exponents.secExponent == 0
            && exponents.cotExponent.isIntegerType() && exponents.cotExponent > 1)
    {
        integrateCscAndCotCombinationWithExponentsGreaterThanOne(
                    result,
                    functionInputTerm,
                    static_cast<unsigned int>(exponents.cscExponent.getInteger()),
                    static_cast<unsigned int>(exponents.cotExponent.getInteger()));
    }
    else if(exponents.sinExponent == 0
            && exponents.cosExponent == 0
            && exponents.tanExponent.isIntegerType() && exponents.tanExponent > 1
            && exponents.cscExponent == 0
            && exponents.secExponent.isIntegerType() && exponents.secExponent > 2
            && exponents.cotExponent == 0)
    {
        integrateSecAndTanCombinationWithExponentsGreaterThanOne(
                    result,
                    functionInputTerm,
                    static_cast<unsigned int>(exponents.secExponent.getInteger()),
                    static_cast<unsigned int>(exponents.tanExponent.getInteger()));
    }
}

void Integration::integrateRecognizedFunctionsSquared(
        Term & result,
        Term const& functionTerm) const
{
    Function const& functionObject(functionTerm.getFunctionConstReference());
    Term const& inputOfFunctionTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
    if(wouldDifferentiationYieldToAConstant(inputOfFunctionTerm))    {
        string const& functionName(functionObject.getFunctionName());
        if(functionName == "sec")
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(Term(tan(inputOfFunctionTerm)), inputOfFunctionTerm);
        }
        else if(functionName == "csc")
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(createExpressionIfPossible(
            {Term(cot(inputOfFunctionTerm)), Term("*"), Term(-1)}), inputOfFunctionTerm);
        }
        else if(functionName == "sech")
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(Term(tanh(inputOfFunctionTerm)), inputOfFunctionTerm);
        }
        else if(functionName == "csch")
        {
            result = divideFirstTermAndDerivativeOfSecondTerm(createExpressionIfPossible(
            {Term(coth(inputOfFunctionTerm)), Term("*"), Term(-1)}), inputOfFunctionTerm);
        }
    }
}

void Integration::integrateSinRaiseToAnIntegerGreaterThanOne(
        Term & result,
        Term const& functionInputTerm,
        unsigned int const exponent) const
{
    if(isEven(exponent))
    {
        Term termToIntegrate(1);
        putReducedSineSquaredToDoubleAngleCosineTerms(termToIntegrate, functionInputTerm, exponent);
        result = integrate(termToIntegrate);
    }
    else
    {
        Term termWithExponent(createExpressionIfPossible({getSineSquaredInCosine(functionInputTerm), Term("^"), Term(exponent/2)}));
        Term termToIntegrate(createExpressionIfPossible({termWithExponent, Term("*"), Term(sin(functionInputTerm))}));
        result = integrate(termToIntegrate);
    }
}

void Integration::integrateCosRaiseToAnIntegerGreaterThanOne(
        Term & result,
        Term const& functionInputTerm,        unsigned int const exponent) const
{
    if(isEven(exponent))
    {
        Term termToIntegrate(1);
        putReducedCosineSquaredToDoubleAngleCosineTerms(termToIntegrate, functionInputTerm, exponent);
        result = integrate(termToIntegrate);
    }
    else
    {
        Term termWithExponent(createExpressionIfPossible({getCosineSquaredInSine(functionInputTerm), Term("^"), Term(exponent/2)}));
        Term termToIntegrate(createExpressionIfPossible({termWithExponent, Term("*"), Term(cos(functionInputTerm))}));
        result = integrate(termToIntegrate);
    }
}

void Integration::integrateTanRaiseToAnIntegerGreaterThanOne(
        Term & result,
        Term const& functionInputTerm,        unsigned int const exponent) const
{
    Term tanRaiseToExponentMinus2(createExpressionIfPossible({Term(tan(functionInputTerm)), Term("^"), Term(exponent-2)}));
    Term termToIntegrate = getTangentSquaredInSecant(functionInputTerm) * tanRaiseToExponentMinus2;
    result = integrate(termToIntegrate);
}

void Integration::integrateCscRaiseToAnIntegerGreaterThanOne(
        Term & result,
        Term const& functionInputTerm,
        unsigned int const exponent) const
{
    if(isEven(exponent))
    {
        Term termToIntegrate(getCosecantSquared(functionInputTerm));
        putCosecantSquaredToCotangentSquaredTerms(termToIntegrate, functionInputTerm, exponent-2);
        result = integrate(termToIntegrate);
    }
    else
    {
        unsigned int const exponentMinus1 = exponent-1;
        unsigned int const exponentMinus2 = exponent-2;
        Term cscRaiseToExponentMinus2(createExpressionIfPossible({Term(csc(functionInputTerm)), Term("^"), Term(exponentMinus2)}));        Term nonIntegralTerm(createExpressionIfPossible({cscRaiseToExponentMinus2, Term("*"), Term(cot(functionInputTerm)), Term("*"), Term(-1)}));
        result = (nonIntegralTerm + Term(exponentMinus2) * integrate(cscRaiseToExponentMinus2))/exponentMinus1;
    }
}

void Integration::integrateSecRaiseToAnIntegerGreaterThanOne(
        Term & result,
        Term const& functionInputTerm,
        unsigned int const exponent) const
{
    if(isEven(exponent))
    {
        Term termToIntegrate(getSecantSquared(functionInputTerm));
        putSecantSquaredToTangentSquaredTerms(termToIntegrate, functionInputTerm, exponent-2);
        result = integrate(termToIntegrate);
    }
    else
    {
        unsigned int const exponentMinus1 = exponent-1;
        unsigned int const exponentMinus2 = exponent-2;
        Term secRaiseToExponentMinus2(createExpressionIfPossible({Term(sec(functionInputTerm)), Term("^"), Term(exponentMinus2)}));        Term nonIntegralTerm(createExpressionIfPossible({secRaiseToExponentMinus2, Term("*"), Term(tan(functionInputTerm))}));
        result = (nonIntegralTerm + Term(exponentMinus2) * integrate(secRaiseToExponentMinus2))/exponentMinus1;
    }
}

void Integration::integrateCotRaiseToAnIntegerGreaterThanOne(
        Term & result,
        Term const& functionInputTerm,
        unsigned int const exponent) const
{
    Term tanRaiseToExponentMinus2(createExpressionIfPossible({Term(cot(functionInputTerm)), Term("^"), Term(exponent-2)}));
    Term termToIntegrate = getCotangentSquaredInCosecant(functionInputTerm) * tanRaiseToExponentMinus2;
    result = integrate(termToIntegrate);
}

void Integration::integrateSinAndCosCombinationWithExponentsGreaterThanOne(
        Term & result,
        Term const& functionInputTerm,
        unsigned int const sinExponent,
        unsigned int const cosExponent) const
{
    Term termToIntegrate(1);
    if(isEven(sinExponent) && isEven(cosExponent))
    {
        putReducedSineSquaredToDoubleAngleCosineTerms(termToIntegrate, functionInputTerm, sinExponent);        putReducedCosineSquaredToDoubleAngleCosineTerms(termToIntegrate, functionInputTerm, cosExponent);
    }
    else if(isOdd(sinExponent) && isEven(cosExponent))
    {
        termToIntegrate = termToIntegrate * Term(createExpressionIfPossible({getSineSquaredInCosine(functionInputTerm), Term("^"), Term(sinExponent/2)}));
        termToIntegrate = termToIntegrate * Term(sin(functionInputTerm));
        termToIntegrate = termToIntegrate * Term(createExpressionIfPossible({cos(functionInputTerm), Term("^"), Term(cosExponent)}));
    }
    else if(isEven(sinExponent) && isOdd(cosExponent))
    {
        termToIntegrate = termToIntegrate * Term(createExpressionIfPossible({getCosineSquaredInSine(functionInputTerm), Term("^"), Term(cosExponent/2)}));
        termToIntegrate = termToIntegrate * Term(cos(functionInputTerm));
        termToIntegrate = termToIntegrate * Term(createExpressionIfPossible({sin(functionInputTerm), Term("^"), Term(sinExponent)}));
    }
    else if(isOdd(sinExponent) && isOdd(cosExponent))
    {
        //This is also can be expressed in cosine.
        termToIntegrate = termToIntegrate * Term(createExpressionIfPossible({getSineSquaredInCosine(functionInputTerm), Term("^"), Term(cosExponent/2)}));
        termToIntegrate = termToIntegrate * Term(cos(functionInputTerm));
        termToIntegrate = termToIntegrate * Term(createExpressionIfPossible({sin(functionInputTerm), Term("^"), Term(sinExponent)}));
    }
    result = integrate(termToIntegrate);
}

void Integration::integrateCscAndCotCombinationWithExponentsGreaterThanOne(
        Term & result,
        Term const& functionInputTerm,        unsigned int const cscExponent,
        unsigned int const cotExponent) const
{
    if(isEven(cscExponent))
    {
        Term termToIntegrate(createExpressionIfPossible({cot(functionInputTerm), Term("^"), Term(cotExponent), Term("*"), csc(functionInputTerm), Term("^"), Term(2)}));
        putCosecantSquaredToCotangentSquaredTerms(termToIntegrate, functionInputTerm, cscExponent-2);
        result = integrate(termToIntegrate);
    }
    else
    {
        Term termToIntegrate(createExpressionIfPossible({csc(functionInputTerm), Term("^"), Term(cscExponent), Term("*"), cot(functionInputTerm)}));
        putCotangentSquaredToCosecantSquaredTerms(termToIntegrate, functionInputTerm, cotExponent-1);
        result = integrate(termToIntegrate);
        // what if cotExponent is even, then squareroot will happen, this is still not solved
    }
}

void Integration::integrateSecAndTanCombinationWithExponentsGreaterThanOne(
        Term & result,        Term const& functionInputTerm,
        unsigned int const secExponent,
        unsigned int const tanExponent) const
{
    if(isEven(secExponent))
    {
        Term termToIntegrate(createExpressionIfPossible({tan(functionInputTerm), Term("^"), Term(tanExponent), Term("*"), sec(functionInputTerm), Term("^"), Term(2)}));
        putSecantSquaredToTangentSquaredTerms(termToIntegrate, functionInputTerm, secExponent-2);
        result = integrate(termToIntegrate);
    }
    else
    {
        Term termToIntegrate(createExpressionIfPossible({sec(functionInputTerm), Term("^"), Term(secExponent), Term("*"), tan(functionInputTerm)}));
        putTangentSquaredToSecantSquaredTerms(termToIntegrate, functionInputTerm, tanExponent-1);
        result = integrate(termToIntegrate);
        // what if tanExponent is even, then squareroot will happen, this is still not solved
    }
}

void Integration::putReducedSineSquaredToDoubleAngleCosineTerms(
        Term & outputTerm,        Term const& inputTerm,
        unsigned int const exponent) const
{
    Term inputTimes2(inputTerm*Term(2));
    Term equivalentToSineSquared(getSineSquaredOfHalvedValue(inputTimes2));
    for(unsigned int i=0; i<exponent; i+=2)
    {
        outputTerm = outputTerm * equivalentToSineSquared;
    }
}

void Integration::putReducedCosineSquaredToDoubleAngleCosineTerms(
        Term & outputTerm,
        Term const& inputTerm,
        unsigned int const exponent) const
{
    Term inputTimes2(inputTerm*Term(2));
    Term equivalentToCosineSquared(getCosineSquaredOfHalvedValue(inputTimes2));
    for(unsigned int i=0; i<exponent; i+=2)
    {
        outputTerm = outputTerm * equivalentToCosineSquared;
    }
}

void Integration::putTangentSquaredToSecantSquaredTerms(
        Term & outputTerm,
        Term const& inputTerm,
        unsigned int const exponent) const
{
    Term termToMultiply(createExpressionIfPossible({getTangentSquaredInSecant(inputTerm), Term("^"), Term(AlbaNumber(exponent)/2)}));
    outputTerm = outputTerm * termToMultiply;
}

void Integration::putCosecantSquaredToCotangentSquaredTerms(
        Term & outputTerm,
        Term const& inputTerm,
        unsigned int const exponent) const
{
    Term termToMultiply(createExpressionIfPossible({getCosecantSquaredInCotangent(inputTerm), Term("^"), Term(AlbaNumber(exponent)/2)}));
    outputTerm = outputTerm * termToMultiply;
}

void Integration::putSecantSquaredToTangentSquaredTerms(
        Term & outputTerm,
        Term const& inputTerm,
        unsigned int const exponent) const
{
    Term termToMultiply(createExpressionIfPossible({getSecantSquaredInTangent(inputTerm), Term("^"), Term(AlbaNumber(exponent)/2)}));
    outputTerm = outputTerm * termToMultiply;
}

void Integration::putCotangentSquaredToCosecantSquaredTerms(
        Term & outputTerm,
        Term const& inputTerm,
        unsigned int const exponent) const
{
    Term termToMultiply(createExpressionIfPossible({getCotangentSquaredInCosecant(inputTerm), Term("^"), Term(AlbaNumber(exponent)/2)}));
    outputTerm = outputTerm * termToMultiply;
}

Integration::TrigonometryFunctionExponents Integration::fixTrigonometricExponents(
        TrigonometryFunctionExponents const& oldExponents) const
{
    TrigonometryFunctionExponents newExponents;
    TrigonometryFunctionExponents exponents;

    exponents.sinExponent = oldExponents.sinExponent;
    exponents.cosExponent = oldExponents.cosExponent;

    //tan change to sin and cos
    exponents.sinExponent += oldExponents.tanExponent;
    exponents.cosExponent += oldExponents.tanExponent*-1;
    exponents.tanExponent = 0;

    //csc change to sin and cos
    exponents.sinExponent += oldExponents.cscExponent*-1;
    exponents.cscExponent = 0;

    //sec change to sin and cos
    exponents.cosExponent += oldExponents.secExponent*-1;
    exponents.secExponent = 0;

    //cot change to sin and cos
    exponents.sinExponent += oldExponents.cotExponent*-1;
    exponents.cosExponent += oldExponents.cotExponent;
    exponents.cotExponent = 0;

    if(exponents.sinExponent >= 0 && exponents.cosExponent <= 0)
    {
        AlbaNumber cosPositiveExponents(getAbsoluteValueForAlbaNumber(exponents.cosExponent));
        if(exponents.sinExponent <= cosPositiveExponents)
        {
            exponents.secExponent = cosPositiveExponents - exponents.sinExponent;
            exponents.tanExponent = exponents.sinExponent;
            exponents.sinExponent = 0;
            exponents.cosExponent = 0;
            exponents.cscExponent = 0;
            exponents.cotExponent = 0;
        }
        newExponents = exponents;
    }
    else if(exponents.sinExponent <= 0 && exponents.cosExponent >= 0)
    {
        AlbaNumber sinPositiveExponents(getAbsoluteValueForAlbaNumber(exponents.sinExponent));
        if(exponents.cosExponent <= sinPositiveExponents)
        {
            exponents.cscExponent = sinPositiveExponents - exponents.cosExponent;
            exponents.cotExponent = exponents.cosExponent;
            exponents.sinExponent = 0;
            exponents.cosExponent = 0;
            exponents.tanExponent = 0;
            exponents.secExponent = 0;
        }
        newExponents = exponents;
    }
    else
    {
        newExponents = oldExponents;
    }
    return newExponents;
}

void Integration::setIsIntegrationUsingSubstitutionAllowed(
        bool const isIntegrationUsingSubstitutionAllowed)
{
    m_isIntegrationUsingSubstitutionAllowed = isIntegrationUsingSubstitutionAllowed;
}

void Integration::setIsIntegrationByPartsAllowed(        bool const isIntegrationByPartsAllowed)
{
    m_isIntegrationByPartsAllowed = isIntegrationByPartsAllowed;
}

void Integration::simplifyForIntegration(
        Term & term,
        Configuration const& configuration) const
{
    simplifyAndFixTrigonometricFunctions(term, configuration.shouldFixTrigonometricFunctions);
    term.simplify();
    {
        SimplificationOfExpression::ScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configuration.expressionSimplification);

        term.simplify();
    }
}

void Integration::simplifyAndFixTrigonometricFunctions(
        Term & term,
        bool const shouldFixTrigonometricFunctions) const
{
    if(shouldFixTrigonometricFunctions)
    {
        TermsOverTerms termsOverTerms(createTermsOverTermsFromTerm(term));
        TermsOverTerms::BaseToExponentMap termsWithExponentsToCheck;
        termsOverTerms.retrieveBaseToExponentMap(termsWithExponentsToCheck);

        InputTermToTrigonometryFunctionExponentsMap trigFunctionsInputTermToExponents;
        TermsOverTerms::BaseToExponentMap remainingTermsWithExponents;

        retrieveInputTermsAndTrigonometricExponents(trigFunctionsInputTermToExponents, remainingTermsWithExponents, termsWithExponentsToCheck);

        if(!trigFunctionsInputTermToExponents.empty())
        {
            bool isChanged(false);
            for(auto & inputTermExponentsPair : trigFunctionsInputTermToExponents)
            {
                TrigonometryFunctionExponents & exponents(inputTermExponentsPair.second);
                TrigonometryFunctionExponents newExponents(fixTrigonometricExponents(exponents));
                isChanged = isChanged || !areExponentsSame(exponents, newExponents);
                exponents = newExponents;
            }
            if(isChanged)
            {
                TermsOverTerms::BaseToExponentMap newTerms(remainingTermsWithExponents);
                for(auto const& inputTermExponentsPair : trigFunctionsInputTermToExponents)
                {
                    Term const& inputTerm(inputTermExponentsPair.first);
                    TrigonometryFunctionExponents const& exponents(inputTermExponentsPair.second);
                    if(exponents.sinExponent != 0)
                    {
                        newTerms[Term(sin(inputTerm))] = exponents.sinExponent;
                    }
                    if(exponents.cosExponent != 0)
                    {
                        newTerms[Term(cos(inputTerm))] = exponents.cosExponent;
                    }
                    if(exponents.tanExponent != 0)
                    {
                        newTerms[Term(tan(inputTerm))] = exponents.tanExponent;
                    }
                    if(exponents.cscExponent != 0)
                    {
                        newTerms[Term(csc(inputTerm))] = exponents.cscExponent;
                    }
                    if(exponents.secExponent != 0)
                    {
                        newTerms[Term(sec(inputTerm))] = exponents.secExponent;
                    }
                    if(exponents.cotExponent != 0)
                    {
                        newTerms[Term(cot(inputTerm))] = exponents.cotExponent;
                    }
                }
                TermsOverTerms termsOverTerms;
                termsOverTerms.saveBaseToExponentMap(newTerms);
                term = termsOverTerms.getCombinedTerm();
            }
        }
    }

}

void Integration::finalizeTermForIntegration(
        Term & term) const
{
    simplifyForIntegration(term, getConfigurationWithFactors());
}

Integration::Configuration Integration::getConfigurationWithoutFactors() const{
    Configuration configuration;
    configuration.shouldFixTrigonometricFunctions = true;
    configuration.expressionSimplification = SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails();
    configuration.expressionSimplification.shouldSimplifyToFactors = false;
    configuration.expressionSimplification.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;
    configuration.expressionSimplification.shouldSimplifyToACommonDenominator = false;
    return configuration;
}

Integration::Configuration Integration::getConfigurationWithFactors() const
{
    Configuration configuration;
    configuration.shouldFixTrigonometricFunctions = true;
    configuration.expressionSimplification = SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails();
    configuration.expressionSimplification.shouldSimplifyToFactors = true;
    configuration.expressionSimplification.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;
    return configuration;
}

Integration::Configuration Integration::getConfigurationWithCommonDenominator() const
{
    Configuration configuration;
    configuration.shouldFixTrigonometricFunctions = true;
    configuration.expressionSimplification = SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails();
    configuration.expressionSimplification.shouldSimplifyToFactors = true;
    configuration.expressionSimplification.shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue = true;
    configuration.expressionSimplification.shouldSimplifyToACommonDenominator = true;
    return configuration;
}

bool Integration::isVariableToIntegrate(
        string const& variableName) const
{
    return variableName == m_nameOfVariableToIntegrate;
}
bool Integration::isChangingTerm(
        Term const& term) const
{
    VariableNamesRetriever retriever;
    retriever.retrieveFromTerm(term);
    VariableNamesSet const& variableNames(retriever.getSavedData());
    return any_of(variableNames.cbegin(), variableNames.cend(),
                  [&](string const& variableName)
    {
        return isVariableToIntegrate(variableName);
    });
}

bool Integration::hasExponentialExpression(Term const& term) const
{
    SubTermsRetriever retriever;
    retriever.retrieveFromTerm(term);
    bool result(false);
    for(Term const& retrievedTerm : retriever.getSavedData())
    {
        if(retrievedTerm.isExpression())
        {
            Expression const& expression(retrievedTerm.getExpressionConstReference());
            if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
            {
                TermRaiseToTerms termRaiseToTerms(expression.getTermsWithAssociation().getTermsWithDetails());
                result = isChangingTerm(termRaiseToTerms.getCombinedExponents());
                break;
            }
        }
    }
    return result;
}

bool Integration::wouldDifferentiationYieldToAConstant(
        Term const& term) const
{
    bool result(0);
    if(term.isVariable() && isVariableToIntegrate(term.getVariableConstReference().getVariableName()))
    {
        result = true;
    }
    else if(term.isMonomial())
    {
        result = term.getMonomialConstReference().getExponentForVariable(m_nameOfVariableToIntegrate) == 1;
    }
    else if(term.isPolynomial())
    {
        result = term.getPolynomialConstReference().getDegreeForVariable(m_nameOfVariableToIntegrate) == 1;
    }
    return result;
}

bool Integration::areExponentsSame(
        TrigonometryFunctionExponents const& exponents1,
        TrigonometryFunctionExponents const& exponents2) const
{
    return exponents1.sinExponent == exponents2.sinExponent
            && exponents1.cosExponent == exponents2.cosExponent
            && exponents1.tanExponent == exponents2.tanExponent
            && exponents1.cscExponent == exponents2.cscExponent
            && exponents1.secExponent == exponents2.secExponent
            && exponents1.cotExponent == exponents2.cotExponent;
}

}

}
