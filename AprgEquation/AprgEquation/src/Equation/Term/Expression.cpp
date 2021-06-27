#include "Expression.hpp"

#include <Equation/Simplification/SimplificationOfExpression.hpp>
#include <Equation/Utilities.hpp>

#include <algorithm>
#include <sstream>

using namespace alba::equation::Simplification;
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
    Term const& term(getTermConstReferenceFromBaseTerm(baseTerm));
    if(isEmpty() && !willHaveNoEffectOnAdditionOrSubtraction(term))
    {
        setTerm(baseTerm);
    }
    else if(!willHaveNoEffectOnAdditionOrSubtraction(term))
    {
        if(containsOnlyOneTerm()
                && willHaveNoEffectOnAdditionOrSubtraction(getTermConstReferenceFromBaseTerm(getFirstTermConstReference())))
        {
            setTerm(baseTerm);
        }        else
        {
            putTermWithAddition(baseTerm);
        }    }
}

void Expression::putTermWithSubtractionIfNeeded(BaseTerm const& baseTerm)
{
    Term const& term(getTermConstReferenceFromBaseTerm(baseTerm));
    if(isEmpty() && !willHaveNoEffectOnAdditionOrSubtraction(term))
    {
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
        putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Negative);
    }
    else if(!willHaveNoEffectOnAdditionOrSubtraction(term))
    {
        if(containsOnlyOneTerm()
                && willHaveNoEffectOnAdditionOrSubtraction(getTermConstReferenceFromBaseTerm(getFirstTermConstReference())))
        {
            m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
            putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Negative);        }
        else
        {
            putTermWithSubtraction(baseTerm);        }
    }
}

void Expression::putTermWithMultiplicationIfNeeded(BaseTerm const& baseTerm)
{
    Term const& term(getTermConstReferenceFromBaseTerm(baseTerm));
    if(isEmpty() && !willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(term))
    {
        setTerm(baseTerm);
    }
    else if(!willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(term))
    {
        if(containsOnlyOneTerm()
                && willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(getTermConstReferenceFromBaseTerm(getFirstTermConstReference())))
        {
            setTerm(baseTerm);
        }        else
        {
            putTermWithMultiplication(baseTerm);
        }    }
}

void Expression::putTermWithDivisionIfNeeded(BaseTerm const& baseTerm)
{
    Term const& term(getTermConstReferenceFromBaseTerm(baseTerm));
    if(isEmpty() && !willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(term))
    {
        m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
        putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Negative);
    }
    else if(!willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(term))
    {
        if(containsOnlyOneTerm()
                && willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(getTermConstReferenceFromBaseTerm(getFirstTermConstReference())))
        {
            m_commonOperatorLevel = OperatorLevel::MultiplicationAndDivision;
            putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Negative);        }
        else
        {
            putTermWithDivision(baseTerm);        }
    }
}

void Expression::putTermWithRaiseToPowerIfNeeded(BaseTerm const& baseTerm)
{
    Term const& term(getTermConstReferenceFromBaseTerm(baseTerm));
    if(isEmpty() && !willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(term))
    {
        setTerm(baseTerm);
    }
    else if(!willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(term))
    {
        putTermWithRaiseToPower(baseTerm);
    }
}

void Expression::putPolynomialFirstWithMultiplication(Polynomial const& polynomial){
    if(OperatorLevel::AdditionAndSubtraction == m_commonOperatorLevel)
    {
        TermsWithDetails termsWithDetails(m_termsWithAssociation.getTermsWithDetails());        clear();
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
        multiplyThenAddOrSubtract(termsWithDetails, Term(secondExpression));
    }
    else if(OperatorLevel::AdditionAndSubtraction == secondExpression.getCommonOperatorLevel())
    {
        Expression thisExpression(*this);
        clear();
        multiplyThenAddOrSubtract(
                    Term(thisExpression),
                    secondExpression.getTermsWithAssociation().getTermsWithDetails());
    }
    else
    {
        putTermWithMultiplicationIfNeeded(Term(secondExpression));
    }
}

void Expression::putTermsWithDetails(TermsWithDetails const& termsToSave)
{
    for(TermWithDetails const& termWithDetails : termsToSave)
    {
        m_termsWithAssociation.putTermWithDetails(termWithDetails);
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

void Expression::setCommonOperatorLevelIfStillUnknown(OperatorLevel const operatorLevel)
{
    if(OperatorLevel::Unknown == m_commonOperatorLevel)
    {
        m_commonOperatorLevel = operatorLevel;
    }
}

void Expression::simplify()
{
    SimplificationOfExpression simplification(*this);
    simplification.simplify();
    *this = simplification.getExpression();
}

void Expression::sort(){
    m_termsWithAssociation.sort();
}

void Expression::putTermWithAddition(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)    {
    case OperatorLevel::Unknown:
        m_commonOperatorLevel = OperatorLevel::AdditionAndSubtraction;
    case OperatorLevel::AdditionAndSubtraction:    {
        putTermForExpressionAndNonExpressions(baseTerm, TermAssociationType::Positive);
        break;
    }
    case OperatorLevel::MultiplicationAndDivision:
    case OperatorLevel::RaiseToPower:
    {
        clearAndPutTermInTermsWithAssociation(Term(Expression(*this)));
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
        clearAndPutTermInTermsWithAssociation(Term(Expression(*this)));
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
        clearAndPutTermInTermsWithAssociation(Term(Expression(*this)));
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
        clearAndPutTermInTermsWithAssociation(Term(Expression(*this)));
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
        clearAndPutTermInTermsWithAssociation(Term(Expression(*this)));
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

void Expression::multiplyThenAddOrSubtract(
        Polynomial const& polynomial,
        Expression const& expression){
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        Expression monomialExpression(createExpressionIfPossible({monomial}));        monomialExpression.putTermWithMultiplicationIfNeeded(Term(expression));
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
        expressionTerm.putTermWithMultiplicationIfNeeded(Term(monomial));
        putTermWithAdditionIfNeeded(Term(expressionTerm));
    }
}

void Expression::multiplyThenAddOrSubtract(
        Polynomial const& polynomial,
        TermsWithDetails const& termsWithDetails)
{
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        multiplyThenAddOrSubtract(Term(monomial), termsWithDetails);
    }
}

void Expression::multiplyThenAddOrSubtract(
        TermsWithDetails const& termsWithDetails,
        Polynomial const& polynomial)
{
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        multiplyThenAddOrSubtract(termsWithDetails, Term(monomial));
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
                        term2,
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

ostream & operator<<(ostream & out, Expression const& expression)
{
    out << expression.getDisplayableString();    return out;
}

}
}
