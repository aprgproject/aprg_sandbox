#include "Expression.hpp"

#include <Equation/Constructs/AdditionAndSubtractionOfExpressions.hpp>
#include <Equation/Constructs/AdditionAndSubtractionOfTermsOverTerms.hpp>
#include <Equation/Constructs/TermsOverTerms.hpp>
#include <Equation/Operations/AccumulateOperations.hpp>
#include <Equation/Factorization/Factorization.hpp>
#include <Equation/Term/Term.hpp>
#include <Equation/Term/TermOperators.hpp>
#include <Equation/Utilities.hpp>
#include <Optional/AlbaOptional.hpp>

#include <algorithm>
#include <sstream>


#include <Debug/AlbaDebug.hpp>

using namespace alba::equation::Factorization;
using namespace std;
using TermWithDetails=alba::equation::TermsWithAssociation::TermWithDetails;using TermsWithDetails=alba::equation::TermsWithAssociation::TermsWithDetails;

namespace alba
{
namespace equation
{

Expression::Expression()
    : m_commonOperatorLevel(OperatorLevel::Unknown)
{}

Expression::Expression(BaseTerm const& baseTerm)
    : m_commonOperatorLevel(OperatorLevel::Unknown)
{
    m_termsWithAssociation.putTermWithPositiveAssociation(baseTerm);
}

Expression::~Expression()
{}

bool Expression::operator==(Expression const& second) const
{
    return m_commonOperatorLevel == second.m_commonOperatorLevel
            && m_termsWithAssociation==second.m_termsWithAssociation;
}

bool Expression::operator!=(Expression const& second) const
{
    return !(operator==(second));
}

bool Expression::operator<(Expression const& second) const
{
    bool result(false);
    if(m_commonOperatorLevel == second.m_commonOperatorLevel)
    {
        return m_termsWithAssociation < second.m_termsWithAssociation;
    }
    else
    {
        result = getOperatorLevelInversePriority(m_commonOperatorLevel)
                < getOperatorLevelInversePriority(second.m_commonOperatorLevel);
    }
    return result;
}

bool Expression::isEmpty() const
{
    return m_termsWithAssociation.isEmpty();
}

bool Expression::containsOnlyOneTerm() const
{
    return 1 == m_termsWithAssociation.getSize();
}

OperatorLevel Expression::getCommonOperatorLevel() const
{
    return m_commonOperatorLevel;
}

BaseTerm const& Expression::getFirstTermConstReference() const
{
    return m_termsWithAssociation.getFirstTermConstReference();
}

TermsWithAssociation const& Expression::getTermsWithAssociation() const
{
    return m_termsWithAssociation;
}

TermsWithAssociation & Expression::getTermsWithAssociationReference()
{
    return m_termsWithAssociation;
}

TermsWithAssociation Expression::getTermsWithDetailsThatSatisfiesCondition(
        ConditionFunctionForTermsWithDetails const& conditionFunction) const
{
    TermsWithAssociation termsWithOnlyExpressions;
    TermsWithDetails const& termsWithDetails(m_termsWithAssociation.getTermsWithDetails());
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        if(conditionFunction(termWithDetails))
        {
            termsWithOnlyExpressions.putTermWithDetails(termWithDetails);
        }
    }
    return termsWithOnlyExpressions;

}

string Expression::getDisplayableString() const
{
    bool isFirst(true);
    stringstream result;
    TermsWithDetails const& termsWithDetails(m_termsWithAssociation.getTermsWithDetails());
    result << "(";
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        if(isFirst)
        {
            result << getFirstStringIfNegativeAssociation(m_commonOperatorLevel, termWithDetails.association);
            isFirst=false;
        }
        else
        {
            result << getOperatingString(m_commonOperatorLevel, termWithDetails.association);
        }
        result << term.getDisplayableString();
    }
    result << ")";
    return result.str();
}

string Expression::getDebugString() const
{
    bool isFirst(true);
    stringstream result;
    TermsWithDetails const& termsWithDetails(m_termsWithAssociation.getTermsWithDetails());
    result << "( " << getEnumShortString(m_commonOperatorLevel) << "||";
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        if(isFirst)
        {
            result << getFirstStringIfNegativeAssociation(m_commonOperatorLevel, termWithDetails.association);
            isFirst=false;
        }
        else
        {
            result << getOperatingString(m_commonOperatorLevel, termWithDetails.association);
        }
        result << term.getDebugString() << getEnumShortString(termWithDetails.association);
    }
    result << " )";
    return result.str();
}

