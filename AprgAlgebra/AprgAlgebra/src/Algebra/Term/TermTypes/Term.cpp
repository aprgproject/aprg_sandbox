#include "Term.hpp"

#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/EnumHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <cassert>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace algebra
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

Term::Term(int const signedValue)
    : m_type(TermType::Constant)
    , m_isSimplified(false)
    , m_baseTermDataPointer(make_unique<Constant>(signedValue))
{}

Term::Term(unsigned int const unsignedValue)
    : m_type(TermType::Constant)
    , m_isSimplified(false)
    , m_baseTermDataPointer(make_unique<Constant>(unsignedValue))
{}

Term::Term(double const doubleValue)
    : m_type(TermType::Constant)
    , m_isSimplified(false)
    , m_baseTermDataPointer(make_unique<Constant>(doubleValue))
{}

Term::Term(AlbaNumber const& number)
    : m_type(TermType::Constant)
    , m_isSimplified(false)
    , m_baseTermDataPointer(make_unique<Constant>(number))
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

Term::Term(Variable const& variable)
    : m_type(TermType::Variable)
    , m_isSimplified(false)
    , m_baseTermDataPointer(nullptr)
{
    m_baseTermDataPointer = make_unique<Variable>(variable);
}

Term::Term(Operator const& operatorTerm)
    : m_type(TermType::Operator)
    , m_isSimplified(false)
    , m_baseTermDataPointer(nullptr)
{
    m_baseTermDataPointer = make_unique<Operator>(operatorTerm);
}

Term::Term(Monomial const& monomial)
    : m_type(TermType::Monomial)
    , m_isSimplified(false)
    , m_baseTermDataPointer(make_unique<Monomial>(monomial))
{}

Term::Term(Polynomial const& polynomial)
    : m_type(TermType::Polynomial)
    , m_isSimplified(false)
    , m_baseTermDataPointer(make_unique<Polynomial>(polynomial))
{}

Term::Term(Expression const& expression)
    : m_type(TermType::Expression)
    , m_isSimplified(false)
    , m_baseTermDataPointer(make_unique<Expression>(expression))
{}

Term::Term(Function const& function)
    : m_type(TermType::Function)
    , m_isSimplified(false)
    , m_baseTermDataPointer(make_unique<Function>(function))
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
        else if(m_type==TermType::Variable)
        {
            result = getVariableConstReference()==second.getVariableConstReference();
        }
        else if(m_type==TermType::Operator)
        {
            result = getOperatorConstReference()==second.getOperatorConstReference();
        }
        else if(m_type==TermType::Monomial)
        {
            result = getMonomialConstReference()==second.getMonomialConstReference();
        }
        else if(m_type==TermType::Polynomial)
        {
            result = getPolynomialConstReference()==second.getPolynomialConstReference();
        }
        else if(m_type==TermType::Expression)
        {
            result = getExpressionConstReference()==second.getExpressionConstReference();
        }
        else if(m_type==TermType::Function)
        {
            result = getFunctionConstReference()==second.getFunctionConstReference();
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
        else if(m_type==TermType::Variable)
        {
            result = getVariableConstReference() < second.getVariableConstReference();
        }
        else if(m_type==TermType::Operator)
        {
            result = getOperatorConstReference() < second.getOperatorConstReference();
        }
        else if(m_type==TermType::Monomial)
        {
            result = getMonomialConstReference() < second.getMonomialConstReference();
        }
        else if(m_type==TermType::Polynomial)
        {
            result = getPolynomialConstReference() < second.getPolynomialConstReference();
        }
        else if(m_type==TermType::Expression)
        {
            result = getExpressionConstReference() < second.getExpressionConstReference();
        }
        else if(m_type==TermType::Function)
        {
            result = getFunctionConstReference() < second.getFunctionConstReference();
        }
    }
    else
    {
        result = getTermTypePriorityValue(m_type) < getTermTypePriorityValue(second.m_type);
    }
    return result;
}

