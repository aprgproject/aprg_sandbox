#include "Expression.hpp"

#include <Optional/AlbaOptional.hpp>
#include <PerformOperation.hpp>
#include <PolynomialOverPolynomial.hpp>
#include <Term.hpp>
#include <TermOperators.hpp>
#include <Utilities.hpp>

#include <algorithm>
#include <sstream>

using namespace std;
using AssociationType=alba::equation::TermsWithPriorityAndAssociation::AssociationType;
using TermWithDetails=alba::equation::TermsWithPriorityAndAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithPriorityAndAssociation::TermsWithDetails;
using ListOfTermsWithDetails=alba::equation::TermsWithPriorityAndAssociation::ListOfTermsWithDetails;

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

TermsWithPriorityAndAssociation const& Expression::getTerms() const
{
    return m_termsWithPriorityAndAssociation;
}

TermsWithPriorityAndAssociation Expression::getTermsWithDetailsThatSatisfiesCondition(
        ConditionFunctionForTermsWithDetails const& conditionFunction) const
{
    TermsWithPriorityAndAssociation termsWithOnlyExpressions;
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
        result << getEnumShortString(termWithDetails.association) << term.getDisplayableString();
    }
    result << " )";
    return result.str();
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

void Expression::sort()
{
    m_termsWithPriorityAndAssociation.sort();
}

void Expression::addTerm(BaseTerm const& baseTerm)
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
            addTermForNonEmptyTerms(baseTerm);
        }
    }
}

void Expression::subtractTerm(BaseTerm const& baseTerm)
{
    if(!willHaveNoEffectOnAdditionOrSubtraction(
                getTermConstReferenceFromBaseTerm(baseTerm)))
    {
        if(isEmpty())
        {
            m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
            putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Negative);
        }
        else
        {
            subtractTermForNonEmptyTerms(baseTerm);
        }
    }
}

void Expression::multiplyTerm(BaseTerm const& baseTerm)
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
            multiplyTermForNonEmptyTerms(baseTerm);
        }
    }
}

void Expression::multiplyPolynomialFirst(Polynomial const& polynomial)
{
    if(OperatorLevel::AdditionAndSubtraction == m_commonOperatorLevel)
    {
        TermsWithDetails termsWithDetails(m_termsWithPriorityAndAssociation.getTermsWithDetails());
        clear();
        for(Monomial const& monomial : polynomial.getMonomialsConstReference())
        {
            for(TermWithDetails const& termWithDetails : termsWithDetails)
            {
                multiplyThenAddTermIfTrueAndSubtractIfFalse(
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
            monomialExpression.multiplyTerm(getBaseTermConstReferenceFromTerm(termExpression));
            addTerm(Term(monomialExpression));
        }

    }
}

void Expression::multiplyPolynomialSecond(Polynomial const& polynomial)
{
    if(OperatorLevel::AdditionAndSubtraction == m_commonOperatorLevel)
    {
        TermsWithDetails termsWithDetails(m_termsWithPriorityAndAssociation.getTermsWithDetails());
        clear();
        for(Monomial const& monomial : polynomial.getMonomialsConstReference())
        {
            for(TermWithDetails const& termWithDetails : termsWithDetails)
            {
                multiplyThenAddTermIfTrueAndSubtractIfFalse(
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
            expressionTerm.multiplyTerm(getBaseTermConstReferenceFromTerm(Term(monomial)));
            addTerm(Term(expressionTerm));
        }
    }
}

void Expression::multiplyExpression(Expression const& expression)
{
    if(OperatorLevel::AdditionAndSubtraction == m_commonOperatorLevel
            && OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel())
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
                multiplyThenAddTermIfTrueAndSubtractIfFalse(
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
            multiplyThenAddTermIfTrueAndSubtractIfFalse(
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
            multiplyThenAddTermIfTrueAndSubtractIfFalse(
                        expressionCopy,
                        getBaseTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer),
                        termWithDetails.hasPositiveAssociation());
        }
    }
    else
    {
        multiplyTerm(Term(expression));
    }
}

void Expression::divideTerm(BaseTerm const& baseTerm)
{
    if(!willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(
                getTermConstReferenceFromBaseTerm(baseTerm)))
    {
        if(isEmpty())
        {
            m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
            putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Negative);
        }
        else
        {
            divideTermForNonEmptyTerms(baseTerm);
        }
    }
}

void Expression::raiseToPowerTerm(BaseTerm const& baseTerm)
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
            raiseToPowerTermForNonEmptyTerms(baseTerm);
        }
    }
}