void Expression::clear()
{
    m_termsWithAssociation.clear();
    m_commonOperatorLevel = OperatorLevel::Unknown;
}

void Expression::clearAndPutTermInTermsWithAssociation(BaseTerm const& baseTerm)
{
    clear();
    m_termsWithAssociation.putTermWithPositiveAssociation(baseTerm);
}

void Expression::putTermWithAdditionIfNeeded(BaseTerm const& baseTerm)
{
    if(!willHaveNoEffectOnAdditionOrSubtraction(
                getTermConstReferenceFromBaseTerm(baseTerm)))
    {
        if(isEmpty())
        {
            setTerm(baseTerm);
        }
        else
        {
            putTermWithAddition(baseTerm);
        }
    }
}

void Expression::putTermWithSubtractionIfNeeded(BaseTerm const& baseTerm)
{
    if(!willHaveNoEffectOnAdditionOrSubtraction(
                getTermConstReferenceFromBaseTerm(baseTerm)))
    {
        if(isEmpty())
        {
            m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
            putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Negative);
        }
        else
        {
            putTermWithSubtraction(baseTerm);
        }
    }
}

void Expression::putTermWithMultiplicationIfNeeded(BaseTerm const& baseTerm)
{
    if(!willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(
                getTermConstReferenceFromBaseTerm(baseTerm)))
    {
        if(isEmpty())
        {
            setTerm(baseTerm);
        }
        else
        {
            putTermWithMultiplication(baseTerm);
        }
    }
}

void Expression::putTermWithDivisionIfNeeded(BaseTerm const& baseTerm)
{
    if(!willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(
                getTermConstReferenceFromBaseTerm(baseTerm)))
    {
        if(isEmpty())
        {
            m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
            putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Negative);
        }
        else
        {
            putTermWithDivision(baseTerm);
        }
    }
}

void Expression::putTermWithRaiseToPowerIfNeeded(BaseTerm const& baseTerm)
{
    if(!willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(
                getTermConstReferenceFromBaseTerm(baseTerm)))
    {
        if(isEmpty())
        {
            setTerm(baseTerm);
        }
        else
        {
            putTermWithRaiseToPower(baseTerm);
        }
    }
}

void Expression::putPolynomialFirstWithMultiplication(Polynomial const& polynomial)
{
    if(OperatorLevel::AdditionAndSubtraction == m_commonOperatorLevel)
    {
        TermsWithDetails termsWithDetails(m_termsWithAssociation.getTermsWithDetails());
        clear();
        multiplyThenAddOrSubtract(polynomial, termsWithDetails);
    }
    else
    {
        Expression expressionCopy(*this);
        clear();
        multiplyThenAddOrSubtract(polynomial, expressionCopy);
    }
}

void Expression::putPolynomialSecondWithMultiplication(Polynomial const& polynomial)
{
    if(OperatorLevel::AdditionAndSubtraction == m_commonOperatorLevel)
    {
        TermsWithDetails termsWithDetails(m_termsWithAssociation.getTermsWithDetails());
        clear();
        multiplyThenAddOrSubtract(termsWithDetails, polynomial);
    }
    else
    {
        Expression expressionCopy(*this);
        clear();
        multiplyThenAddOrSubtract(expressionCopy, polynomial);
    }
}

void Expression::putExpressionWithMultiplication(Expression const& secondExpression)
{
    if(OperatorLevel::AdditionAndSubtraction == m_commonOperatorLevel
            && OperatorLevel::AdditionAndSubtraction == secondExpression.getCommonOperatorLevel())
    {
        TermsWithDetails termsWithDetails1(m_termsWithAssociation.getTermsWithDetails());
        TermsWithDetails termsWithDetails2(secondExpression.getTermsWithAssociation().getTermsWithDetails());
        clear();
        multiplyThenAddOrSubtract(termsWithDetails1, termsWithDetails2);
    }
    else if(OperatorLevel::AdditionAndSubtraction == m_commonOperatorLevel)
    {
        TermsWithDetails termsWithDetails(m_termsWithAssociation.getTermsWithDetails());
        clear();
        multiplyThenAddOrSubtract(termsWithDetails, getBaseTermConstReferenceFromTerm(Term(secondExpression)));
    }
    else if(OperatorLevel::AdditionAndSubtraction == secondExpression.getCommonOperatorLevel())
    {
        Expression thisExpression(*this);
        clear();
        multiplyThenAddOrSubtract(
                    getBaseTermConstReferenceFromTerm(Term(thisExpression)),
                    secondExpression.getTermsWithAssociation().getTermsWithDetails());
    }
    else
    {
        putTermWithMultiplicationIfNeeded(Term(secondExpression));
    }
}

