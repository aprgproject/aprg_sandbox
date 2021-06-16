#include "Expression.hpp"

#include <Factorization.hpp>
#include <Optional/AlbaOptional.hpp>
#include <PerformOperations.hpp>
#include <Term.hpp>
#include <TermOperators.hpp>
#include <Utilities.hpp>

#include <algorithm>
#include <sstream>

using namespace alba::equation::Factorization;
using namespace std;
using TermWithDetails=alba::equation::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithAssociation::TermsWithDetails;

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
    m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
}

Expression::~Expression()
{}

bool Expression::operator==(Expression const& second) const
{
    return m_commonOperatorLevel == second.m_commonOperatorLevel
            && m_termsWithPriorityAndAssociation==second.m_termsWithPriorityAndAssociation;
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
        return m_termsWithPriorityAndAssociation < second.m_termsWithPriorityAndAssociation;
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
    return m_termsWithPriorityAndAssociation.isEmpty();
}

bool Expression::containsOnlyOneTerm() const
{
    return 1 == m_termsWithPriorityAndAssociation.getSize();
}

OperatorLevel Expression::getCommonOperatorLevel() const
{
    return m_commonOperatorLevel;
}

BaseTerm const& Expression::getFirstTermConstReference() const
{
    return m_termsWithPriorityAndAssociation.getFirstTermConstReference();
}

TermsWithAssociation const& Expression::getTerms() const
{
    return m_termsWithPriorityAndAssociation;
}

TermsWithAssociation Expression::getTermsWithDetailsThatSatisfiesCondition(
        ConditionFunctionForTermsWithDetails const& conditionFunction) const
{
    TermsWithAssociation termsWithOnlyExpressions;
    TermsWithDetails const& termsWithDetails(m_termsWithPriorityAndAssociation.getTermsWithDetails());
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
    TermsWithDetails const& termsWithDetails(m_termsWithPriorityAndAssociation.getTermsWithDetails());
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
    TermsWithDetails const& termsWithDetails(m_termsWithPriorityAndAssociation.getTermsWithDetails());
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
        result << getEnumShortString(termWithDetails.association) << term.getDebugString();
    }
    result << " )";
    return result.str();
}

void Expression::clear()
{
    m_termsWithPriorityAndAssociation.clear();
    m_commonOperatorLevel = OperatorLevel::Unknown;
}

void Expression::clearAndPutTermInTermsWithAssociation(BaseTerm const& baseTerm)
{
    clear();
    m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
}

void Expression::putTermWithAdditionIfNeeded(BaseTerm const& baseTerm)
{
    if(!willHaveNoEffectOnAdditionOrSubtraction(
                getTermConstReferenceFromBaseTerm(baseTerm)))    {
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
                getTermConstReferenceFromBaseTerm(baseTerm)))    {
        if(isEmpty())
        {
            m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;            putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Negative);
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
                getTermConstReferenceFromBaseTerm(baseTerm)))    {
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
                getTermConstReferenceFromBaseTerm(baseTerm)))    {
        if(isEmpty())
        {
            m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;            putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Negative);
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
                getTermConstReferenceFromBaseTerm(baseTerm)))    {
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
    if(OperatorLevel::AdditionAndSubtraction == m_commonOperatorLevel)    {
        TermsWithDetails termsWithDetails(m_termsWithPriorityAndAssociation.getTermsWithDetails());
        clear();
        for(Monomial const& monomial : polynomial.getMonomialsConstReference())
        {
            for(TermWithDetails const& termWithDetails : termsWithDetails)
            {
                multiplyThenPutTermAsAddIfTrueAndAsSubtractIfFalse(
                            createOrCopyExpressionFromATerm(Term(monomial)),
                            getBaseTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer),
                            termWithDetails.hasPositiveAssociation());
            }
        }
    }
    else
    {
        Term termExpression(*this);
        clear();
        for(Monomial const& monomial : polynomial.getMonomialsConstReference())
        {
            Expression monomialExpression(createExpressionIfPossible(Terms{monomial}));
            monomialExpression.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(termExpression));
            putTermWithAdditionIfNeeded(Term(monomialExpression));
        }

    }}

