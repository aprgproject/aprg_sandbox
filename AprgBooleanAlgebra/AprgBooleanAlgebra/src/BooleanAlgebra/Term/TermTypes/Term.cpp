#include "Term.hpp"

#include <BooleanAlgebra/Term/Utilities/ConvertHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/EnumHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/StringHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <cassert>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace booleanAlgebra
{

Term::Term()
    : m_type(TermType::Empty)
    , m_isSimplified(false)
    , m_baseTermDataPointer(nullptr)
{}

Term::Term(Term const& term)
    : m_type(term.getTermType())
    , m_isSimplified(term.m_isSimplified)
    , m_baseTermDataPointer(nullptr)
{
    resetBaseDataTermPointerBasedFromTerm(term);
}

Term::Term(bool const boolValue)
    : m_type(TermType::Constant)
    , m_isSimplified(false)
    , m_baseTermDataPointer(make_unique<Constant>(boolValue))
{}

Term::Term(char const* const characterString)
    : m_type(TermType::Empty)
    , m_isSimplified(false)
    , m_baseTermDataPointer(nullptr)
{
    initializeBasedOnString(string(characterString));
}

Term::Term(string const& stringAsParameter)
    : m_type(TermType::Empty)
    , m_isSimplified(false)
    , m_baseTermDataPointer(nullptr)
{
    initializeBasedOnString(stringAsParameter);
}

Term::Term(Constant const& constant)
    : m_type(TermType::Constant)
    , m_isSimplified(false)
    , m_baseTermDataPointer(make_unique<Constant>(constant))
{}

Term::Term(VariableTerm const& variableTerm)
    : m_type(TermType::VariableTerm)
    , m_isSimplified(false)
    , m_baseTermDataPointer(nullptr)
{
    m_baseTermDataPointer = make_unique<VariableTerm>(variableTerm);
}

Term::Term(Operator const& operatorTerm)
    : m_type(TermType::Operator)
    , m_isSimplified(false)
    , m_baseTermDataPointer(nullptr)
{
    m_baseTermDataPointer = make_unique<Operator>(operatorTerm);
}

Term::Term(Expression const& expression)
    : m_type(TermType::Expression)
    , m_isSimplified(false)
    , m_baseTermDataPointer(make_unique<Expression>(expression))
{}

Term& Term::operator=(Term const& term)
{
    m_type = term.m_type;
    m_isSimplified = term.m_isSimplified;
    resetBaseDataTermPointerBasedFromTerm(term);
    return *this;
}

bool Term::operator==(Term const& second) const
{
    bool result(false);
    if(m_type==second.m_type)
    {
        if(m_type==TermType::Empty)
        {
            result=true;
        }
        else if(m_type==TermType::Constant)
        {
            result = getConstantConstReference()==second.getConstantConstReference();
        }
        else if(m_type==TermType::VariableTerm)
        {
            result = getVariableTermConstReference()==second.getVariableTermConstReference();
        }
        else if(m_type==TermType::Operator)
        {
            result = getOperatorConstReference()==second.getOperatorConstReference();
        }
        else if(m_type==TermType::Expression)
        {
            result = getExpressionConstReference()==second.getExpressionConstReference();
        }
    }
    return result;
}

bool Term::operator!=(Term const& second) const
{
    return !(operator==(second));
}

bool Term::operator<(Term const& second) const
{
    bool result(false);
    if(m_type == second.m_type)
    {
        if(m_type==TermType::Empty)
        {
            result=false;
        }
        else if(m_type==TermType::Constant)
        {
            result = getConstantConstReference() < second.getConstantConstReference();
        }
        else if(m_type==TermType::VariableTerm)
        {
            result = getVariableTermConstReference() < second.getVariableTermConstReference();
        }
        else if(m_type==TermType::Operator)
        {
            result = getOperatorConstReference() < second.getOperatorConstReference();
        }
        else if(m_type==TermType::Expression)
        {
            result = getExpressionConstReference() < second.getExpressionConstReference();
        }
    }
    else
    {
        result = getTermTypePriorityValue(m_type) < getTermTypePriorityValue(second.m_type);
    }
    return result;
}

Term Term::operator~() const
{
    Term result(*this);
    result.negate();
    return result;
}

bool Term::isEmpty() const
{
    bool result(false);
    if(m_type==TermType::Empty)
    {
        result = true;
    }
    else if(m_type==TermType::Expression)
    {
        result = getExpressionConstReference().isEmpty();
    }
    return result;
}

bool Term::isConstant() const
{
    return TermType::Constant == m_type;
}

bool Term::isVariableTerm() const
{
    return TermType::VariableTerm == m_type;
}

bool Term::isOperator() const
{
    return TermType::Operator == m_type;
}

bool Term::isExpression() const
{
    return TermType::Expression == m_type;
}

bool Term::isSimplified() const
{
    return m_isSimplified;
}

TermType Term::getTermType() const
{
    return m_type;
}

Constant const& Term::getConstantConstReference() const
{
    assert(m_type==TermType::Constant);
    return *dynamic_cast<Constant const * const>(m_baseTermDataPointer.get());
}

VariableTerm const& Term::getVariableTermConstReference() const
{
    assert(m_type==TermType::VariableTerm);
    return *dynamic_cast<VariableTerm const * const>(m_baseTermDataPointer.get());
}

Operator const& Term::getOperatorConstReference() const
{
    assert(m_type==TermType::Operator);
    return *dynamic_cast<Operator const * const>(m_baseTermDataPointer.get());
}

Expression const& Term::getExpressionConstReference() const
{
    assert((m_type==TermType::Expression));
    return *dynamic_cast<Expression const * const>(m_baseTermDataPointer.get());
}

bool Term::getBooleanValue() const
{
    return getConstantConstReference().getBooleanValue();
}

string Term::getDisplayableString() const
{
    string result;
    if(m_type==TermType::Empty)
    {
        result = "{EmptyTerm}";
    }
    else if(m_type==TermType::Constant)
    {
        result = getConstantConstReference().getDisplayableString();
    }
    else if(m_type==TermType::VariableTerm)
    {
        result = getVariableTermConstReference().getDisplayableString();
    }
    else if(m_type==TermType::Operator)
    {
        result = getOperatorConstReference().getDisplayableString();
    }
    else if(m_type==TermType::Expression)
    {
        result = getExpressionConstReference().getDisplayableString();
    }
    return result;
}

string Term::getDebugString() const
{
    string result;
    if(m_type==TermType::Constant)
    {
        result = getConstantConstReference().getDisplayableString();
    }
    else if(m_type==TermType::VariableTerm)
    {
        result = getVariableTermConstReference().getDisplayableString();
    }
    else if(m_type==TermType::Operator)
    {
        result = getOperatorConstReference().getDisplayableString();
    }
    else if(m_type==TermType::Expression)
    {
        result = getExpressionConstReference().getDebugString();
    }
    result += "{";
    result += getEnumShortString(m_type);
    result += "}";
    return result;
}

Constant & Term::getConstantReference()
{
    clearSimplifiedFlag();
    assert(m_type==TermType::Constant);
    return *dynamic_cast<Constant*>(m_baseTermDataPointer.get());
}

VariableTerm & Term::getVariableTermReference()
{
    clearSimplifiedFlag();
    assert(m_type==TermType::VariableTerm);
    return *dynamic_cast<VariableTerm*>(m_baseTermDataPointer.get());
}

Operator & Term::getOperatorReference()
{
    clearSimplifiedFlag();
    assert(m_type==TermType::Operator);
    return *dynamic_cast<Operator*>(m_baseTermDataPointer.get());
}

Expression & Term::getExpressionReference()
{
    clearSimplifiedFlag();
    assert((m_type==TermType::Expression));
    return *dynamic_cast<Expression*>(m_baseTermDataPointer.get());
}

void Term::clear()
{
    m_type=TermType::Empty;
    m_baseTermDataPointer.reset();
    clearSimplifiedFlag();
}

void Term::simplify()
{
    if(!m_isSimplified)
    {
        if(m_type==TermType::Expression)
        {
            *this = simplifyAndConvertExpressionToSimplestTerm(getExpressionConstReference());
        }
        setAsSimplified();
    }
}

void Term::sort()
{
    if(isExpression())
    {
        getExpressionReference().sort();
    }
    clearAllInnerSimplifiedFlags();
}

void Term::negate()
{
    switch(m_type)
    {
    case TermType::Empty:
        break;
    case TermType::Constant:
        getConstantReference().negate();
        break;
    case TermType::VariableTerm:
        getVariableTermReference().negate();
        break;
    case TermType::Operator:
        break;
    case TermType::Expression:
        getExpressionReference().negate();
        break;
    }
    clearAllInnerSimplifiedFlags();
}

void Term::setAsSimplified()
{
    m_isSimplified = true;
}

void Term::clearSimplifiedFlag()
{
    m_isSimplified = false;
}

void Term::clearAllInnerSimplifiedFlags()
{
    if(m_type==TermType::Expression)
    {
        getExpressionReference().clearAllInnerSimplifiedFlags();
    }
    clearSimplifiedFlag();
}

void Term::resetBaseDataTermPointerBasedFromTerm(Term const& term)
{
    switch(term.getTermType())
    {
    case TermType::Empty:
        break;
    case TermType::Constant:
        m_baseTermDataPointer = make_unique<Constant>(term.getConstantConstReference());
        break;
    case TermType::VariableTerm:
        m_baseTermDataPointer = make_unique<VariableTerm>(term.getVariableTermConstReference());
        break;
    case TermType::Operator:
        m_baseTermDataPointer = make_unique<Operator>(term.getOperatorConstReference());
        break;
    case TermType::Expression:
        m_baseTermDataPointer = make_unique<Expression>(term.getExpressionConstReference());
        break;
    }
}

void Term::initializeBasedOnString(string const& stringAsParameter)
{
    if(stringAsParameter.empty())
    {
        // do nothing
    }
    else if(booleanAlgebra::isConstant(stringAsParameter))
    {
        m_type=TermType::Constant;
        m_baseTermDataPointer = make_unique<Constant>(convertStringToBool(stringAsParameter));
    }
    else if(booleanAlgebra::isOperator(stringAsParameter))
    {
        m_type=TermType::Operator;
        m_baseTermDataPointer = make_unique<Operator>(stringAsParameter);
    }
    else
    {
        m_type=TermType::VariableTerm;
        m_baseTermDataPointer = make_unique<VariableTerm>(stringAsParameter, false);
    }
}

ostream & operator<<(ostream & out, Term const& term)
{
    out << term.getDisplayableString();
    return out;
}


}

}