void Expression::reverseTheAssociationOfTheTerms()
{
    m_termsWithAssociation.reverseTheAssociationOfTheTerms();
}

void Expression::set(OperatorLevel const operatorLevel, TermsWithAssociation const& termsWithPriorityAndAssociation)
{
    m_commonOperatorLevel = operatorLevel;
    m_termsWithAssociation = termsWithPriorityAndAssociation;
}

void Expression::setTerm(BaseTerm const& baseTerm)
{
    *this = createOrCopyExpressionFromATerm(
                getTermConstReferenceFromBaseTerm(baseTerm));
}

void Expression::setCommonOperatorLevel(OperatorLevel const operatorLevel)
{
    m_commonOperatorLevel = operatorLevel;
}

void Expression::factorize()
{
    factorize(*this);
}

void Expression::simplify()
{
    Expression beforeSimplify(*this);

    TermsWithDetails termsToUpdate;
    simplifyAndCopyTerms(termsToUpdate, m_termsWithAssociation.getTermsWithDetails());
    m_termsWithAssociation.clear();
    processTermsBaseOnOperatorLevel(termsToUpdate);

    Expression afterSimplify(*this);
    simplifyFurtherIfNeeded(beforeSimplify, afterSimplify);
}

void Expression::simplifyToACommonDenominator()
{
    simplifyToACommonDenominatorForExpressionAndReturnIfChanged(*this);
    simplify();
    putNegativeExponentsOnDenominator(*this);
}

void Expression::sort()
{
    m_termsWithAssociation.sort();
}

void Expression::factorize(Expression & expression)
{
    TermsWithDetails termsToPut;
    TermsWithDetails & termsWithDetails(expression.m_termsWithAssociation.m_termsWithDetails);
    for(TermsWithDetails::iterator it=termsWithDetails.begin(); it!=termsWithDetails.end(); it++)
    {
        Term & term(getTermReferenceFromSharedPointer(it->baseTermSharedPointer));
        ALBA_PRINT1(term.getDebugString());
        if(term.isExpression())
        {
            Expression & subExpression(term.getExpressionReference());
            factorize(subExpression);
        }
        else if(term.isFunction())
        {
            Expression & inputExpression(term.getFunctionReference().getInputExpressionReference());
            factorize(inputExpression);
        }
        else if(term.isPolynomial())
        {
            factorizePolynomialAndUpdate(expression, termsToPut, term.getPolynomialConstReference(), it->association);
            termsWithDetails.erase(it);
            it--;
        }
    }
    expression.putTermsWithDetails(termsToPut);
}

void Expression::factorizePolynomialAndUpdate(
        Expression & expression,
        TermsWithDetails & termsToPut,
        Polynomial const& polynomial,
        TermAssociationType const overallAssociation)
{
    if(OperatorLevel::Unknown == expression.m_commonOperatorLevel)
    {
        expression.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
    }
    if(OperatorLevel::MultiplicationAndDivision == expression.m_commonOperatorLevel)
    {
        TermsWithDetails factorizedTermsWithDetails;
        factorizePolynomialAndEmplaceInTermsWithDetails(
                    factorizedTermsWithDetails,
                    polynomial,
                    overallAssociation);
        copy(factorizedTermsWithDetails.cbegin(), factorizedTermsWithDetails.cend(), back_inserter(termsToPut));
    }
    else
    {
        TermsWithDetails factorizedTermsWithDetails;
        factorizePolynomialAndEmplaceInTermsWithDetails(
                    factorizedTermsWithDetails,
                    polynomial,
                    TermAssociationType::Positive);
        Expression newSubExpression;
        newSubExpression.setCommonOperatorLevel(OperatorLevel::MultiplicationAndDivision);
        newSubExpression.putTermsWithDetails(factorizedTermsWithDetails);
        termsToPut.emplace_back(getBaseTermConstReferenceFromTerm(Term(newSubExpression)), overallAssociation);
    }
}