void Expression::putPolynomialSecondWithMultiplication(Polynomial const& polynomial)
{    if(OperatorLevel::AdditionAndSubtraction == m_commonOperatorLevel)
    {
        TermsWithDetails termsWithDetails(m_termsWithPriorityAndAssociation.getTermsWithDetails());
        clear();
        for(Monomial const& monomial : polynomial.getMonomialsConstReference())
        {
            for(TermWithDetails const& termWithDetails : termsWithDetails)
            {
                multiplyThenPutTermAsAddIfTrueAndAsSubtractIfFalse(
                            createOrCopyExpressionFromATerm(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer)),
                            getBaseTermConstReferenceFromTerm(Term(monomial)),
                            termWithDetails.hasPositiveAssociation());
            }
        }
    }
    else
    {
        Expression expressionCopy(*this);
        clear();
        for(Monomial const& monomial : polynomial.getMonomialsConstReference())
        {
            Expression expressionTerm(expressionCopy);
            expressionTerm.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(Term(monomial)));
            putTermWithAdditionIfNeeded(Term(expressionTerm));
        }
    }
}
void Expression::putExpressionWithMultiplication(Expression const& expression)
{
    if(OperatorLevel::AdditionAndSubtraction == m_commonOperatorLevel            && OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel())
    {
        TermsWithDetails termsWithDetails1(m_termsWithPriorityAndAssociation.getTermsWithDetails());
        TermsWithDetails termsWithDetails2(expression.getTerms().getTermsWithDetails());
        clear();
        for(TermWithDetails const& termWithDetails1 : termsWithDetails1)
        {
            for(TermWithDetails const& termWithDetails2 : termsWithDetails2)
            {
                Term const& term1(getTermConstReferenceFromSharedPointer(termWithDetails1.baseTermSharedPointer));
                Term const& term2(getTermConstReferenceFromSharedPointer(termWithDetails2.baseTermSharedPointer));
                multiplyThenPutTermAsAddIfTrueAndAsSubtractIfFalse(
                            createOrCopyExpressionFromATerm(term1),
                            getBaseTermConstReferenceFromTerm(term2),
                            termWithDetails1.association == termWithDetails2.association);
            }
        }
    }
    else if(OperatorLevel::AdditionAndSubtraction == m_commonOperatorLevel)
    {
        TermsWithDetails termsWithDetails(m_termsWithPriorityAndAssociation.getTermsWithDetails());
        clear();
        for(TermWithDetails const& termWithDetails : termsWithDetails)
        {
            multiplyThenPutTermAsAddIfTrueAndAsSubtractIfFalse(
                        createOrCopyExpressionFromATerm(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer)),
                        getBaseTermConstReferenceFromTerm(Term(expression)),
                        termWithDetails.hasPositiveAssociation());
        }
    }
    else if(OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel())
    {
        Expression expressionCopy(*this);
        clear();
        for(TermWithDetails const& termWithDetails : expression.getTerms().getTermsWithDetails())
        {
            multiplyThenPutTermAsAddIfTrueAndAsSubtractIfFalse(
                        expressionCopy,
                        getBaseTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer),
                        termWithDetails.hasPositiveAssociation());
        }
    }
    else
    {
        putTermWithMultiplicationIfNeeded(Term(expression));
    }
}
void Expression::reverseTheAssociationOfTheTerms()
{
    m_termsWithPriorityAndAssociation.reverseTheAssociationOfTheTerms();}

void Expression::set(OperatorLevel const operatorLevel, TermsWithAssociation const& termsWithPriorityAndAssociation)
{
    m_commonOperatorLevel = operatorLevel;
    m_termsWithPriorityAndAssociation = termsWithPriorityAndAssociation;
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

void Expression::simplify()
{
    Expression beforeSimplify(*this);

    TermsWithDetails termsToUpdate;
    simplifyAndCopyTerms(termsToUpdate, m_termsWithPriorityAndAssociation.getTermsWithDetails());
    m_termsWithPriorityAndAssociation.clear();
    processTermsBaseOnOperatorLevel(termsToUpdate);

    Expression afterSimplify(*this);
    simplifyFurtherIfNeeded(beforeSimplify, afterSimplify);
}

void Expression::simplifyToCommonDenominators()
{
    simplify();

    Terms denominatorTerms;
    retrieveDenominatorTerms(denominatorTerms, *this);
    for(Term const& denominatorTerm : denominatorTerms)
    {
        putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(denominatorTerm));
    }

    simplify();}

void Expression::sort()
{    m_termsWithPriorityAndAssociation.sort();
}