void Expression::set(OperatorLevel const operatorLevel, TermsWithPriorityAndAssociation termsWithPriorityAndAssociation)
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

void Expression::reverseTheAssociationOfTheTerms()
{
    m_termsWithPriorityAndAssociation.reverseTheAssociationOfTheTerms();
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

void Expression::simplifyFurtherIfNeeded(Expression const& beforeSimplify, Expression const& afterSimplify)
{
    if(beforeSimplify != afterSimplify)
    {
        simplify();
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
            simplifyAndCopyTermsFromAnExpression(termsToUpdate, expression, termWithDetails.association);
        }
        else if(term.isValueTermButNotAnExpression())
        {
            termsToUpdate.emplace_back(baseTerm, termWithDetails.association);
        }
    }
}

void Expression::simplifyAndCopyTermsFromAnExpression(
        TermsWithDetails & termsToUpdate,
        Expression const& expression,
        AssociationType const association)
{
    OperatorLevel expressionOperatorLevel(expression.getCommonOperatorLevel());
    if(expression.containsOnlyOneTerm() || OperatorLevel::Unknown == m_commonOperatorLevel || expressionOperatorLevel == m_commonOperatorLevel)
    {
        if(OperatorLevel::Unknown == m_commonOperatorLevel)
        {
            m_commonOperatorLevel = expression.getCommonOperatorLevel();
        }
        TermsWithPriorityAndAssociation termsWithAssociation(expression.getTerms());
        if(AssociationType::Negative == association)
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
    Term combinedTerm;
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


    Term nonExpressionCombinedTermNumerator;
    accumulateTermsForMultiplicationAndDivision(getBaseTermReferenceFromTerm(nonExpressionCombinedTermNumerator), nonExpressionsForNumerator);
    if(nonExpressionsForNumerator.empty())
    {
        combinedTerm = Term(1);
    }
    else
    {
        combinedTerm = nonExpressionCombinedTermNumerator;
    }
    if(!nonExpressionsForDenominator.empty())
    {
        Term nonExpressionCombinedTermDenominator;
        for(TermWithDetails & termWithDetails : nonExpressionsForDenominator)
        {
            termWithDetails.association = AssociationType::Positive;
        }
        accumulateTermsForMultiplicationAndDivision(getBaseTermReferenceFromTerm(nonExpressionCombinedTermDenominator), nonExpressionsForDenominator);
        PolynomialOverPolynomial numeratorAndDenominator(
                    createPolynomialIfPossible(nonExpressionCombinedTermNumerator),
                    createPolynomialIfPossible(nonExpressionCombinedTermDenominator));
        numeratorAndDenominator.simplify();
        combinedTerm = simplifyAndConvertPolynomialToSimplestTerm(numeratorAndDenominator.getNumerator())
                /simplifyAndConvertPolynomialToSimplestTerm(numeratorAndDenominator.getDenominator());
    }

    removeSameTermsInNumeratorAndDenominatorForMultiplicationAndDivision(expressionsForNumerator, expressionsForDenominator);

    accumulateTermsForMultiplicationAndDivision(combinedBaseTerm, expressionsForNumerator);
    accumulateTermsForMultiplicationAndDivision(combinedBaseTerm, expressionsForDenominator);
    setTerm(combinedBaseTerm);
}

void Expression::processAndSaveTermsForRaiseToPower(
        TermsWithDetails const& termsToProcess)
{
    Term combinedTerm;
    BaseTerm & combinedBaseTerm(getBaseTermReferenceFromTerm(combinedTerm));
    accumulateTermsForRaiseToPower(combinedBaseTerm, termsToProcess);
    setTerm(combinedBaseTerm);
}

void Expression::segregateNonExpressionsAndExpressions(
        TermsWithDetails & termsWithNonExpressions,
        TermsWithDetails & termsWithExpressions,
        TermsWithDetails const& termsToSegregate)
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
        TermsWithDetails const& termsToSegregate)
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