void Expression::factorizePolynomialAndEmplaceInTermsWithDetails(
        TermsWithDetails & factorizedTermsWithDetails,
        Polynomial const& polynomial,
        TermAssociationType const overallAssociation){
    Polynomials factorizedPolynomials(Factorization::factorize(polynomial));
    for(Polynomial const& factorizedPolynomial : factorizedPolynomials)
    {        factorizedTermsWithDetails.emplace_back(getBaseTermConstReferenceFromTerm(Term(factorizedPolynomial)), overallAssociation);
    }
}

void Expression::simplifyAndCopyTerms(
        TermsWithDetails & termsToUpdate,
        TermsWithDetails const& termsToCheck)
{
    for(TermWithDetails const& termWithDetails : termsToCheck)
    {
        BaseTerm const& baseTerm(getBaseTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        Term const& term(getTermConstReferenceFromBaseTerm(baseTerm));
        if(term.isExpression())
        {
            Expression expression(term.getExpressionConstReference());
            expression.simplify();
            simplifyAndCopyTermsFromAnExpressionAndSetOperatorLevelIfNeeded(termsToUpdate, expression, termWithDetails.association);
        }
        else if(term.isValueTermAndNotAnExpression())
        {
            termsToUpdate.emplace_back(baseTerm, termWithDetails.association);
        }
    }
}

void Expression::simplifyAndCopyTermsFromAnExpressionAndSetOperatorLevelIfNeeded(
        TermsWithDetails & termsToUpdate,
        Expression const& expression,
        TermAssociationType const association)
{
    OperatorLevel expressionOperatorLevel(expression.getCommonOperatorLevel());
    if(expression.containsOnlyOneTerm() || OperatorLevel::Unknown == m_commonOperatorLevel || expressionOperatorLevel == m_commonOperatorLevel)
    {
        setCommonOperatorLevelIfStillUnknown(expression.getCommonOperatorLevel());
        TermsWithAssociation termsWithAssociation(getTermsWithAssociationAndReverseIfNeeded(expression, association));
        simplifyAndCopyTerms(termsToUpdate, termsWithAssociation.getTermsWithDetails());
    }
    else
    {
        termsToUpdate.emplace_back(getBaseTermConstReferenceFromTerm(Term(expression)), association);
    }
}

void Expression::simplifyFurtherIfNeeded(Expression const& beforeSimplify, Expression const& afterSimplify)
{
    if(beforeSimplify != afterSimplify)
    {
        simplify();
    }
}

bool Expression::simplifyToACommonDenominatorForExpressionAndReturnIfChanged(Expression & expression)
{
    bool isChanged(false);
    if(expression.getCommonOperatorLevel() == OperatorLevel::AdditionAndSubtraction)
    {
        isChanged = tryToAddSubtractTermsOverTermsAndReturnIfChanged(expression);
    }
    else
    {
        simplifyTermsWithDetailsInExpressionToACommonDenominator(expression);
    }
    return isChanged;
}

void Expression::simplifyTermsWithDetailsInExpressionToACommonDenominator(Expression & expression)
{
    bool isChanged(true);
    while(isChanged)
    {
        isChanged=false;
        for(TermWithDetails & termWithDetails : expression.m_termsWithAssociation.m_termsWithDetails)
        {
            Term & term(getTermReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
            if(term.isExpression())
            {
                Expression & subExpression(term.getExpressionReference());
                isChanged = isChanged || simplifyToACommonDenominatorForExpressionAndReturnIfChanged(subExpression);
            }
        }
        if(isChanged)
        {
            expression.simplify();
        }
    }
}

bool Expression::tryToAddSubtractTermsOverTermsAndReturnIfChanged(Expression & addSubtractExpression)
{
    AdditionAndSubtractionOfTermsOverTerms addSubtractTermsOverTerms;
    bool shouldTermsOverTermsBeAddedOrSubtracted(false);
    for(TermWithDetails const& addSubtractTermWithDetails : addSubtractExpression.getTermsWithAssociation().getTermsWithDetails())
    {
        Term const& addSubtractTerm(getTermConstReferenceFromSharedPointer(addSubtractTermWithDetails.baseTermSharedPointer));
        bool isTermAddedOrSubtracted(false);
        if(addSubtractTerm.isExpression())
        {
            Expression expression(addSubtractTerm.getExpressionConstReference());
            if(expression.getCommonOperatorLevel() == OperatorLevel::MultiplicationAndDivision)
            {
                TermsWithDetails numerators;
                TermsWithDetails denominators;
                segregateTermsWithPositiveAndNegativeAssociations(expression.getTermsWithAssociation().getTermsWithDetails(), numerators, denominators);
                if(!denominators.empty())
                {
                    shouldTermsOverTermsBeAddedOrSubtracted=true;
                }
                addSubtractTermsOverTerms.putAsAddOrSubtraction(TermsOverTerms(numerators, denominators), addSubtractTermWithDetails.association);
                isTermAddedOrSubtracted=true;
            }
        }
        if(!isTermAddedOrSubtracted)
        {
            addSubtractTermsOverTerms.putAsAddOrSubtraction(TermsOverTerms({addSubtractTerm}, {}), addSubtractTermWithDetails.association);
        }
    }
    if(shouldTermsOverTermsBeAddedOrSubtracted)
    {
        addSubtractExpression=addSubtractTermsOverTerms.getCombinedExpression();
        addSubtractExpression.simplify();
    }
    return shouldTermsOverTermsBeAddedOrSubtracted;
}

void Expression::putNegativeExponentsOnDenominator(Expression & expression)
{
    TermsWithDetails & termsWithDetails(expression.m_termsWithAssociation.m_termsWithDetails);
    ListOfPolynomialOverPolynomial numeratorsAndDenominators;
    for(TermsWithDetails::iterator it=termsWithDetails.begin(); it!=termsWithDetails.end(); it++)
    {
        Term & term(getTermReferenceFromSharedPointer(it->baseTermSharedPointer));
        if(term.isExpression())
        {
            Expression & subExpression(term.getExpressionReference());
            putNegativeExponentsOnDenominator(subExpression);
        }
        else if(canBeConvertedToPolynomial(term)
                && (termsWithDetails.size() == 1 || expression.getCommonOperatorLevel()==OperatorLevel::MultiplicationAndDivision))
        {
            emplaceToNumeratorsAndDenominators(numeratorsAndDenominators, createPolynomialIfPossible(term), it->association);
            termsWithDetails.erase(it);
            it--;
        }
    }
    putListOfPolynomialOverPolynomialInExpression(expression, numeratorsAndDenominators);
}

void Expression::processTermsBaseOnOperatorLevel(
        TermsWithDetails const& termsToProcess)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
    {
        putTermsWithDetails(termsToProcess);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    {
        processAndSaveTermsForAdditionAndSubtraction(termsToProcess);
        break;
    }
    case OperatorLevel::MultiplicationAndDivision:
    {
        processAndSaveTermsForMultiplicationAndDivision(termsToProcess);
        break;
    }
    case OperatorLevel::RaiseToPower:
    {
        processAndSaveTermsForRaiseToPower(termsToProcess);
        break;
    }
    }
}

void Expression::processAndSaveTermsForAdditionAndSubtraction(
        TermsWithDetails const& termsToProcess)
{
    Term combinedTerm;
    BaseTerm & combinedBaseTerm(getBaseTermReferenceFromTerm(combinedTerm));
    TermsWithDetails termsWithNonExpressions;
    TermsWithDetails termsWithExpressions;
    segregateNonExpressionsAndExpressions(termsToProcess, termsWithNonExpressions, termsWithExpressions);
    accumulateTermsForAdditionAndSubtraction(combinedTerm, termsWithNonExpressions);
    addOrSubtractTermsWithExpressions(combinedBaseTerm, termsWithExpressions);
    setTerm(combinedBaseTerm);
}

void Expression::processAndSaveTermsForMultiplicationAndDivision(
        TermsWithDetails const& termsToProcess)
{
    Term combinedTerm(1);
    BaseTerm & combinedBaseTerm(getBaseTermReferenceFromTerm(combinedTerm));
    TermsWithDetails numerators;
    TermsWithDetails denominators;
    segregateTermsWithPositiveAndNegativeAssociations(termsToProcess, numerators, denominators);
    processNumeratorsAndDenominators(combinedBaseTerm, numerators, denominators);
    setTerm(combinedBaseTerm);
}

void Expression::processAndSaveTermsForRaiseToPower(
        TermsWithDetails const& termsToProcess)
{
    if(!termsToProcess.empty())
    {
        Term combinedTerm;
        Term const& baseOfRaiseToPower=getTermConstReferenceFromSharedPointer(termsToProcess.at(0).baseTermSharedPointer);
        if(baseOfRaiseToPower.isTheValueZero())
        {
            combinedTerm = Term(Constant(0));
        }
        else if(baseOfRaiseToPower.isTheValueOne())
        {
            combinedTerm = Term(1);
        }
        else if(termsToProcess.size() == 2)
        {
            accumulateTermsForRaiseToPower(combinedTerm, termsToProcess);
        }
        else
        {
            TermsWithDetails exponents(termsToProcess.cbegin()+1, termsToProcess.cend());
            saveBaseAndExponentsToTerm(combinedTerm, baseOfRaiseToPower, exponents);
        }
        setTerm(getBaseTermConstReferenceFromTerm(combinedTerm));
    }
}

void Expression::putTermsWithDetails(TermsWithDetails const& termsToSave)
{
    for(TermWithDetails const& termWithDetails : termsToSave)
    {
        m_termsWithAssociation.putTermWithDetails(termWithDetails);
    }
}

void Expression::putTermWithAddition(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
    case OperatorLevel::AdditionAndSubtraction:
    {
        putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Positive);
        break;
    }
    case OperatorLevel::MultiplicationAndDivision:
    case OperatorLevel::RaiseToPower:
    {
        clearAndPutTermInTermsWithAssociation(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
        putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Positive);
        break;
    }
    }
}