void Expression::substituteVariablesToValues(VariablesToValuesMap const& variableValueMap)
{
    m_termsWithPriorityAndAssociation.substituteVariablesToValues(variableValueMap);
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
        else if(term.isValueTermButNotAnExpression())
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
        if(OperatorLevel::Unknown == m_commonOperatorLevel)
        {
            m_commonOperatorLevel = expression.getCommonOperatorLevel();
        }
        TermsWithAssociation termsWithAssociation(expression.getTerms());
        if(TermAssociationType::Negative == association)
        {
            termsWithAssociation.reverseTheAssociationOfTheTerms();
        }
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
    segregateNonExpressionsAndExpressions(termsWithNonExpressions, termsWithExpressions, termsToProcess);
    accumulateTermsForAdditionAndSubtraction(combinedBaseTerm, termsWithNonExpressions);
    accumulateTermsForAdditionAndSubtractionForTermsWithExpressions(combinedBaseTerm, termsWithExpressions);
    setTerm(combinedBaseTerm);
}

void Expression::processAndSaveTermsForMultiplicationAndDivision(
        TermsWithDetails const& termsToProcess)
{
    Term combinedTerm(1);
    BaseTerm & combinedBaseTerm(getBaseTermReferenceFromTerm(combinedTerm));
    TermsWithDetails termsWithNonExpressions;
    TermsWithDetails termsWithExpressions;
    TermsWithDetails nonExpressionsForNumerator;
    TermsWithDetails nonExpressionsForDenominator;
    TermsWithDetails expressionsForNumerator;
    TermsWithDetails expressionsForDenominator;
    segregateNonExpressionsAndExpressions(termsWithNonExpressions, termsWithExpressions, termsToProcess);
    segregateNumeratorAndDenominatorForMultiplicationAndDivision(nonExpressionsForNumerator, nonExpressionsForDenominator, termsWithNonExpressions);
    segregateNumeratorAndDenominatorForMultiplicationAndDivision(expressionsForNumerator, expressionsForDenominator, termsWithExpressions);
    processNonExpressionsForMultiplicationAndDivision(getBaseTermReferenceFromTerm(combinedTerm), nonExpressionsForNumerator, nonExpressionsForDenominator);
    processExpressionForMultiplicationAndDivision(combinedBaseTerm, expressionsForNumerator, expressionsForDenominator);
    //processAllForMultiplicationAndDivision(combinedBaseTerm, nonExpressionsForNumerator, nonExpressionsForDenominator, expressionsForNumerator, expressionsForDenominator);
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
        else
        {
            Term exponentTerm;
            TermsWithDetails exponents(termsToProcess.cbegin()+1, termsToProcess.cend());
            BaseTerm & exponentBaseTerm(getBaseTermReferenceFromTerm(exponentTerm));
            accumulateTermsForMultiplicationAndDivision(exponentBaseTerm, exponents);
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
        }        setTerm(getBaseTermConstReferenceFromTerm(combinedTerm));
    }
}
void Expression::accumulateTermsForAdditionAndSubtraction(
        BaseTerm & combinedBaseTerm,
        TermsWithDetails const& termsToCombine) const
{
    Term & combinedTerm(getTermReferenceFromBaseTerm(combinedBaseTerm));
    bool isFirst(willHaveNoEffectOnAdditionOrSubtraction(combinedTerm));
    for(TermWithDetails const& termWithDetails : termsToCombine)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        if(willHaveNoEffectOnAdditionOrSubtraction(term))
        {
            continue;
        }
        else if(isFirst)
        {
            if(termWithDetails.hasPositiveAssociation())
            {
                combinedTerm = term;
            }
            else if(termWithDetails.hasNegativeAssociation())
            {
                combinedTerm = -term;
            }
            isFirst=false;
        }
        else
        {
            accumulateAndDoOperationOnTermDetails(combinedTerm, OperatorLevel::AdditionAndSubtraction, termWithDetails);
        }
    }
}

