#pragma once

#include <BaseTermData.hpp>
#include <Constant.hpp>
#include <Expression.hpp>
#include <Math/AlbaNumber.hpp>
#include <Monomial.hpp>#include <Operator.hpp>
#include <Polynomial.hpp>
#include <Variable.hpp>

#include <memory>
#include <string>
#include <vector>
namespace alba
{
namespace equation
{

enum class TermType
{
    Empty,
    Constant,
    Variable,
    Operator,    Monomial,
    Polynomial,
    Expression
};

class Term : public BaseTerm
{
public:
    Term();
    Term(Term const& term);
    Term(Constant const& constant);
    Term(std::string const& variableOrOperator);
    Term(Monomial const& monomial);
    Term(Polynomial const& polynomial);
    Term(Expression const& expression);

    TermType getTermType() const;

    Constant & getConstantReference();
    Variable & getVariableReference();
    Operator & getOperatorReference();
    Monomial & getMonomialReference();
    Polynomial & getPolynomialReference();
    Expression & getExpressionReference();

    Constant const& getConstantConstReference() const;
    Variable const& getVariableConstReference() const;
    Operator const& getOperatorConstReference() const;
    Monomial const& getMonomialConstReference() const;
    Polynomial const& getPolynomialConstReference() const;
    Expression const& getExpressionConstReference() const;

private:
    TermType m_type;
    std::unique_ptr<BaseTermData> m_baseDataTermPointer;
};

using Terms = std::vector<Term>;

}

}