void Expression::putTermWithSubtraction(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
    case OperatorLevel::AdditionAndSubtraction:
    {
        putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Negative);
        break;
    }
    case OperatorLevel::MultiplicationAndDivision:
    case OperatorLevel::RaiseToPower:
    {
        clearAndPutTermInTermsWithAssociation(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
        putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Negative);
        break;
    }
    }
}

void Expression::putTermWithMultiplication(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
    case OperatorLevel::MultiplicationAndDivision:
    {
        putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Positive);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    case OperatorLevel::RaiseToPower:
    {
        clearAndPutTermInTermsWithAssociation(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
        putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Positive);
        break;
    }
    }
}

void Expression::putTermWithDivision(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
    case OperatorLevel::MultiplicationAndDivision:
    {
        putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Negative);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    case OperatorLevel::RaiseToPower:
    {
        clearAndPutTermInTermsWithAssociation(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
        putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Negative);
        break;
    }
    }
}

void Expression::putTermWithRaiseToPower(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::RaiseToPower;
    case OperatorLevel::RaiseToPower:
    {
        putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Positive);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    case OperatorLevel::MultiplicationAndDivision:
    {
        clearAndPutTermInTermsWithAssociation(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::RaiseToPower;
        putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Positive);
        break;
    }
    }
}