void Expression::accumulateTermsForMultiplicationAndDivision(
        BaseTerm & combinedBaseTerm,
        TermsWithDetails const& termsToCombine) const
{
    Term & combinedTerm(getTermReferenceFromBaseTerm(combinedBaseTerm));
    bool isFirst(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(combinedTerm));
    if(combinedTerm.isTheValueZero())
    {
        combinedTerm = Term(Constant(0));
    }
    else
    {
        for(TermWithDetails const& termWithDetails : termsToCombine)
        {
            Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
            if(term.isTheValueZero() && termWithDetails.hasPositiveAssociation())
            {
                combinedTerm = Term(Constant(0));
                break;
            }
            if(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(term))
            {
                continue;
            }
            else if(isFirst)
            {
                if(termWithDetails.hasPositiveAssociation())
                {
                    combinedTerm = term;
                }
                else if(termWithDetails.hasNegativeAssociation())
                {
                    combinedTerm = Term(Constant(1))/term;
                }
                isFirst=false;
            }
            else
            {
                accumulateAndDoOperationOnTermDetails(combinedTerm, OperatorLevel::MultiplicationAndDivision, termWithDetails);
            }
        }
    }
}

void Expression::accumulateTermsForRaiseToPower(
        BaseTerm & combinedBaseTerm,
        TermsWithDetails const& termsToCombine) const
{
    Term & combinedTerm(getTermReferenceFromBaseTerm(combinedBaseTerm));
    bool isFirst(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(combinedTerm));
    for(TermWithDetails const& termWithDetails : termsToCombine)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        if(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(term))
        {
            continue;
        }
        else if(isFirst)
        {
            combinedTerm = term;
            isFirst=false;
        }
        else
        {
            accumulateAndDoOperationOnTermDetails(combinedTerm, OperatorLevel::RaiseToPower, termWithDetails);
        }
    }
}

void Expression::segregateNonExpressionsAndExpressions(
        TermsWithDetails & termsWithNonExpressions,
        TermsWithDetails & termsWithExpressions,
        TermsWithDetails const& termsToSegregate) const
{
    for(TermWithDetails const& termToSegregate : termsToSegregate)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(termToSegregate.baseTermSharedPointer));
        if(term.isExpression())
        {
            termsWithExpressions.emplace_back(termToSegregate);
        }
        if(term.isValueTermButNotAnExpression())
        {
            termsWithNonExpressions.emplace_back(termToSegregate);
        }
    }
}

void Expression::segregateNumeratorAndDenominatorForMultiplicationAndDivision(
        TermsWithDetails & termsForNumerator,
        TermsWithDetails & termsForDenominator,
        TermsWithDetails const& termsToSegregate) const
{
    for(TermWithDetails const& termToSegregate : termsToSegregate)
    {
        if(termToSegregate.hasPositiveAssociation())
        {
            termsForNumerator.emplace_back(termToSegregate);
        }
        if(termToSegregate.hasNegativeAssociation())
        {
            termsForDenominator.emplace_back(termToSegregate);
        }
    }
}

void Expression::putTermsWithDetails(TermsWithDetails const& termsToSave)
{
    for(TermWithDetails const& termWithDetails : termsToSave)
    {
        m_termsWithPriorityAndAssociation.putTermWithDetails(termWithDetails);
    }
}

