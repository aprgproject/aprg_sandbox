#include "Term.hpp"

#include <Utilities.hpp>

using namespace std;

namespace alba
{

namespace equation
{

Term::Term()
    : m_type(TermType::Unknown)
{}

Term::Term(Constant const& constant)
    : m_type(TermType::Constant)
{
    Constant & constantDataReference = m_data.acquire<Constant>();
    constantDataReference = constant;
}

Term::Term(std::string const& variableOrOperator)
    : m_type(TermType::Unknown)
{
    if(isOperator(variableOrOperator))
    {
        m_type=TermType::Operator;
        Operator & operatorDataReference = m_data.acquire<Operator>();
        operatorDataReference = Operator(variableOrOperator);
    }
    else
    {
        m_type=TermType::Variable;
        Variable & variableDataReference = m_data.acquire<Variable>();
        variableDataReference = Variable(variableOrOperator);
    }
}

Term::Term(Monomial const& monomial)
    : m_type(TermType::Monomial)
{
    Monomial & monomialDataReference = m_data.acquire<Monomial>();
    monomialDataReference = monomial;
}

Term::Term(Polynomial const& polynomial)
    : m_type(TermType::Polynomial)
{
    Polynomial & polynomialDataReference = m_data.acquire<Polynomial>();
    polynomialDataReference = polynomial;
}

TermType Term::getTermType() const
{
    return m_type;
}

Constant & Term::getConstantReference()
{
    return m_data.acquire<Constant>();
}

Variable & Term::getVariableReference()
{
    return m_data.acquire<Variable>();
}

Operator & Term::getOperatorReference()
{
    return m_data.acquire<Operator>();
}

Monomial & Term::getMonomialReference()
{
    return m_data.acquire<Monomial>();
}

Polynomial & Term::getPolynomialReference()
{
    return m_data.acquire<Polynomial>();
}

}

}
