#pragma once

#include <Algebra/Term/TermTypes/BaseTermData.hpp>
#include <Algebra/Term/TermTypes/Constant.hpp>
#include <Algebra/Term/TermTypes/Expression.hpp>
#include <Algebra/Term/TermTypes/Function.hpp>
#include <Algebra/Term/TermTypes/Monomial.hpp>
#include <Algebra/Term/TermTypes/Operator.hpp>
#include <Algebra/Term/TermTypes/Polynomial.hpp>
#include <Algebra/Term/TermTypes/TermType.hpp>
#include <Algebra/Term/TermTypes/Variable.hpp>
#include <Math/Number/AlbaNumber.hpp>

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
    explicit Term(int const signedValue);
    explicit Term(unsigned int const unsignedValue);
    explicit Term(double const doubleValue);
    Term(std::string const& stringTerm);
    Term(Constant const& constant);
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
    bool isSimplified() const;

    TermType getTermType() const;
    Constant const& getConstantConstReference() const;
    Variable const& getVariableConstReference() const;
    Operator const& getOperatorConstReference() const;
    Monomial const& getMonomialConstReference() const;
    Polynomial const& getPolynomialConstReference() const;
    Expression const& getExpressionConstReference() const;
    Function const& getFunctionConstReference() const;
    AlbaNumber const& getConstantValueConstReference() const;
    std::string getDisplayableString() const override;
    std::string getDebugString() const override;

    Constant & getConstantReference();
    Variable & getVariableReference();
    Operator & getOperatorReference();
    Monomial & getMonomialReference();
    Polynomial & getPolynomialReference();
    Expression & getExpressionReference();
    Function & getFunctionReference();

    void clear();
    void simplify();
    void sort();

    void setAsSimplified();
    void clearSimplifiedFlag();
    void clearAllInnerSimplifiedFlags();

private:
    void resetBaseDataTermPointerBasedFromTerm(Term const& term);
    TermType m_type;
    bool m_isSimplified;
    std::unique_ptr<BaseTermData> m_baseDataTermPointer;
};

using Terms = std::vector<Term>;

std::ostream & operator<<(std::ostream & out, Term const& term);

}

}
