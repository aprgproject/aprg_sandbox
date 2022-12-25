#include "Expression.hpp"

#include <BooleanAlgebra/Simplification/SimplificationOfExpression.hpp>
#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/EnumHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/StringHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/TermUtilities.hpp>
#include <BooleanAlgebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <algorithm>
#include <sstream>

using namespace alba::booleanAlgebra::Simplification;
using namespace std;

namespace alba
{

namespace booleanAlgebra
{

Expression::Expression()
    : m_commonOperatorLevel(OperatorLevel::Unknown)
    , m_wrappedTerms()
    , m_isSimplified(false)
{}

Expression::Expression(
        Expression const& expression)
    : m_commonOperatorLevel(expression.m_commonOperatorLevel)
    , m_wrappedTerms(expression.m_wrappedTerms)
    , m_isSimplified(expression.m_isSimplified)
{}

Expression::Expression(BaseTerm const& baseTerm)
    : m_commonOperatorLevel(OperatorLevel::Unknown)
    , m_wrappedTerms()
    , m_isSimplified(getTermConstReferenceFromBaseTerm(baseTerm).isSimplified())
{
    m_wrappedTerms.emplace_back(baseTerm);
}

Expression::Expression(
        OperatorLevel const operatorLevel,        WrappedTerms const& wrappedTerms)
    : m_commonOperatorLevel(operatorLevel)
    , m_wrappedTerms(wrappedTerms)
    , m_isSimplified(false)
{
    if(wrappedTerms.empty())
    {
        m_commonOperatorLevel = OperatorLevel::Unknown;
    }
}

Expression::~Expression()
{}

bool Expression::operator==(Expression const& second) const
{
    return m_commonOperatorLevel == second.m_commonOperatorLevel            && m_wrappedTerms==second.m_wrappedTerms;
}

bool Expression::operator!=(Expression const& second) const{
    return !(operator==(second));
}

bool Expression::operator<(Expression const& second) const
{
    bool result(false);
    if(m_commonOperatorLevel == second.m_commonOperatorLevel)
    {
        return m_wrappedTerms < second.m_wrappedTerms;
    }
    else
    {
        result = getOperatorLevelInversePriority(m_commonOperatorLevel)
                < getOperatorLevelInversePriority(second.m_commonOperatorLevel);
    }
    return result;
}

Expression Expression::operator~() const
{
    Expression result(*this);
    result.negate();
    return result;
}

bool Expression::isEmpty() const
{
    return m_wrappedTerms.empty();
}

bool Expression::isSimplified() const
{
    return m_isSimplified;
}

bool Expression::containsOnlyOneTerm() const
{
    return m_wrappedTerms.size() == 1;
}

OperatorLevel Expression::getCommonOperatorLevel() const
{
    return m_commonOperatorLevel;
}

BaseTerm const& Expression::getFirstTermConstReference() const
{
    return getBaseTermReferenceFromSharedPointer(m_wrappedTerms.front().baseTermSharedPointer);
}

WrappedTerms const& Expression::getWrappedTerms() const{
    return m_wrappedTerms;
}
string Expression::getDisplayableString() const
{
    stringstream ss;
    ss << *this;
    return ss.str();
}

string Expression::getDebugString() const
{
    stringstream result;
    result << "( " << getEnumShortString(m_commonOperatorLevel) << "||";
    for(WrappedTerm const& wrappedTerm : m_wrappedTerms)
    {
        Term const& term(getTermConstReferenceFromSharedPointer(wrappedTerm.baseTermSharedPointer));
        result << getString(m_commonOperatorLevel) << term.getDebugString();
    }
    result << " )";    return result.str();
}

WrappedTerms & Expression::getWrappedTermsReference(){
    clearSimplifiedFlag();
    return m_wrappedTerms;
}

void Expression::clear()
{
    m_wrappedTerms.clear();
    m_commonOperatorLevel = OperatorLevel::Unknown;
    clearSimplifiedFlag();
}

void Expression::clearAndPutTermInWrappedTerms(BaseTerm const& baseTerm)
{
    clear();
    m_wrappedTerms.emplace_back(baseTerm);
    clearSimplifiedFlag();
}
void Expression::putTerm(BaseTerm const& baseTerm)
{
    m_wrappedTerms.emplace_back(baseTerm);    clearSimplifiedFlag();
}

void Expression::putTerm(
        BaseTerm const& baseTerm,
        OperatorLevel const operatorLevel)
{
    if(OperatorLevel::And == operatorLevel)
    {
        putTermWithAndOperationIfNeeded(baseTerm);
    }
    else if(OperatorLevel::Or == operatorLevel)
    {
        putTermWithOrOperationIfNeeded(baseTerm);
    }
    clearSimplifiedFlag();
}

void Expression::putTermWithAndOperationIfNeeded(BaseTerm const& baseTerm)
{
    Expression const& thisExpression(*this);
    Term const& term(getTermConstReferenceFromBaseTerm(baseTerm));
    if(willHaveNoEffectOnAndOperation(term))
    {
        if(isEmpty())
        {
            setTerm(Term(true));
        }
    }
    else if(isTheValue(term, false))
    {
        if(!isTheValue(thisExpression, false))
        {
            setTerm(Term(false));
        }
    }
    else
    {
        if(willHaveNoEffectOnAndOperation(thisExpression))
        {
            setTerm(baseTerm);
        }
        else if(isTheValue(thisExpression, false))
        {
            // do nothing
        }
        else
        {
            putTermWithAndOperation(baseTerm);
        }
    }
    clearSimplifiedFlag();
}

void Expression::putTermWithOrOperationIfNeeded(BaseTerm const& baseTerm)
{
    Expression const& thisExpression(*this);
    Term const& term(getTermConstReferenceFromBaseTerm(baseTerm));
    if(willHaveNoEffectOnOrOperation(term))
    {
        if(isEmpty())
        {
            setTerm(Term(false));
        }
    }
    else if(isTheValue(term, true))
    {
        if(!isTheValue(thisExpression, true))
        {
            setTerm(Term(true));
        }
    }
    else
    {
        if(willHaveNoEffectOnOrOperation(thisExpression))
        {
            setTerm(baseTerm);
        }
        else if(isTheValue(thisExpression, true))
        {
            // do nothing
        }
        else
        {
            putTermWithOrOperation(baseTerm);
        }
    }
    clearSimplifiedFlag();
}

void Expression::putWrappedTerm(WrappedTerm const& termToSave)
{
    m_wrappedTerms.emplace_back(termToSave);
    clearSimplifiedFlag();
}

void Expression::putWrappedTerms(WrappedTerms const& termsToSave)
{
    m_wrappedTerms.reserve(m_wrappedTerms.size() + termsToSave.size());
    copy(termsToSave.cbegin(), termsToSave.cend(), back_inserter(m_wrappedTerms));
    clearSimplifiedFlag();
}

void Expression::set(OperatorLevel const operatorLevel, WrappedTerms const& wrappedTerms)
{
    m_commonOperatorLevel = operatorLevel;
    m_wrappedTerms = wrappedTerms;
    clearSimplifiedFlag();
}

void Expression::setTerm(BaseTerm const& baseTerm)
{
    *this = createOrCopyExpressionFromATerm(
                getTermConstReferenceFromBaseTerm(baseTerm));
    clearSimplifiedFlag();
}

void Expression::setCommonOperatorLevel(OperatorLevel const operatorLevel)
{
    m_commonOperatorLevel = operatorLevel;
    clearSimplifiedFlag();
}

void Expression::setCommonOperatorLevelIfStillUnknown(OperatorLevel const operatorLevel)
{
    if(OperatorLevel::Unknown == m_commonOperatorLevel)
    {
        m_commonOperatorLevel = operatorLevel;
    }
    clearSimplifiedFlag();
}

void Expression::simplify()
{
    if(!m_isSimplified)
    {
        SimplificationOfExpression simplification(*this);
        simplification.simplify();
        *this = simplification.getExpression();
        setAsSimplified();
    }
}

void Expression::sort()
{
    ::sort(m_wrappedTerms.begin(), m_wrappedTerms.end());
    clearSimplifiedFlag();
}

void Expression::negate()
{
    // Using De Morgan's Law
    // (x | y | z + ...)’ = x’ & y’ & z’ & ...
    // (x & y & z & ...)’ = x’ | y’ | z’ + ...
    for(WrappedTerm & wrappedTerm : m_wrappedTerms)
    {
        Term & term(getTermReferenceFromSharedPointer(wrappedTerm.baseTermSharedPointer));
        term.negate();
    }
    m_commonOperatorLevel = getDualOperatorLevel(m_commonOperatorLevel);    clearSimplifiedFlag();
}

void Expression::setAsSimplified(){
    m_isSimplified = true;
}

void Expression::clearSimplifiedFlag()
{
    m_isSimplified = false;
}

void Expression::clearAllInnerSimplifiedFlags()
{
    for(WrappedTerm & wrappedTerm : m_wrappedTerms)
    {
        Term & term(getTermReferenceFromSharedPointer(wrappedTerm.baseTermSharedPointer));
        term.clearAllInnerSimplifiedFlags();
    }
    clearSimplifiedFlag();}

void Expression::putTermWithAndOperation(BaseTerm const& baseTerm)
{    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
    case OperatorLevel::And:
    {
        m_commonOperatorLevel = OperatorLevel::And;
        putTermForExpressionAndNonExpressions(baseTerm);
        break;
    }
    case OperatorLevel::Or:
    {
        clearAndPutTermInWrappedTerms(Term(*this));
        m_commonOperatorLevel = OperatorLevel::And;
        putTermForExpressionAndNonExpressions(baseTerm);
        break;
    }
    }
}

void Expression::putTermWithOrOperation(BaseTerm const& baseTerm)
{
    switch(m_commonOperatorLevel)
    {
    case OperatorLevel::Unknown:
    case OperatorLevel::Or:
    {
        m_commonOperatorLevel = OperatorLevel::Or;
        putTermForExpressionAndNonExpressions(baseTerm);
        break;
    }
    case OperatorLevel::And:
    {
        clearAndPutTermInWrappedTerms(Term(*this));
        m_commonOperatorLevel = OperatorLevel::Or;
        putTermForExpressionAndNonExpressions(baseTerm);
        break;
    }
    }
}

void Expression::putTermForExpressionAndNonExpressions(
        BaseTerm const& baseTerm)
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
                putWrappedTerms(expression.getWrappedTerms());
            }
            else
            {
                putTerm(baseTerm);
            }
        }
    }
    else if(isNonEmptyOrNonOperatorOrNonExpressionType(term))
    {
        putTerm(baseTerm);
    }
}

ostream & operator<<(ostream & out, Expression const& expression)
{
    WrappedTerms const& wrappedTerms(expression.m_wrappedTerms);
    string operatorString(getString(expression.m_commonOperatorLevel));
    out << "(";
    if(!wrappedTerms.empty())
    {
        out << getTermConstReferenceFromSharedPointer(wrappedTerms.front().baseTermSharedPointer);
        for(auto it=wrappedTerms.cbegin()+1; it!=wrappedTerms.cend(); it++)
        {
            Term const& term(getTermConstReferenceFromSharedPointer(it->baseTermSharedPointer));
            out << operatorString << term;
        }
    }    out << ")";
    return out;
}
}

}
