#include "Term.hpp"

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

Term::Term(Variable const& variable)
    : m_type(TermType::Variable)
{
    Variable & variableDataReference = m_data.acquire<Variable>();
    variableDataReference = variable;
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