void Expression::putTermForExpressionAndNonExpressions(
        BaseTerm const& baseTerm,
        TermAssociationType const overallAssociation)
{
    Term const& term(getTermConstReferenceFromBaseTerm(baseTerm));
    if(term.isExpression())
    {
        Expression const & expression(term.getExpressionConstReference());
        if(!expression.isEmpty())
        {
            if(m_commonOperatorLevel == expression.getCommonOperatorLevel() ||
                    OperatorLevel::Unknown == expression.getCommonOperatorLevel())
            {
                putTermsWithAssociation(expression.getTermsWithAssociation(), overallAssociation);
            }
            else
            {
                putTerm(baseTerm, overallAssociation);
            }
        }
    }
    else if(term.isValueTermAndNotAnExpression())
    {
        putTerm(baseTerm, overallAssociation);
    }
}

void Expression::putTerm(BaseTerm const& baseTerm, TermAssociationType const overallAssociation)
{
    if(TermAssociationType::Positive == overallAssociation)
    {
        m_termsWithAssociation.putTermWithPositiveAssociation(baseTerm);
    }
    else if(TermAssociationType::Negative == overallAssociation)
    {
        m_termsWithAssociation.putTermWithNegativeAssociation(baseTerm);
    }
}

void Expression::putTermsWithAssociation(TermsWithAssociation const& termsWithAssociation, TermAssociationType const overallAssociation)
{
    TermsWithAssociation newTermsWithAssociation(termsWithAssociation);
    if(TermAssociationType::Negative == overallAssociation)
    {
        newTermsWithAssociation.reverseTheAssociationOfTheTerms();
    }
    for(TermWithDetails const& termWithDetails : newTermsWithAssociation.getTermsWithDetails())
    {
        m_termsWithAssociation.putTermWithDetails(termWithDetails);
    }
}

