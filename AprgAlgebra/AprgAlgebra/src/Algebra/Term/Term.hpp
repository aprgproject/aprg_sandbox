#pragma once

#include <Algebra/Term/BaseTermData.hpp>
#include <Algebra/Term/Constant.hpp>
#include <Algebra/Term/Expression.hpp>
#include <Algebra/Term/Function.hpp>
#include <Algebra/Term/Monomial.hpp>
#include <Algebra/Term/Operator.hpp>
#include <Algebra/Term/Polynomial.hpp>
#include <Algebra/Term/TermType.hpp>
#include <Algebra/Term/Variable.hpp>
#include <Math/AlbaNumber.hpp>

#include <memory>
#include <string>
#include <vector>

namespace alba
{

namespace algebra
{

class Term : public BaseTerm
{
public:
    Term();
    Term(Term const& term);
    Term(Constant const& constant);
    Term(std::string const& stringTerm);
    Term(Variable const& variable);
    Term(Operator const& operatorTerm);
    Term(Monomial const& monomial);
    Term(Polynomial const& polynomial);
    Term(Expression const& expression);
    Term(Function const& function);

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
    bool isFunction() const;
    bool isValueTerm() const;
    bool isValueTermAndNotAnExpression() const;
    bool isTheValueZero() const;
    bool isTheValueOne() const;

    TermType getTermType() const;
    Constant const& getConstantConstReference() const;
    Variable const& getVariableConstReference() const;
    Operator const& getOperatorConstReference() const;
    Monomial const& getMonomialConstReference() const;
    Polynomial const& getPolynomialConstReference() const;
    Expression const& getExpressionConstReference() const;
    Function const& getFunctionConstReference() const;
    std::string getDisplayableString() const override;
    std::string getDebugString() const override;

    Constant & getConstantReference();
    Variable & getVariableReference();
    Operator & getOperatorReference();
    Monomial & getMonomialReference();
    Polynomial & getPolynomialReference();
    Expression & getExpressionReference();
    Function & getFunctionReference();

    void simplify();
    void sort();

private:
    void resetBaseDataTermPointerBasedFromTerm(Term const& term);
    TermType m_type;
    std::unique_ptr<BaseTermData> m_baseDataTermPointer;
};

using Terms = std::vector<Term>;

std::ostream & operator<<(std::ostream & out, Term const& term);

}

}
