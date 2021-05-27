#pragma once

#include <BaseTerm.hpp>
#include <Constant.hpp>
#include <Container/AlbaUniqueVariant.hpp>
#include <Expression.hpp>
#include <Math/AlbaNumber.hpp>
#include <Monomial.hpp>
#include <Operator.hpp>
#include <Polynomial.hpp>
#include <Variable.hpp>


#include <string>
#include <vector>
namespace alba
{
namespace equation
{

enum class TermType
{
    Unknown,
    Constant,
    Variable,
    Operator,
    Monomial,
    Polynomial,
    Expression};

class Term : public BaseTerm
{
public:
    Term();
    Term(Constant const& constant);
    Term(std::string const& variableOrOperator);
    Term(Monomial const& monomial);
    Term(Polynomial const& polynomial);
    TermType getTermType() const;
    Constant & getConstantReference();
    Variable & getVariableReference();
    Operator & getOperatorReference();
    Monomial & getMonomialReference();
    Polynomial & getPolynomialReference();

private:
    TermType m_type;
    UniqueVariant<Constant, Variable, Operator, Monomial, Polynomial, Expression> m_data;
};

}
}