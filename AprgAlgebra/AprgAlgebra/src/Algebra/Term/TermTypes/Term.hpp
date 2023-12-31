#pragma once

#include <Algebra/Term/TermTypes/BaseTermData.hpp>
#include <Algebra/Term/TermTypes/BaseTermPointers.hpp>
#include <Algebra/Term/TermTypes/Constant.hpp>
#include <Algebra/Term/TermTypes/Expression.hpp>
#include <Algebra/Term/TermTypes/Function.hpp>
#include <Algebra/Term/TermTypes/Monomial.hpp>
#include <Algebra/Term/TermTypes/Operator.hpp>
#include <Algebra/Term/TermTypes/Polynomial.hpp>
#include <Algebra/Term/TermTypes/TermType.hpp>
#include <Algebra/Term/TermTypes/Variable.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>

#include <memory>
#include <string>
#include <vector>

namespace alba {

namespace algebra {

class Term : public BaseTerm {
public:
    using BaseTermDataPointer = std::unique_ptr<BaseTermData>;

    Term();
    Term(TermType const type, bool const isSimplified, BaseTermDataPointer&& m_baseTermDataPointer);  // for move
    Term(AlbaNumber const& number);
    Term(char const* const characterString);
    Term(std::string const& stringAsParameter);
    Term(Constant const& constant);
    Term(Variable const& variable);
    Term(Operator const& operatorTerm);
    Term(Monomial const& monomial);
    Term(Polynomial const& polynomial);
    Term(Expression const& expression);
    Term(Function const& function);

    // enabled via a type template parameter
    template <typename ArithmeticType, typename = std::enable_if_t<typeHelper::isArithmeticType<ArithmeticType>()>>
    Term(ArithmeticType const value) : Term(AlbaNumber(value)) {}

    // rule of five or six
    ~Term() = default;
    Term(Term const& term);
    Term& operator=(Term const& term);
    Term(Term&& term) = default;
    Term& operator=(Term&& term) = default;

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
    Constant const& getAsConstant() const;
    Variable const& getAsVariable() const;
    Operator const& getAsOperator() const;
    Monomial const& getAsMonomial() const;
    Polynomial const& getAsPolynomial() const;
    Expression const& getAsExpression() const;
    Function const& getAsFunction() const;
    AlbaNumber const& getAsNumber() const;
    std::string getDebugString() const;

    Constant& getAsConstantReference();
    Variable& getAsVariableReference();
    Operator& getAsOperatorReference();
    Monomial& getAsMonomialReference();
    Polynomial& getAsPolynomialReference();
    Expression& getAsExpressionReference();
    Function& getAsFunctionReference();

    BaseTermUniquePointer createBasePointerByMove();

    void clear();
    void simplify();
    void sort();

    void setAsSimplified();
    void clearSimplifiedFlag();
    void clearAllInnerSimplifiedFlags();

private:
    BaseTermDataPointer createANewDataPointerFrom(Term const& term);
    void initializeBasedOnString(std::string const& stringAsParameter);

    friend std::ostream& operator<<(std::ostream& out, Term const& term);

    TermType m_type;
    bool m_isSimplified;
    BaseTermDataPointer m_baseTermDataPointer;
};

using Terms = std::vector<Term>;

}  // namespace algebra

}  // namespace alba
