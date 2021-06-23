#pragma once

#include <Equation/Term/BaseTermData.hpp>
#include <Equation/Term/Constant.hpp>
#include <Equation/Term/Expression.hpp>
#include <Equation/Term/Monomial.hpp>
#include <Equation/Term/Operator.hpp>
#include <Equation/Term/Polynomial.hpp>
#include <Equation/Term/TermType.hpp>
#include <Equation/Term/Variable.hpp>
#include <Math/AlbaNumber.hpp>

#include <memory>
#include <string>
#include <vector>

namespace alba
{

namespace equation
{

class Term : public BaseTerm
{
    friend std::ostream & operator<<(std::ostream & out, Term const& term);
public:
    Term();
    Term(Term const& term);
    Term(Constant const& constant);
    Term(std::string const& variableOrOperator);
    Term(Variable const& variable);
    Term(Operator const& operatorTerm);
    Term(Monomial const& monomial);
    Term(Polynomial const& polynomial);
    Term(Expression const& expression);

    Term & operator=(Term const& term);
    bool operator==(Term const& second) const;
    bool operator!=(Term const& second) const;
    bool operator<(Term const& second) const;
    bool isEmpty() const;
    bool isConstant() const;
    bool isVariable() const;
    bool isOperator() const;
    bool isMonomial() const;
    bool isPolynomial() const;
    bool isExpression() const;
    bool isValueTerm() const;
    bool isValueTermButNotAnExpression() const;
    bool isTheValueZero() const;
    bool isTheValueOne() const;

    TermType getTermType() const;
    Constant const& getConstantConstReference() const;
    Variable const& getVariableConstReference() const;
    Operator const& getOperatorConstReference() const;
    Monomial const& getMonomialConstReference() const;
    Polynomial const& getPolynomialConstReference() const;
    Expression const& getExpressionConstReference() const;
    std::string getDisplayableString() const override;
    std::string getDebugString() const override;

    Constant & getConstantReference();
    Variable & getVariableReference();
    Operator & getOperatorReference();
    Monomial & getMonomialReference();
    Polynomial & getPolynomialReference();
    Expression & getExpressionReference();

    void simplify();
    void simplifyToCommonDenominator();
    void sort();

private:
    void resetBaseDataTermPointerBasedFromTerm(Term const& term);    TermType m_type;
    std::unique_ptr<BaseTermData> m_baseDataTermPointer;
};

using Terms = std::vector<Term>;

std::ostream & operator<<(std::ostream & out, Term const& term);

}

}