void Expression::accumulateTermsForAdditionAndSubtraction(
        BaseTerm & combinedBaseTerm,
        TermsWithDetails const& termsToCombine)
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
            accumulateAndDoOperationOnTermDetails(combinedTerm, m_commonOperatorLevel, termWithDetails);
        }
    }
}

void Expression::accumulateTermsForMultiplicationAndDivision(
        BaseTerm & combinedBaseTerm,
        TermsWithDetails const& termsToCombine)
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
                accumulateAndDoOperationOnTermDetails(combinedTerm, m_commonOperatorLevel, termWithDetails);
            }
        }
    }
}

void Expression::accumulateTermsForRaiseToPower(
        BaseTerm & combinedBaseTerm,
        TermsWithDetails const& termsToCombine)
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
            accumulateAndDoOperationOnTermDetails(combinedTerm, m_commonOperatorLevel, termWithDetails);
        }
    }
}

void Expression::putCombinedTerm(BaseTerm const& combinedBaseTerm)
{
    Term const& combinedTerm(getTermConstReferenceFromBaseTerm(combinedBaseTerm));
    if(combinedTerm.isExpression())
    {
        Expression const& expression(combinedTerm.getExpressionConstReference());
        m_commonOperatorLevel = expression.getCommonOperatorLevel();
        for(TermWithDetails const& termWithDetails : expression.getTerms().getTermsWithDetails())
        {
            m_termsWithPriorityAndAssociation.putTermWithDetails(termWithDetails);
        }
    }
    else if(combinedTerm.isValueTermButNotAnExpression())
    {
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(getBaseTermConstReferenceFromTerm(combinedTerm));
    }
}

void Expression::putTermsWithDetails(TermsWithDetails const& termsToSave)
{
    for(TermWithDetails const& termWithDetails : termsToSave)
    {
        m_termsWithPriorityAndAssociation.putTermWithDetails(termWithDetails);
    }
}

void Expression::addTermForNonEmptyTerms(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
    case OperatorLevel::AdditionAndSubtraction:
    {
        putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Positive);
        break;
    }
    case OperatorLevel::MultiplicationAndDivision:
    case OperatorLevel::RaiseToPower:
    {
        clearAndPutTermInTermsWithAssociation(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
        putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Positive);
        break;
    }
    }
}

void Expression::subtractTermForNonEmptyTerms(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
    case OperatorLevel::AdditionAndSubtraction:
    {
        putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Negative);
        break;
    }
    case OperatorLevel::MultiplicationAndDivision:
    case OperatorLevel::RaiseToPower:
    {
        clearAndPutTermInTermsWithAssociation(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
        putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Negative);
        break;
    }
    }
}

void Expression::multiplyTermForNonEmptyTerms(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
    case OperatorLevel::MultiplicationAndDivision:
    {
        putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Positive);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    case OperatorLevel::RaiseToPower:
    {
        clearAndPutTermInTermsWithAssociation(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
        putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Positive);
        break;
    }
    }
}

void Expression::divideTermForNonEmptyTerms(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
    case OperatorLevel::MultiplicationAndDivision:
    {
        putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Negative);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    case OperatorLevel::RaiseToPower:
    {
        clearAndPutTermInTermsWithAssociation(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
        putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Negative);
        break;
    }
    }
}

void Expression::raiseToPowerTermForNonEmptyTerms(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::RaiseToPower;
    case OperatorLevel::RaiseToPower:
    {
        putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Positive);
        break;
    }
    case OperatorLevel::AdditionAndSubtraction:
    case OperatorLevel::MultiplicationAndDivision:
    {
        clearAndPutTermInTermsWithAssociation(getBaseTermConstReferenceFromTerm(Term(Expression(*this))));
        m_commonOperatorLevel = OperatorLevel::RaiseToPower;
        putTermForExpressionAndNonExpressions(baseTerm, AssociationType::Positive);
        break;
    }
    }
}

void Expression::putTermForExpressionAndNonExpressions(
        BaseTerm const& baseTerm,
        AssociationType const overallAssociation)
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

