#include "Term.hpp"

#include <Utilities.hpp>

#include <cassert>

using namespace std;

namespace alba{

namespace equation
{

Term::Term()
    : m_type(TermType::Empty)
    , m_baseDataTermPointer(nullptr)
{}

Term::Term(Term const& term)
    : m_type(term.getTermType())
    , m_baseDataTermPointer(nullptr)
{
    switch(term.getTermType())
    {
    case TermType::Empty:
        break;
    case TermType::Constant:
        m_baseDataTermPointer.reset(new Constant(term.getConstantConstReference()));
        break;
    case TermType::Variable:
        m_baseDataTermPointer.reset(new Variable(term.getVariableConstReference()));
        break;
    case TermType::Operator:
        m_baseDataTermPointer.reset(new Operator(term.getOperatorConstReference()));
        break;
    case TermType::Monomial:
        m_baseDataTermPointer.reset(new Monomial(term.getMonomialConstReference()));
        break;
    case TermType::Polynomial:
        m_baseDataTermPointer.reset(new Polynomial(term.getPolynomialConstReference()));
        break;
    case TermType::Expression:
        m_baseDataTermPointer.reset(new Expression(term.getExpressionConstReference()));
        break;
    }
}

Term::Term(Constant const& constant)
    : m_type(TermType::Constant)
    , m_baseDataTermPointer(new Constant(constant))
{}

Term::Term(string const& variableOrOperator)
    : m_type(TermType::Empty)
    , m_baseDataTermPointer(nullptr)
{
    if(isOperator(variableOrOperator))
    {
        m_type=TermType::Operator;
        m_baseDataTermPointer.reset(new Operator(variableOrOperator));
    }
    else
    {
        m_type=TermType::Variable;
        m_baseDataTermPointer.reset(new Variable(variableOrOperator));
    }
}

Term::Term(Monomial const& monomial)
    : m_type(TermType::Monomial)
    , m_baseDataTermPointer(new Monomial(monomial))
{}

Term::Term(Polynomial const& polynomial)
    : m_type(TermType::Polynomial)
    , m_baseDataTermPointer(new Polynomial(polynomial))
{}

Term::Term(Expression const& expression)
    : m_type(TermType::Expression)
    , m_baseDataTermPointer(new Expression(expression))
{}

TermType Term::getTermType() const
{
    return m_type;}

Constant & Term::getConstantReference()
{
    assert(m_type==TermType::Constant);
    return *dynamic_cast<Constant*>(m_baseDataTermPointer.get());
}

Variable & Term::getVariableReference()
{
    assert(m_type==TermType::Variable);
    return *dynamic_cast<Variable*>(m_baseDataTermPointer.get());
}

Operator & Term::getOperatorReference()
{
    assert(m_type==TermType::Operator);
    return *dynamic_cast<Operator*>(m_baseDataTermPointer.get());
}

Monomial & Term::getMonomialReference()
{
    assert(m_type==TermType::Monomial);
    return *dynamic_cast<Monomial*>(m_baseDataTermPointer.get());
}

Polynomial & Term::getPolynomialReference()
{
    assert(m_type==TermType::Polynomial);
    return *dynamic_cast<Polynomial*>(m_baseDataTermPointer.get());
}

Expression & Term::getExpressionReference()
{
    assert(m_type==TermType::Expression);
    return *dynamic_cast<Expression*>(m_baseDataTermPointer.get());
}

Constant const& Term::getConstantConstReference() const
{
    assert(m_type==TermType::Constant);
    return *dynamic_cast<Constant const * const>(m_baseDataTermPointer.get());
}

Variable const& Term::getVariableConstReference() const
{
    assert(m_type==TermType::Variable);
    return *dynamic_cast<Variable const * const>(m_baseDataTermPointer.get());
}

Operator const& Term::getOperatorConstReference() const
{
    assert(m_type==TermType::Operator);
    return *dynamic_cast<Operator const * const>(m_baseDataTermPointer.get());
}

Monomial const& Term::getMonomialConstReference() const
{
    assert(m_type==TermType::Monomial);
    return *dynamic_cast<Monomial const * const>(m_baseDataTermPointer.get());
}

Polynomial const& Term::getPolynomialConstReference() const
{
    assert(m_type==TermType::Polynomial);
    return *dynamic_cast<Polynomial const * const>(m_baseDataTermPointer.get());
}

Expression const& Term::getExpressionConstReference() const
{
    assert(m_type==TermType::Expression);
    return *dynamic_cast<Expression const * const>(m_baseDataTermPointer.get());
}


}

}