void Expression::putListOfPolynomialOverPolynomialInExpression(
        Expression & expression,
        ListOfPolynomialOverPolynomial const& numeratorsAndDenominators)
{
    for(PolynomialOverPolynomial const& numeratorAndDenominator : numeratorsAndDenominators)
    {
        putPolynomialOverPolynomialInExpression(expression, numeratorAndDenominator);
    }
}

void Expression::putPolynomialOverPolynomialInExpression(
        Expression & expression,
        PolynomialOverPolynomial const& numeratorAndDenominator)
{
    expression.putTermWithMultiplicationIfNeeded(
                getBaseTermConstReferenceFromTerm(
                    simplifyAndConvertPolynomialToSimplestTerm(
                        numeratorAndDenominator.getNumerator())));
    expression.putTermWithDivisionIfNeeded(
                getBaseTermConstReferenceFromTerm(
                    simplifyAndConvertPolynomialToSimplestTerm(
                        numeratorAndDenominator.getDenominator())));
}

void Expression::addOrSubtractTermsWithExpressions(
        BaseTerm & combinedBaseTerm,
        TermsWithDetails const& termsWithExpressions) const
{
    AdditionAndSubtractionOfExpressions additionAndSubtraction;
    additionAndSubtraction.putTermsWithDetails(termsWithExpressions);
    additionAndSubtraction.combineExpressionsIfPossible();
    accumulateTermsForAdditionAndSubtraction(getTermReferenceFromBaseTerm(combinedBaseTerm), additionAndSubtraction.getAsTermsWithDetails());
}

void Expression::processNumeratorsAndDenominators(
        BaseTerm & combinedBaseTerm,
        TermsWithDetails const& numerators,
        TermsWithDetails const& denominators) const
{
    TermsOverTerms termsOverTerms(numerators, denominators);
    termsOverTerms.simplify();
    accumulateTermsForMultiplicationAndDivision(
                getTermReferenceFromBaseTerm(combinedBaseTerm),
                termsOverTerms.getNumeratorAndDenominatorAsTermWithDetails());
}

void Expression::saveBaseAndExponentsToTerm(
        BaseTerm & combinedBaseTerm,
        BaseTerm const& baseOfRaiseToPowerBaseTerm,
        TermsWithDetails const& exponents)
{
    Term & combinedTerm(getTermReferenceFromBaseTerm(combinedBaseTerm));
    Term const& baseOfRaiseToPower(getTermConstReferenceFromBaseTerm(baseOfRaiseToPowerBaseTerm));
    Term exponentTerm;
    BaseTerm & exponentBaseTerm(getBaseTermReferenceFromTerm(exponentTerm));
    accumulateTermsForMultiplicationAndDivision(exponentTerm, exponents);
    if(exponentTerm.isTheValueZero())
    {
        combinedTerm = Term(1);
    }
    else if(exponentTerm.isTheValueOne())
    {
        combinedTerm = baseOfRaiseToPower;
    }
    else
    {
        Expression raiseToPowerExpression(createOrCopyExpressionFromATerm(baseOfRaiseToPower));
        raiseToPowerExpression.putTermWithRaiseToPowerIfNeeded(exponentBaseTerm);
        combinedTerm = Term(raiseToPowerExpression);
    }
}

void Expression::multiplyThenAddOrSubtract(
        Polynomial const& polynomial,
        Expression const& expression)
{
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        Expression monomialExpression(createExpressionIfPossible({monomial}));
        monomialExpression.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression)));
        putTermWithAdditionIfNeeded(Term(monomialExpression));
    }
}