void Expression::putTerm(BaseTerm const& baseTerm, AssociationType const overallAssociation)
{
    if(AssociationType::Positive == overallAssociation)
    {
        m_termsWithPriorityAndAssociation.putTermWithPositiveAssociation(baseTerm);
    }
    else if(AssociationType::Negative == overallAssociation)
    {
        m_termsWithPriorityAndAssociation.putTermWithNegativeAssociation(baseTerm);
    }
}

void Expression::putTermsWithAssociation(TermsWithPriorityAndAssociation const& termsWithAssociation, AssociationType const overallAssociation)
{
    TermsWithPriorityAndAssociation newTermsWithAssociation(termsWithAssociation);
    if(AssociationType::Negative == overallAssociation)
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
        TermsWithDetails const& termsWithExpressions)
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
        TermWithDetails & termExpressionWithDetails2)
{
    bool isMerged(false);
    Term & termExpression1(getTermReferenceFromSharedPointer(termExpressionWithDetails1.baseTermSharedPointer));
    Term & termExpression2(getTermReferenceFromSharedPointer(termExpressionWithDetails2.baseTermSharedPointer));
    Expression expression1(createOrCopyExpressionFromATerm(termExpression1));
    Expression expression2(createOrCopyExpressionFromATerm(termExpression2));
    Expression uniqueExpression1(getUniqueExpressionForAdditionOrSubtractionMergeChecking(expression1));
    Expression uniqueExpression2(getUniqueExpressionForAdditionOrSubtractionMergeChecking(expression2));
    uniqueExpression1.sort();
    uniqueExpression2.sort();
    Term mergeTerm1;
    Term mergeTerm2;
    accumulateMergeTermForAdditionOrSubtractionMergeChecking(getBaseTermReferenceFromTerm(mergeTerm1), expression1);
    accumulateMergeTermForAdditionOrSubtractionMergeChecking(getBaseTermReferenceFromTerm(mergeTerm2), expression2);
    if(canBeMergedForAdditionAndSubtraction(uniqueExpression1, uniqueExpression2, mergeTerm1, mergeTerm2))
    {
        Term resultMergeTerm;
        TermsWithDetails termsToMerge;
        termsToMerge.emplace_back(getBaseTermConstReferenceFromTerm(mergeTerm1), termExpressionWithDetails1.association);
        termsToMerge.emplace_back(getBaseTermConstReferenceFromTerm(mergeTerm2), termExpressionWithDetails2.association);
        accumulateTermsForAdditionAndSubtraction(resultMergeTerm, termsToMerge);
        termExpressionWithDetails1 = TermWithDetails(
                    getBaseTermConstReferenceFromTerm(resultMergeTerm*Term(uniqueExpression1)),
                    AssociationType::Positive);
        termExpressionWithDetails2.clear();
        isMerged = true;
    }
    return isMerged;
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

Expression Expression::getUniqueExpressionForAdditionOrSubtractionMergeChecking(Expression const& expression)
{
    Expression result;
    if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        TermsWithPriorityAndAssociation uniqueExpressions(
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

void Expression::accumulateMergeTermForAdditionOrSubtractionMergeChecking(BaseTerm & combinedBaseTerm, Expression const& expression)
{
    Term & combinedTerm(getTermReferenceFromBaseTerm(combinedBaseTerm));
    if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        TermsWithPriorityAndAssociation termsToBeMerged(
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

void Expression::removeSameTermsInNumeratorAndDenominatorForMultiplicationAndDivision(
        TermsWithDetails & expressionsForNumerator,
        TermsWithDetails & expressionsForDenominator)
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
        expressionsForNumerator.emplace_back(getBaseTermConstReferenceFromTerm(Term(1)), AssociationType::Positive);
    }
}

void Expression::multiplyThenAddTermIfTrueAndSubtractIfFalse(
        Expression const& multiplicand,
        BaseTerm const& term,
        bool const isAdd)
{
    Expression expressionToAddOrSubtract(multiplicand);
    expressionToAddOrSubtract.multiplyTerm(getTermConstReferenceFromBaseTerm(term));
    if(isAdd)
    {
        addTerm(Term(expressionToAddOrSubtract));
    }
    else
    {
        subtractTerm(Term(expressionToAddOrSubtract));
    }
}

}

}