void Expression::putTermWithAddition(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
    case OperatorLevel::AdditionAndSubtraction:
    {        putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Positive);
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
    {    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
    case OperatorLevel::AdditionAndSubtraction:
    {        putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Negative);
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
    {    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
    case OperatorLevel::MultiplicationAndDivision:
    {        putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Positive);
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
    {    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
    case OperatorLevel::MultiplicationAndDivision:
    {        putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Negative);
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
    {    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::RaiseToPower;
    case OperatorLevel::RaiseToPower:
    {        putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Positive);
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
                putTermsWithAssociation(expression.getTerms(), overallAssociation);
            }
            else
            {
                putTerm(baseTerm, overallAssociation);
            }
        }
    }
    else if(term.isValueTermButNotAnExpression())
    {
        putTerm(baseTerm, overallAssociation);
    }
}

void Expression::putTerm(BaseTerm const& baseTerm, TermAssociationType const overallAssociation)
{
    if(TermAssociationType::Positive == overallAssociation)
    {
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
    }
    else if(TermAssociationType::Negative == overallAssociation)
    {
        m_termsWithPriorityAndAssociation.putTermWithNegativeAssociation(baseTerm);
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
        m_termsWithPriorityAndAssociation.putTermWithDetails(termWithDetails);
    }
}

void Expression::accumulateTermsForAdditionAndSubtractionForTermsWithExpressions(
        BaseTerm & combinedBaseTerm,
        TermsWithDetails const& termsWithExpressions) const
{
    TermsWithDetails newTermsWithExpressions(termsWithExpressions);
    for(TermsWithDetails::iterator first = newTermsWithExpressions.begin();
        first != newTermsWithExpressions.end();
        first++)
    {
        TermsWithDetails::iterator second=first;
        second++;
        for(;second != newTermsWithExpressions.end();  second++)
        {
            if(mergeForAdditionAndSubtractionAndReturnIfMerged(*first, *second))
            {
                newTermsWithExpressions.erase(second);
                second=first;
            }
        }
    }
    accumulateTermsForAdditionAndSubtraction(combinedBaseTerm, newTermsWithExpressions);
}

bool Expression::mergeForAdditionAndSubtractionAndReturnIfMerged(
        TermWithDetails & termExpressionWithDetails1,
        TermWithDetails & termExpressionWithDetails2) const
{
    bool isMerged(false);
    Expression uniqueExpression1, uniqueExpression2;
    Term mergeTerm1, mergeTerm2;
    retrieveUniqueExpressionsAndMergeTerms(uniqueExpression1, uniqueExpression2, mergeTerm1, mergeTerm2, termExpressionWithDetails1, termExpressionWithDetails2);
    if(canBeMergedForAdditionAndSubtraction(uniqueExpression1, uniqueExpression2, mergeTerm1, mergeTerm2))
    {
        Term resultMergeTerm;
        TermsWithDetails termsToMerge;
        termsToMerge.emplace_back(getBaseTermConstReferenceFromTerm(mergeTerm1), termExpressionWithDetails1.association);
        termsToMerge.emplace_back(getBaseTermConstReferenceFromTerm(mergeTerm2), termExpressionWithDetails2.association);
        accumulateTermsForAdditionAndSubtraction(resultMergeTerm, termsToMerge);
        termExpressionWithDetails1 = TermWithDetails(
                    getBaseTermConstReferenceFromTerm(resultMergeTerm*Term(uniqueExpression1)),
                    TermAssociationType::Positive);
        termExpressionWithDetails2.clear();
        isMerged = true;
    }
    return isMerged;
}

void Expression::retrieveUniqueExpressionsAndMergeTerms(
        Expression & uniqueExpression1,
        Expression & uniqueExpression2,
        BaseTerm & mergeTerm1,
        BaseTerm & mergeTerm2,
        TermWithDetails const& termExpressionWithDetails1,
        TermWithDetails const& termExpressionWithDetails2) const
{
    Term const& termExpression1(getTermConstReferenceFromSharedPointer(termExpressionWithDetails1.baseTermSharedPointer));
    Term const& termExpression2(getTermConstReferenceFromSharedPointer(termExpressionWithDetails2.baseTermSharedPointer));
    Expression expression1(createOrCopyExpressionFromATerm(termExpression1));
    Expression expression2(createOrCopyExpressionFromATerm(termExpression2));
    uniqueExpression1 = getUniqueExpressionForAdditionOrSubtractionMergeChecking(expression1);
    uniqueExpression2 = getUniqueExpressionForAdditionOrSubtractionMergeChecking(expression2);
    uniqueExpression1.sort();
    uniqueExpression2.sort();
    accumulateMergeTermForAdditionOrSubtractionMergeChecking(mergeTerm1, expression1);
    accumulateMergeTermForAdditionOrSubtractionMergeChecking(mergeTerm2, expression2);
}

Expression Expression::getUniqueExpressionForAdditionOrSubtractionMergeChecking(Expression const& expression) const
{
    Expression result;
    if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        TermsWithAssociation uniqueExpressions(
                    expression.getTermsWithDetailsThatSatisfiesCondition(
                        [](TermWithDetails const& termWithDetails) -> bool {
                        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
                        return termWithDetails.hasNegativeAssociation() || term.isExpression();
                    }));
        result.set(OperatorLevel::MultiplicationAndDivision, uniqueExpressions);
        result.simplify();
    }
    else if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
    {
        result = expression;
    }
    return result;
}

void Expression::accumulateMergeTermForAdditionOrSubtractionMergeChecking(BaseTerm & combinedBaseTerm, Expression const& expression) const
{
    Term & combinedTerm(getTermReferenceFromBaseTerm(combinedBaseTerm));
    if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        TermsWithAssociation termsToBeMerged(
                    expression.getTermsWithDetailsThatSatisfiesCondition(
                        [](TermWithDetails const& termWithDetails) -> bool {
                        Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
                        return !(termWithDetails.hasNegativeAssociation() || term.isExpression());
                    }));
        accumulateTermsForAdditionAndSubtraction(combinedBaseTerm, termsToBeMerged.getTermsWithDetails());
    }
    else if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
    {
        combinedTerm = Term(1);
    }
}