void Expression::multiplyThenAddOrSubtract(
        Expression const& expression,
        Polynomial const& polynomial)
{
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        Expression expressionTerm(expression);
        expressionTerm.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(Term(monomial)));
        putTermWithAdditionIfNeeded(Term(expressionTerm));
    }
}

void Expression::multiplyThenAddOrSubtract(
        Polynomial const& polynomial,
        TermsWithDetails const& termsWithDetails)
{
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        multiplyThenAddOrSubtract(getBaseTermConstReferenceFromTerm(Term(monomial)), termsWithDetails);
    }
}

void Expression::multiplyThenAddOrSubtract(
        TermsWithDetails const& termsWithDetails,
        Polynomial const& polynomial)
{
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        multiplyThenAddOrSubtract(termsWithDetails, getBaseTermConstReferenceFromTerm(Term(monomial)));
    }
}

void Expression::multiplyThenAddOrSubtract(
        BaseTerm const& baseTerm,
        TermsWithDetails const& termsWithDetails)
{
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        multiplyThenAddOrSubtract(
                    createOrCopyExpressionFromATerm(getTermConstReferenceFromBaseTerm(baseTerm)),
                    getBaseTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer),
                    termWithDetails.hasPositiveAssociation());
    }
}

void Expression::multiplyThenAddOrSubtract(
        TermsWithDetails const& termsWithDetails,
        BaseTerm const& baseTerm)
{
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        multiplyThenAddOrSubtract(
                    createOrCopyExpressionFromATerm(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer)),
                    baseTerm,
                    termWithDetails.hasPositiveAssociation());
    }
}

void Expression::multiplyThenAddOrSubtract(
        TermsWithDetails const& termsWithDetails1,
        TermsWithDetails const& termsWithDetails2)
{
    for(TermWithDetails const& termWithDetails1 : termsWithDetails1)
    {
        for(TermWithDetails const& termWithDetails2 : termsWithDetails2)
        {
            Term const& term1(getTermConstReferenceFromSharedPointer(termWithDetails1.baseTermSharedPointer));
            Term const& term2(getTermConstReferenceFromSharedPointer(termWithDetails2.baseTermSharedPointer));
            multiplyThenAddOrSubtract(
                        createOrCopyExpressionFromATerm(term1),
                        getBaseTermConstReferenceFromTerm(term2),
                        termWithDetails1.association == termWithDetails2.association);
        }
    }
}

void Expression::multiplyThenAddOrSubtract(
        Expression const& multiplicand,
        BaseTerm const& multiplier,
        bool const isAdd)
{
    Expression expressionToAddOrSubtract(multiplicand);
    expressionToAddOrSubtract.putTermWithMultiplicationIfNeeded(getTermConstReferenceFromBaseTerm(multiplier));
    if(isAdd)
    {
        putTermWithAdditionIfNeeded(Term(expressionToAddOrSubtract));
    }
    else
    {
        putTermWithSubtractionIfNeeded(Term(expressionToAddOrSubtract));
    }
}

void Expression::setCommonOperatorLevelIfStillUnknown(OperatorLevel const operatorLevel)
{
    if(OperatorLevel::Unknown == m_commonOperatorLevel)
    {
        m_commonOperatorLevel = operatorLevel;
    }
}

TermsWithAssociation Expression::getTermsWithAssociationAndReverseIfNeeded(Expression const& expression, TermAssociationType const association)
{
    TermsWithAssociation termsWithAssociation(expression.getTermsWithAssociation());
    if(TermAssociationType::Negative == association)
    {
        termsWithAssociation.reverseTheAssociationOfTheTerms();
    }
    return termsWithAssociation;
}

void Expression::emplaceToNumeratorsAndDenominators(
        ListOfPolynomialOverPolynomial & numeratorsAndDenominators,
        Polynomial const& polynomial,
        TermAssociationType const termAssociationType)
{
    Polynomial numerator(polynomial);
    Polynomial denominator(createPolynomialFromConstant(1));
    if(TermAssociationType::Negative == termAssociationType)
    {
        swap(numerator, denominator);
    }
    PolynomialOverPolynomial numeratorAndDenominator(numerator, denominator);
    numeratorAndDenominator.simplify();
    numeratorsAndDenominators.emplace_back(numeratorAndDenominator);
}

ostream & operator<<(ostream & out, Expression const& expression)
{
    out << expression.getDisplayableString();
    return out;
}

}

}