bool Term::isEmpty() const
{
    bool result(false);
    if(m_type==TermType::Empty)
    {
        result = true;
    }
    else if(m_type==TermType::Polynomial)
    {
        result = getPolynomialConstReference().isEmpty();
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

bool Term::isVariable() const
{
    return TermType::Variable == m_type;
}

bool Term::isOperator() const
{
    return TermType::Operator == m_type;
}

bool Term::isMonomial() const
{
    return TermType::Monomial == m_type;
}

bool Term::isPolynomial() const
{
    return TermType::Polynomial == m_type;
}

bool Term::isExpression() const
{
    return TermType::Expression == m_type;
}

bool Term::isFunction() const
{
    return TermType::Function == m_type;
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

Variable const& Term::getVariableConstReference() const
{
    assert(m_type==TermType::Variable);
    return *dynamic_cast<Variable const * const>(m_baseTermDataPointer.get());
}

Operator const& Term::getOperatorConstReference() const
{
    assert(m_type==TermType::Operator);
    return *dynamic_cast<Operator const * const>(m_baseTermDataPointer.get());
}

Monomial const& Term::getMonomialConstReference() const
{
    assert(m_type==TermType::Monomial);
    return *dynamic_cast<Monomial const * const>(m_baseTermDataPointer.get());
}

Polynomial const& Term::getPolynomialConstReference() const
{
    assert(m_type==TermType::Polynomial);
    return *dynamic_cast<Polynomial const * const>(m_baseTermDataPointer.get());
}

Expression const& Term::getExpressionConstReference() const
{
    assert((m_type==TermType::Expression));
    return *dynamic_cast<Expression const * const>(m_baseTermDataPointer.get());
}

Function const& Term::getFunctionConstReference() const
{
    assert((m_type==TermType::Function));
    return *dynamic_cast<Function const * const>(m_baseTermDataPointer.get());
}

AlbaNumber const& Term::getConstantValueConstReference() const
{
    return getConstantConstReference().getNumberConstReference();
}

string Term::getDebugString() const
{
    stringstream ss;
    ss.precision(16);
    switch (m_type)
    {
    case TermType::Empty:
        ss << "{EmptyTerm}";
        break;
    case TermType::Constant:
        ss << getConstantConstReference();
        break;
    case TermType::Variable:
        ss << getVariableConstReference();
        break;
    case TermType::Operator:
        ss << getOperatorConstReference();
        break;
    case TermType::Monomial:
        ss << getMonomialConstReference();
        break;
    case TermType::Polynomial:
        ss << getPolynomialConstReference();
        break;
    case TermType::Expression:
        ss << getExpressionConstReference().getDebugString();
        break;
    case TermType::Function:
        ss << getFunctionConstReference().getDebugString();
        break;
    default:
        break;
    }
    ss << "{" << getEnumShortString(m_type) << "}";
    return ss.str();
}

Constant & Term::getConstantReference()
{
    clearSimplifiedFlag();
    assert(m_type==TermType::Constant);
    return *dynamic_cast<Constant*>(m_baseTermDataPointer.get());
}

Variable & Term::getVariableReference()
{
    clearSimplifiedFlag();
    assert(m_type==TermType::Variable);
    return *dynamic_cast<Variable*>(m_baseTermDataPointer.get());
}

Operator & Term::getOperatorReference()
{
    clearSimplifiedFlag();
    assert(m_type==TermType::Operator);
    return *dynamic_cast<Operator*>(m_baseTermDataPointer.get());
}

Monomial & Term::getMonomialReference()
{
    clearSimplifiedFlag();
    assert(m_type==TermType::Monomial);
    return *dynamic_cast<Monomial*>(m_baseTermDataPointer.get());
}

Polynomial & Term::getPolynomialReference()
{
    clearSimplifiedFlag();
    assert(m_type==TermType::Polynomial);
    return *dynamic_cast<Polynomial*>(m_baseTermDataPointer.get());
}

Expression & Term::getExpressionReference()
{
    clearSimplifiedFlag();
    assert((m_type==TermType::Expression));
    return *dynamic_cast<Expression*>(m_baseTermDataPointer.get());
}

Function & Term::getFunctionReference()
{
    clearSimplifiedFlag();
    assert((m_type==TermType::Function));
    return *dynamic_cast<Function*>(m_baseTermDataPointer.get());
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
        if(m_type==TermType::Monomial)
        {
            *this = simplifyAndConvertMonomialToSimplestTerm(getMonomialConstReference());
        }
        else if(m_type==TermType::Polynomial)
        {
            *this = simplifyAndConvertPolynomialToSimplestTerm(getPolynomialConstReference());
        }
        else if(m_type==TermType::Expression)
        {
            *this = simplifyAndConvertExpressionToSimplestTerm(getExpressionConstReference());
        }
        else if(m_type==TermType::Function)
        {
            *this = simplifyAndConvertFunctionToSimplestTerm(getFunctionConstReference());
        }
        setAsSimplified();
    }
}

void Term::sort()
{
    if(isPolynomial())
    {
        getPolynomialReference().sortMonomialsWithInversePriority();
    }
    else if(isExpression())
    {
        getExpressionReference().sort();
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
    if(m_type==TermType::Monomial)
    {
        getMonomialReference().clearSimplifiedFlag();
    }
    else if(m_type==TermType::Polynomial)
    {
        getPolynomialReference().clearSimplifiedFlag();
    }
    else if(m_type==TermType::Expression)
    {
        getExpressionReference().clearAllInnerSimplifiedFlags();
    }
    else if(m_type==TermType::Function)
    {
        getFunctionReference().clearAllInnerSimplifiedFlags();
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
    case TermType::Variable:
        m_baseTermDataPointer = make_unique<Variable>(term.getVariableConstReference());
        break;
    case TermType::Operator:
        m_baseTermDataPointer = make_unique<Operator>(term.getOperatorConstReference());
        break;
    case TermType::Monomial:
        m_baseTermDataPointer = make_unique<Monomial>(term.getMonomialConstReference());
        break;
    case TermType::Polynomial:
        m_baseTermDataPointer = make_unique<Polynomial>(term.getPolynomialConstReference());
        break;
    case TermType::Expression:
        m_baseTermDataPointer = make_unique<Expression>(term.getExpressionConstReference());
        break;
    case TermType::Function:
        m_baseTermDataPointer = make_unique<Function>(term.getFunctionConstReference());
        break;
    }
}

void Term::initializeBasedOnString(string const& stringAsParameter)
{
    if(stringAsParameter.empty())
    {
        // do nothing
    }
    else if(isNumber(stringAsParameter.front()))
    {
        m_type=TermType::Constant;
        m_baseTermDataPointer = make_unique<Constant>(convertStringToAlbaNumber(stringAsParameter));
    }
    else if(algebra::isOperator(stringAsParameter))
    {
        m_type=TermType::Operator;
        m_baseTermDataPointer = make_unique<Operator>(stringAsParameter);
    }
    else if(algebra::isFunction(stringAsParameter))
    {
        m_type=TermType::Function;
        m_baseTermDataPointer = make_unique<Function>(createFunctionWithEmptyInputExpression(stringAsParameter));
    }
    else
    {
        m_type=TermType::Variable;
        m_baseTermDataPointer = make_unique<Variable>(stringAsParameter);
    }
}

ostream & operator<<(ostream & out, Term const& term)
{
    switch (term.m_type)
    {
    case TermType::Empty:
        out << "{EmptyTerm}";
        break;
    case TermType::Constant:
        out << term.getConstantConstReference();
        break;
    case TermType::Variable:
        out << term.getVariableConstReference();
        break;
    case TermType::Operator:
        out << term.getOperatorConstReference();
        break;
    case TermType::Monomial:
        out << term.getMonomialConstReference();
        break;
    case TermType::Polynomial:
        out << term.getPolynomialConstReference();
        break;
    case TermType::Expression:
        out << term.getExpressionConstReference();
        break;
    case TermType::Function:
        out << term.getFunctionConstReference();
        break;
    default:
        break;
    }
    return out;
}


}

}