bool Expression::canBeMergedForAdditionAndSubtraction(
        Expression const& uniqueExpression1,
        Expression const& uniqueExpression2,
        BaseTerm const& mergeTerm1,
        BaseTerm const& mergeTerm2) const
{
    return uniqueExpression1 == uniqueExpression2 &&
            canBeMergedByAdditionOrSubtraction(
                getTermConstReferenceFromBaseTerm(mergeTerm1), getTermConstReferenceFromBaseTerm(mergeTerm2));
}

void Expression::processNonExpressionsForMultiplicationAndDivision(
        BaseTerm & combinedBaseTerm,
        TermsWithDetails const& nonExpressionsForNumerator,
        TermsWithDetails const& nonExpressionsForDenominator) const
{
    Term & combinedTerm(getTermReferenceFromBaseTerm(combinedBaseTerm));
    Term nonExpressionCombinedTermNumerator(1);
    accumulateTermsForMultiplicationAndDivision(getBaseTermReferenceFromTerm(nonExpressionCombinedTermNumerator), nonExpressionsForNumerator);
    if(!nonExpressionsForNumerator.empty())
    {
        combinedTerm = nonExpressionCombinedTermNumerator;
    }
    if(!nonExpressionsForDenominator.empty())
    {
        TermsWithDetails newDenominators(nonExpressionsForDenominator);
        Term nonExpressionCombinedTermDenominator;
        for(TermWithDetails & termWithDetails : newDenominators)
        {
            termWithDetails.association = TermAssociationType::Positive;
        }
        accumulateTermsForMultiplicationAndDivision(getBaseTermReferenceFromTerm(nonExpressionCombinedTermDenominator), newDenominators);
        PolynomialOverPolynomial numeratorAndDenominator(
                    createPolynomialIfPossible(nonExpressionCombinedTermNumerator),
                    createPolynomialIfPossible(nonExpressionCombinedTermDenominator));
        numeratorAndDenominator.simplify();
        combinedTerm = simplifyAndConvertPolynomialToSimplestTerm(numeratorAndDenominator.getNumerator())
                /simplifyAndConvertPolynomialToSimplestTerm(numeratorAndDenominator.getDenominator());
    }
}

void Expression::processExpressionForMultiplicationAndDivision(
        BaseTerm & combinedBaseTerm,
        TermsWithDetails const& expressionsForNumerator,
        TermsWithDetails const& expressionsForDenominator) const
{
    TermsWithDetails numerator(expressionsForNumerator);
    TermsWithDetails denominator(expressionsForDenominator);
    removeSameTermsInNumeratorAndDenominatorForMultiplicationAndDivision(numerator, denominator);
    accumulateTermsForMultiplicationAndDivision(combinedBaseTerm, numerator);
    accumulateTermsForMultiplicationAndDivision(combinedBaseTerm, denominator);
}

void Expression::removeSameTermsInNumeratorAndDenominatorForMultiplicationAndDivision(
        TermsWithDetails & expressionsForNumerator,
        TermsWithDetails & expressionsForDenominator) const
{
    bool areSomeTermsCancelled(false);
    for(TermsWithDetails::iterator first = expressionsForNumerator.begin();
        first != expressionsForNumerator.end();
        first++)
    {
        for(TermsWithDetails::iterator second = expressionsForDenominator.begin();
            second != expressionsForDenominator.end();
            second++)
        {
            Term & termExpression1(getTermReferenceFromSharedPointer(first->baseTermSharedPointer));
            Term & termExpression2(getTermReferenceFromSharedPointer(second->baseTermSharedPointer));
            if(termExpression1 == termExpression2)
            {
                expressionsForNumerator.erase(first);
                expressionsForDenominator.erase(second);
                first--;
                second--;
                areSomeTermsCancelled = true;
            }
        }
    }
    if(expressionsForNumerator.empty() && expressionsForDenominator.empty() && areSomeTermsCancelled)
    {
        expressionsForNumerator.emplace_back(getBaseTermConstReferenceFromTerm(Term(1)), TermAssociationType::Positive);
    }
}

void Expression::multiplyThenPutTermAsAddIfTrueAndAsSubtractIfFalse(
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
}

}